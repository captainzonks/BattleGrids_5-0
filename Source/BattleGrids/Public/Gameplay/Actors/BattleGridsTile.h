// © 2021, Matthew Barham. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BattleGridsTile.generated.h"

UCLASS()
class BATTLEGRIDS_API ABattleGridsTile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABattleGridsTile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USceneComponent> SpawnPoint;
};
