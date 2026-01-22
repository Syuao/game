#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FPSEnemyCharacter.generated.h"

UCLASS()
class AFPSEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AFPSEnemyCharacter();

protected:
	virtual void BeginPlay() override;

public:	
    // Health System
    UPROPERTY(Replicated, BlueprintReadOnly, Category = "Health")
    float Health;

    UPROPERTY(EditDefaultsOnly, Category = "Health")
    float MaxHealth;

    // Attack properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
    float AttackRange;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
    float AttackDamage;

    // AI
    virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
    
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

    UFUNCTION(BlueprintCallable, Category = "Combat")
    void Attack();
};