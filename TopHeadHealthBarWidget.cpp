// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/TopHeadHealthBarWidget.h"
#include "FCTween.h"
#include "Brushes/SlateImageBrush.h"
#include "Components/Image.h"
#include "Components/ProgressBar.h"

void UTopHeadHealthBarWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UTopHeadHealthBarWidget::Init(float InMax, TArray<UProgressBar*> Bars)
{
	Max = InMax;
	AllBars = Bars;
	Current = 0;
	
	for (UProgressBar* AllBar : AllBars)
	{
		AllBar->SetPercent(1.f);
	}

	Current = Max;
	LastBarIndexSet = AllBars.Num();
}

void UTopHeadHealthBarWidget::InitBackgroundBars(TArray<UProgressBar*> Bars)
{
	BackgroundBars = Bars;
	LastBarBgIndexSet = BackgroundBars.Num();
}

void UTopHeadHealthBarWidget::BarPercentUpdate(int32 BarIndexTarget, float Remainer)
{	
	if (BarIndexTarget == AllBars.Num())
	{
		for (UProgressBar* AllBar : AllBars)
		{
			auto Start = AllBar->GetPercent();
			FCTween::Play(Start, 1.f,[=](float t)
			{
				AllBar->SetPercent(t);
			},1.f, EFCEase::Linear);

			LastBarIndexSet = AllBars.Num();
		}
		
		return;
	}

	if (BarIndexTarget > LastBarIndexSet)
	{
		auto LastBar = AllBars[LastBarIndexSet + 1];
		auto Target = BarIndexTarget == LastBarIndexSet + 1 ? Remainer : 0.f;
		auto Start = LastBar->GetPercent();
		
		FCTween::Play(Start, Target,[=](float t)
		{
			LastBar->SetPercent(t);
		},1.f, EFCEase::Linear)->SetOnComplete([=]
		{
			LastBarIndexSet++;
			BarPercentUpdate(BarIndexTarget, Remainer);
		});
		
		return;
	}
	
	if (BarIndexTarget < LastBarIndexSet)
	{
		UProgressBar* LastBar = AllBars[LastBarIndexSet - 1];
		auto Target = BarIndexTarget == LastBarIndexSet - 1 ? Remainer : 0.f;
		auto Start = LastBar->GetPercent();
		
		FCTween::Play(Start, Target,[=](float t)
		{
			if (LastBarIndexSet != AllBars.Num())
			{
				UProgressBar* LastBarUpdate = AllBars[LastBarIndexSet];
				if (LastBarUpdate->GetPercent() <= 0.3f && !OnceLoop /*>= 0.f*/)
				{
					OnceLoop = true;
					float LastBarPercent = LastBarUpdate->GetPercent();
					FCTween::Play(LastBarPercent, 0.f,[=](float t2)
					{
						AllBars[LastBarIndexSet]->SetPercent(t2);
					}, 1.f, EFCEase::Linear);
				}
			}
			
			if (t <= 0.3)
			{
				BarPercentUpdate(BarIndexTarget, Remainer);
				if (LastBarIndexSet == BarIndexTarget)
				{
					OnceLoop = false;
				}
				return;
			}
			LastBar->SetPercent(t);
		},1.f, EFCEase::Linear)->SetOnComplete([=]
		{
			LastBarIndexSet--;
			BarPercentUpdate(BarIndexTarget, Remainer);
		});
	}
	else
	{
		LastBarIndexSet++;
	}
}

void UTopHeadHealthBarWidget::UpdateBackgroundBar(int BarIndexTarget, const float Remainer)
{
	/*GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Cyan, FString::Printf(TEXT("BarIndexTarget : %d"), BarIndexTarget));
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Cyan, FString::Printf(TEXT("Remainer : %f"), Remainer));
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Cyan, FString::Printf(TEXT("LastBarBgIndexSet : %d"), LastBarBgIndexSet));*/
	if (BarIndexTarget == BackgroundBars.Num())
	{
		for (UProgressBar* AllBar : BackgroundBars)
		{
			auto Start = AllBar->GetPercent();
			FCTween::Play(Start, 1.f,[=](float t)
			{
				AllBar->SetPercent(t);
			},1.f, EFCEase::Linear);

			LastBarBgIndexSet = BackgroundBars.Num();
		}
		
		return;
	}

	if (BarIndexTarget > LastBarBgIndexSet)
	{
		auto LastBar = BackgroundBars[LastBarBgIndexSet + 1];
		auto Target = BarIndexTarget == LastBarBgIndexSet + 1 ? Remainer : 0.f;
		auto Start = LastBar->GetPercent();
		
		FCTween::Play(Start, Target,[=](float t)
		{
			LastBar->SetPercent(t);
		},1.f, EFCEase::Linear)->SetOnComplete([=]
		{
			LastBarBgIndexSet++;
			BarPercentUpdate(BarIndexTarget, Remainer);
		});
		
		return;
	}
	
	if (BarIndexTarget < LastBarBgIndexSet)
	{
		auto LastBar = BackgroundBars[LastBarBgIndexSet - 1];
		auto Target = BarIndexTarget == LastBarBgIndexSet - 1 ? Remainer : 0.f;
		auto Start = LastBar->GetPercent();
		
		FCTween::Play(Start, Target,[=](float t)
		{
			LastBar->SetPercent(t);
		},1.f, EFCEase::Linear)->SetOnComplete([=]
		{
			LastBarBgIndexSet--;
			BarPercentUpdate(BarIndexTarget, Remainer);
		});
	}
	else
	{
		LastBarBgIndexSet++;
	}
}

void UTopHeadHealthBarWidget::SetPanelColor(ETeam TeamColor)
{
	OnInit();
	if (AllBars.IsEmpty()) return;
	for (UProgressBar* AllBar : AllBars)
	{
		if (!IsValid(AllBar)) return;
		FProgressBarStyle Style = AllBar->GetWidgetStyle();
		FSlateImageBrush Background = FSlateImageBrush(BackgroundPanel, FVector2d(32, 29));
		FSlateImageBrush RedPanel = FSlateImageBrush(RedPanelColor, FVector2d(32, 29));
		FSlateImageBrush BluePanel = FSlateImageBrush(BluePanelColor, FVector2d(32, 29));
		Style.SetBackgroundImage(Background);
		if (TeamColor == ETeam::ET_RED)
		{
			Backdrop->SetBrushFromTexture(RedPanelHPBar); // yellow
			Style.SetFillImage(RedPanel);
		}
		else
		{
			Backdrop->SetBrushFromTexture(BluePanelHPBar); // cyan
			Style.SetFillImage(BluePanel);
		}		
		AllBar->SetWidgetStyle(Style);
	}
}
