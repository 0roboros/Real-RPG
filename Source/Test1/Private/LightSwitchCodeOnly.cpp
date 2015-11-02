// Fill out your copyright notice in the Description page of Project Settings.

#include "Test1.h"
#include "LightSwitchCodeOnly.h"


ALightSwitchCodeOnly::ALightSwitchCodeOnly(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP), DesiredIntensity(3000.0f)
{
    PointLight1 = PCIP.CreateDefaultSubobject<UPointLightComponent>(this, "PointLight1");
    PointLight1->Intensity = DesiredIntensity;
    PointLight1->bVisible = true;
    RootComponent = PointLight1;

    Sphere1 = PCIP.CreateDefaultSubobject<USphereComponent>(this, TEXT("Sphere1"));
    Sphere1->InitSphereRadius(250.0f);
    Sphere1->AttachParent = RootComponent;

    Sphere1->OnComponentBeginOverlap.AddDynamic(this, &ALightSwitchCodeOnly::BeginOverlap);        // set up a notification for when this component overlaps something
    Sphere1->OnComponentEndOverlap.AddDynamic(this, &ALightSwitchCodeOnly::EndOverlap);      // set up a notification for when this component overlaps something

}

void ALightSwitchCodeOnly::BeginOverlap_Implementation(AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool FromSweep, const FHitResult& SweepResult)
{
    if ( OtherActor && (OtherActor != this) && OtherComp )
    {
        PointLight1->ToggleVisibility();
    }
}


void ALightSwitchCodeOnly::EndOverlap_Implementation(AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    if ( OtherActor && (OtherActor != this) && OtherComp )
    {
        PointLight1->ToggleVisibility();
    }
}
