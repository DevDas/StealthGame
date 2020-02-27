// Fill out your copyright notice in the Description page of Project Settings.

#include "ExtractionZone.h"
#include "Components\BoxComponent.h"

// Sets default values
AExtractionZone::AExtractionZone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	OverlapComp = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapComp"));
	OverlapComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	OverlapComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	OverlapComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	OverlapComp->SetBoxExtent(FVector(200.f)); // Change The Size
	RootComponent = OverlapComp;
	OverlapComp->SetHiddenInGame(false);
}
// Called when the game starts or when spawned
void AExtractionZone::BeginPlay()
{
	Super::BeginPlay();
	
	OverlapComp->OnComponentBeginOverlap.AddDynamic(this, &AExtractionZone::HandleOverlap);
}

void AExtractionZone::HandleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Hey It Is Working"))
}