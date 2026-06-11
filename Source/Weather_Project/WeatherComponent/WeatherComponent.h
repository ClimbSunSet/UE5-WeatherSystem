// WeatherComponent.h

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"

#include "Enums/WeatherState/WeatherState.h"
#include "DataTable/WeatherStateRow.h"

#include "WeatherComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnWeatherStateChanged, EWeatherState, WeatherState, float, TotalTimeValue);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent), Blueprintable)
class WEATHER_PROJECT_API UWeatherComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UWeatherComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	UPROPERTY(BlueprintAssignable)
	FOnWeatherStateChanged OnWeatherStateChanged;

public:
	UFUNCTION()
	void ChangeWeatherState(EWeatherState NewState);

private:
	UPROPERTY(Replicated)
	EWeatherState CurrentWeatherState;

	UPROPERTY(EditDefaultsOnly, Category = "WeatherStateRow")
	TObjectPtr<UDataTable> WeatherDataTable;

	FTimerHandle WeatherTimer;

	float TotalTimeValue = 0.0f;

private:
	void OnWeatherTimerEnd();

	void StartWeatherTimer();

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
