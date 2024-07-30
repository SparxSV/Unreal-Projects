// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class INTRO_CPP_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

	// Sets default values for this character's properties
	APlayerCharacter();

public:
	UPROPERTY(BlueprintReadWrite)
	bool bIsAttacking;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	void LineTrace();

protected:
	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* SwordMesh;

	UPROPERTY(EditAnywhere)
	class UAnimSequence* AttackAnimation;

	UPROPERTY(EditAnywhere)
	int Damage;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveVertical(float InputValue);
	void MoveHorizontal(float InputValue);

	void LookHorizontal(float InputValue);
	void LookVertical(float InputValue);

	void StartAttack();	

};
