// Fill out your copyright notice in the Description page of Project Settings.

#include "CelestialBody.h"
#include "Universe.h"
#include "Star.h"


AUniverse::AUniverse()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AUniverse::BeginPlay()
{
	Super::BeginPlay();

	stars.Empty();

	for (TActorIterator<AActor> It(GetWorld(), AStar::StaticClass()); It; ++It)
	{
		AStar* star = Cast<AStar>(*It);
		if (star && star->IsPendingKill() == false)
		{
			star->OnAddedToUniverse(this);
		}
	}
}

void AUniverse::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	if (stop)
	{
		return;
	}

	totalTickDeltaTime += (DeltaTime * daysEqualToOneSec / 365.f);

	while (totalTickDeltaTime > fixedTickInterval)
	{
		for (auto star : stars)
		{
			if (star)
			{
				star->CalcAccumulatedForce();
			}
		}

		for (auto star : stars)
		{
			if (star)
			{
				star->UpdatePosition(fixedTickInterval);
			}
		}

		totalTickDeltaTime -= fixedTickInterval;
	}

	// collision check
	for (auto i = 0; !stop && i < stars.Num(); ++i)
	{
		for (auto j = i + 1; !stop && j < stars.Num(); ++j)
		{
			auto distance = UU2AU((stars[i]->GetActorLocation() - stars[j]->GetActorLocation()).Size());	// do it properly
			const auto combinedRadius = 0.00001f;	// sum of two stars' radius
			if (distance < combinedRadius)
			{
				stop = true;
			}
		}
	}
}

