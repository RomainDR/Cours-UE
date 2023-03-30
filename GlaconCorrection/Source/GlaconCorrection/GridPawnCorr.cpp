
#include "GridPawnCorr.h"
#include "Util.h"
#include "InputUtils.h"
#include "GameModeGridCorr.h"

AGridPawnCorr::AGridPawnCorr()
{
	PrimaryActorTick.bCanEverTick = true;
	mesh = CREATE(UStaticMeshComponent, "mesh");
	mesh->SetStaticMesh(LoadObject<UStaticMesh>(this, TEXT("'/Engine/BasicShapes/Sphere.Sphere'")));
	springArm = CREATE(USpringArmComponent, "springArm");
	camera = CREATE(UCameraComponent, "camera");

	RootComponent = mesh;

	demo = CREATE(UDemoModeComponentCorr, "Demo");
	AddOwnedComponent(demo);

	ATTACH_TO(springArm, RootComponent);
	ATTACH_TO(camera, springArm);
	
}

void AGridPawnCorr::BeginPlay()
{
	Super::BeginPlay();
	InitPawn();
	
}
void AGridPawnCorr::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGridPawnCorr::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	BIND_ACTION_PAWN(UP, IE_Pressed, this, AGridPawnCorr::UpMove);
	BIND_ACTION_PAWN(DOWN, IE_Pressed, this, AGridPawnCorr::DownMove);
	BIND_ACTION_PAWN(LEFT, IE_Pressed, this, AGridPawnCorr::LeftMove);
	BIND_ACTION_PAWN(RIGHT, IE_Pressed, this, AGridPawnCorr::RightMove);
	BIND_ACTION_PAWN(SELECT, IE_Pressed, this, AGridPawnCorr::SelectGridCell);

}

void AGridPawnCorr::InitPawn()
{
	grid = GetGrid();
	if (!grid)
		return;
	grid->SnapToStart(this);
	SelectGridCell();
	if (useDemoMode && demo) {
		demo->StartDemo();
		DisableInput(FPC);
	}
}

TObjectPtr<AGridActorCorr> AGridPawnCorr::GetGrid() const
{
	AGameModeGridCorr* _gm =  GetWorld()->GetAuthGameMode<AGameModeGridCorr>();
	if (!_gm)
		return nullptr;
	return _gm->GetGrid();

}

void AGridPawnCorr::UpMove()
{
	if (!grid) return;
	grid->MoveToCellDirection(this, FVector(1, 0, 0));
}

void AGridPawnCorr::DownMove()
{
	if (!grid) return;
	grid->MoveToCellDirection(this, FVector(-1, 0, 0));
}

void AGridPawnCorr::LeftMove()
{
	if (!grid) return;
	grid->MoveToCellDirection(this, FVector(0, -1, 0));
}

void AGridPawnCorr::RightMove()
{
	if (!grid) return;
	grid->MoveToCellDirection(this, FVector(0, 1, 0));
}

void AGridPawnCorr::SelectGridCell()
{
	if (!grid)  return;
	grid->PickLocation(this);
}
