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

	/* the scale of this body's position. I.E. setting this to 0.1 will place the star whose actual location is (5au, 5au, 0au) to (0.5au, 0.5au, 0). 
	The ue unit transform from AU set in the universe will still be applied on top of that. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Star")
	float positionScale = 1.f;

	UPROPERTY()
	class AUniverse* universe;

	void OnAddedToUniverse(class AUniverse* universe);
	void CalcAccumulatedForce();
	void UpdatePosition(float deltaTime);
};
