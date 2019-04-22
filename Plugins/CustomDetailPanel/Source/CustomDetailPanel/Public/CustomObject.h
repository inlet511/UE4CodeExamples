// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "StructVariable.h"
#include "CustomObject.generated.h"

/**
 * 
 */
UCLASS(BlueprintType,Blueprintable)
class CUSTOMDETAILPANEL_API UCustomObject : public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, Category = "SampleCategory")
	FStructVariable SampleStructVariable;
};
