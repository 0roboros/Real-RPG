// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "LightSwitchCodeOnly.generated.h"

/**
 * 
 */
UCLASS()
class TEST1_API ALightSwitchCodeOnly : public AActor
{
	GENERATED_UCLASS_BODY()

	/** point light component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Switch Components")
	TSubobjectPtr<UPointLightComponent> PointLight1;

	/** sphere component */

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Switch Components")
	TSubobjectPtr<USphereComponent> Sphere1;
	
	/** called when something begins overlapping the sphere component */
	UFUNCTION(BlueprintNativeEvent, Category = "Switch Functions")
	void BeginOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool FromSweep, const FHitResult& SweepResult);
	
	/** called when something stops overlapping the sphere component */
	UFUNCTION(BlueprintNativeEvent, Category = "Switch Functions")
	void EndOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	/** the desired intensity for the light */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Switch Variables")
	float DesiredIntensity;
};
