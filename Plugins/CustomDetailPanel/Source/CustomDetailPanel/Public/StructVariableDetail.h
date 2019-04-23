#pragma once
#include "CoreMinimal.h"
#include "IPropertyTypeCustomization.h"

class FStructVariableDetail:public IPropertyTypeCustomization
{
    public:
		virtual void CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override;
		virtual void CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override;
		static TSharedRef<IPropertyTypeCustomization> MakeInstance();

		void OnPropertyTextCommited(const FText& InText, ETextCommit::Type InCommitType) const;

private:
	TSharedPtr<IPropertyHandle> PropertyText;
	TSharedPtr<class SEditableTextBox> EditableTextBox;
};