// Fill out your copyright notice in the Description page of Project Settings.


#include "TestGameInstance.h"
#include "MoviePlayer.h"
#include "SLoadingScreen.h"

void UTestGameInstance::Init()
{
	Super::Init();

	FCoreUObjectDelegates::PreLoadMap.AddUObject(this, &UTestGameInstance::BeginLoadingScreen);
	FCoreUObjectDelegates::PostLoadMapWithWorld.AddUObject(this, &UTestGameInstance::EndLoadingScreen);
}

void UTestGameInstance::BeginLoadingScreen(const FString& MapName)
{
	if (!IsRunningDedicatedServer())
	{
		FLoadingScreenAttributes LoadingScreen;
		LoadingScreen.MinimumLoadingScreenDisplayTime = MinimumLoadingScreenDisplayTime;
		LoadingScreen.bAutoCompleteWhenLoadingCompletes = false;
		LoadingScreen.WidgetLoadingScreen = SNew(SLoadingScreen).MapName(MapName);
 
		GetMoviePlayer()->SetupLoadingScreen(LoadingScreen);
	}
}

void UTestGameInstance::EndLoadingScreen(UWorld* InLoadedWorld)
{
}
