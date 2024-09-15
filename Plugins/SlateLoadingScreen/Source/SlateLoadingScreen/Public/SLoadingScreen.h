// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class SLATELOADINGSCREEN_API SLoadingScreen : public SCompoundWidget
{
public:

	SLATE_BEGIN_ARGS(SLoadingScreen) {}
		SLATE_ARGUMENT(FString, MapName)
	SLATE_END_ARGS()
	
	SLoadingScreen();
	~SLoadingScreen();
};
