#pragma once
#include "SEditorViewport.h"


class SCustomViewport : public SEditorViewport
{
public:
	SLATE_BEGIN_ARGS(SCustomViewport){}
	SLATE_ATTRIBUTE(class UCustomAsset*, CustomAsset)
	SLATE_END_ARGS()
public:
	void Construct(const FArguments& InArgs);

	virtual TSharedRef<FEditorViewportClient> MakeEditorViewportClient() override;

	class UCustomAsset* CustomAsset;


};