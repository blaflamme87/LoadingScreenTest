// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "LoadingScreenConfig.h"
#include "MoviePlayer.h"
#include "Widgets/Images/SThrobber.h"

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

    void Construct(const FArguments& InArgs)
    {
        FString MapName = InArgs._MapName;
        
        const ULoadingScreenConfig* Settings = ULoadingScreenConfig::Get();
        if (!Settings) { return; }

        // Get object path from the map name
        FSoftObjectPath MapPath(MapName);
        FString AssetPathString = FPackageName::ObjectPathToPackageName(MapPath.ToString());
        FString AssetName = FPackageName::GetShortName(AssetPathString);
        FString FullObjectPathString = FString::Printf(TEXT("%s.%s"), *AssetPathString, *AssetName);
        FSoftObjectPath FullObjectPath(FullObjectPathString);

        // Use Contains to check if the TMap has a brush for the full object path
        const FSlateBrush* MapBrush = nullptr;
        if (Settings->MapBrushes.Contains(FullObjectPath))
        {
            MapBrush = &Settings->MapBrushes[FullObjectPath];
        }
        else
        {
            MapBrush = &Settings->LoadingScreenBrushDefault;
        }
        
        SelectedLoadingText = GetRandomLoadingText();
        
        ChildSlot
        [
            SNew(SOverlay)
            + SOverlay::Slot()
            [
                SNew(SImage).Image(MapBrush)
            ]
            + SOverlay::Slot()
            .VAlign(VAlign_Center)
            .HAlign(HAlign_Center)
            .Padding(FMargin(0, 0, 0, 50)) 
            [
                SNew(SThrobber)
                .Visibility(this, &SLoadingScreen::GetLoadIndicatorVisibility)
            ]
            + SOverlay::Slot()
            .VAlign(VAlign_Bottom)
            .HAlign(HAlign_Center)
            .Padding(FMargin(0, 0, 0, 50))
            [
                SNew(STextBlock)
                .Text(this, &SLoadingScreen::GetSelectedLoadingText)
                .Font(Settings->LoadingScreenFont)
                .Justification(ETextJustify::Center)
                .RenderTransformPivot(FVector2D(0.5f, 1.0f))  // Pivot at (0.5, 1)
                .Visibility(this, &SLoadingScreen::GetMessageIndicatorVisibility)
            ]
        ];
    }

private:

    FText SelectedLoadingText;
    
    EVisibility GetLoadIndicatorVisibility() const
    {
        return GetMoviePlayer()->IsLoadingFinished() ? EVisibility::Collapsed : EVisibility::Visible;
    }

    EVisibility GetMessageIndicatorVisibility() const
    {
        return EVisibility::Visible;
    }

    FText GetRandomLoadingText() const
    {
        const TArray<FText>& Texts = ULoadingScreenConfig::Get()->LoadingScreenTexts;
        if (Texts.Num() > 0)
        {
            int32 Index = FMath::RandRange(0, Texts.Num() - 1);
            return Texts[Index];
        }
        return FText::FromString(TEXT("Loading...")); // Default text
    }
    
    FText GetSelectedLoadingText() const
    {
        return SelectedLoadingText;
    }

};
