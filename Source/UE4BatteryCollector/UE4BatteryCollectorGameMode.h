// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/GameModeBase.h"
#include "UE4BatteryCollectorGameMode.generated.h"

//enum to store the current state of gameplay

UENUM(BlueprintType)
enum class EBatteryPlayState : uint8
{
	EPlaying,
	EGameOver,
	EWon,
	EUnknown
};



UCLASS(minimalapi)
class AUE4BatteryCollectorGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AUE4BatteryCollectorGameMode();

	virtual void Tick(float DeltaTime) override;

	/*Returns power needed to win - need for the HUD*/
	UFUNCTION(BlueprintPure, Category = "Power")
	float GetPowerToWin( ) const;

	virtual void BeginPlay( ) override;

	/* Returns the current playing state */
	UFUNCTION(BlueprintPure, Category = "Power")
	EBatteryPlayState GetCurrntState( ) const;

	/* Sets a new playing state */
	UFUNCTION(BlueprintPure, Category = "Power")
	EBatteryPlayState SetCurrentState(EBatteryPlayState newState);

protected:
	/* The rate at which the character loses power */
	UPROPERTY(EditDefaultsOnly , BlueprintReadWrite, Category = "Power", Meta = (BlueprintProctected = "ture"))
	float DecayRate;

	/*the power needed to win the game*/
	UPROPERTY(EditDefaultsOnly ,BlueprintReadWrite, Category = "Power" ,Meta = (BlueprintProctected = "ture"))
	float PowerToWin;

	/*the widget class to use for our HUD screen*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Power", Meta = (BlueprintProctected = "ture"))
	TSubclassOf<class UUserWidget> HUDWidgetClass;

	/* The instance of the HUD */
	UPROPERTY()
	class UUserWidget* CurrentWidget;

private: 
	/*Keeps track of the current playing state*/
	EBatteryPlayState CurrentState;

	TArray<class ASpawnVolume*> SpawnVolumeActors;

};



