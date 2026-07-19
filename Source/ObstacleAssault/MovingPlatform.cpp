// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	startPosition = GetActorLocation();
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MovePlatform(DeltaTime);
	RotatePlatform(DeltaTime);
}

void AMovingPlatform::MovePlatform(float DeltaTime)
{
	distanceMoved = GetDistanceMoved();

	if (distanceMoved >= maxDistance) 
	{
		float overshootDistance = distanceMoved - maxDistance;
		UE_LOG(LogTemp, Warning, TEXT("%s overshoot by %f"), *GetName(), overshootDistance);

		FVector moveDirection = platformVelocity.GetSafeNormal();
		FVector newStartPosition = startPosition + moveDirection * maxDistance;
		SetActorLocation(newStartPosition);
		startPosition = newStartPosition;

		platformVelocity = -platformVelocity;
	}
	else 
	{
		FVector currentLocation = GetActorLocation();

		currentLocation += platformVelocity * DeltaTime;
		SetActorLocation(currentLocation);
	}
}

void AMovingPlatform::RotatePlatform(float DeltaTime)
{
	FRotator rotationToAdd = rotationVelocity * DeltaTime;
	AddActorLocalRotation(rotationToAdd);
}

float AMovingPlatform::GetDistanceMoved()
{
	return FVector::Dist(startPosition, GetActorLocation());
}

