// Fill out your copyright notice in the Description page of Project Settings.

#include "CelestialBody.h"
#include "Star.h"
#include "Universe.h"

#include "DrawDebugHelpers.h"

AStar::AStar()
{
	PrimaryActorTick.bStartWithTickEnabled = true;
	PrimaryActorTick.bCanEverTick = true;
}

void AStar::Tick(float deltaTime)
{
	Super::Tick(deltaTime);
}

FVector Astronomic2Ue(const FVector& position)
{
	return position * 400.f;
}

FVector Ue2Astronomic2(const FVector& position)
{
	return position / 400.f;
}

void AStar::BeginPlay()
{
	Super::BeginPlay();

	if (AUniverse::theUniverse)
	{
		AUniverse::theUniverse->stars.AddUnique(this);
	}

	position = Ue2Astronomic2(GetActorLocation());
}

const float G = 4 * PI * PI;	// this is based on mass being solar mass, length being astronomical unit (AU), time being year

void AStar::CalcAccumulatedForce()
{
	force = FVector::ZeroVector;

	for (auto other : AUniverse::theUniverse->stars)
	{
		if (other != this)
		{
			auto toOther = other->position - this->position;
			auto normalized = toOther.GetSafeNormal();
			force += (G * other->mass * this->mass / toOther.SizeSquared()) * normalized;
		}
	}
}


void AStar::UpdatePosition(float deltaTime)
{
	auto acceleration = force / mass;
	velocity += acceleration * deltaTime;
	position += velocity * deltaTime;

	//UE_LOG(LogTemp, Log, TEXT("%s: acc: %s, velocity: %s"), *GetActorLabel(), *acceleration.ToString(), *velocity.ToString());

	SetActorLocation(Astronomic2Ue(position));
}