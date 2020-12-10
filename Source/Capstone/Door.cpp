// Fill out your copyright notice in the Description page of Project Settings.


#include "Door.h"

// Sets default values
ADoor::ADoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
	Super::BeginPlay();
	originVec = GetActorLocation();
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, FString::Printf(TEXT("open vec: %f, %f, %f"), openVec.X, openVec.Y, openVec.Z));
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, FString::Printf(TEXT("origin vec: %f, %f, %f"), originVec.X, originVec.Y, originVec.Z));
}

// Called every frame
void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADoor::OpenDoor() {

	FVector temp = originVec + openVec;
	this->SetActorLocation(temp);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, FString::Printf(TEXT("Door opened new vec: %f, %f, %f"), temp.X, temp.Y, temp.Z));
}

void ADoor::CloseDoor() {

	this->SetActorLocation(originVec);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, FString::Printf(TEXT("Door closed new vec: %f, %f, %f"), originVec.X, originVec.Y, originVec.Z));
}