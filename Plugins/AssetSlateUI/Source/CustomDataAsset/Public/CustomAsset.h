// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CustomAsset.generated.h"

/**
 * 
 */
UCLASS()
class CUSTOMDATAASSET_API UCustomAsset : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "MyCustomAsset")
		FText MyText;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "MyCustomAsset")
		float FloatVar;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "MyCustomAsset")
		int32 IntVar;
};
