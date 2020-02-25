// Fill out your copyright notice in the Description page of Project Settings.


#include "BlackHole.h"
#include "Components\SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/World.h"

// Sets default values
ABlackHole::ABlackHole()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision); // Because its Blackhole
	RootComponent = MeshComp;

	InnerSphere = CreateDefaultSubobject<USphereComponent>(TEXT("InnerSphere"));
	InnerSphere->SetSphereRadius(100);
	InnerSphere->SetupAttachment(MeshComp);

	OuterSphere = CreateDefaultSubobject<USphereComponent>(TEXT("OuterSphere"));
	OuterSphere->SetSphereRadius(3000);
	OuterSphere->SetupAttachment(MeshComp);
}

// Called when the game starts or when spawned
void ABlackHole::BeginPlay()
{
	Super::BeginPlay();
	
	InnerSphere->OnComponentBeginOverlap.AddDynamic(this, &ABlackHole::InnerSphereOverlap);
}

// Called every frame
void ABlackHole::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TArray<UPrimitiveComponent*>OverlappingComps;
	OuterSphere->GetOverlappingComponents(OverlappingComps);

	for (int32 i = 0; i < OverlappingComps.Num(); i++)
	{
		UPrimitiveComponent* PrimitiveComp = OverlappingComps[i];
		if (PrimitiveComp && PrimitiveComp->IsSimulatingPhysics())
		{
			const float SphereRadius = OuterSphere->GetScaledSphereRadius();
			const float ForceStrength = -2000; // To Pull it

			PrimitiveComp->AddRadialForce(GetActorLocation(), SphereRadius, ForceStrength, ERadialImpulseFalloff::RIF_Constant, true);
		}
	}
}

void ABlackHole::InnerSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		OtherActor->Destroy();
	}
}