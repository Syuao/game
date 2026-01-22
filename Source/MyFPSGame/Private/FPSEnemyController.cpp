#include "FPSEnemyController.h"
#include "FPSEnemyCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"

void AFPSEnemyController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);
    ControlledEnemy = Cast<AFPSEnemyCharacter>(InPawn);
}

void AFPSEnemyController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (ControlledEnemy)
    {
        AActor* Target = GetClosestPlayer();
        
        if (Target)
        {
            MoveToActor(Target, 50.0f); 

            float Dist = FVector::Dist(ControlledEnemy->GetActorLocation(), Target->GetActorLocation());
            if (Dist <= ControlledEnemy->AttackRange)
            {
                ControlledEnemy->Attack();
            }
        }
    }
}

AActor* AFPSEnemyController::GetClosestPlayer()
{
    TArray<AActor*> Players;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACharacter::StaticClass(), Players);
    
    AActor* Closest = nullptr;
    float MinDist = FLT_MAX;
    
    for (AActor* Actor : Players)
    {
        if (Actor == ControlledEnemy) continue;
        if (Actor->IsA(AFPSEnemyCharacter::StaticClass())) continue; // Ignore other enemies
        
        float Dist = FVector::Dist(ControlledEnemy->GetActorLocation(), Actor->GetActorLocation());
        if (Dist < MinDist)
        {
            MinDist = Dist;
            Closest = Actor;
        }
    }
    return Closest;
}