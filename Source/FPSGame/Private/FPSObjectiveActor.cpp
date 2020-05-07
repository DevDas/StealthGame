// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSObjectiveActor.h"
#include "Components\SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "FPSGame\Public\FPSCharacter.h"

// Sets default values
AFPSObjectiveActor::AFPSObjectiveActor()
{
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = MeshComp;

	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	SphereComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereComp->SetCollisionResponseToAllChannels(ECR_Ignore); //Response: Projectile is Hitting it but We Will not Stop it
	SphereComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap); // only Pawn Will Block and overlap
	SphereComp->SetupAttachment(MeshComp);

	SetReplicates(true);
}

// Called when the game starts or when spawned
void AFPSObjectiveActor::BeginPlay()
{
	Super::BeginPlay();
	
	PlayEffects();
}

void AFPSObjectiveActor::PlayEffects()
{
	UGameplayStatics::SpawnEmitterAtLocation(this, PickupFX, GetActorLocation());
}

void AFPSObjectiveActor::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	PlayEffects();

	if (GetLocalRole() == ROLE_Authority || GetLocalRole() == ROLE_SimulatedProxy)
	{
		AFPSCharacter* MyCharacter = Cast<AFPSCharacter>(OtherActor); // Because We Don't Know What The Actor is
		if (MyCharacter) // if Someone Else Overlap Then
		{
			MyCharacter->Inventory++;
			if (MyCharacter->Inventory >= 2)
			{
				MyCharacter->bIsCarryingObjective = true;
			}
			Destroy();
		}
	}
}