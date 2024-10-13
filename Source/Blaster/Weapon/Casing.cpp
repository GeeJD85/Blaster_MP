// Copyright Mintcakegames


#include "Casing.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Sound//SoundCue.h"

ACasing::ACasing()
{
	PrimaryActorTick.bCanEverTick = false;

	CasingMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CasingMesh"));
	SetRootComponent(CasingMesh);
	CasingMesh->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	CasingMesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
	CasingMesh->SetSimulatePhysics(true);
	CasingMesh->SetEnableGravity(true);
	CasingMesh->SetNotifyRigidBodyCollision(true);

	ShellEjectionImpulse = 5.f;
}

void ACasing::BeginPlay()
{
	Super::BeginPlay();

	FVector RandomShellRotation = UKismetMathLibrary::RandomUnitVectorInConeInDegrees(GetActorForwardVector(), 20.f);
	CasingMesh->OnComponentHit.AddDynamic(this, &ACasing::OnHit);
	CasingMesh->AddImpulse(RandomShellRotation * ShellEjectionImpulse);

	SetLifeSpan(LifetimeMax);
}

void ACasing::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	BounceCount++;
	
	if (GetVelocity().Length() <= 0)
	{		
		CasingMesh->SetNotifyRigidBodyCollision(false);
		CasingMesh->SetSimulatePhysics(false);
		return;
	}
	
	if (ShellSound && BounceCount <= 5)
	{		
		UGameplayStatics::PlaySoundAtLocation(this, ShellSound, GetActorLocation());
	}
}


