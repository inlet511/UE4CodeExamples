#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"

#include "ContigencyPlanFactory.generated.h"

/**
 * 
 */
UCLASS()
class CONTIGENCYPLANEDITOR_API UContigencyPlanFactory : public UFactory
{
	GENERATED_UCLASS_BODY()
public:
	virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn, FName CallingContext) override;
};
