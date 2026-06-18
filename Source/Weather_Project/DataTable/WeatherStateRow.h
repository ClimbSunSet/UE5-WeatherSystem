// WeatherStateRow.h

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "WeatherStateRow.generated.h"

USTRUCT(BlueprintType)
struct FWeatherStateRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float WeatherBaseDuration = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float RandomScale = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BlendTime = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float WeatherIntensity = 0.0f;
};