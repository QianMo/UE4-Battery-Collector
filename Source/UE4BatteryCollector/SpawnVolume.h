//-----------------------------------------------------------------------------------
// 物体生成类 ASpawnVolume
// Create by QianMo. 2018/1/13
//-----------------------------------------------------------------------------------

#pragma once

#include "GameFramework/Actor.h"
#include "SpawnVolume.generated.h"

UCLASS()
class UE4BATTERYCOLLECTOR_API ASpawnVolume : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnVolume();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Returns the WhereToSpawn subobject 
	FORCEINLINE class UBoxComponent* GetWhereToSpawn( ) const { return WhereToSpawn; }

	UFUNCTION(BlueprintPure,Category ="Spawning")
	FVector GetRandomPointInVolume( );

protected:
	//the pickup to spawn
	UPROPERTY(EditAnywhere , Category = "Spawning")
	TSubclassOf<class APickup> WhatToSpawn;

	FTimerHandle SpawnTimer;

	//Minimum spawn delay
	UPROPERTY(EditAnywhere, BlueprintReadWrite ,Category = "Spawning")
	float SpawnDelayRangeLow;

	//Maxium spawn delay
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	float SpawnDelayRangeHigh;


private:
	UPROPERTY(VisibleAnyWhere,BlueprintReadOnly, Category = "Spawning" , meta =( AllowPrivateAccess= "true"))
	class UBoxComponent* WhereToSpawn;
	
	//Handle spawning a new pickup
	void SpawnPickup( );

	//the current spawn delay
	float SpawnDelay;
};
