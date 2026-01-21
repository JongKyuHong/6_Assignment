#include "SpawnVolume.h"
#include "Components/BoxComponent.h"
#include "RotatingPlatform.h"
#include "MovingPlatform.h"
#include "Kismet/GameplayStatics.h"  

ASpawnVolume::ASpawnVolume()
{
	PrimaryActorTick.bCanEverTick = false;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	SetRootComponent(SceneRoot);

	SpawningBox = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawningBox"));
	SpawningBox->SetupAttachment(SceneRoot);

    SpawnCount = 10;
    TimerDelay = 5.0f;
}

void ASpawnVolume::BeginPlay()
{
	Super::BeginPlay();

    SpawnRandomPlatforms();

    GetWorldTimerManager().SetTimer(
        TimerHandle,
        this,
        &ASpawnVolume::SpawnRandomPlatforms,
        TimerDelay,
        true 
    );
}

void ASpawnVolume::SpawnRandomPlatforms()
{
    for (ABasePlatform* Platform : SpawnedPlatforms)
    {
        if (Platform && Platform->IsValidLowLevel())
        {
            Platform->Destroy();
        }
    }
    SpawnedPlatforms.Empty();

    for (int32 i = 0; i < SpawnCount; ++i)
    {
        int32 RandomIndex = FMath::RandRange(0, PlatformClasses.Num() - 1);
        TSubclassOf<ABasePlatform> SelectedClass = PlatformClasses[RandomIndex];

        if (!SelectedClass) continue;

        FVector SpawnLocation = GetRandomPointInVolume();
        ABasePlatform* SpawnedPlatform = GetWorld()->SpawnActor<ABasePlatform>(
            SelectedClass, SpawnLocation, FRotator::ZeroRotator,
            FActorSpawnParameters()
        );

        if (SpawnedPlatform)
        {
            if (ARotatingPlatform* RotatingPlatform = Cast<ARotatingPlatform>(SpawnedPlatform))
            {
                RotatingPlatform->bVisibleToggle = FMath::RandBool();
                if (RotatingPlatform->bVisibleToggle) {
                    RotatingPlatform->TimerDelay = FMath::RandRange(1.0f, 3.0f);
                }
                RotatingPlatform->RotationSpeed = FMath::RandRange(50.0f, 200.0f);
            }
            else if (AMovingPlatform* MovingPlatform = Cast<AMovingPlatform>(SpawnedPlatform))
            {
                MovingPlatform->bUseTeleportMode = FMath::RandBool();
                if (MovingPlatform->bUseTeleportMode) {
                    MovingPlatform->TimerDelay = FMath::RandRange(1.0f, 3.0f);
                }
                MovingPlatform->MoveSpeed = 200.f;
            }

            SpawnedPlatforms.Add(SpawnedPlatform);
        }
    }
}

FVector ASpawnVolume::GetRandomPointInVolume() const
{
    FVector Origin = SpawningBox->GetComponentLocation();
    FVector BoxExtent = SpawningBox->GetScaledBoxExtent();

    return FVector(
        FMath::RandRange(Origin.X - BoxExtent.X, Origin.X + BoxExtent.X),
        FMath::RandRange(Origin.Y - BoxExtent.Y, Origin.Y + BoxExtent.Y),
        FMath::RandRange(Origin.Z - BoxExtent.Z, Origin.Z + BoxExtent.Z)
    );
}