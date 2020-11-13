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

	if ((thisVector_ - targetVector_).Size() > 200.0f) {
		//to allow the NPC to follow player's position using seek
		FVector resultPos = thisVector_;

		FVector velocity = targetVector_ - thisVector_;

		velocity.Normalize();
		velocity *= maxSpeed_;

		resultPos.X += (velocity.X * DeltaTime);
		resultPos.Y += (velocity.Y * DeltaTime);

		SetActorLocation(resultPos, true);
	}

		//make actor look at player

		//FRotator resultAngle;
		//resultAngle = this->GetActorRotation();

		//if (velocity.Size() > 0) {
		//	resultAngle.Yaw += (atan2(-velocity.X, velocity.Z) * DeltaTime);
		//	can dampen angular velocity by a small amount to prevent it from spinning forever 
		//	SetActorRotation(resultAngle, ETeleportType::None);
		//}

		FRotator resultRot;
		resultRot = UKismetMathLibrary::FindLookAtRotation(thisVector_, targetVector_);
		resultRot.Pitch = 0;
		resultRot.Roll = 0;
		SetActorRotation(resultRot, ETeleportType::None);
	
		if ((thisVector_ - targetVector_).Size() <= 200.0f) {
			//insert attack 
				//MeleeAttack();
			//pause seeking for duration of attack before resuming

		}
}

void AAiActor::RangeFollow(FVector targetVector_, FVector thisVector_, float maxSpeed_, float DeltaTime) {

	float temp = (thisVector_ - targetVector_).Size();

	if (temp < 400.0f) {
		FVector resultPos = thisVector_;

		FVector velocity = targetVector_ - thisVector_;

		velocity.Normalize();
		velocity *= maxSpeed_;

		resultPos.X -= (velocity.X * DeltaTime);
		resultPos.Y -= (velocity.Y * DeltaTime);

		SetActorLocation(resultPos, true);
	}

	if (temp > 600.0f) {
		FVector resultPos = thisVector_;

		FVector velocity = targetVector_ - thisVector_;

		velocity.Normalize();
		velocity *= maxSpeed_;

		resultPos.X += (velocity.X * DeltaTime);
		resultPos.Y += (velocity.Y * DeltaTime);

		SetActorLocation(resultPos, true);
	}

	if (temp <600.0f && temp >400.0f) {
		//insert attack
	
		//pause seeking and fleeing for duration of attack
		//can use SetTimer to delay functions
	}


	//make actor look at player

//FRotator resultAngle;
//resultAngle = this->GetActorRotation();

//if (velocity.Size() > 0) {
//	resultAngle.Yaw += (atan2(-velocity.X, velocity.Z) * DeltaTime);
//	SetActorRotation(resultAngle, ETeleportType::None);
//}

	FRotator resultRot;
	resultRot = UKismetMathLibrary::FindLookAtRotation(thisVector_, targetVector_);
	resultRot.Pitch = 0;
	resultRot.Roll = 0;
	SetActorRotation(resultRot, ETeleportType::None);

	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, FString::Printf(TEXT("Distance: %f"), temp));
}