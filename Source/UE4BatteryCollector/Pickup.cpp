//-----------------------------------------------------------------------------------
// 拾起物体actor类 APickup
// Create by QianMo. 2018/1/13
//-----------------------------------------------------------------------------------

#include "UE4BatteryCollector.h"
#include "Pickup.h"


// Sets default values
APickup::APickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// All pickups start active
	bIsActive = true;

	//Create the static mesh component 
	PickupMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickupMesh"));
	RootComponent = PickupMesh;
}

// Called when the game starts or when spawned
void APickup::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//Returns active state
bool APickup::IsActive( )
{
	return bIsActive;
}

//change active state
void APickup::SetActive(bool NewPickupState)
{
	bIsActive = NewPickupState;
}

void APickup::WasCollected_Implementation( )
{
	//log a debug message
	FString PickupDebugString = GetName( );
	UE_LOG(LogClass, Log, TEXT("YOU have collected %s"), *PickupDebugString);


}

