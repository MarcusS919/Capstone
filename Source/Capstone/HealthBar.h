// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CapstoneCharacter.h"
#include "HealthBar.generated.h"

/**
 * 
 */
UCLASS( Abstract)
class CAPSTONE_API UHealthBar : public UUserWidget
{
	GENERATED_BODY()
public:
	void SetOwner(ACapstoneCharacter* InPlayer) { Owner = InPlayer; }

protected:
	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	TWeakObjectPtr<ACapstoneCharacter> Owner;
	
	UPROPERTY(meta = (BindWidget))
		class UProgressBar* HealthBar;
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* CurrentHealthLabel;
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* MaxHealthLabel;

};