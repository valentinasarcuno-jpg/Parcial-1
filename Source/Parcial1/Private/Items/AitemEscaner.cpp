// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/Items/AitemEscaner.h"
#include "Public/Interfaces/ScanInterface.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "DrawDebugHelpers.h"
#include "Parcial1Character.h"
#include "Public/Items/AItemEscaneable.h"



// Sets default values
AAitemEscaner::AAitemEscaner()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	EscanerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("EscanerMesh"));
	RootComponent = EscanerMesh;
	EscanerMesh->SetCollisionProfileName(TEXT("NoCollision")); 

    ZonaColision = CreateDefaultSubobject<UBoxComponent>(TEXT("ZonaColision"));
    ZonaColision->SetupAttachment(RootComponent); 
    ZonaColision->SetBoxExtent(FVector(60.f, 60.f, 60.f)); 
    ZonaColision->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
    ZonaColision->SetGenerateOverlapEvents(true);
}

// Called when the game starts or when spawned
void AAitemEscaner::BeginPlay()
{
	Super::BeginPlay();
	
}

AActor* AAitemEscaner::DispararRayoEscaneo()
{
    FVector Inicio = EscanerMesh->GetComponentLocation();
    FVector Fin = Inicio; 

    
    AActor* MiPersonaje = GetAttachParentActor();
    if (MiPersonaje)
    {
        
        Fin = Inicio + (MiPersonaje->GetActorForwardVector() * 500.0f);
    }
    else
    {
        Fin = Inicio + (EscanerMesh->GetForwardVector() * 500.0f);
    }

    FHitResult ResultadoImpacto;
    FCollisionQueryParams ParametrosRayo;
    ParametrosRayo.AddIgnoredActor(this);
    ParametrosRayo.AddIgnoredActor(GetAttachParentActor());

    bool bGolpeoAlgo = GetWorld()->LineTraceSingleByChannel(ResultadoImpacto, Inicio, Fin, ECC_Visibility, ParametrosRayo);

   
    DrawDebugLine(GetWorld(), Inicio, Fin, bGolpeoAlgo ? FColor::Green : FColor::Red, false, 0.1f, 0, 2.0f);

    if (bGolpeoAlgo)
    {
        return ResultadoImpacto.GetActor();
    }
    return nullptr;
}
// Called every frame
//void AAitemEscaner::Tick(float DeltaTime)
//{
	//Super::Tick(DeltaTime);
//}

void AAitemEscaner::IniciarEscaneo()
{
    
    OverlapActor = DispararRayoEscaneo();

    if (OverlapActor && OverlapActor->Implements<UScanInterface>())
    {
        GetWorldTimerManager().ClearTimer(TimerHandle_Escaneo);
        ProgresoActual = 0.0f;
        GetWorldTimerManager().SetTimer(TimerHandle_Escaneo, this, &AAitemEscaner::AvanzarEscaneo, 0.1f, true);
        
        if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Cyan, TEXT("Escaneando... ¡Mantené apuntado!"));
    }
}

void AAitemEscaner::DetenerEscaneo()
{
    if (GetWorldTimerManager().IsTimerActive(TimerHandle_Escaneo))
    {
        GetWorldTimerManager().ClearTimer(TimerHandle_Escaneo);
        ProgresoActual = 0.0f;
        OverlapActor = nullptr; 
        
        if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Orange, TEXT("Escaneo cancelado."));
    }
}

void AAitemEscaner::AvanzarEscaneo()
{
    
    AActor* ActorApuntadoAhora = DispararRayoEscaneo();
    
    if (ActorApuntadoAhora != OverlapActor)
    {
        DetenerEscaneo();
        return;
    }

    AAItemEscaneable* Item = Cast<AAItemEscaneable>(OverlapActor);
    
    if (Item)
    {
        ProgresoActual += 0.1f;
        
        
        float TiempoObjetivo = Item->DatosObjeto.TiempoEscaneoRequerido; 

        if (GEngine) GEngine->AddOnScreenDebugMessage(1, 0.15f, FColor::Yellow, 
            FString::Printf(TEXT("Progreso: %.1f / %.1f"), ProgresoActual, TiempoObjetivo));

        if (ProgresoActual >= TiempoObjetivo)
        {
            GetWorldTimerManager().ClearTimer(TimerHandle_Escaneo);
            IScanInterface::Execute_Scan(OverlapActor, this);

            AParcial1Character* MiPersonaje = Cast<AParcial1Character>(GetAttachParentActor());
            if (MiPersonaje)
            {
                MiPersonaje->RegistrarNuevoEscaneo(Item->DatosObjeto.NombreItem, Item->DatosObjeto.DescripcionItem, Item->DatosObjeto.AntiguedadItem);
            }
        }
    }
}