#include "ContingencyPlanFactory.h"
#include "ContingencyPlan.h"

UContingencyPlanFactory::UContingencyPlanFactory(const FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer)
{
	bCreateNew = true;
	bEditAfterNew = true;
	SupportedClass = UContingencyPlan::StaticClass();
}

UObject* UContingencyPlanFactory::FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn, FName CallingContext)
{
	UContingencyPlan* NewTaskAsset = NewObject<UContingencyPlan>(InParent, InClass, InName, Flags | RF_Transactional);
	return NewTaskAsset;
}
