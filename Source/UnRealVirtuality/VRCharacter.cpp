// Fill out your copyright notice in the Description page of Project Settings.

#include "VRCharacter.h"
#include "Camera/CameraComponent.h"
#include "NavigationSystem.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "DrawDebugHelpers.h"
#include "Components/SplineComponent.h"
#include "HandController.h"

// Sets default values
AVRCharacter::AVRCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	VRRoot = CreateDefaultSubobject<USceneComponent>(TEXT("VRRoot"));
	VRRoot->SetupAttachment(GetRootComponent());

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(VRRoot);

	//LeftController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("LeftController"));
	//LeftController->SetupAttachment(VRRoot);
	//LeftController->SetTrackingSource(EControllerHand::Left);
	//LeftController->bDisplayDeviceModel = true;

	//RightController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("RightController"));
	//RightController->SetupAttachment(VRRoot);
	//RightController->SetTrackingSource(EControllerHand::Right);
	//RightController->bDisplayDeviceModel = true;

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

}

// Called every frame
void AVRCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector NewCameraOffset = Camera->GetComponentLocation() - GetActorLocation();
	NewCameraOffset.Z = 0;
	AddActorWorldOffset(NewCameraOffset);
	VRRoot->AddWorldOffset(-NewCameraOffset);

	UpdateDestinationMarker();
}

// Called to bind functionality to input
void AVRCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


bool AVRCharacter::FindTeleportDestination(TArray<FVector> &OutPoints, FVector &OutLocation) 
{

	FHitResult HitResult;
	FVector Start = RightController->GetActorLocation();
	FVector Look = RightController->GetActorForwardVector();
	Look = Look.RotateAngleAxis(30,RightController->GetActorRightVector());
	FVector End = Start * Look * MaxTeleportDistance;


	FPredictProjectilePathParams Params(
		TeleportProjectileRadius,
		RightController->GetActorLocation(),
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