// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Character.h"
#include "Math/UnrealMathVectorCommon.h"
#include "Components/SphereComponent.h"
#include "AiActor.generated.h"

UCLASS()
class CAPSTONE_API AAiActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAiActor();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Type")
		bool isRanged;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void MeleeFollow(FVector targetVector_, FVector thisVector_);

	void RangeFollow(FVector targetVector_, FVector thisVector_);

	//variable to store player's current position
	FVector targetVector;
	FVector thisVector;

};
