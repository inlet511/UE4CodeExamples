#include "StructVariableDetail.h"
#include "Widgets/Images/SImage.h"
#include "DetailWidgetRow.h"

void FStructVariableDetail::CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils)
{
	HeaderRow
	.NameContent()
	[
		PropertyHandle->CreatePropertyNameWidget()
	]
	.ValueContent()
	.MinDesiredWidth(125.0f)
	.MaxDesiredWidth(325.0f)
	[
		SNew(SImage)
	];

}

void FStructVariableDetail::CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils)
{
}

TSharedRef<IPropertyTypeCustomization> FStructVariableDetail::MakeInstance()
{
	return MakeShareable(new FStructVariableDetail);
}
