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
	void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	void Tick( float DeltaSeconds ) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Transient, Category = "Universe")
	TArray<class AStar*> stars;
	
	bool stop = false;

	static AUniverse* theUniverse;
	
};
