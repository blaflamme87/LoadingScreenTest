// Fill out your copyright notice in the Description page of Project Settings.


#include "TestGameInstance.h"

void UTestGameInstance::Init()
{
	Super::Init();

	FCoreUObjectDelegates::PreLoadMap.AddUObject(this, &UTestGameInstance::BeginLoadingScreen);
	FCoreUObjectDelegates::PostLoadMapWithWorld.AddUObject(this, &UTestGameInstance::EndLoadingScreen);
}

void UTestGameInstance::BeginLoadingScreen(const FString& MapName)
{
}

void UTestGameInstance::EndLoadingScreen(UWorld* InLoadedWorld)
{
}
