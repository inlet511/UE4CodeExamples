#pragma once
#include "CoreMinimal.h"
#include "Engine/Texture2D.h"
#include "StructVariable.generated.h"


USTRUCT(BlueprintType)
struct CUSTOMDETAILPANEL_API FStructVariable
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "SampleSubCaegory1")
		FText MyText;

	UPROPERTY(EditAnywhere, Category = "SampleSubCaegory1")
	int MyInt;


};