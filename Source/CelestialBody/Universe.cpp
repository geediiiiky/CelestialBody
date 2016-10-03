// Fill out your copyright notice in the Description page of Project Settings.

#include "CelestialBody.h"
#include "Universe.h"
#include "Star.h"


AUniverse* AUniverse::theUniverse = nullptr;

AUniverse::AUniverse()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AUniverse::BeginPlay()
{
	Super::BeginPlay();

	AUniverse::theUniverse = this;

	stars.Empty();

	for (TActorIterator<AActor> It(GetWorld(), AStar::StaticClass()); It; ++It)
	{
		AStar* star = Cast<AStar>(*It);
		if (star && star->IsPendingKill() == false)
		{
			stars.Add(star);
		}
	}
}

void AUniverse::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	AUniverse::theUniverse = nullptr;

}

void AUniverse::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	if (stop)
	{
		return;
	}

	const auto clips = 50;

	for (auto i = 0; i < clips; ++i)
	{
		auto dt = DeltaTime / (float)clips;

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
				star->UpdatePosition(dt);
			}
		}
	}

	// collision check
	for (auto i = 0; !stop && i < stars.Num(); ++i)
	{
		for (auto j = i + 1; !stop && j < stars.Num(); ++j)
		{
			auto distance = (stars[i]->GetActorLocation() - stars[j]->GetActorLocation()).Size() / 400.f;	// do it properly
			const auto combinedRadius = 0.00001f;	// sum of two stars' radius
			if (distance < combinedRadius)
			{
				stop = true;
			}
		}
	}
}

