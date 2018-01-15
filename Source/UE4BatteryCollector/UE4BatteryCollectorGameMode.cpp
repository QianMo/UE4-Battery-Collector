// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "UE4BatteryCollector.h"
#include "UE4BatteryCollectorGameMode.h"
#include "UE4BatteryCollectorCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "SpawnVolume.h"

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
		//If our power is greater than needed to win, set the game's state to won
		if (MyCharacter->GetCurrentPower( )>PowerToWin)
		{
			SetCurrentState(EBatteryPlayState::EWon);
		}

		//If the character's power is positive
		else if (MyCharacter->GetCurrentPower()>0)
		{
			//decrease the character's power using the decay rate
			MyCharacter->UpdatePower(-DeltaTime * DecayRate * (MyCharacter->GetInitialPower( )));
		}

		else
		{
			SetCurrentState(EBatteryPlayState::EGameOver);
		}
	}

}

float AUE4BatteryCollectorGameMode::GetPowerToWin( ) const
{
	return PowerToWin;
}

void AUE4BatteryCollectorGameMode::BeginPlay( )
{
	Super::BeginPlay( );

	SetCurrentState(EBatteryPlayState::EPlaying);

	//set the score to beat
	AUE4BatteryCollectorCharacter* MyCharacter = Cast<AUE4BatteryCollectorCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));
	if (MyCharacter)
	{
		PowerToWin = (MyCharacter->GetInitialPower( ))*1.25f;
	}
	if (HUDWidgetClass != nullptr)
	{
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld( ), HUDWidgetClass);
		if (CurrentWidget != nullptr)
		{
			CurrentWidget->AddToViewport( );
		}
	}

	// find all spawning volume Actors
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld( ), ASpawnVolume::StaticClass( ), FoundActors);

	for (auto Actor : FoundActors)
	{
		ASpawnVolume* SpawnVolumeActor = Cast<ASpawnVolume>(Actor);
		if (SpawnVolumeActor)
		{
			SpawnVolumeActors.AddUnique(SpawnVolumeActor);
		}
	}

}

EBatteryPlayState AUE4BatteryCollectorGameMode::GetCurrntState( ) const
{
	return CurrentState;
}

EBatteryPlayState AUE4BatteryCollectorGameMode::SetCurrentState(EBatteryPlayState newState)
{
	// set current state
	CurrentState = newState;
	// handle the new state
	HandleNewState(CurrentState);

	return CurrentState;
}

void AUE4BatteryCollectorGameMode::HandleNewState(EBatteryPlayState NewState)
{
	switch (NewState)
	{
		// If the game is playing
		case  EBatteryPlayState::EPlaying:
		{
			//spawn volumes active
			for (ASpawnVolume* Volume : SpawnVolumeActors)
			{
				Volume->SetSpawningActive(true);
			}
		}
		break;
		// If we've won the game
		case  EBatteryPlayState::EWon:
		{
			// spawn volums inactive
			for (ASpawnVolume* Volume : SpawnVolumeActors)
			{
				Volume->SetSpawningActive(false);
			}
		}
		break;
		// If we've lost the game
		case  EBatteryPlayState::EGameOver:
		{
			// spawn volums inactives
			for (ASpawnVolume* Volume : SpawnVolumeActors)
			{
				Volume->SetSpawningActive(false);
			}
			// block player input
			APlayerController* PlayController = UGameplayStatics::GetPlayerController(this, 0);
			if (PlayController)
			{
				PlayController->SetCinematicMode(true, false, false, true, true);
			}
			// ragdoll the character
			ACharacter* MyCharacter = UGameplayStatics::GetPlayerCharacter(this, 0);
			if (MyCharacter)
			{
				MyCharacter->GetMesh( )->SetSimulatePhysics(true);
				MyCharacter->GetMovementComponent( )->MovementState.bCanJump = false;
			}
		}
		break;
		//Unkown
		default:
			break;
			// If we've won the game
		case  EBatteryPlayState::EUnknown:
		{
			// do nothing
		}
		break;

	}
}
