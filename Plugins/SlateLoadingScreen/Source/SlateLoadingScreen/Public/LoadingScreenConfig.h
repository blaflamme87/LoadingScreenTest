// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "LoadingScreenConfig.generated.h"

/**
 * 
 */
UCLASS(Config=Game, defaultconfig)
class SLATELOADINGSCREEN_API ULoadingScreenConfig : public UDeveloperSettings
{
	GENERATED_BODY()
	
public:

	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly)
	TMap<FSoftObjectPath, FSlateBrush> MapBrushes;
	
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly)
	FSlateBrush LoadingScreenBrushDefault;

	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly)
	TArray<FText> LoadingScreenTexts;

	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly)
	FSlateFontInfo LoadingScreenFont;

	UFUNCTION(BlueprintPure)
	static const ULoadingScreenConfig* Get()
	{
		return GetDefault<ULoadingScreenConfig>();
	}
	
};
