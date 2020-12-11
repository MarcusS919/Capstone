// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "Components/PointLightComponent.h"
#include "ProxiLight.generated.h"

UCLASS()
class PROXIMITYLIGHT_API AProxiLight : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProxiLight();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light Info")
		float startIntensity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light Info")
		float endIntensity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light Info")
		USceneComponent * Root;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light Info")
		USphereComponent * collider;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light Info")
		UPointLightComponent * light;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "CollisionEvents")
		void BeginOverlap(class UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION(BlueprintCallable, Category = "CollisionEvents")
		void EndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
