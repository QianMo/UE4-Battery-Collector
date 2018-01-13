// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "UE4BatteryCollector.h"
#include "UE4BatteryCollectorGameMode.h"
#include "UE4BatteryCollectorCharacter.h"
#include "Kismet/GameplayStatics.h"

AUE4BatteryCollectorGameMode::AUE4BatteryCollectorGameMode()
{
	// Set this to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	//base decay rate
	DecayRate = 0.01f;
}

void AUE4BatteryCollectorGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AUE4BatteryCollectorCharacter* MyCharacter = Cast<AUE4BatteryCollectorCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));
	if (MyCharacter)
	{
		if (MyCharacter->GetCurrentPower()>0)
		{
			//decrease the character's power using the decay rate
			MyCharacter->UpdatePower(-DeltaTime * DecayRate * (MyCharacter->GetInitialPower( )));
		}
	}

}