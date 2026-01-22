#include "MyFPSGameMode.h"
#include "MyFPSCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "GameFramework/PlayerState.h"

AMyFPSGameMode::AMyFPSGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	// Note: This path assumes the user creates a BP named BP_FirstPersonCharacter in that location. 
    // If not, they can set it in the Editor.
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	if (PlayerPawnClassFinder.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnClassFinder.Class;
	}

    ScoreToWin = 5;
}

void AMyFPSGameMode::EnemyKilled(AController* KillerController)
{
    if (KillerController && KillerController->PlayerState)
    {
        float NewScore = KillerController->PlayerState->GetScore() + 1.0f;
        KillerController->PlayerState->SetScore(NewScore);
        
        if (NewScore >= ScoreToWin)
        {
            // Simple Win: Restart Game
            RestartGame();
        }
    }
}