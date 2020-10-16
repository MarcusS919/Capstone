// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AiPhysicsBase.generated.h"

UCLASS()
class CAPSTONE_API AAiPhysicsBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAiPhysicsBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FVector Seek(FVector characterPos_, FVector targetPos_, float maxSpeed_, float DeltaTime);

};
