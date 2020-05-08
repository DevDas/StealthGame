// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "FPSGameState.generated.h"

/**
 * 
 */
UCLASS()
class FPSGAME_API AFPSGameState : public AGameStateBase
{
    GENERATED_BODY()

public:

    // NetMulticast Means If MulticastOnMissionComplete() This Function Called From Server Then It Gets Sent To All Clients including Server
    UFUNCTION(NetMulticast, Reliable)
    void MulticastOnMissionComplete(APawn* InstigatorPawn, bool bMissionSuccess);
};