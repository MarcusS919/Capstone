// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CapstoneCharacter.h"
#include "EnemyRangeAttack.generated.h"

UCLASS()
class CAPSTONE_API AEnemyRangeAttack : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemyRangeAttack();
	FVector ActorLocation;
	FVector PlayerLocation;
	FVector Direction;
	FVector destPos;
	FVector destPos_;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UPROPERTY(EditAnywhere)ACapstoneCharacter* Player;
	UFUNCTION()
		void OnOverlap(AActor* MyOverlappedActor, AActor* OtherActor);
	UFUNCTION()
		void ShootingAtPlayer(AActor* MyOverlappedActor);


	float t = 100;
};
