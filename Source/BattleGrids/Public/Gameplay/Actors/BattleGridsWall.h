// © 2021, Matthew Barham. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BattleGridsWall.generated.h"

UCLASS()
class BATTLEGRIDS_API ABattleGridsWall : public AActor
{
	GENERATED_BODY()
	
public:	
	ABattleGridsWall();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;
};
