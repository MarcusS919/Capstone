// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackActor.h"

// Sets default values
AAttackActor::AAttackActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAttackActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAttackActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	ActorLocation = GetActorLocation();
	ActorLocation.X += 10.0f;
	SetActorLocation(ActorLocation, true);
}

