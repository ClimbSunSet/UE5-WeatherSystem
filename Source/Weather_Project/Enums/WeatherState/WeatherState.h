// WeatherState.h

#pragma once

#include "CoreMinimal.h"
#include "WeatherState.generated.h"

UENUM (BlueprintType)
enum class EWeatherState : uint8
{
	Calm		UMETA(DisplayName = "전조증상"),
	Warning		UMETA(DisplayName = "경보"),
	Peak		UMETA(DisplayName = "절정"),
	Decrease	UMETA(DisplayName = "감소")
};