// Fill out your copyright notice in the Description page of Project Settings.


#include "PFGrid.h"

// Sets default values
APFGrid::APFGrid()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APFGrid::BeginPlay()
{
	Super::BeginPlay();
	DrawDebugBox(GetWorld(), this->GetActorLocation(), gridWorldSize, FColor::Blue, true, -1, 0, gridThickness);
}

// Called every frame
void APFGrid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

