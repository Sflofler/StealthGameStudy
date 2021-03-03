// Fill out your copyright notice in the Description page of Project Settings.


#include "BlackHole.h"

// Sets default values
ABlackHole::ABlackHole()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));	
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = MeshComponent;
	
	InnerSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Inner Sphere Component"));
	InnerSphere->SetupAttachment(MeshComponent);
	InnerSphere->SetSphereRadius(150);
	InnerSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	InnerSphere->OnComponentBeginOverlap.AddDynamic(this, &ABlackHole::HandleInnerSphereOverlapped);
	
	OuterSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Outer Sphere Component"));
	OuterSphere->SetupAttachment(MeshComponent);
	OuterSphere->SetSphereRadius(4000);
	OuterSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

// Called when the game starts or when spawned
void ABlackHole::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABlackHole::HandleInnerSphereOverlapped(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor)
	{
		OtherActor->Destroy();
	}
}

// Called every frame
void ABlackHole::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TArray<UPrimitiveComponent*> OverlappingComponents;
	OuterSphere->GetOverlappingComponents(OverlappingComponents);

	if(OverlappingComponents.Num() > 0)
	{
		for (int32 i = 0; i < OverlappingComponents.Num(); i++)
		{
			UPrimitiveComponent* PrimitiveComponent = OverlappingComponents[i];

			if(PrimitiveComponent && PrimitiveComponent->IsSimulatingPhysics())
			{
				const float OuterSphereRadius = OuterSphere->GetScaledSphereRadius();
				PrimitiveComponent->AddRadialForce(GetActorLocation(), OuterSphereRadius, GravityForce, RIF_Constant, true);
			}
		}
	}
}