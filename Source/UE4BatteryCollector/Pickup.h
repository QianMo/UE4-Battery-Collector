//-----------------------------------------------------------------------------------
// 拾起物体actor类 APickup
// Create by QianMo. 2018/1/13
//-----------------------------------------------------------------------------------

#pragma once

#include "GameFramework/Actor.h"
#include "Pickup.generated.h"

UCLASS()
class UE4BATTERYCOLLECTOR_API APickup : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickup();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Return the mesh for the pickup
	FORCEINLINE class UStaticMeshComponent* GetMesh( ) const { return PickupMesh; }

	//Reture whether or not the pickup is active
	UFUNCTION(BlueprintPure, Category = "Pickup")
	bool IsActive( );

	//Allow other classes to safely change whether or not pickup is active
	UFUNCTION(BlueprintCallable, Category = "Pickup")
	void SetActive(bool NewPickupState);

	//Function to call when the pickup is collected
	UFUNCTION(BlueprintNativeEvent )
	void WasCollected( );
	virtual void WasCollected_Implementation( );

protected:
	//True when the pick up can be used,and false when pickup is deactived
	bool bIsActive;

private: 
	UPROPERTY(VisibleAnyWhere,BlueprintReadOnly,Category ="Pickup",meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* PickupMesh;
	
};
