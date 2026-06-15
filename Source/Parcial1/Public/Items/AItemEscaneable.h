// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Public/Interfaces/ScanInterface.h"
#include "AItemEscaneable.generated.h"

USTRUCT(BlueprintType)
struct FDatosEscaneo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString NombreItem;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (MultiLine = true))
	FText DescripcionItem;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText AntiguedadItem;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float TiempoEscaneoRequerido;

	FDatosEscaneo()
	{
		NombreItem = TEXT("Objeto Desconocido");
		DescripcionItem = FText::FromString(TEXT("Sin descripción"));
		AntiguedadItem = FText::FromString(TEXT("Sin información"));
		TiempoEscaneoRequerido = 5.0f;
	}
};

UCLASS()

class PARCIAL1_API AAItemEscaneable : public AActor, public IScanInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AAItemEscaneable();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* ItemMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Datos de Escaneo")
	FDatosEscaneo DatosObjeto;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	//virtual void Tick(float DeltaTime) override;
	
	UFUNCTION()
	virtual void Scan_Implementation (AActor* Actor) override;
};
