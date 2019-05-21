#include "ContigencyPlanFactory.h"
#include "ContigencyPlan.h"

UContigencyPlanFactory::UContigencyPlanFactory(const FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer)
{
	bCreateNew = true;
	bEditAfterNew = true;
	SupportedClass = UContigencyPlan::StaticClass();
}

UObject* UContigencyPlanFactory::FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn, FName CallingContext)
{
	UContigencyPlan* NewTaskAsset = NewObject<UContigencyPlan>(InParent, InClass, InName, Flags | RF_Transactional);
	return NewTaskAsset;
}
