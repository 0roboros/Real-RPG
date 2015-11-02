// Fill out your copyright notice in the Description page of Project Settings.

#include "Test1.h"
#include "Powerup.h"


APowerup::APowerup(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	PrimaryActorTick.bCanEverTick = true;
	TouchSphere = PCIP.CreateDefaultSubobject<USphereComponent>(this, TEXT("TouchSphereComponent"));
	TouchSphere->SetSphereRadius(20.f, false);
	RootComponent = TouchSphere;
	RotationRate = 180.f;

}

void APowerup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FRotator MyRot = GetActorRotation();
	MyRot.Yaw += RotationRate * DeltaTime;
	SetActorRotation(MyRot);


}


