// Fill out your copyright notice in the Description page of Project Settings.


#include "PathFinding.h"
#include "Engine/Engine.h"
// Sets default values
APathFinding::APathFinding()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	EnemyMesh = CreateDefaultSubobject<UStaticMeshComponent>("Enemy");
}

// Called when the game starts or when spawned
void APathFinding::BeginPlay()
{
	Super::BeginPlay();
	
	if (Target != nullptr) {
		//UE_LOG(LogTemp, Log, TEXT("Start Path Finding : %s"), *Target->GetName());
	}
	if (isRange == true) {
		maxHealth = 100.0f;
		health = maxHealth;
		healthPercent = 1.0f;
	}
	else {
		maxHealth = 150.0f;
		health = maxHealth;
		healthPercent = 1.0f;
	}
}

// Called every frame
void APathFinding::Tick(float DeltaTime)
{
	
	Super::Tick(DeltaTime);

	if (Target != nullptr) {

		//AStarPathFinding();

		if (FinalNodeList.Num() > 0) {

			//where the Ai wants to go
			FVector destPos = FinalNodeList[0]->Position;

			//where the Ai is at
			FVector currentPos = GetActorLocation();
			destPos.Z = currentPos.Z;

			
			FVector dir = destPos - currentPos;
			FQuat dirQuat(dir.Rotation());
			FQuat rot = FQuat::Slerp(GetActorQuat(), dirQuat, 5 * DeltaTime);

			SetActorRotation(rot);

			SetActorLocation(GetActorLocation() + (dir.GetSafeNormal() * speed));

			if (FVector::Distance(GetActorLocation(), destPos) < 0.001f) {
				//AStarPathFinding();
			}
		}
		else {
			// run path finding
		}
	}
}

void APathFinding::Patrol(){
	speed = 6.0f;
	isPatroling = true;
	AStarPathFinding();
}

void APathFinding::Chase(){
	isPatroling = false;
	AStarPathFinding();
}

void APathFinding::Attack(){
	if (isRange == true) {
		if (t == 0) {
			AActor* spawnActor = GetWorld()->SpawnActor<AActor>(temp, this->GetActorLocation(), this->GetActorRotation());
			t += 50;
		}
		else {
			t -= 1;
		}
	}
	
}

void APathFinding::flee(){
	isFleeing = true;
	speed = 15.0f;
	AStarPathFinding();
}
//updaating the health when the enemy is hit
void APathFinding::UpdateHealth(float healthChange_)
{
	health = FMath::Clamp(health += healthChange_, 0.0f, maxHealth);
	healthPercent = health / maxHealth;
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, FString::Printf(TEXT("health: %f"), healthPercent));
	if (health <= 0.0f){
		Destroy();
	}
}

void APathFinding::AStarPathFinding(){
	
	PathFindingNode* startNode = MyGrid->WorldToNode(GetActorLocation());
	PathFindingNode* goalNode;

	// picking what goal the ai is going to head for depending on the Ai's state
	if (isPatroling == false && isFleeing == false) {
		goalNode = MyGrid->WorldToNode(Target->GetActorLocation());
	}
	else if(isPatroling == true && atPointOne == false) {
		goalNode = MyGrid->WorldToNode(PartolPoint1->GetActorLocation());
		
	}
	else if (isFleeing == true) {
		goalNode = MyGrid->WorldToNode(FleePoint->GetActorLocation());
	}
	else  {
		goalNode = MyGrid->WorldToNode(PartolPoint2->GetActorLocation());
	
	}
	
	openList.Empty();
	closeList.Empty();

	openList.Add(startNode);
	
	while (openList.Num() > 0) {
		
		PathFindingNode* currentNode = openList[0];

		for (int i = 1; i < openList.Num(); i++) {

			if (openList[i]->GetFCost() < currentNode->GetFCost() || openList[i]->GetGCost() == currentNode->GetFCost() && openList[i]->GetHCost() < currentNode->GetHCost()) {
				currentNode = openList[i];
			}
		}
		openList.Remove(currentNode);
		closeList.Add(currentNode);

		//check to see if the goal the Ai is at is the goal
		if (currentNode == goalNode) {
		
			//if ai is at patrol point one
			if (atPointOne == false) {
				if (startNode == MyGrid->WorldToNode(PartolPoint1->GetActorLocation())){
					atPointOne = true;
				}
			}

			//if ai is at patrol point two
			if (atPointOne == true) {
				if (startNode == MyGrid->WorldToNode(PartolPoint2->GetActorLocation())){
					atPointOne = false;
				}
			}

			//if ai has made it away from the player
			if (startNode == MyGrid->WorldToNode(FleePoint->GetActorLocation())) {
				isFleeing = false;
			}




			FinishFinding(startNode, goalNode);

			for (auto& PathFindingNode : FinalNodeList) {
			//	UE_LOG(LogTemp, Warning, TEXT("The Path is [%d, %d]"), PathFindingNode->arrayX, PathFindingNode->arrayY);
			}
			return;
		}

		for (auto& neighbourNode : MyGrid->GetNeighbours(currentNode)) {
			
			if (!neighbourNode->IsObstacle && !closeList.Contains(neighbourNode)) {
				
				int gCost = currentNode->GetGCost() + ManhattanDistance(*currentNode, *neighbourNode);

				if (!openList.Contains(neighbourNode)) {
					neighbourNode->SetGCost(gCost);

					neighbourNode->SetHCost(ManhattanDistance(*neighbourNode, *goalNode));

					neighbourNode->ParentNode = currentNode;

					if (!openList.Contains(neighbourNode)) {
						openList.Add(neighbourNode);
					}
				}
			}
		}
	}

}

void APathFinding::FinishFinding(PathFindingNode* startNode, PathFindingNode* goalNode){

	TArray<PathFindingNode*> tempPath;

	PathFindingNode *indicator = goalNode;

	while (indicator != startNode) {

		tempPath.Add(indicator);

		indicator = indicator->ParentNode;
		
	}

	Algo::Reverse(tempPath);

		FinalNodeList = tempPath;
		
}

int APathFinding::ManhattanDistance(const PathFindingNode& current, const PathFindingNode& neighbour)
{
	int distance = FMath::Abs((current.arrayX - neighbour.arrayX) * MyGrid->nodeHeight) + FMath::Abs((current.arrayY - neighbour.arrayY) * MyGrid->nodeWidth);
	return distance;
}

