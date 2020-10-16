// Fill out your copyright notice in the Description page of Project Settings.


#include "AiActor.h"

// Sets default values
AAiActor::AAiActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AAiActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAiActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	targetVector = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
	thisVector = this->GetActorLocation();
	
	if (isRanged == true) {
		RangeFollow(targetVector, thisVector, maxSpeed, DeltaTime);
	}
	else
	{
		MeleeFollow(targetVector, thisVector, maxSpeed, DeltaTime);
	}
}

void AAiActor::MeleeFollow(FVector targetVector_, FVector thisVector_, float maxSpeed_, float DeltaTime) {

	FVector resultPos = thisVector_;

	FVector velocity = targetVector_ - thisVector_;

	velocity.Normalize();
	velocity *= maxSpeed_;

	resultPos += (velocity * DeltaTime);

	//SetActorLocation(FMath::Lerp(thisVector_, resultPos, 0.01), true);
	SetActorLocation(resultPos, true);
}

void AAiActor::RangeFollow(FVector targetVector_, FVector thisVector_, float maxSpeed_, float DeltaTime) {

	float temp = (thisVector_ - targetVector_).Size();
	FVector tempVector = targetVector_;
	tempVector.X *= -1.0f;
	tempVector.Y *= -1.0f;

	if (temp < 500.0f) {
		SetActorLocation(FMath::Lerp(thisVector_, targetVector_, 0.01), true);
	}

	if (temp > 500.0f) {
		//SetActorLocation(FMath::Lerp(thisVector_, targetVector_, 0.01), true);
	}

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, FString::Printf(TEXT("Distance: %f"), temp));
}