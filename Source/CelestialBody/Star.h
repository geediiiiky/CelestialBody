// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Star.generated.h"

UCLASS()
class CELESTIALBODY_API AStar : public AActor
{
	GENERATED_BODY()
	
public:	
	
	AStar();

	void BeginPlay() override;
	void Tick(float deltaTime) override;

	/* mass of the star, in solar mass*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Star")
	float mass;

	/* velocity, in AU / year*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Star")
	FVector velocity;

	UPROPERTY()
	FVector position;	// in AU

	UPROPERTY(BlueprintReadOnly, Category = "Star")
	FVector force;



	void CalcAccumulatedForce();
	void UpdatePosition(float deltaTime);
};
