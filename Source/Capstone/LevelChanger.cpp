// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelChanger.h"
#include "CapstoneCharacter.h"

// Sets default values
ALevelChanger::ALevelChanger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ALevelChanger::BeginPlay()
{
	Super::BeginPlay();
	OnActorBeginOverlap.AddDynamic(this, &ALevelChanger::OnOverlap);
}

// Called every frame
void ALevelChanger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALevelChanger::OnOverlap(AActor* MyOverlappedActor, AActor* OtherActor)
{
	if (OtherActor != nullptr && OtherActor != this)
	{
		class ACapstoneCharacter* MyCharacter = Cast<ACapstoneCharacter>(OtherActor);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, FString::Printf(TEXT("GameOver")));
		if (MyCharacter)
		{
			FName levelName = FName(*levelString);
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, FString::Printf(TEXT("loading new level")));
			UGameplayStatics::OpenLevel(GetWorld(), levelName);
		}
		
	}
}
