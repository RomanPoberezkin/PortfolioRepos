#pragma once
#include "Engine/World.h"

namespace TraceUtils
{
	bool SweepCapsuleSingleByChannel (const UWorld* World, struct FHitResult& OutHit, const FVector& Start, const FVector& End, float CapsuleRadius, float CapsuleHalfHight,  const FQuat& Rot, ECollisionChannel TraceChannel, const FCollisionQueryParams& Params = FCollisionQueryParams::DefaultQueryParam, const FCollisionResponseParams& ResponseParam = FCollisionResponseParams::DefaultResponseParam, bool bDrawDebug = false, float DrawTime = 1.0f, FColor TraceColor = FColor::Blue, FColor HitColor = FColor::Red );

	bool SweepSphereSingleByChannel (const UWorld* World, struct FHitResult& OutHit, const FVector& Start, const FVector& End, float Radius, ECollisionChannel TraceChannel, const FCollisionQueryParams& Params = FCollisionQueryParams::DefaultQueryParam, const FCollisionResponseParams& ResponseParam = FCollisionResponseParams::DefaultResponseParam, bool bDrawDebug = false, float DrawTime = -1.0f, FColor TraceColor = FColor::Black, FColor HitColor = FColor::Red );

	bool OverlapCapsuleAnyByProfile (const UWorld* World, const FVector& Position, float CapsuleRadius, float CapsuleHalfHeight, FQuat Rotation, FName ProfileName, const FCollisionQueryParams& QueryParams, bool bDrawDebug = false, float DrawTime = 0.1f, FColor HitColor = FColor::Red);
	
	bool OverlapCapsuleBlockingByProfile (const UWorld* World, const FVector& Position, float CapsuleRadius, float CapsuleHalfHeight, FQuat Rotation, FName ProfileName, const FCollisionQueryParams& QueryParams, bool bDrawDebug = false, float DrawTime = 0.1f, FColor HitColor = FColor::Red);

	bool BoxTraceByChannel (const UWorld* World, const FVector Start, const FVector End, const FVector HalfSize, const FRotator BoxRotation, FHitResult& HitResult, const TArray<AActor*>& ActorsToIgnore, bool bIgnoreSelf = true, bool TraceComplex = false, bool DrawDebug = true, float DrawTime = 1, ETraceTypeQuery TraceChannel = TraceTypeQuery1,  FLinearColor TraceColor = FColor::Green, FLinearColor TraceHitColor = FColor::Red );
}
