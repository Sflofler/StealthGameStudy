// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "FPSObjectiveActor.generated.h"

UCLASS()
class FPSGAME_API AFPSObjectiveActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFPSObjectiveActor();

protected:

	// Variables
	UPROPERTY(VisibleAnywhere, Category = "Components");
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(VisibleAnywhere, Category = "Components");
	USphereComponent* SphereComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Effects");
	UParticleSystem* PickupFX;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void PlayEffect();

	void Initialize();

public:
	
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
};
