// Copyright Mintcakegames


#include "BlasterGameState.h"

#include "Blaster/PlayerState/BlasterPlayerState.h"
#include "Net/UnrealNetwork.h"

void ABlasterGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ABlasterGameState, TopScoringPlayers);
}

void ABlasterGameState::UpdateTopScore(ABlasterPlayerState* ScoringPLayer)
{
	if (TopScoringPlayers.Num() == 0)
	{
		TopScoringPlayers.Add(ScoringPLayer);
		TopScore = ScoringPLayer->GetScore();
	}
	else if (ScoringPLayer->GetScore() == TopScore)
	{
		TopScoringPlayers.AddUnique(ScoringPLayer);
	}
	else if (ScoringPLayer->GetScore() > TopScore)
	{
		TopScoringPlayers.Empty();
		TopScoringPlayers.AddUnique(ScoringPLayer);
		TopScore = ScoringPLayer->GetScore();
	}
}
