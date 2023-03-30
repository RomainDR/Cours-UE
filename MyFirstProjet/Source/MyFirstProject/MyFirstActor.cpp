
#include "MyFirstActor.h"

#include "Utils.h"

#pragma region UE_CONSTRUCTOR
// Sets default values
AMyFirstActor::AMyFirstActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	RootComponent = mesh;

	mesh->SetStaticMesh(LoadObject<UStaticMesh>(this, TEXT("'/Engine/BasicShapes/Cube.Cube'")));
	mesh->SetMaterial(0, LoadObject<UMaterialInterface>(this, TEXT("'/Engine/BufferVisualization/WorldNormal.WorldNormal'")));

	
}
#pragma endregion UE_CONSTRUCTOR

#pragma region CUSTOMS
void AMyFirstActor::MoveToLocation(const FVector& _target)
{
	originLocation = _target;
	MoveToLocation();
}
void AMyFirstActor::MoveToLocation()
{
	if (!isInstantSpawn)
		return;
	SetActorLocation(GetSpawnLocation());


	//if (!targetSpawn)
	//	return;
	//originLocation = targetSpawn ? targetSpawn->GetActorLocation() : originLocation;


	//LOG_E(CCC, "Debug CCC")

	//LOG("toto %s", *FVector(10).ToString());

	//LOG_W("Warn");
	//LOG_E("Error");
	//LOG_SCREEN(5, COLOR(Blue), "Position: %s", *GetActorLocation().ToString());

	//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, TEXT("Test"));
	//UE_LOG(LogTemp, Warning, TEXT("OriginLocation: %s Actor %s: %s"), 
		//*originLocation.ToString(), *GetName(), *GetActorLocation().ToString());
}

void AMyFirstActor::MoveToLocation_Interp(const float& _speed)
{
	if (!canMove)
		return;
	const FVector _result = FMath::VInterpConstantTo(GetActorLocation(), GetSpawnLocation(), DELTATIME, _speed);
	SetActorLocation(_result);

}

/// <summary>
/// Return the current position of actor
/// </summary>
/// <returns></returns>
FVector AMyFirstActor::GetFromPoint() const
{
	return GetActorLocation();
}

void AMyFirstActor::DrawDebug()
{
	if (!drawDebug)
		return;
	const UWorld* _w = GetWorld();
	FlushDebugStrings(_w);


	DRAW_SPHERE(GetActorLocation(), 100, COLOR(Green), 10);
	DRAW_SPHERE(GetSpawnLocation(), 100, COLOR(Yellow), 2);
	DRAW_BOX(fromLocation, FVector(100), COLOR(Magenta), 2);
	DRAW_LINE(GetSpawnLocation(), fromLocation, COLOR(Red), 2);
	DRAW_LINE(GetSpawnLocation(), GetActorLocation(), COLOR(Red), 2);
	DRAW_TEXT(fromLocation, *fromLocation.ToCompactString(), COLOR(Black), 1.1f);

	/*DrawDebugSphere(_w, fromLocation, 100, 20, FColor::Green);
	//DrawDebugSphere(_w, originLocation, 50, 20, FColor::Yellow);
	DrawDebugLine(_w, originLocation,fromLocation, FColor::Red);
	//DrawDebugSphere(_w, fromLocation, 100, 20, FColor::Magenta);
	DrawDebugBox(_w, fromLocation, FVector(100), FColor::Magenta);
	DrawDebugLine(_w, fromLocation, fromLocation, FColor::Red);*/

	//DrawDebugString(_w, fromLocation, *fromLocation.ToCompactString());
}
#pragma endregion CUSTOMS

#pragma region UE_METHODS
// Called when the game starts or when spawned
void AMyFirstActor::BeginPlay()
{
	Super::BeginPlay();
	if (!isControlledBy)
		return;
	canMove = !isInstantSpawn;
	fromLocation = GetFromPoint();
	MoveToLocation();
}

// Called every frame
void AMyFirstActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MoveToLocation_Interp(speed);
	DrawDebug();
}
#pragma endregion UE_METHODS

