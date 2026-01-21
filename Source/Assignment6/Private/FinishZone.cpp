#include "FinishZone.h"
#include "Components/SphereComponent.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"

AFinishZone::AFinishZone()
{
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	Collision->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	Collision->SetupAttachment(SceneRoot);

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComp->SetupAttachment(SceneRoot);

}

void AFinishZone::BeginPlay()
{
	Super::BeginPlay();
    Collision->OnComponentBeginOverlap.AddDynamic(this, &AFinishZone::OnOverlap);
}

void AFinishZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFinishZone::OnOverlap(
    UPrimitiveComponent* OverlappedComponent,
    AActor* OtherActor,
    UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex,
    bool bFromSweep,
    const FHitResult& SweepResult)
{
    if (!OtherActor) return;
    // 피니시존에 닿으면 HUD출력
    if (HUDWidgetClass)
    {
        APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
        if (PlayerController)
        {
            UUserWidget* HUDWidget = CreateWidget<UUserWidget>(PlayerController, HUDWidgetClass);
            if (HUDWidget)
            {
                HUDWidget->AddToViewport();
            }

            PlayerController->SetIgnoreMoveInput(true);
            PlayerController->SetIgnoreLookInput(true);
            PlayerController->bShowMouseCursor = true;

            // 2초후 게임 꺼지게
            GetWorld()->GetTimerManager().SetTimer(
                QuitTimerHandle,
                this,
                &AFinishZone::QuitGameDelayed,
                2.0f,
                false // 반복없게끔 
            );
        }
    }
}

void AFinishZone::QuitGameDelayed()
{
    APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
    UKismetSystemLibrary::QuitGame(this, PlayerController, EQuitPreference::Quit, false);
}