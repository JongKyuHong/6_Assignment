#pragma once

#include "CoreMinimal.h"
#include "BasePlatform.h"
#include "RotatingPlatform.generated.h"


UCLASS()
class ASSIGNMENT6_API ARotatingPlatform : public ABasePlatform
{
	GENERATED_BODY()
public:
	ARotatingPlatform();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	// true면 TimerDelay마다 사라졌다 나타났다 반복
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visible")
	bool bVisibleToggle = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visible")
	float TimerDelay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rotate")
	float RotationSpeed;

	UFUNCTION()
	void ToggleVisibility();

	FTimerHandle TimerHandle;
	bool bIsVisible;
};
