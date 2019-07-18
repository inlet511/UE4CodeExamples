// Fill out your copyright notice in the Description page of Project Settings.

#include "RulerTool.h"
#include "DrawDebugHelpers.h"
#include "SharedPointer.h"
#include "Editor/EditorEngine.h"
#include "EngineUtils.h"
#include "Editor.h"



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

void RulerTool::ShowAllActors()
{
	for (TActorIterator<AActor> Iter(GEditor->GetEditorWorldContext().World()); Iter; ++Iter)
	{
		//UE_LOG(LogTemp, Warning, TEXT("%s"),*(Iter->GetActorLabel()));
		TArray<UStaticMeshComponent*> StaticComps;
		Iter->GetComponents<UStaticMeshComponent>(StaticComps);
		for (auto comp : StaticComps)
		{
			UE_LOG(LogTemp, Warning, TEXT("%s"), *(comp->GetFName().ToString()));
		}
	}
}

