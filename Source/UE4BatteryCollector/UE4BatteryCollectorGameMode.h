// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/GameModeBase.h"
#include "UE4BatteryCollectorGameMode.generated.h"

UCLASS(minimalapi)
class AUE4BatteryCollectorGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AUE4BatteryCollectorGameMode();

	virtual void Tick(float DeltaTime) override;

protected:
	/* The rate at which the character loses power */
	UPROPERTY(EditDefaultsOnly , BlueprintReadWrite, Category = "Power" )
	float DecayRate;

};



