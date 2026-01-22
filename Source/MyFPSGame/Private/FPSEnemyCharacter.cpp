#include "FPSEnemyCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Net/UnrealNetwork.h"
#include "Components/CapsuleComponent.h"
#include "Engine/DamageEvents.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/GameModeBase.h"
#include "MyFPSGameMode.h"
#include "FPSEnemyController.h"

AFPSEnemyCharacter::AFPSEnemyCharacter()
{
    MaxHealth = 50.0f;
    Health = MaxHealth;
    AttackRange = 150.0f;
    AttackDamage = 10.0f;

    // AI settings
    AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
    AIControllerClass = AFPSEnemyController::StaticClass();
    
    bReplicates = true;
}

void AFPSEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
}

float AFPSEnemyCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
    float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
    
    if (Health > 0.0f)
    {
        Health -= ActualDamage;
        if (Health <= 0.0f)
        {
            // Notify GameMode to award points
            if (GetWorld())
            {
                AMyFPSGameMode* GM = Cast<AMyFPSGameMode>(GetWorld()->GetAuthGameMode());
                if (GM)
                {
                    GM->EnemyKilled(EventInstigator);
                }
            }
            Destroy();
        }
    }
    return ActualDamage;
}

void AFPSEnemyCharacter::Attack()
{
    // Simple sphere check for players
    FVector Start = GetActorLocation();
    FCollisionShape Sphere = FCollisionShape::MakeSphere(AttackRange);
    TArray<FOverlapResult> Overlaps;
    FCollisionQueryParams Params;
    Params.AddIgnoredActor(this);

    if (GetWorld()->OverlapMultiByChannel(Overlaps, Start, FQuat::Identity, ECC_Pawn, Sphere, Params))
    {
        for (auto& Result : Overlaps)
        {
            AActor* HitActor = Result.GetActor();
            if (HitActor && HitActor->IsA(APawn::StaticClass())) 
            {
                 // Check if it's not another enemy (assuming enemies are same class)
                 if (!HitActor->IsA(AFPSEnemyCharacter::StaticClass()))
                 {
                     FDamageEvent DamageEvent;
                     HitActor->TakeDamage(AttackDamage, DamageEvent, GetController(), this);
                 }
            }
        }
    }
}

void AFPSEnemyCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(AFPSEnemyCharacter, Health);
}