#include "MyTestDetailCustomization.h"
#include "DeclarativeSyntaxSupport.h"
#include "DetailCategoryBuilder.h"
#include "DetailLayoutBuilder.h"
#include "DetailWidgetRow.h"
#include "PropertyCustomizationHelpers.h"
#include "SImage.h"

#define LOCTEXT_NAMESPACE "MyTestDetailCustomization"
void FMyTestDetailCustomization::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)
{
	//Create New Category
	IDetailCategoryBuilder& CategoryBuilder = DetailBuilder.EditCategory(TEXT("CustomizeDetails"));

	TSharedPtr<IPropertyHandle> MyFloatHandle = DetailBuilder.GetProperty("Myfloat");

	//DetailBuilder.AddPropertyToCategory(MyFloatHandle);
	//Add a new row under category
	CategoryBuilder.AddCustomRow(LOCTEXT("MMM", "Hello World"))

	//形式1：作为整体
	//.WholeRowContent()
	//[SNew(STextBlock)
	// .Text(LOCTEXT("TTTT", "SampleText"))];

	//形式2：分为左右两部分
	//.NameContent()
	//[
	//	SNew(STextBlock)
	//		.Text(LOCTEXT("Extra info", "Custom row header name"))
	//		.Font(IDetailLayoutBuilder::GetDetailFont())
	//]
	//.ValueContent()
	//.MinDesiredWidth(500)
	//[
	//	SNew(STextBlock)
	//		.Text(LOCTEXT("Extra info", "Custom row content"))
	//		.Font(IDetailLayoutBuilder::GetDetailFont())
	//];

	//Custom content
	.WholeRowContent()
	[
		SNew(SHorizontalBox) 
		+ SHorizontalBox::Slot()
		[
			SNew(SProperty, MyFloatHandle)
			//.CustomWidget()
			//[
			//	 SNew(SImage)
			//]
		] 
		+SHorizontalBox::Slot()
		[
			SNew(SProperty, DetailBuilder.GetProperty("MyInt"))
		]
		//more goes here
 
	];
}

TSharedRef<IDetailCustomization> FMyTestDetailCustomization::MakeInstance()
{
	return MakeShareable(new FMyTestDetailCustomization);
}
#undef LOCTEXT_NAMESPACE