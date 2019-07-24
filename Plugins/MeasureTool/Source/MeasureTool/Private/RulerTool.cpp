// Fill out your copyright notice in the Description page of Project Settings.

#include "RulerTool.h"
#include "DrawDebugHelpers.h"
#include "SharedPointer.h"



// Sets default values
RulerTool::RulerTool()
{


}

RulerTool::~RulerTool()
{

}


RulerTool* RulerTool::Get()
{
	static RulerTool* CurrentRulerTool = nullptr;
	static bool bInit = false;
	if (!bInit)
	{
		bInit = true;
		CurrentRulerTool = new RulerTool();
	}
	return CurrentRulerTool;
}

void RulerTool::Render(const FSceneView* View, FViewport* Viewport, FPrimitiveDrawInterface* PDI)
{

}

// Called every frame
void RulerTool::Tick(FEditorViewportClient* ViewportClient, float DeltaTime)
{



}

