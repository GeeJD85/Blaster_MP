// Copyright Mintcakegames


#include "HitScanWeapon.h"

#include "Blaster/Character/BlasterCharacter.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Kismet/GameplayStatics.h"

void AHitScanWeapon::Fire(const FVector& HitTarget)
{
	Super::Fire(HitTarget);

	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (!OwnerPawn) return;
	
	AController* InstigatorController = OwnerPawn->GetController();
	const USkeletalMeshSocket* MuzzleFlashSocket = GetWeaponMesh()->GetSocketByName("MuzzleFlash");

	if(MuzzleFlashSocket && InstigatorController)
	{
		FTransform SocketTranmsform = MuzzleFlashSocket->GetSocketTransform((GetWeaponMesh()));
		FVector Start = SocketTranmsform.GetLocation();
		FVector End = Start + (HitTarget - Start) * 1.25f;

		FHitResult FireHit;
		if (TObjectPtr<UWorld> World = GetWorld())
		{
			World->LineTraceSingleByChannel(
				FireHit,
				Start,
				End,
				ECC_Visibility
				);
			if (FireHit.bBlockingHit)
			{
				if (TObjectPtr<ABlasterCharacter> BlasterCharacter = Cast<ABlasterCharacter>(FireHit.GetActor()))
				{
					if (HasAuthority())
					{
						UGameplayStatics::ApplyDamage(
						BlasterCharacter,
						Damage,
						InstigatorController,
						this,
						UDamageType::StaticClass()
						);
					}
				}
				if (ImpactParticles)
				{
					UGameplayStatics::SpawnEmitterAtLocation(
						World,
						ImpactParticles,
						FireHit.ImpactPoint,
						FireHit.ImpactNormal.Rotation()
						);
				}
			}
		}
	}
}
