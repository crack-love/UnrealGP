#include "GpCharacter.h"

#include "Components/SkeletalMeshComponent.h"
//#include "GameFramework/SpringArmComponent.h"

#include "Gp/GpPlayerController.h"
#include "Gp/CharacterView/GpCharacterViewManager.h"
//#include "GpCharacterAnim.h"
//#include "Gp/CameraView/GpCharacterView.h"

AGpCharacter::AGpCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	USkeletalMeshComponent* SkeletalMesh = GetMesh();
	SkeletalMesh->SetRelativeLocationAndRotation(FVector(0,0,-85), FRotator(0,-90,0));

	//CC = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMM"));
	//CC->SetupAttachment(RootComponent);
}

void AGpCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	//AGpPlayerController* Con = Cast<AGpPlayerController>(NewController);
	//Con->GetCharacterViewManager()->SetView(TEXT("ThirdPerson"), this);
	//RegisterAllComponents();
}

void AGpCharacter::UnPossessed()
{
	Super::UnPossessed();
}
