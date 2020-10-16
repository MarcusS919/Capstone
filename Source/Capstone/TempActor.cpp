// Fill out your copyright notice in the Description page of Project Settings.


#include "TempActor.h"

// Sets default values
ATempActor::ATempActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Replication
	SetRemoteRoleForBackwardsCompat(ROLE_SimulatedProxy);
	bReplicates = true;
	bReplicateMovement = true;
}

// Called when the game starts or when spawned
void ATempActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATempActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ActorLocation = GetActorLocation();
	ActorLocation.X += 10.0f;
	SetActorLocation(ActorLocation, true);
}

