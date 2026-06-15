// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/Items/AItemEscaneable.h"



// Sets default values
AAItemEscaneable::AAItemEscaneable()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMesh"));
	RootComponent = ItemMesh;
	
}

// Called when the game starts or when spawned
void AAItemEscaneable::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
//void AAItemEscaneable::Tick(float DeltaTime)
//{
	//Super::Tick(DeltaTime);
//}

void AAItemEscaneable::Scan_Implementation(AActor* Actor)
{
	
}

