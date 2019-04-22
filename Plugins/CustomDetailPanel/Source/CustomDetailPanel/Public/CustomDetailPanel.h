// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "PropertyEditorDelegates.h"

class FCustomDetailPanelModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:
	//登记已经注册的修改，以便于注销自定义的内容
	TSet<FName> RegisteredClassNames;
	TSet<FName> RegisteredPropertyTypes;
};
