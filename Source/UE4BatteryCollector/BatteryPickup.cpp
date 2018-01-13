//-----------------------------------------------------------------------------------
// 电池拾起物体actor类 ABatteryPickup
// Create by QianMo. 2018/1/13
//-----------------------------------------------------------------------------------

#include "UE4BatteryCollector.h"
#include "BatteryPickup.h"


//set default values
ABatteryPickup::ABatteryPickup( )
{
	GetMesh( )->SetSimulatePhysics(true);

	//the base power level of the battery
	BatteryPower = 150.0f;
}

void ABatteryPickup::WasCollected_Implementation( )
{
	//Use the base pickup behavior
	Super::WasCollected_Implementation( );

	//Destroy the battery
	Destroy( );
}

float ABatteryPickup::GetPower( )
{
	return BatteryPower;
}
