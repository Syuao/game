#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MyFPSGameMode.generated.h"

UCLASS(minimalapi)
class AMyFPSGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AMyFPSGameMode();

    void EnemyKilled(AController* KillerController);

protected:
    UPROPERTY(EditDefaultsOnly, Category="Rules")
    int32 ScoreToWin;
};