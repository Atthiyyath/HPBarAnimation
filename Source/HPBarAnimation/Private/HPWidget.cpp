// Fill out your copyright notice in the Description page of Project Settings.


#include "HPWidget.h"

#include "FCTween.h"
#include "Components/ProgressBar.h"

void UHPWidget::UpdateBarPercent(int32 RoundedBar, float RemainBar)
{
	if (RoundedBar < BarTarget)
	{
		UE_LOG(LogTemp, Warning, TEXT("BarTarget : %d"), BarTarget);
		UE_LOG(LogTemp, Warning, TEXT("RoundedBar : %d"), RoundedBar);
		LastBar = AllBars[BarTarget - 1];
		Target = RoundedBar == BarTarget - 1 ? RemainBar : 0.f;
		Start = LastBar->GetPercent();
	
		FCTween::Play(Start, Target,[&](float t)
		{
			LastBar->SetPercent(t);
		},1.f, EFCEase::Linear)->SetOnComplete([=]
		{
			BarTarget--;
			UpdateBarPercent(RoundedBar, RemainBar);
		});
	}
}
