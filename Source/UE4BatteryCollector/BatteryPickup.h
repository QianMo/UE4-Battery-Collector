//-----------------------------------------------------------------------------------
// 电池拾起物体actor类 ABatteryPickup
// Create by QianMo. 2018/1/13
//-----------------------------------------------------------------------------------

#pragma once

#include "Pickup.h"
#include "BatteryPickup.generated.h"

UCLASS()
class UE4BATTERYCOLLECTOR_API ABatteryPickup : public APickup
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	ABatteryPickup( );
	
	/*Override the WasCollected function - use Implementation because it's a Blueprint Native Event*/
	void WasCollected_Implementation( ) override;

	/*Public way to access the battery's  power level */
	float GetPower( );

protected:
	/*Set the amount of power the battery gives to the character */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Power" ,Meta = (BlueprintProtected = "true"))
	float BatteryPower;

};
