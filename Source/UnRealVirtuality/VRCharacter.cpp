// Fill out your copyright notice in the Description page of Project Settings.

#include "VRCharacter.h"
#include "Camera/CameraComponent.h"
#include "NavigationSystem.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "DrawDebugHelpers.h"
#include "Components/SplineComponent.h"
#include "EngineUtils.h"
#include "AirBalloonBasket.h"
#include "MotionControllerComponent.h"
// Sets default values
AVRCharacter::AVRCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	VRRoot = CreateDefaultSubobject<USceneComponent>(TEXT("VRRoot"));
	VRRoot->SetupAttachment(GetRootComponent());

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(VRRoot);

	LeftController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("LeftController"));
	LeftController->SetupAttachment(VRRoot);
	LeftController->SetTrackingSource(EControllerHand::Left);
	LeftController->bDisplayDeviceModel = true;

	RightController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("RightController"));
	RightController->SetupAttachment(VRRoot);
	RightController->SetTrackingSource(EControllerHand::Right);
	RightController->bDisplayDeviceModel = true;

	TeleportPath = CreateDefaultSubobject<USplineComponent>(TEXT("TeleportPath"));
	TeleportPath->SetupAttachment(VRRoot);

	DestinationMarker = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DestinationMarker"));
	DestinationMarker->SetupAttachment(GetRootComponent());



}

// Called when the game starts or when spawned
void AVRCharacter::BeginPlay()
{
	Super::BeginPlay();
	DestinationMarker->SetVisibility(false);
	for (TActorIterator<AAirBalloonBasket> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		AAirBalloonBasket*_airBalloonBasket = Cast<AAirBalloonBasket>(*ActorItr);
	if (_airBalloonBasket)
	{
		AirBalloon = _airBalloonBasket;
	}
	}
	/*
	LeftController = GetWorld()->SpawnActor<AHandController>();
	if ( LeftController != nullptr ) {

		LeftController->AttachToComponent(VRRoot,FAttachmentTransformRules::KeepRelativeTransform);
		LeftController->SetHand(EControllerHand::Left);
		LeftController->SetOwner(this);
	}


	RightController = GetWorld()->SpawnActor<AHandController>();
	if ( RightController != nullptr ) {

		RightController->AttachToComponent(VRRoot,FAttachmentTransformRules::KeepRelativeTransform);
		RightController->SetHand(EControllerHand::Right);
		RightController->SetOwner(this);
	}


	*/
	CachedRotation = GetActorRotation();
	CachedLocation = GetActorLocation();

}
/*
float AVRCharacter::GetScalar_TiltSpeed(float DeltaTime) {

	float scalar = 0;
	DeltaRotation = UKismetMathLibrary::NormalizedDeltaRotator(Camera->GetComponentRotation(),CachedRotation);
	CachedRotation = GetActorRotation();
	scalar = DeltaRotation.Roll * DeltaTime;
	return scalar;
}

float AVRCharacter::GetScalar_TiltDegrees() {

	float scalar = 0;
	FVector LeftForward = (FVector)LeftController->GetForwardVector().Normalize();
	FVector LeftToRight = (FVector)(RightController->GetComponentLocation() - LeftController->GetComponentLocation()).Normalize();

	scalar = UKismetMathLibrary::Acos(FVector::DotProduct(LeftForward,LeftToRight));

	return scalar;
}

*/

FVector AVRCharacter::GetPositionAndTiltDirection() {

	
	FVector diff = (FVector)(RightController->GetComponentLocation() - LeftController->GetComponentLocation());
	FVector dir = (FVector)diff.Normalize();
	FVector scale = (FVector)diff.Size()*0.5;
	FVector controllerCenter = LeftController->GetComponentLocation() + dir * scale;
	FVector diff2 = (FVector)(Camera->GetComponentLocation() - controllerCenter);
	FVector dir2 = (FVector)diff2.Normalize();
	FVector scale2 = (FVector)diff2.Size()*0.5;
	FVector deviceCenter = controllerCenter + dir2 * scale2; // 
	FVector diff3 = (FVector)(deviceCenter - GetRootComponent()->GetComponentLocation());
	FVector dir3 =(FVector) diff3.Normalize();
	return (FVector)(deviceCenter + dir3 * diff3.Size());

}

float AVRCharacter::GetMoveSpeed(FVector velocity, float DeltaTime) {

	return (float)((velocity - CachedLocation).Size() * DeltaTime);
}

	
// Called every frame
void AVRCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector NewCameraOffset = Camera->GetComponentLocation() - GetActorLocation();
	NewCameraOffset.Z = 0;
	AddActorWorldOffset(NewCameraOffset);
	VRRoot->AddWorldOffset(-NewCameraOffset);

	FVector newPos = GetPositionAndTiltDirection();
	FHitResult HitResult;
	bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, Camera->GetComponentLocation() , newPos, ECollisionChannel::ECC_Visibility);
	DrawDebugLine(GetWorld(),Camera->GetComponentLocation(),newPos,FColor::Red,false,1.0,2.0);

	float speed = GetMoveSpeed(newPos,DeltaTime);

	FVector FinalLocation = (newPos*speed);

	CachedLocation = newPos;

	UpdateDestinationMarker();
	/*
	float degrees = 0;
	int direction = IsLeaning(degrees);
	if (  direction != 0 ) {
		if ( direction > 0 ) {
			UE_LOG(LogTemp,Warning,TEXT("Tilt Right"));
		} else if ( direction < 0 ) {
			UE_LOG(LogTemp,Warning,TEXT("Tilt Left"));
		}
	} else {
			UpdateDestinationMarker();
	}
*/
	
}

// Called to bind functionality to input
void AVRCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("RightTriggerAxis", this, &AVRCharacter::throttle);
}


bool AVRCharacter::FindTeleportDestination(TArray<FVector> &OutPoints, FVector &OutLocation) 
{

	FHitResult HitResult;
	FVector Start = RightController->GetComponentLocation();
	FVector Look = RightController->GetForwardVector();
	Look = Look.RotateAngleAxis(30,RightController->GetRightVector());
	FVector End = Start * Look * MaxTeleportDistance;


	FPredictProjectilePathParams Params(
		TeleportProjectileRadius,
		RightController->GetComponentLocation(),
		Look * TeleportProjectileSpeed,
		TeleportSimulationTime,
		ECollisionChannel::ECC_Visibility,
		this
	);

	Params.DrawDebugType = EDrawDebugTrace::ForOneFrame;
	Params.bTraceComplex = true;
	//Params.DrawDebugTime = 1.0f;

	FPredictProjectilePathResult Result;


	//bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECollisionChannel::ECC_Visibility);
	//DrawDebugLine(GetWorld(),Start,End,FColor::Red,false,1.0,2.0);

	
	bool bHit = UGameplayStatics::PredictProjectilePath(this,Params,Result);
	if ( !bHit ) 
		return false;

	for ( FPredictProjectilePathPointData Point : Result.PathData) {
		OutPoints.Add(Point.Location);
	}


	FNavLocation NavLocation;
	bool bOnNavMesh = UNavigationSystemV1::GetCurrent(GetWorld())->ProjectPointToNavigation(Result.HitResult.Location,NavLocation,TeleportProjectionExtent);
	if ( !bOnNavMesh ) 
		return false;


	OutLocation = NavLocation.Location;

	return true;

}


void AVRCharacter::UpdateSpline(const TArray<FVector> &Path) {

	TeleportPath->ClearSplinePoints(false);
	int i = 0;
	for ( FVector Point : Path) 
	{

		//FVector LocalPosition = TeleportPath->GetComponentTransform().InverseTransformPosition(Path[i]);

		TeleportPath->AddPoint(FSplinePoint(i++,Point,ESplinePointType::Curve),false);

	}

	TeleportPath->UpdateSpline();
}

void AVRCharacter::UpdateDestinationMarker() {

	FVector Location;
	TArray<FVector> Path; 
	bool bHasDestination = FindTeleportDestination(Path, Location);
	if (bHasDestination ) {

		DestinationMarker->SetVisibility(true);
		DestinationMarker->SetWorldLocation(Location);

		//UpdateSpline(Path);

	} else {
		DestinationMarker->SetVisibility(false);
		
	}
}

void AVRCharacter::throttle(float axis) {

	if (AirBalloon==nullptr)
		return;

		AirBalloon->throttle(axis);
}

void AVRCharacter::BeginTeleport() {

	APlayerController* PC = Cast<APlayerController>(GetController());

	if ( PC != nullptr ) {

		PC->PlayerCameraManager->StartCameraFade(0,1,TeleportFadeTime,FLinearColor::Black);
	
	}

	FTimerHandle Handle;
	GetWorldTimerManager().SetTimer(Handle,this,&AVRCharacter::FinishTeleport, TeleportFadeTime);
}

void AVRCharacter::FinishTeleport() {
	
	SetActorLocation(DestinationMarker->GetComponentLocation());

	APlayerController* PC = Cast<APlayerController>(GetController());

	if ( PC != nullptr ) {

		PC->PlayerCameraManager->StartCameraFade(1,-1,TeleportFadeTime,FLinearColor::Black);
	
	}
}