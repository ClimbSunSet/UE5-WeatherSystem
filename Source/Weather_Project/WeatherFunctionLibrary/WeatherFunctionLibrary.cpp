// Fill out your copyright notice in the Description page of Project Settings.


#include "WeatherFunctionLibrary/WeatherFunctionLibrary.h"
#include "DataTable/WeatherStateRow.h"

const FWeatherStateRow* UWeatherFunctionLibrary::GetWeatherStateData(EWeatherState State, const UDataTable* WeatherDataTable)
{
	FString EnumString = UEnum::GetValueAsString(State);

	EnumString.RemoveFromStart(TEXT("EWeatherState::"));

	FName StateName = FName(*EnumString);

	const FWeatherStateRow* Row = nullptr;

	if (IsValid(WeatherDataTable))
	{
		Row = WeatherDataTable->FindRow<FWeatherStateRow>(StateName, TEXT("GetWeatherStateData"));
	}

	return Row;
}
