// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSLaunchPad.h"
#include "FPSCharacter.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AFPSLaunchPad::AFPSLaunchPad()
{
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	SetRootComponent(BoxComponent);

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(BoxComponent);

	LaunchStrength = 1500;
	LaunchPitchAngle = 45;
	UE_LOG(LogTemp, Warning, TEXT("Started"));
}

void AFPSLaunchPad::BeginPlay()
{
	Super::BeginPlay();
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AFPSLaunchPad::HandleBeginOverlap);
}

void AFPSLaunchPad::HandleBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                       UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Someting overlapped"));
	FRotator LaunchDirection = GetActorRotation();
	LaunchDirection.Pitch += LaunchPitchAngle;
	const FVector LaunchVelocity = LaunchDirection.Vector() * LaunchStrength;
	
	ACharacter* Character = Cast<ACharacter>(OtherActor);

	if(Character)
	{
		UE_LOG(LogTemp, Display, TEXT("Launching player"));
		Character->LaunchCharacter(LaunchVelocity, true, true);
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), LaunchParticleEffect, GetActorLocation());
	}
	else if(OtherComp && OtherComp->IsSimulatingPhysics())
	{
		UE_LOG(LogTemp, Display, TEXT("Launching other"));
		OtherComp->AddImpulse(LaunchVelocity, NAME_None, true);
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), LaunchParticleEffect, GetActorLocation());
	}
}
