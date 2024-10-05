// Copyright Mintcakegames


#include "ProjectileRocket.h"

#include "Kismet/GameplayStatics.h"

AProjectileRocket::AProjectileRocket()
{
	RocketMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RocketMesh"));
	RocketMesh->SetupAttachment(RootComponent);
	RocketMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AProjectileRocket::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                              FVector NormalImpulse, const FHitResult& Hit)
{
	if (TObjectPtr<APawn> FiringPawn = GetInstigator())
	{
		if (TObjectPtr<AController> FiringController = FiringPawn->GetController())
		{
			UGameplayStatics::ApplyRadialDamageWithFalloff(
				this, // World Context object
				Damage, // Base damage
				10.f, // Minimum damage
				GetActorLocation(), // Origin
				DamageInnerRadius, // Damage inner radius
				DamageOuterRadius, // Damage outer radius
				1.f, // Damage falloff
				UDamageType::StaticClass(), // Damage type class
				TArray<AActor*>(), // Ignore actors
				this, // Damage causer
				FiringController // Instigator controller
				);
		}
	}
	Super::OnHit(HitComp, OtherActor, OtherComp, NormalImpulse, Hit);
}
