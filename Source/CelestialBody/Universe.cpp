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

void AUniverse::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (realTimeSimulation)
	{
		const auto simulateYears = simulationYearsPerSecond * DeltaTime;

		if (totalTickYears > simulateYears)
		{
			Simulate(0);	// already got enough food on my plate
		}
		else
		{
			Simulate(simulateYears);
		}
	}
}

void AUniverse::Simulate(float years)
{
	totalTickYears += years;

	const auto startTime = FPlatformTime::Seconds();

	while (totalTickYears > fixedSimulationYearsInterval)
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
				star->UpdatePosition(fixedSimulationYearsInterval);
			}
		}

		totalTickYears -= fixedSimulationYearsInterval;

		const auto now = FPlatformTime::Seconds();
		const float timeTaken = now - startTime;

		const auto MIN_FPS = 10.f;
		if (timeTaken >= 1.f / MIN_FPS)	// so I am expecting at least MIN_FPS
		{
			break;
		}
	}

	// collision check
	//for (auto i = 0; !stop && i < stars.Num(); ++i)
	//{
	//	for (auto j = i + 1; !stop && j < stars.Num(); ++j)
	//	{
	//		auto distance = UU2AU((stars[i]->GetActorLocation() - stars[j]->GetActorLocation()).Size());	// do it properly
	//		const auto combinedRadius = 0.00001f;	// sum of two stars' radius
	//		if (distance < combinedRadius)
	//		{
	//			stop = true;
	//		}
	//	}
	//}
}


