// Fill out your copyright notice in the Description page of Project Settings.


#include "Intro_CPP/Player/PlayerCharacter.h"
#include "Intro_CPP/Components/HealthComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Player Camera"));
	Camera->SetupAttachment(RootComponent);
	Camera->bUsePawnControlRotation = true;

	SwordMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Sword Mesh"));
	SwordMesh->SetupAttachment(GetMesh(), FName("SwordSocket"));
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &APlayerCharacter::StartAttack);

	PlayerInputComponent->BindAxis("MoveVertical", this, &APlayerCharacter::MoveVertical);
	PlayerInputComponent->BindAxis("MoveHorizontal", this, &APlayerCharacter::MoveHorizontal);

	PlayerInputComponent->BindAxis("LookHorizontal", this, &APlayerCharacter::LookHorizontal);
	PlayerInputComponent->BindAxis("LookVertical", this, &APlayerCharacter::LookVertical);
}

void APlayerCharacter::MoveVertical(float InputValue)
{
	FVector ForwardDirection = GetActorForwardVector();
	AddMovementInput(ForwardDirection, InputValue);
}

void APlayerCharacter::MoveHorizontal(float InputValue)
{
	FVector RightDirection = GetActorRightVector();
	AddMovementInput(RightDirection, InputValue);
}

void APlayerCharacter::LookHorizontal(float InputValue)
{
	AddControllerYawInput(InputValue);
}

void APlayerCharacter::LookVertical(float InputValue)
{
	AddControllerPitchInput(-InputValue);
}

void APlayerCharacter::StartAttack()
{
	// Call attack animation
	if(AttackAnimation != nullptr && !bIsAttacking)
	{
		GetMesh()->PlayAnimation(AttackAnimation, false);
		bIsAttacking = true;
	}
}

void APlayerCharacter::LineTrace()
{
	// Get socket locations
	FVector StartLocation = SwordMesh->GetSocketLocation(FName("Start"));
	FVector EndLocation = SwordMesh->GetSocketLocation(FName("End"));

	// Setup line trace
	FHitResult HitResult;
	FCollisionQueryParams TraceParams;
	TraceParams.AddIgnoredActor(this);

	// Line trace
	GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Visibility, TraceParams);

	// Debug Lines
	//DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Red, false, 1, 0, 1);

	if(HitResult.bBlockingHit)
	{
		AActor* ActorHit = HitResult.GetActor();
		UHealthComponent* OtherHit = ActorHit->FindComponentByClass<UHealthComponent>();

		if(IsValid(OtherHit))
			OtherHit->TakeDamage(Damage);
	}
}

