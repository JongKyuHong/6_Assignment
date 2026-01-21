#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BasePlatform.generated.h"

UCLASS()
class ASSIGNMENT6_API ABasePlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	ABasePlatform();

protected:
	virtual void BeginPlay() override;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BasePlatform|Components")
	USceneComponent* SceneRoot;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BasePlatform|Components")
	UStaticMeshComponent* StaticMeshComp;

public:	
	virtual void Tick(float DeltaTime) override;

};
