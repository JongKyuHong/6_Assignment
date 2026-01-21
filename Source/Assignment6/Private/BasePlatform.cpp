#include "BasePlatform.h"

ABasePlatform::ABasePlatform()
{
	PrimaryActorTick.bCanEverTick = false;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComp->SetupAttachment(SceneRoot);
}

void ABasePlatform::BeginPlay()
{
	Super::BeginPlay();
}

void ABasePlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

