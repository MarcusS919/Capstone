// Fill out your copyright notice in the Description page of Project Settings.


#include "ObstacleMesh.h"

// Sets default values
AObstacleMesh::AObstacleMesh()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AObstacleMesh::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AObstacleMesh::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

