// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Universe.generated.h"

UCLASS()
class CELESTIALBODY_API AUniverse : public AActor
{
	GENERATED_BODY()
	
public:	
	AUniverse();

	void BeginPlay() override;
	void Tick( float DeltaSeconds ) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Transient, Category = "Universe")
	TArray<class AStar*> stars;

	/* How many years does 1 second in simulation equal to. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Universe")
	float simulationYearsPerSecond = 1.f;

	/* fixed tick interval (in simulation years). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Universe")
	float fixedSimulationYearsInterval = 0.01f;

	/* How many unreal units (or centi meters) in simulation does 1AU equal to. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Universe")
	float unrealUnitsPerAU = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Universe")
	bool realTimeSimulation = true;

	UFUNCTION(BlueprintCallable, Category = "Universe")
	void Simulate(float years);

private:
	float totalTickYears = 0.f;
	

public:
	float UU2AU(float unrealUnit) const { return unrealUnit / unrealUnitsPerAU; }
	FVector UU2AU(const FVector& unrealUnitVec) const { return unrealUnitVec / unrealUnitsPerAU; }

	float AU2UU(float au) const { return au * unrealUnitsPerAU; }
	FVector AU2UU(const FVector& auVec) const { return auVec * unrealUnitsPerAU; }
};
