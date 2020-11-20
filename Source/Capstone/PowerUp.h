// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Character.h"
#include "PowerUp.generated.h"

UCLASS()
class CAPSTONE_API APowerUp : public AActor
{

	GENERATED_BODY()

		UPROPERTY(EditAnywhere, Category = Powerup)
		USceneComponent * Root;

	UPROPERTY(EditAnywhere, Category = Powerup)
		USphereComponent * Collider;

	UPROPERTY(EditAnywhere, Category = Powerup)
		UStaticMeshComponent * Mesh;

	UPROPERTY(EditAnywhere, Category = Powerup)
		float PitchValue;

	UPROPERTY(EditAnywhere, Category = Powerup)
		float YawValue;

	UPROPERTY(EditAnywhere, Category = Powerup)
		float RollValue;


public:
	// Sets default values for this actor's properties
	APowerUp();
	UFUNCTION(BlueprintCallable, Category = "Powerup")
		void OnCollect(class UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
