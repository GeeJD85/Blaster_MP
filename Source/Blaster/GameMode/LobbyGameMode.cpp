// Copyright Mintcakegames


#include "LobbyGameMode.h"

#include "GameFramework/GameStateBase.h"

void ALobbyGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	int32 NumberOfPlayers = GameState.Get()->PlayerArray.Num();
	if(NumberOfPlayers == 2)
	{
		bUseSeamlessTravel = true;
		FTimerHandle LoadLevelTimer;
		GetWorldTimerManager().SetTimer(LoadLevelTimer, this, &ThisClass::LoadLevel, 5.f);			
	}
}

void ALobbyGameMode::LoadLevel()
{
	if(UWorld* World = GetWorld())
	{
		World->ServerTravel(FString("/Game/Maps/BlasterMap?listen"));
	}
}
