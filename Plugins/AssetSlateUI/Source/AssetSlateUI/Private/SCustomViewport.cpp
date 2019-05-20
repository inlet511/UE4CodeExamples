#include "SCustomViewport.h"
#include "FCustomViewportClient.h"

void SCustomViewport::Construct(const FArguments& InArgs)
{
	CustomAsset = InArgs._CustomAsset.Get();
	SEditorViewport::Construct(SEditorViewport::FArguments());
}

TSharedRef<FEditorViewportClient> SCustomViewport::MakeEditorViewportClient()
{
	TSharedRef<FCustomViewportClient> Instance = MakeShareable(new FCustomViewportClient());
	Instance->SetCustomAsset(CustomAsset);
	return Instance;
}

