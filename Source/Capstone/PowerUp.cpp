// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerUp.h"

// Sets default values
APowerUp::APowerUp()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	RootComponent = Root;

	Collider = CreateDefaultSubobject<USphereComponent>(TEXT("TouchSphereCollider"));
	Collider->SetSphereRadius(20.f, false);
	Collider->SetGenerateOverlapEvents(true);
	Collider->SetupAttachment(Root);

	Collider->OnComponentBeginOverlap.AddDynamic(this, &APowerUp::OnCollect);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PowerUpMesh"));
	Mesh->SetupAttachment(Root);

}

// Called when the game starts or when spawned
void APowerUp::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void APowerUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FRotator NewRotation = FRotator(PitchValue, YawValue, RollValue);

	FQuat QuatRotation = FQuat(NewRotation);
	AddActorLocalRotation(QuatRotation, false, 0, ETeleportType::None);

}


void APowerUp::OnCollect(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ACharacter* const Character = Cast<ACharacter>(OtherActor);
	UCapsuleComponent* const Component = Cast<UCapsuleComponent>(OtherComp);

	//if the colliding object is not a PowerUp (collect)
	if (Character && Component)
	{
		Destroy();
	}
}


