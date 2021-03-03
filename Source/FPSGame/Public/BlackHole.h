// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "BlackHole.generated.h"

UCLASS()
class FPSGAME_API ABlackHole : public AActor
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	ABlackHole();

protected:
	
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	USphereComponent* InnerSphere;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	USphereComponent* OuterSphere;

	UPROPERTY(EditDefaultsOnly, Category = "Components")
	int GravityForce = -2000;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void HandleInnerSphereOverlapped(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
