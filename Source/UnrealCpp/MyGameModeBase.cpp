// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameModeBase.h"
#include "MyCharacter.h"

AMyGameModeBase::AMyGameModeBase()
{
	
	//DefaultPawnClass = AMyCharacter::StaticClass();
	static ConstructorHelpers::FClassFinder<AMyCharacter> BP_Player(TEXT("/Script/Engine.Blueprint'/Game/BluePrint/BP_Player.BP_Player_C'"));
	
	if (BP_Player.Succeeded())
	{
		DefaultPawnClass = BP_Player.Class;
	}
	

}
