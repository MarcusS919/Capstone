// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Character.h"
#include "Math/UnrealMathVectorCommon.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/SphereComponent.h"
#include "Components/CapsuleComponent.h"
#include "AiActor.generated.h"

UCLASS()
class CAPSTONE_API AAiActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAiActor();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Info")
		bool isRanged;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Info")
		FVector targetVector;

	//UPROPERTY(Replicated)
	//	FVector targetVecRep;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Info")
		FVector thisVector;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Info")
		float maxSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Info")
		USphereComponent * Collider;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Info")
		bool playerDetected;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void MeleeFollow(FVector targetVector_, FVector thisVector_,float maxSpeed_, float DeltaTime);

	void RangeFollow(FVector targetVector_, FVector thisVector_, float maxSpeed_, float DeltaTime);

	//void GetlifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;

	UFUNCTION(BlueprintCallable, Category = "CollisionEvents")
	void BeginOverlap(class UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION(BlueprintCallable, Category = "CollisionEvents")
		void EndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
