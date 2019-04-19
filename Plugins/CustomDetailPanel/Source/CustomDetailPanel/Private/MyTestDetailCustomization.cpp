#include "MyTestDetailCustomization.h"

void FMyTestDetailCustomization::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)
{
}

TSharedRef<IDetailCustomization> FMyTestDetailCustomization::MakeInstance()
{
	return nullptr;
}
