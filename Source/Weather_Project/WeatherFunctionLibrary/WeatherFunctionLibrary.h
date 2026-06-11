// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "Enums/WeatherState/WeatherState.h"

#include "WeatherFunctionLibrary.generated.h"

struct FWeatherStateRow;

UCLASS()
class WEATHER_PROJECT_API UWeatherFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	static const FWeatherStateRow* GetWeatherStateData(EWeatherState State, const UDataTable* WeatherDataTable);

};
