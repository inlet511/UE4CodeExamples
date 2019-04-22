#include "MyTestDetailCustomization.h"
#include "DeclarativeSyntaxSupport.h"
#include "DetailCategoryBuilder.h"
#include "DetailLayoutBuilder.h"
#include "DetailWidgetRow.h"

#define LOCTEXT_NAMESPACE "MyTestDetailCustomization"
void FMyTestDetailCustomization::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)
{
	//创建新的分类
	IDetailCategoryBuilder& CategoryBuilder = DetailBuilder.EditCategory(TEXT("CustomizeDetails"));

	//分类下增加一行
	CategoryBuilder.AddCustomRow(LOCTEXT("MMM", "Hello World"))

	//形式1：作为整体
	//.WholeRowContent()
	//[SNew(STextBlock)
	// .Text(LOCTEXT("TTTT", "SampleText"))];

	//形式2：分为左右两部分
	.NameContent()
	[
		SNew(STextBlock)
			.Text(LOCTEXT("Extra info", "Custom row header name"))
			.Font(IDetailLayoutBuilder::GetDetailFont())
	]
	.ValueContent()
	.MinDesiredWidth(500)
	[
		SNew(STextBlock)
			.Text(LOCTEXT("Extra info", "Custom row content"))
			.Font(IDetailLayoutBuilder::GetDetailFont())
	];
}

TSharedRef<IDetailCustomization> FMyTestDetailCustomization::MakeInstance()
{
	return MakeShareable(new FMyTestDetailCustomization);
}
#undef LOCTEXT_NAMESPACE