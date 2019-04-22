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
	//�Ǽ��Ѿ�ע����޸ģ��Ա���ע���Զ��������
	TSet<FName> RegisteredClassNames;
	TSet<FName> RegisteredPropertyTypes;
};
