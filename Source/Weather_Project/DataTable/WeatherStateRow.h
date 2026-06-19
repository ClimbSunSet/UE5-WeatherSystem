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
	float BaseDuration = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DurationRandomScale = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BaseWindSpeed = 0.0f; // cm/s, 이 상태의 기본 풍속 (Calm = 0)

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float WindRandomScale = 0.0f; // 0 ~ 1, 풍속 변동 폭 (DurationRandomScale과 동일)

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BlendTime = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float WeatherIntensity = 0.0f;
};