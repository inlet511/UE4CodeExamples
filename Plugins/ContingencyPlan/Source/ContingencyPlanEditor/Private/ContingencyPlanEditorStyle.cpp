// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "ContingencyPlanEditorStyle.h"
#include "ContingencyPlanEditor.h"
#include "Framework/Application/SlateApplication.h"
#include "Styling/SlateStyleRegistry.h"
#include "Slate/SlateGameResources.h"
#include "Interfaces/IPluginManager.h"

TSharedPtr< FSlateStyleSet > FContingencyPlanEditorStyle::StyleInstance = NULL;

void FContingencyPlanEditorStyle::Initialize()
{
	if (!StyleInstance.IsValid())
	{
		StyleInstance = Create();
		FSlateStyleRegistry::RegisterSlateStyle(*StyleInstance);
	}
}

void FContingencyPlanEditorStyle::Shutdown()
{
	FSlateStyleRegistry::UnRegisterSlateStyle(*StyleInstance);
	ensure(StyleInstance.IsUnique());
	StyleInstance.Reset();
}

FName FContingencyPlanEditorStyle::GetStyleSetName()
{
	static FName StyleSetName(TEXT("ContingencyPlanEditorStyle"));
	return StyleSetName;
}

#define IMAGE_BRUSH( RelativePath, ... ) FSlateImageBrush( Style->RootToContentDir( RelativePath, TEXT(".png") ), __VA_ARGS__ )
#define BOX_BRUSH( RelativePath, ... ) FSlateBoxBrush( Style->RootToContentDir( RelativePath, TEXT(".png") ), __VA_ARGS__ )
#define BORDER_BRUSH( RelativePath, ... ) FSlateBorderBrush( Style->RootToContentDir( RelativePath, TEXT(".png") ), __VA_ARGS__ )
#define TTF_FONT( RelativePath, ... ) FSlateFontInfo( Style->RootToContentDir( RelativePath, TEXT(".ttf") ), __VA_ARGS__ )
#define OTF_FONT( RelativePath, ... ) FSlateFontInfo( Style->RootToContentDir( RelativePath, TEXT(".otf") ), __VA_ARGS__ )

const FVector2D Icon16x16(16.0f, 16.0f);
const FVector2D Icon20x20(20.0f, 20.0f);
const FVector2D Icon40x40(40.0f, 40.0f);
const FVector2D Icon512x512(512.0f, 512.0f);

TSharedRef< FSlateStyleSet > FContingencyPlanEditorStyle::Create()
{
	TSharedRef< FSlateStyleSet > Style = MakeShareable(new FSlateStyleSet("ContingencyPlanEditorStyle"));
	Style->SetContentRoot(IPluginManager::Get().FindPlugin("ContingencyPlan")->GetBaseDir() / TEXT("Resources"));

	Style->Set("ContingencyPlanEditor.PluginAction", new IMAGE_BRUSH(TEXT("ButtonIcon_40x"), Icon40x40));
	Style->Set("ContingencyPlanEditor.TaskIcon", new IMAGE_BRUSH(TEXT("TaskIcon_512"), Icon512x512));

	return Style;
}

#undef IMAGE_BRUSH
#undef BOX_BRUSH
#undef BORDER_BRUSH
#undef TTF_FONT
#undef OTF_FONT

void FContingencyPlanEditorStyle::ReloadTextures()
{
	if (FSlateApplication::IsInitialized())
	{
		FSlateApplication::Get().GetRenderer()->ReloadTextureResources();
	}
}

const ISlateStyle& FContingencyPlanEditorStyle::Get()
{
	return *StyleInstance;
}
