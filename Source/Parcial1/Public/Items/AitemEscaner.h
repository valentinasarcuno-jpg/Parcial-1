// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AitemEscaner.generated.h"



UCLASS()
class PARCIAL1_API AAitemEscaner : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AAitemEscaner();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UStaticMeshComponent* EscanerMesh;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UBoxComponent* ZonaColision;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:
	// Called every frame
	//virtual void Tick(float DeltaTime) override;

private: 
	
	UPROPERTY()
	TObjectPtr<AActor> OverlapActor; 
	
	FTimerHandle TimerHandle_Escaneo;
	float ProgresoActual;
	void AvanzarEscaneo();
	
	AActor* DispararRayoEscaneo();
	
public: 
	
	UFUNCTION()
	void IniciarEscaneo();
	
	UFUNCTION()
	void DetenerEscaneo();
};
