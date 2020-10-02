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
		RangeFollow(targetVector, thisVector);
	}
	else
	{
		MeleeFollow(targetVector, thisVector);
	}
}

void AAiActor::MeleeFollow(FVector targetVector_, FVector thisVector_) {
	SetActorLocation(FMath::Lerp(thisVector_, targetVector_, 0.01), true);
}

void AAiActor::RangeFollow(FVector targetVector_, FVector thisVector_) {
	SetActorLocation(FMath::Lerp(thisVector_, targetVector_, 0.01), true);
}