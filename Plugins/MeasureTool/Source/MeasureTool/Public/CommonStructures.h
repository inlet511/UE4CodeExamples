#pragma once

#include "CoreMinimal.h"
#include "Text.h"
#include "CommonStructures.generated.h"

enum class EMeasureTool : uint8
{
	POINT_RULER_TOOL,
	OBJECT_RULER_TOOL,
	ANNOTATION_TOOL
};


UCLASS()
class MEASURETOOL_API UMeasure : public UObject
{
	GENERATED_BODY()

public:	
	
	UPROPERTY()
	FVector StartLocation;

	UPROPERTY()
	FVector EndLocation;

	UPROPERTY()
	FName Name;

	UFUNCTION()
	void SetStartLocation(FVector loc) { StartLocation = loc; }

	UFUNCTION()
	void SetEndLocation(FVector loc) { EndLocation = loc; }

	//UFUNCTION()
	//void SetName(const FText& Text) { Name = FName(*Text.ToString()); }

	//UFUNCTION()
	//FText GetMeasureName() { return FText::FromName(Name); }

};


USTRUCT()
struct FMeasureRay
{
	GENERATED_BODY()
public:
	UPROPERTY()
	FVector CameraLocation;

	UPROPERTY()
	FVector RayStart;

	UPROPERTY()
	FVector RayDirection;
};

UCLASS()
class MEASURETOOL_API UAnnotation : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY()
		FVector LineStartPos;
	UPROPERTY()
		FVector ShowTextPos;
	UPROPERTY()
		FText AnnotationContent;
};