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

void AStar::BeginPlay()
{
	Super::BeginPlay();
}

void AStar::OnAddedToUniverse(AUniverse* theUniverse)
{
	universe = theUniverse;

	universe->stars.AddUnique(this);
	position = universe->UU2AU(GetActorLocation());
}


const float G = 4 * PI * PI;	// this is based on mass being solar mass, length being astronomical unit (AU), time being year

void AStar::CalcAccumulatedForce()
{
	force = FVector::ZeroVector;

	for (auto other : universe->stars)
	{
		if (other != this && other->mass > 0 && this->mass > 0)
		{
			auto toOther = other->position - this->position;
			auto normalized = toOther.GetSafeNormal();
			force += (G * other->mass * this->mass / toOther.SizeSquared()) * normalized;
		}
	}
}


void AStar::UpdatePosition(float deltaTime)
{
	if (mass > 0)
	{
		auto acceleration = force / mass;
		velocity += acceleration * deltaTime;
		position += velocity * deltaTime;

		//UE_LOG(LogTemp, Log, TEXT("%s: acc: %s, velocity: %s"), *GetActorLabel(), *acceleration.ToString(), *velocity.ToString());

		SetActorLocation(universe->AU2UU(position));
	}
}
