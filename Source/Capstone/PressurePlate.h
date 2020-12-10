// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Character.h"
#include "Components/BoxComponent.h"
#include "Door.h"
#include "PressurePlate.generated.h"

UCLASS()
class CAPSTONE_API APressurePlate : public AActor
{
	GENERATED_BODY()
	

	UPROPERTY(EditAnywhere, Category = Powerup)
		USceneComponent * root;

	UPROPERTY(EditAnywhere, Category = Powerup)
		UBoxComponent * collider;

public:	
	// Sets default values for this actor's properties
	APressurePlate();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Temp)
		ADoor* door;

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
