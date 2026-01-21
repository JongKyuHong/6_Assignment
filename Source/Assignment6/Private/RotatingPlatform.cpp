#include "RotatingPlatform.h"

ARotatingPlatform::ARotatingPlatform()
{
    PrimaryActorTick.bCanEverTick = true;
    RotationSpeed = 90.0f;
    TimerDelay = 2.0f;
}

void ARotatingPlatform::BeginPlay()
{
    Super::BeginPlay();

    // 사라지는 발판 토글
    if (bVisibleToggle) {
        // 처음에 TimerDelay만큼 지연이 되어서 바로 한번 실행
        ToggleVisibility();
        GetWorld()->GetTimerManager().SetTimer(
            TimerHandle,
            this,
            &ARotatingPlatform::ToggleVisibility,
            TimerDelay,
            true  // 반복
        );
    }
}

void ARotatingPlatform::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (!FMath::IsNearlyZero(RotationSpeed))
    {
        AddActorLocalRotation(FRotator(0.0f, RotationSpeed * DeltaTime, 0.0f));
    }
}

void ARotatingPlatform::ToggleVisibility()
{
    bIsVisible = !bIsVisible;

    SetActorHiddenInGame(!bIsVisible);
    SetActorEnableCollision(bIsVisible);
}