#include "FCustomViewportClient.h"
#include "CustomViewportClient.h"
void FCustomViewportClient::Tick(float DeltaSeconds)
{
	FCustomViewportClient::Tick(DeltaSeconds);
	DrawScene.GetWorld()->Tick(LEVELTICK_All, DeltaSeconds);
}

