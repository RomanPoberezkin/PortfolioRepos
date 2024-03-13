#include "TraceUtils.h"
#include  "DrawDebugHelpers.h"
#include "Kismet/KismetSystemLibrary.h"


bool TraceUtils::SweepCapsuleSingleByChannel(const UWorld* World, FHitResult& OutHit, const FVector& Start,
                                             const FVector& End, float CapsuleRadius, float CapsuleHalfHight, const FQuat& Rot, ECollisionChannel TraceChannel,
                                             const FCollisionQueryParams& Params, const FCollisionResponseParams& ResponseParam, bool bDrawDebug, float DrawTime,
                                             FColor TraceColor, FColor HitColor)
{
	bool bResult = false;

	FCollisionShape CollisionShape = FCollisionShape::MakeCapsule(CapsuleRadius, CapsuleHalfHight);
	bResult = World->SweepSingleByChannel(OutHit, Start, End, Rot, TraceChannel, CollisionShape, Params, ResponseParam);
	bool DrawDebug = bDrawDebug;

	if (DrawDebug)
	{
		DrawDebugCapsule (World, Start, CapsuleHalfHight, CapsuleRadius,FQuat::Identity, TraceColor, bDrawDebug, DrawTime );
		DrawDebugCapsule (World, End, CapsuleHalfHight, CapsuleRadius,FQuat::Identity, TraceColor, bDrawDebug, DrawTime );
		DrawDebugLine(World,Start, End, TraceColor, false, DrawTime);
		if (bResult)
		{
			DrawDebugCapsule (World, OutHit.Location, CapsuleHalfHight, CapsuleRadius,FQuat::Identity, HitColor, false, DrawTime );
			DrawDebugPoint(World, OutHit.ImpactPoint, 10.0f, HitColor, false, DrawTime );
		}	
	
	}

	
	return bResult;
}

bool TraceUtils::SweepSphereSingleByChannel(const UWorld* World, FHitResult& OutHit, const FVector& Start,
	const FVector& End, float Radius, ECollisionChannel TraceChannel, const FCollisionQueryParams& Params,
	const FCollisionResponseParams& ResponseParam, bool bDrawDebug, float DrawTime, FColor TraceColor, FColor HitColor)
{
	bool bResult = false;

	FCollisionShape CollisionShape = FCollisionShape::MakeSphere(Radius);
	bResult = World->SweepSingleByChannel(OutHit, Start, End, FQuat::Identity, TraceChannel, CollisionShape, Params, ResponseParam);

#if ENABLE_DRAW_DEBUG
	if (bDrawDebug)
	{
		FVector DebugCenter ((Start-End)*0.5f);
		FVector TraceVector = End - Start;
		float DebudDrawCapsuleHalfHeight = TraceVector.Size() *0.5f;

		FQuat DebugCapsuleRotation = FRotationMatrix::MakeFromZ(TraceVector).ToQuat();
		
		DrawDebugCapsule(World, DebugCenter, DebudDrawCapsuleHalfHeight, Radius, DebugCapsuleRotation, TraceColor, true, DrawTime);
	
		if (bResult)
		{
			DrawDebugSphere(World, OutHit.Location, Radius, 32, HitColor, false, DrawTime);
			DrawDebugPoint(World, OutHit.ImpactPoint, 10.0f, HitColor, false, DrawTime );
		}
	}
#endif

	return bResult;
	
}

bool TraceUtils::OverlapCapsuleAnyByProfile(const UWorld* World, const FVector& Position, float CapsuleRadius,
                                            float CapsuleHalfHeight, FQuat Rotation, FName ProfileName, const FCollisionQueryParams& QueryParams,
                                            bool bDrawDebug, float DrawTime, FColor HitColor)
{
	bool bResult = false;
	FCollisionShape CollisionShape = FCollisionShape::MakeCapsule(CapsuleRadius,CapsuleHalfHeight);
	bResult = World->OverlapAnyTestByProfile(Position, Rotation, ProfileName, CollisionShape, QueryParams);
	
#if ENABLE_DRAW_DEBUG
	if (bDrawDebug && bResult)
	{
		DrawDebugCapsule(World, Position, CapsuleHalfHeight, CapsuleRadius, Rotation, HitColor, false, DrawTime );
	}
#endif
	
	return bResult;
}

bool TraceUtils::OverlapCapsuleBlockingByProfile(const UWorld* World, const FVector& Position, float CapsuleRadius,
	float CapsuleHalfHeight, FQuat Rotation, FName ProfileName, const FCollisionQueryParams& QueryParams,
	bool bDrawDebug, float DrawTime, FColor HitColor)
{
	bool bResult = false;
	FCollisionShape CollisionShape = FCollisionShape::MakeCapsule(CapsuleRadius,CapsuleHalfHeight);
	bResult = World->OverlapBlockingTestByProfile(Position, Rotation, ProfileName, CollisionShape, QueryParams);
	
#if ENABLE_DRAW_DEBUG
	if (bDrawDebug && bResult)
	{
		DrawDebugCapsule(World, Position, CapsuleHalfHeight, CapsuleRadius, Rotation, HitColor, false, DrawTime );
	}
#endif
	
	return bResult;
}

bool TraceUtils::BoxTraceByChannel(const UWorld* World, const FVector Start, const FVector End, const FVector HalfSize,
	const FRotator BoxRotation, FHitResult& HitResult, const TArray<AActor*>& ActorsToIgnore, bool bIgnoreSelf, bool TraceComplex,
	bool DrawDebug, float DrawTime, ETraceTypeQuery TraceChannel, FLinearColor TraceColor, FLinearColor TraceHitColor)
{
	bool Result;
	EDrawDebugTrace::Type DrawTrace;
	DrawTrace = DrawDebug? EDrawDebugTrace::ForDuration : EDrawDebugTrace::None;

	Result =  UKismetSystemLibrary::BoxTraceSingle(World,Start,End, HalfSize, BoxRotation, TraceChannel, TraceComplex, ActorsToIgnore, DrawTrace, HitResult, bIgnoreSelf, TraceColor, TraceHitColor, DrawTime );



	return Result;
}
