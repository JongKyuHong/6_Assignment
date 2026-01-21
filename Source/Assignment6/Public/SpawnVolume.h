#pragma once

#include "CoreMinimal.h"
#include "BasePlatform.h"
#include "GameFramework/Actor.h"
#include "SpawnVolume.generated.h"

class UBoxComponent;

UCLASS()
class ASSIGNMENT6_API ASpawnVolume : public AActor
{
	GENERATED_BODY()
	
public:	
	ASpawnVolume();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawning")
	USceneComponent* SceneRoot;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawning")
	UBoxComponent* SpawningBox;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawning")
	TArray<TSubclassOf<ABasePlatform>> PlatformClasses;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	float TimerDelay;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawning")
	TArray<ABasePlatform*> SpawnedPlatforms;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawning")
	int32 SpawnCount;

	FTimerHandle TimerHandle;

	UFUNCTION(BlueprintCallable, Category = "Spawning")
	void SpawnRandomPlatforms();

	FVector GetRandomPointInVolume() const;
protected:
	void BeginPlay();
};
