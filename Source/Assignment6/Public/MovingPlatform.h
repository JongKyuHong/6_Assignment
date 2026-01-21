#pragma once

#include "CoreMinimal.h"
#include "BasePlatform.h"
#include "MovingPlatform.generated.h"

UCLASS()
class ASSIGNMENT6_API AMovingPlatform : public ABasePlatform
{
	GENERATED_BODY()
public:
	AMovingPlatform();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	// 시작 위치
	FVector StartLocation;
	
	// 어디까지 움직일지
	float MaxRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Moving")
	float MoveSpeed;

	// true면 텔레포트, false면 평범하게 좌우로 움직임
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Moving")
	bool bUseTeleportMode;
	
	// 텔레포트 주기
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Moving")
	float TimerDelay;

	// true면 처음에 왼쪽으로 이동
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Moving")
	bool IsStartLeft;


	FTimerHandle TeleportTimerHandle;

	// MaxRange범위에서 랜덤위치로 이동
	UFUNCTION()
	void TeleportToRandom();

	

	float MoveDirection;
};
