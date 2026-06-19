// WeatherEventPayload.h

#pragma once

#include "CoreMinimal.h"

#include "Enums/WeatherState/WeatherState.h"

#include "WeatherEventPayload.generated.h"

USTRUCT(BlueprintType)
struct FWeatherEventPayload
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EWeatherState WeatherState = EWeatherState::Calm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TotalTimeValue = 0.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BlendTime = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float WindSpeed = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float WeatherIntensity = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BaseWindDirectionDegrees = 0.0f; // 각도 도 단위
};