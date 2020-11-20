// Fill out your copyright notice in the Description page of Project Settings.


#include "PathFinding.h"

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
}

// Called every frame
void APathFinding::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Target != nullptr) {

		AStarPathFinding();

		if (FinalNodeList.Num() > 0) {

			FVector destPos = FinalNodeList[0]->Position;
			FVector currentPos = GetActorLocation();
			destPos.Z = currentPos.Z;

			FVector dir = destPos - currentPos;
			FQuat dirQuat(dir.Rotation());
			FQuat rot = FQuat::Slerp(GetActorQuat(), dirQuat, 5 * DeltaTime);

			SetActorRotation(rot);

			SetActorLocation(GetActorLocation() + (dir.GetSafeNormal() * 3.F));

			if (FVector::Distance(GetActorLocation(), destPos) < 0.001f) {
				AStarPathFinding();
			}
		}
		else {
			// run path finding
		}
	}
}

void APathFinding::AStarPathFinding(){

	PathFindingNode* startNode = MyGrid->WorldToNode(GetActorLocation());
	PathFindingNode* goalNode = MyGrid->WorldToNode(Target->GetActorLocation());

	//UE_LOG(LogTemp, Warning, TEXT("Start Node [%d, %d]"), startNode->arrayX, startNode->arrayY);
	//UE_LOG(LogTemp, Warning, TEXT("Goal Node [%d, %d]"), goalNode->arrayX, goalNode->arrayY);

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

		if (currentNode == goalNode) {
		//	UE_LOG(LogTemp, Warning, TEXT("Found out Node [%d, %d]"), currentNode->arrayX, currentNode->arrayY);
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

	PathFindingNode* indicator = goalNode;

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

