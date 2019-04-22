#pragma once
#include "CoreMinimal.h"
#include "Engine/Texture2D.h"
#include "StructVariable.generated.h"


USTRUCT(BlueprintType)
struct CUSTOMDETAILPANEL_API FStructVariable
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = "SampleSubCaegory1")
	float Myfloat;

	UPROPERTY(EditAnywhere, Category = "SampleSubCaegory1")
	int MyInt;

	UPROPERTY(EditAnywhere, Category = "SampleSubCaegory2")
	UTexture2D* MyTexture;
};