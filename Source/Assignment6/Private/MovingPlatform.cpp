#include "MovingPlatform.h"

AMovingPlatform::AMovingPlatform()
{
    PrimaryActorTick.bCanEverTick = true;
    MoveSpeed = 200.0f;
    IsStartLeft = true;
    TimerDelay = 2.0f;
    bUseTeleportMode = false;
}

void AMovingPlatform::BeginPlay()
{
    Super::BeginPlay();

    StartLocation = GetActorLocation();
    MaxRange = StartLocation.X + 600.0f;

    if (IsStartLeft) {
        MoveDirection = -1.0f;
    } else {
        MoveDirection = 1.0f;
    }

    // 텔레포트 모드일 경우 타이머 시스템 활용 
    if (bUseTeleportMode) {
        // tick대신 타이머 시스템 쓰므로 false
        PrimaryActorTick.bCanEverTick = false;
        GetWorld()->GetTimerManager().SetTimer(
            TeleportTimerHandle,
            this,
            &AMovingPlatform::TeleportToRandom,
            TimerDelay,
            true
        );
    }
}

void AMovingPlatform::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // 텔레포트 모드면 바로 return
    if (bUseTeleportMode) return;

    if (!FMath::IsNearlyZero(MoveSpeed))
    {
        // MaxRange보다 커지면 방향을 바꿈
        if (FMath::Abs(StartLocation.X - GetActorLocation().X) > MaxRange) {
            MoveDirection *= -1;
        }
        AddActorLocalOffset(FVector(MoveSpeed * MoveDirection * DeltaTime, 0.0f, 0.0f));
    }
}

void AMovingPlatform::TeleportToRandom()
{
    float RandomX = StartLocation.X + FMath::RandRange(-MaxRange, MaxRange);
    FVector RandomLocation(RandomX, StartLocation.Y, StartLocation.Z);

    SetActorLocation(RandomLocation);
}
