// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyGameMode.h"

#include "GameFramework/GameStateBase.h"

void ALobbyGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	int32 NumberOfPlayers = GameState.Get()->PlayerArray.Num();
	if(NumberOfPlayers == 2)
	{
		if(const TObjectPtr<UWorld> World = GetWorld())
		{
			bUseSeamlessTravel = true;
			FTimerHandle LoadLevelTimer;
			GetWorldTimerManager().SetTimer(LoadLevelTimer, this, &ThisClass::LoadLevel, 5.f);			
		}
	}
}

void ALobbyGameMode::LoadLevel()
{
	if(const TObjectPtr<UWorld> World = GetWorld())
	{
		World->ServerTravel(FString("/Game/Maps/BlasterMap?listen"));
	}
}
