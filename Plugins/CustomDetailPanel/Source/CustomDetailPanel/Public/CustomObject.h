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

	UPROPERTY(EditAnywhere, Category = "SampleSubCaegory1")
		float Myfloat;

	UPROPERTY(EditAnywhere, Category = "SampleSubCaegory1")
		int MyInt;

	UPROPERTY(EditAnywhere, Category = "SampleSubCaegory2")
		UTexture2D* MyTexture;
};
