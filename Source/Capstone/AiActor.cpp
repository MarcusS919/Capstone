// Fill out your copyright notice in the Description page of Project Settings.


#include "AiActor.h"
#include "UnrealNetwork.h"

// Sets default values
AAiActor::AAiActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
	bReplicateMovement = true;
	Collider = CreateDefaultSubobject<USphereComponent>(TEXT("PlayerDetectionSphereCollider"));
	Collider->SetSphereRadius(20.f, false);
	Collider->SetGenerateOverlapEvents(true);
	Collider->SetupAttachment(GetRootComponent());

	Collider->OnComponentBeginOverlap.AddDynamic(this, &AAiActor::BeginOverlap);
	Collider->OnComponentEndOverlap.AddDynamic(this, &AAiActor::EndOverlap);

	playerDetected = false;
}

// Called when the game starts or when spawned
void AAiActor::BeginPlay()
{
	Super::BeginPlay();
	
}

//void AAiActor::GetlifetimeReplicatedProps(TArray<FLifetimeProperty> & OutLifetimeProps) const
//{
//	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
//
//	DOREPLIFETIME(AAiActor, targetVecRep);
//}

// Called every frame
void AAiActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//targetVector = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
	////targetVecRep = targetVector;
	//thisVector = this->GetActorLocation();
	//
	//if (isRanged == true) {
	//	RangeFollow(targetVector, thisVector, maxSpeed, DeltaTime);
	//}
	//else
	//{
	//	MeleeFollow(targetVector, thisVector, maxSpeed, DeltaTime);
	//}
	
	if (playerDetected == true) {
		if (isRanged == true) {
			RangeFollow(targetVector, thisVector, maxSpeed, DeltaTime);
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, FString::Printf(TEXT("tagV %f %f %f"), targetVector.X, targetVector.Y, targetVector.Z));

			MeleeFollow(targetVector, thisVector, maxSpeed, DeltaTime);
		}
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

void AAiActor::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ACharacter* const Character = Cast<ACharacter>(OtherActor);
	UCapsuleComponent* const Component = Cast<UCapsuleComponent>(OtherComp);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, FString::Printf(TEXT("PLAYER DETECTED")));

	targetVector = Character->GetActorLocation();
	//targetVecRep = targetVector;
	thisVector = this->GetActorLocation();
	playerDetected = true;
}

void AAiActor::EndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, FString::Printf(TEXT("PLAYER NOT DETECTED")));

	playerDetected = false;
}