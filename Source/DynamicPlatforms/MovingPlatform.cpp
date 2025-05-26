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

	StartLocation = GetActorLocation();
	Forward = GetActorForwardVector();

	FString Name = GetName();

	UE_LOG(LogTemp, Display, TEXT("%s has been spawned"), *Name);
	
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
	if (ShouldPlatformReturn())
	{
		StartLocation = StartLocation + Forward * MoveDistance;
		SetActorLocation(StartLocation);
		Forward = -Forward;
	}
	else
	{
		FVector CurentLocation = GetActorLocation();
		CurentLocation = CurentLocation + Forward * MoveSpeed * DeltaTime;
		SetActorLocation(CurentLocation);
	}
}

void AMovingPlatform::RotatePlatform(float DeltaTime)
{
	AddActorLocalRotation(RotationVelocity * DeltaTime);
}
bool AMovingPlatform::ShouldPlatformReturn() const
{
	return GetDistanceMoved() > MoveDistance;
}

float AMovingPlatform::GetDistanceMoved() const
{
	FVector CurrentLocation = GetActorLocation();
	FVector DistanceMoved = CurrentLocation - StartLocation;
	return DistanceMoved.Size();
}
