#include "MyTestDetailCustomization.h"
#include "DeclarativeSyntaxSupport.h"
#include "DetailCategoryBuilder.h"
#include "DetailLayoutBuilder.h"
#include "DetailWidgetRow.h"

#define LOCTEXT_NAMESPACE "MyTestDetailCustomization"
void FMyTestDetailCustomization::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)
{
	//�����µķ���
	IDetailCategoryBuilder& CategoryBuilder = DetailBuilder.EditCategory(TEXT("CustomizeDetails"));

	//����������һ��
	CategoryBuilder.AddCustomRow(LOCTEXT("MMM", "Hello World"))

	//��ʽ1����Ϊ����
	//.WholeRowContent()
	//[SNew(STextBlock)
	// .Text(LOCTEXT("TTTT", "SampleText"))];

	//��ʽ2����Ϊ����������
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