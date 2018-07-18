// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "Components/PrimitiveComponent.h"

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
	FindPhysicsHandleComponent();
	SetupInputComponent();
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);	
	/// if the physics handle is attached
	if (PhysicsHandle->GrabbedComponent) {
		/// move the object that we're holding
		PhysicsHandle->SetTargetLocation(GetLineTrace().v2);
	}
}

void UGrabber::Grab()
{
	auto HitResult = GetFirstPhysicsBodyInReach();
	/// if we hit smth then attach a physics handle
	if (HitResult.GetActor()) {
		auto ComponentToGrab = HitResult.GetComponent();
		PhysicsHandle->GrabComponent(
			ComponentToGrab,
			NAME_None, // no bones needed
			ComponentToGrab->GetOwner()->GetActorLocation(),
			true // allow rotation
		);
	}
}

void UGrabber::Release()
{
	PhysicsHandle->ReleaseComponent();
}

void UGrabber::FindPhysicsHandleComponent()
{/// Looks for attached physics handle
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Cannot find physical handler owned by %s."),
			*(GetOwner()->GetName()));
	}
}

void UGrabber::SetupInputComponent()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent)
	{
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Cannot find InputComponent owned by %s."), *(GetOwner()->GetName()));
	}
}

FTwoVectors UGrabber::GetLineTrace() const
{/// Get player view point
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation
	);
	FVector LineTraceEnd = PlayerViewPointLocation +
		PlayerViewPointRotation.Vector() * PlayerHandsLength;/// multiply unit vector to hands length 
	return FTwoVectors(PlayerViewPointLocation, LineTraceEnd);
}

FHitResult UGrabber::GetFirstPhysicsBodyInReach() const
{
	/// Setup query parameters
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());
	FHitResult Hit;
	/// Ray cast (line-trace) out to reach distance
	if (GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		GetLineTrace().v1,
		GetLineTrace().v2,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody)
	)) {
		FString HittedActor = Hit.GetActor()->GetName();
		UE_LOG(LogTemp, Warning, TEXT("Hitting %s"), *HittedActor);
	}
	/// See what we hit
	return Hit;
}
