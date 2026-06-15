// WeatherControlComponent.h

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"

#include "Enums/WeatherState/WeatherState.h"
#include "Structs/WeatherEventPayload.h"

#include "WeatherControlComponent.generated.h"

class UNiagaraComponent;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent), Blueprintable)
class WEATHER_PROJECT_API UWeatherControlComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UWeatherControlComponent();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY()
	EWeatherState WeatherState;

	UPROPERTY()
	UNiagaraComponent* OwnerNiagaraComponent;

	UPROPERTY()
	float CurrentSpawnRate = 0.0f;

	UPROPERTY()
	float TargetSpawnRate = 0.0f;

	UPROPERTY()
	float InitialSpawnRate = 0.0f;

	UPROPERTY()
	float ElapsedTime = 0.0f;

	UPROPERTY()
	float BlendDuration = 0.0f;

public:
	UFUNCTION()
	void ChangeWeatherState(FWeatherEventPayload WeatherEventPayload);

private:
	void StartWeatherBlend(FWeatherEventPayload WeatherEventPayload);

	void UpdateWeatherBlend(float DeltaTime);
};
