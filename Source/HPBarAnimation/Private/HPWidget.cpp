// Fill out your copyright notice in the Description page of Project Settings.


#include "HPWidget.h"

#include "FCTween.h"
#include "Components/ProgressBar.h"

void UHPWidget::UpdateBarPercent(int32 RoundedBar, float RemainBar)
{
	// 5.7 out of 10
	// Rounded = 5, Remain = 0.7

	/*for (int32 i = AllBars.Num(); i > RoundedBar; --i)
	{
		auto LastBar = AllBars[i - 1];
		const float Target = RoundedBar == i - 1 ? RemainBar : 0.f;
		
		if (i == RoundedBar + 1)
		{
			auto RemainingBar = AllBars[i];
			RemainingBar->SetBarFillType(EProgressBarFillType::LeftToRight);
			RemainingBar->SetPercent(Target);
		}

		if (RoundedBar <= i)
		{
			LastBar->SetPercent(Target);
		}
	}*/
	
	/*UE_LOG(LogTemp, Warning, TEXT("BarTarget : %d"), BarTarget);*/

	if (AllBars.IsEmpty()) return;
	
	if (RoundedBar < BarTarget)
	{
		LastBar = AllBars[BarTarget - 1];
		Target = RoundedBar == BarTarget - 1 ? RemainBar : 0.f;
		Start = LastBar->GetPercent();
		UE_LOG(LogTemp, Warning, TEXT("BarTarget : %d"), BarTarget);
	
		/*if (BarTarget == RoundedBar + 1)
		{
			auto RemainingBar = AllBars[BarTarget];
			RemainingBar->SetBarFillType(EProgressBarFillType::LeftToRight);
			RemainingBar->SetPercent(Target);
		}*/
	
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
