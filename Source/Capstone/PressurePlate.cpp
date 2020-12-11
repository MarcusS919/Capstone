// Fill out your copyright notice in the Description page of Project Settings.


#include "PressurePlate.h"

// Sets default values
APressurePlate::APressurePlate()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;

	root = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	RootComponent = root;
	
	collider = CreateDefaultSubobject<UBoxComponent>(TEXT("TouchSphereCollider"));
	collider->SetGenerateOverlapEvents(true);
	collider->SetupAttachment(root);

	collider->OnComponentBeginOverlap.AddDynamic(this, &APressurePlate::BeginOverlap);
	collider->OnComponentEndOverlap.AddDynamic(this, &APressurePlate::EndOverlap);

}

// Called when the game starts or when spawned
void APressurePlate::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APressurePlate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APressurePlate::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ACharacter* const Character = Cast<ACharacter>(OtherActor);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, FString::Printf(TEXT("pressure plate overlap")));
	if (Character != nullptr) {
		door->OpenDoor();
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, FString::Printf(TEXT("pressure plate overlap")));
	}
}

void APressurePlate::EndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ACharacter* const Character = Cast<ACharacter>(OtherActor);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, FString::Printf(TEXT("pressure plate end overlap")));
	if (Character != nullptr) {
		door->CloseDoor();
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, FString::Printf(TEXT("pressure plate end overlap")));
	}
}
