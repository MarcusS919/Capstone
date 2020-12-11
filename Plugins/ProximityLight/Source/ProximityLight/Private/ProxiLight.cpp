// Fill out your copyright notice in the Description page of Project Settings.


#include "ProxiLight.h"

// Sets default values
AProxiLight::AProxiLight()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	RootComponent = Root;

	collider = CreateDefaultSubobject<USphereComponent>(TEXT("Player Detection Collider"));
	collider->SetSphereRadius(20.f, false);
	collider->SetGenerateOverlapEvents(true);
	collider->SetupAttachment(Root);

	collider->OnComponentBeginOverlap.AddDynamic(this, &AProxiLight::BeginOverlap);
	collider->OnComponentEndOverlap.AddDynamic(this, &AProxiLight::EndOverlap);

	startIntensity = 0.0f;
	endIntensity = 10.0f;

	light = CreateDefaultSubobject<UPointLightComponent>(TEXT("Point Light"));
	light->SetupAttachment(Root);

}

// Called when the game starts or when spawned
void AProxiLight::BeginPlay()
{
	Super::BeginPlay();
	
	light->SetIntensity(startIntensity);
}

// Called every frame
void AProxiLight::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProxiLight::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	light->SetIntensity(endIntensity);
}

void AProxiLight::EndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && (OtherActor != this) && OtherComp) {
		light->SetIntensity(startIntensity);
	}

}