// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSGameState.h"

#include "EngineUtils.h"
#include "FPSCharacter.h"

void AFPSGameState::MulticastOnMissionComplete_Implementation(APawn* InstigatorPawn, bool bMissionSuccess)
{
	for (TActorIterator<APawn> It(GetWorld()); It; ++It)
	{
		APawn* Pawn = *It;

		if (Pawn && Pawn->IsLocallyControlled())
		{
			Pawn->DisableInput(nullptr);
		}
	}
}
