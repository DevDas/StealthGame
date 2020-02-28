// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "FPSGameMode.h"
#include "FPSHUD.h"
#include "FPSCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet\GameplayStatics.h"

AFPSGameMode::AFPSGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Blueprints/BP_Player"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AFPSHUD::StaticClass();
}

void AFPSGameMode::CompleteMission(APawn* InstigatorPawn)
{
	if (InstigatorPawn)
	{
		InstigatorPawn->DisableInput(nullptr);

		if (!SpectatingViewPointClass) { UE_LOG(LogTemp, Warning, TEXT("Spectating Class Not Found!!!")) }

		TArray<AActor*> ReturnedActors; // GetAllActorsOfClass will fill ReturnedActors if he find Any Actor
		UGameplayStatics::GetAllActorsOfClass(this, SpectatingViewPointClass, ReturnedActors);
		
		// Change ViewTarget if Any Valid Actor Found
		if (ReturnedActors.Num() > 0)
		{
			AActor* NewViewTarget = ReturnedActors[0];
			APlayerController* PlayerController = Cast<APlayerController>(InstigatorPawn->GetController());
			if (PlayerController)
			{
				PlayerController->SetViewTargetWithBlend(NewViewTarget, 1.f, EViewTargetBlendFunction::VTBlend_Cubic);
			}
		}
	}
	OnMissionCompleted(InstigatorPawn); // Just Calling It From BP to Show A Widget
}