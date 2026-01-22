#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "FPSEnemyController.generated.h"

UCLASS()
class AFPSEnemyController : public AAIController
{
	GENERATED_BODY()
    
public:
    virtual void Tick(float DeltaTime) override;
    
protected:
    virtual void OnPossess(APawn* InPawn) override;

private:
    class AFPSEnemyCharacter* ControlledEnemy;
    AActor* GetClosestPlayer();
};