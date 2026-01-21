#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FinishZone.generated.h"

class USphereComponent;

UCLASS()
class ASSIGNMENT6_API AFinishZone : public AActor
{
	GENERATED_BODY()
	
public:	
	AFinishZone();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "FinishZone|Components")
	USceneComponent* SceneRoot;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "FinishZone|Components")
	UStaticMeshComponent* StaticMeshComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "FinishZone|Components")
	USphereComponent* Collision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> HUDWidgetClass;

	UFUNCTION()
	void OnOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);

	FTimerHandle QuitTimerHandle;

	UFUNCTION()
	void QuitGameDelayed();
public:	
	virtual void Tick(float DeltaTime) override;

};
