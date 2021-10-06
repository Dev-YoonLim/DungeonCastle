// Fill out your copyright notice in the Description page of Project Settings.


#include "RogueMovementComponent.h"

void URogueMovementComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (!PawnOwner || !UpdatedComponent || ShouldSkipUpdate(DeltaTime)) {
		return;
	}

	FVector DesiredMovementthisFrame = ConsumeInputVector().GetClampedToMaxSize(1.0f) * DeltaTime * 150.0f;
	if (!DesiredMovementthisFrame.IsNearlyZero()) {
		FHitResult Hit;
		SafeMoveUpdatedComponent(DesiredMovementthisFrame, UpdatedComponent->GetComponentRotation(), true, Hit);
		if (Hit.IsValidBlockingHit()) {
			SlideAlongSurface(DesiredMovementthisFrame, 1.0f - Hit.Time, Hit.Normal, Hit);
		}
	}
}