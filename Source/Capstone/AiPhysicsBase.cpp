// Fill out your copyright notice in the Description page of Project Settings.


#include "AiPhysicsBase.h"

// Sets default values
AAiPhysicsBase::AAiPhysicsBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
}

// Called when the game starts or when spawned
void AAiPhysicsBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAiPhysicsBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FVector Seek(FVector characterPos_, FVector targetPos_, float maxSpeed_, float DeltaTime) {
	float resultVelocity;
	FVector resultPos = characterPos_;

	FVector velocity = targetPos_ - characterPos_;
	resultVelocity = velocity.Size();
	resultVelocity *= maxSpeed_;

	resultPos.X += resultVelocity * DeltaTime;
	resultPos.Y += resultVelocity * DeltaTime;
	return resultPos;
}