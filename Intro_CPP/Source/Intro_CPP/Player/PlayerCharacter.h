// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
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

#pragma region Enhanced Inputs

	UPROPERTY(EditAnywhere, Category = "Enhanced Inputs")
	class UInputMappingContext* InputMapping;

	UPROPERTY(EditAnywhere, Category = "Enhanced Inputs")
	class UInputAction* AttackAction;

	UPROPERTY(EditAnywhere, Category = "Enhanced Inputs")
	class UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, Category = "Enhanced Inputs")
	class UInputAction* LookAction;

	UPROPERTY(EditAnywhere, Category = "Enhanced Inputs")
	class UInputAction* JumpAction;

#pragma endregion

	UPROPERTY(EditAnywhere, Category="Stats")
	int Damage;

	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* SwordMesh;

	UPROPERTY(EditAnywhere)
	class UAnimSequence* AttackAnimation;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);

	void StartAttack();	

};
