// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DrawDebugHelpers.h"
#include "PFGrid.generated.h"

UCLASS()
class CAPSTONE_API APFGrid : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APFGrid();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid Info")
		FVector gridWorldSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid Info")
		float nodeRadius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid Info")
		float gridThickness;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
