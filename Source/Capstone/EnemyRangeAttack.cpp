// Fill out your copyright notice in the Description page of Project Settings.

#include "CapstoneCharacter.h"
#include "PathFinding.h"
#include "Engine/Engine.h"
#include "EnemyRangeAttack.h"

// Sets default values
AEnemyRangeAttack::AEnemyRangeAttack()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemyRangeAttack::BeginPlay()
{
	Super::BeginPlay();
	OnActorBeginOverlap.AddDynamic(this, &AEnemyRangeAttack::OnOverlap);
}

// Called every frame
void AEnemyRangeAttack::Tick(float DeltaTime)
{

	Super::Tick(DeltaTime);
	
	ActorLocation = GetActorLocation();
	int speed = 10;
	ActorLocation.X -= speed;
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, FString::Printf(TEXT("health: %f"), destPos.X));
	SetActorLocation(ActorLocation, true);
	//ActorLocation.X += 10;
	/*GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, FString::Printf(TEXT("health: %f"), destPos.X));
	
	FVector currentPos = GetActorLocation();
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, FString::Printf(TEXT("me: %f"), currentPos.X));
	destPos.Z = currentPos.Z;
	Direction = destPos - currentPos;
	FQuat dirQuat(Direction.Rotation());
	FQuat rot = FQuat::Slerp(GetActorQuat(), dirQuat, 5 * DeltaTime);

	SetActorRotation(rot);

	SetActorLocation(GetActorLocation() + (Direction.GetSafeNormal() * 10));*/


	if (t == 0) {
		Destroy();

	}
	else {
		t = t - 1;
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, FString::Printf(TEXT("me: %f"), t));
	}

	//shooting at the player
	ShootingAtPlayer(this);
	
}

void AEnemyRangeAttack::OnOverlap(AActor* MyOverlappedActor, AActor* OtherActor)
{
	
	if (OtherActor != nullptr && OtherActor != this)
	{
		class APathFinding* EnemyCharacter = Cast<APathFinding>(OtherActor);
		
		class ACapstoneCharacter* MyCharacter = Cast<ACapstoneCharacter>(OtherActor);

		if (EnemyCharacter) {
			destPos = EnemyCharacter->destPos;

			//Direction = EnemyCharacter->dir * 1.5f;
			
		}

		if (MyCharacter)
		{
			MyCharacter->UpdateHealth(-10.0f);
			Destroy();
		}
	}
}

void AEnemyRangeAttack::ShootingAtPlayer(AActor* MyOverlappedActor)
{
	

}
