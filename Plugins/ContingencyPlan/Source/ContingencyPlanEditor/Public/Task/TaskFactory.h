// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "AssetTypeCategories.h"
#include "TaskFactory.generated.h"

static EAssetTypeCategories::Type ContingencyCategory;

UCLASS()
class CONTINGENCYPLANEDITOR_API UTaskFactory : public UFactory
{
	GENERATED_UCLASS_BODY()
public:
	virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn, FName CallingContext) override;
};
