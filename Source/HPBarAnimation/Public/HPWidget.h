// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HPWidget.generated.h"

class UProgressBar;
/**
 * 
 */
UCLASS()
class HPBARANIMATION_API UHPWidget : public UUserWidget
{
	GENERATED_BODY()

public:	
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void UpdateHealth(float Damage);

	UFUNCTION(BlueprintCallable)
	void UpdateBarPercent(int32 RoundedBar, float RemainBar);

	UPROPERTY(Transient, BlueprintReadWrite)
	TArray<UProgressBar*> AllBars;
	
	UPROPERTY(Transient, BlueprintReadWrite)
	int32 BarTarget = 0;

	UPROPERTY(Transient, BlueprintReadWrite)
	float CurrentHealth;

	UPROPERTY(Transient, BlueprintReadWrite)
	float MaxHealth;
	
	UProgressBar* LastBar;
	float Target = 0.f;
	float Start = 0.f;
};
