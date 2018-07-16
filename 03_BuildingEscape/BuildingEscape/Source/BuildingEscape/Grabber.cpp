// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("Grabber reporting for duty!"));

	/// Looks for attached physics handle
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle)
	{
		/// Physics handle is found
		UE_LOG(LogTemp, Warning, TEXT("Find PhysicsHandleComponent owned by %s."),
			*(GetOwner()->GetName()));
	}
	else 
	{
		UE_LOG(LogTemp, Error, TEXT("Cannot find physical handler owned by %s."), 
			*(GetOwner()->GetName()));
	}
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent)
	{
		/// Physics handle is found
		UE_LOG(LogTemp, Warning, TEXT("Find InputComponent owned by %s."), *(GetOwner()->GetName()));
		/// Bind the input axis
		InputComponent->BindAction("Grab", IE_Pressed, this, UGrabber::Grab);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Cannot find InputComponent owned by %s."), *(GetOwner()->GetName()));
	}
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	/// Get player view point this tick
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation
	);

	/*FString PlayerLocation = PlayerViewPointLocation.ToString();
	FString PlaterRotation = PlayerViewPointRotation.ToString();
	UE_LOG(LogTemp, Warning, TEXT("%s, %s"), *PlayerLocation, *PlaterRotation);*/

	FVector LineTraceEnd = PlayerViewPointLocation + 
		PlayerViewPointRotation.Vector() * PlayerHandsLength;// multiply unit vector to hands length 
	// Draw a red trace in the world to visualize
	DrawDebugLine(GetWorld(), PlayerViewPointLocation, LineTraceEnd,
												FColor::Green, false, 0.f, 0.f, 5.f);
	/// Setup query parameters
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());

	/// Ray cast (line-trace) out to reach distance
	FHitResult Hit;
	if (GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		PlayerViewPointLocation,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody)
	)) {
		FString HittedActor = Hit.GetActor()->GetName();
		UE_LOG(LogTemp, Warning, TEXT("Hitting %s"), *HittedActor);
	}
	/// See what we hit
	
}

void UGrabber::Grab()
{
}

