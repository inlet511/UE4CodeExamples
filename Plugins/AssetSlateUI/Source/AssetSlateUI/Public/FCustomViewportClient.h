#pragma once
#include "EditorViewportClient.h"

class FCustomViewportClient : public FEditorViewportClient
{
public:
	virtual void Tick(float DeltaSeconds) override;
private:
	FPreviewScene DrawScene;
};