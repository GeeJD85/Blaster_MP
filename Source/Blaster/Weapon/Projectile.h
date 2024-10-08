// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class BLASTER_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	AProjectile();
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(NetMulticast, Reliable) // Unreliable yields strange results
	void MulticastDestroyProjectile(bool bPlayerHit);

protected:
	virtual void BeginPlay() override;
	void PlayImpactEffects();

	UFUNCTION()
	virtual void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UPROPERTY(EditAnywhere)
	float Damage = 20.f;
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UParticleSystem> ImpactParticles;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class USoundCue> ImpactSound;
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UBoxComponent> CollisionBox;
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UProjectileMovementComponent> ProjectileMovementComponent;
	
private:	

	UPROPERTY(EditAnywhere)
	TObjectPtr<UParticleSystem> Tracer;

	TObjectPtr<class UParticleSystemComponent> TracerComponent;


public:	
	

};
