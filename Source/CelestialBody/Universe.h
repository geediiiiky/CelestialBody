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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Universe")
	float fixedTickInterval = 0.01f;

	/* How many days does 1 second in simulation equal to. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Universe")
	float daysEqualToOneSec = 365;

	/* How many unreal units (or centi meters) in simulation does 1AU equal to. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Universe")
	float unrealUnitsEqualToOneAU = 100.f;

private:
	float totalTickDeltaTime = 0.f;
	bool stop = false;

public:
	float UU2AU(float unrealUnit) const { return unrealUnit / unrealUnitsEqualToOneAU; }
	FVector UU2AU(const FVector& unrealUnitVec) const { return unrealUnitVec / unrealUnitsEqualToOneAU; }

	float AU2UU(float au) const { return au * unrealUnitsEqualToOneAU; }
	FVector AU2UU(const FVector& auVec) const { return auVec * unrealUnitsEqualToOneAU; }
};
