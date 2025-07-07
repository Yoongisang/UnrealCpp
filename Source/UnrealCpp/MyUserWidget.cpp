// Fill out your copyright notice in the Description page of Project Settings.


#include "MyUserWidget.h"
#include "Components/ProgressBar.h"
#include "MyActorComponent.h"

void UMyUserWidget::BindHp(UMyActorComponent* ActorComp)
{
	MyActorComp = ActorComp;
	MyActorComp->OnHpChanged.AddUObject(this, &UMyUserWidget::UpdateHp);

}

void UMyUserWidget::UpdateHp()
{
	HP_ProgressBar->SetPercent(MyActorComp->GetHpRatio());
}


