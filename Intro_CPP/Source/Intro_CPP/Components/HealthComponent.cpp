// Fill out your copyright notice in the Description page of Project Settings.


#include "Intro_CPP/Components/HealthComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	bCanTakeDamage = true;

	CurrentHealth = MaxHealth;
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UHealthComponent::Die()
{
	GetOwner()->Destroy();
}

void UHealthComponent::AllowTakeDamage()
{
	bCanTakeDamage = true;
}

void UHealthComponent::TakeDamage(int Damage)
{
	if(bCanTakeDamage)
	{
		// Handle MaxHealth Values
		CurrentHealth -= Damage;
		bCanTakeDamage = false;

		// Delay
		FTimerHandle ITimerDelay;
		GetWorld()->GetTimerManager().SetTimer(ITimerDelay, this, &UHealthComponent::AllowTakeDamage, 0.5f, false);

		// Die Function
		if(CurrentHealth <= 0) Die();
	}
}

int UHealthComponent::GetHealth()
{
	return CurrentHealth;
}

