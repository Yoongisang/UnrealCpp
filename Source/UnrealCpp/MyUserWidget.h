// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MyUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class UNREALCPP_API UMyUserWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY()
	class UMyActorComponent* MyActorComp;
	UPROPERTY(meta = (BindWidget))
	class UProgressBar* HP_ProgressBar;
public:
	void BindHp(class UMyActorComponent* ActorComp);
	void UpdateHp();
};
