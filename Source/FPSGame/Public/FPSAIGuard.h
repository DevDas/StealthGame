// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FPSAIGuard.generated.h"

// uint8 needed To Expose Blueprint Otherwise Its Not Needed
UENUM(BlueprintType)
enum class EAIState : uint8
{
	Idle,

	Suspicious,

	Alerted
};

UCLASS()
class FPSGAME_API AFPSAIGuard : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFPSAIGuard();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		class UPawnSensingComponent* PawnSensingComp;

	UFUNCTION()
		void OnPawnSeen(APawn* SeenPawn);

	UFUNCTION()
		void OnNoiseHeard(APawn* NoiseInstigator, const FVector& Location, float Volume);

	FRotator OriginalRotation;

	UFUNCTION()
		void ResetOrientation();

	FTimerHandle TimerHandle_ResetOrientation;

	//Replicating Here 
	UPROPERTY(ReplicatedUsing = OnRep_GuardState)
	EAIState GuardState;

	UFUNCTION()
	void OnRep_GuardState(); // On Rep Only Clients

	void SetGuardState(EAIState NewState);
	
	UFUNCTION(BlueprintImplementableEvent, Category = "AI")
	void OnStateChanged(EAIState NewState);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:

	// Let The Guard Go On Patrol
	UPROPERTY(EditInstanceOnly, Category = "AI")
	bool bPatrol;

	// meta = (EditCondition = "bPatrol") Because If U Wanna Assign FirstPatrolPoint  Then bPatrol Always Need To Set True in Editor
	UPROPERTY(EditInstanceOnly, Category = "AI", meta = (EditCondition = "bPatrol"))
	AActor* FirstPatrolPoint;

	UPROPERTY(EditInstanceOnly, Category = "AI", meta = (EditCondition = "bPatrol"))
	AActor* SecondPatrolPoint;

	// The Current point The Actor is Either Moving to or Standing At
	AActor* CurrentPatrolPoint;

	void MoveToNextPatrolPoint();
};