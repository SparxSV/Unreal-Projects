// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class INTRO_CPP_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

	// Sets default values for this component's properties
	UHealthComponent();

public:


public:	
	void TakeDamage(int Damage);

protected:
	UPROPERTY(EditAnywhere)
	int Health;

	bool bCanTakeDamage;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void Die();
	void AllowTakeDamage();

};
