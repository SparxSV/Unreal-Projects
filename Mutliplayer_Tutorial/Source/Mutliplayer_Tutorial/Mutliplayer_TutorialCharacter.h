// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "Mutliplayer_TutorialCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class AMutliplayer_TutorialCharacter : public ACharacter
{
	GENERATED_BODY()

public:

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	/** Shoot Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* ShootAction;

public:

	AMutliplayer_TutorialCharacter();

	/** Property replication */
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	/** Getter for MaxHealth */
	UFUNCTION(BlueprintPure, Category="Health")
	FORCEINLINE float GetMaxHealth() const { return MaxHealth; }

	/** Getter for Current Health.*/
	UFUNCTION(BlueprintPure, Category="Health")
	FORCEINLINE float GetCurrentHealth() const { return CurrentHealth; }

	/** Setter for Current Health. Clamps the value between 0 and MaxHealth and calls OnHealthUpdate. Should only be called on the server.*/
	UFUNCTION(BlueprintCallable, Category="Health")
	void SetCurrentHealth(float HealthValue);

	/** Event for taking damage. Overriden from APawn.*/
	UFUNCTION(BlueprintCallable, Category="Health")
	float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

protected:

	UPROPERTY(EditDefaultsOnly, Category="Gameplay|Projectile")
	TSubclassOf<class AProjectile> ProjectileClass;

	/** Delay between shots in seconds. Used to control fire rate for your test projectile, but also to prevent an overflow of server functions from binding SpawnProjectile directly to input.*/
	UPROPERTY(EditDefaultsOnly, Category="Gameplay")
	float FireRate;

	/** If true, you are in the process of firing projectiles. */
	bool bIsFiringWeapon;

	/** A timer handle used for providing the fire rate delay in-between spawns. */
	FTimerHandle FiringTimer;

	// Max health does not replicate and is only editable in defaults.
	UPROPERTY(EditDefaultsOnly, Category = "Health")
	float MaxHealth;

	// replicates but is not editable or accessibe
	UPROPERTY(ReplicatedUsing = OnRep_CurrentHealth)
	float CurrentHealth;

protected:

	/** RepNotify for Changes made to current health. */
	UFUNCTION()
	void OnRep_CurrentHealth();

	/** Function for beginning weapon fire. */
	UFUNCTION(BlueprintCallable, Category="Gameplay")
	void StartFire();

	/** Function for ending weapon fire. Once this is called, the player can use StartFire again. */
	UFUNCTION(BlueprintCallable, Category="Gameplay")
	void StopFire();

	/** Server function for spawning projectiles. */
	UFUNCTION(Server, Reliable)
	void HandleFire();

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	/** Response to health being updated. Called on the server immediately after modication, and in clients in response to a RepNotify. */
	void OnHealthUpdate();

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// To add mapping context
	virtual void BeginPlay();

};

