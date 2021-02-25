// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Grid.h"
#include "PathFinding.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PathFinding.generated.h"

UCLASS()
class CAPSTONE_API APathFinding : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APathFinding();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(VisibleAnywhere) UStaticMeshComponent* EnemyMesh;
	UPROPERTY(EditAnywhere) AGrid* MyGrid = nullptr;
	UPROPERTY(EditAnywhere) AActor* Target = nullptr;
	UPROPERTY(EditAnywhere) AActor* PartolPoint1= nullptr;
	UPROPERTY(EditAnywhere) AActor* PartolPoint2 = nullptr;
	UPROPERTY(EditAnywhere) AActor* FleePoint = nullptr;

	UPROPERTY(EditAnywhere) TSubclassOf<AActor> temp;

	UPROPERTY(EditAnywhere) bool isRange;
	UPROPERTY(EditAnywhere) float maxHealth;
	UPROPERTY(EditAnywhere) float health;
	UPROPERTY(EditAnywhere) float healthPercent;
	

	void Patrol();
	void Chase();
	void Attack();
	
	void flee();
	bool isFleeing;
	float speed = 6.0f;
	UFUNCTION()
		void UpdateHealth(float healthChange_);
private:
	TArray<PathFindingNode*> openList;
	TArray<PathFindingNode*> closeList;
	TArray<PathFindingNode*> FinalNodeList;

	void AStarPathFinding();
	void FinishFinding(PathFindingNode* startNode, PathFindingNode* goalNode);

	int ManhattanDistance(const PathFindingNode& current, const PathFindingNode& neighbour);
	bool isPatroling;
	bool atPointOne;
	bool atSafeSpot;
	
	int t = 50;
};
