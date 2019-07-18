#pragma once
#include "UObject/ObjectMacros.h"

UENUM(BlueprintType)
enum WorkerGroup
{
	WG_Machinery UMETA(DisplayName="机械组"),
	WG_Construction UMETA(DisplayName="土建组"),
	WG_ElectricInstrument UMETA(DisplayName="电仪组"),
	WG_Mesuring UMETA(DisplayName="测绘组"),
	WG_Surpport UMETA(DisplayName="综合保障组"),
	WG_Machinery01 UMETA(DisplayName = "机械一组"),
	WG_Machinery02 UMETA(DisplayName = "机械二组")
};