// Copyright Mintcakegames

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "BlasterPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class BLASTER_API ABlasterPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	/*
	 *  Replication Notifies
	 */
	virtual void OnRep_Score() override;
	UFUNCTION()
	virtual void OnRep_Defeats();
	UFUNCTION()
	virtual void OnRep_ShowDefeatedByText();
	UFUNCTION()
	virtual void OnRep_SetHUDWeaponInfo();
	
	void AddToScore(float ScoreAmount);
	void AddToDefeats(int32 DefeatsAmount);
	void ShowDefeatedByText(FString AttackerName);
	void SetHUDWeaponInfo(FName WeaponName, UTexture2D* WeaponIcon);
	

private:
	UPROPERTY()
	class ABlasterCharacter* Character;
	UPROPERTY()
	class ABlasterPlayerController* Controller;

	UPROPERTY(ReplicatedUsing=OnRep_Defeats)
	int32 Defeats;

	UPROPERTY(ReplicatedUsing=OnRep_ShowDefeatedByText)
	FString KilledByName;

	UPROPERTY(ReplicatedUsing=OnRep_SetHUDWeaponInfo)
	FName NewWeaponName;

	UPROPERTY(ReplicatedUsing=OnRep_SetHUDWeaponInfo)
	TObjectPtr<UTexture2D> NewWeaponIcon;
};
