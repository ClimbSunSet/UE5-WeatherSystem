// WeatherControlComponent.h

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"

#include "Enums/WeatherState/WeatherState.h"
#include "Structs/WeatherEventPayload.h"

#include "WeatherControlComponent.generated.h"

class UNiagaraComponent;
class UCurveFloat;

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

	UPROPERTY(EditDefaultsOnly, Category = "CurveFloat")
	TObjectPtr<UCurveFloat> CurveFloat;

	UPROPERTY(EditAnywhere, Category = "SpawnRateScale")
	float SpawnRateScale = 2000.0f;

	UPROPERTY()
	float CurrentIntensity = 0.0f;

	UPROPERTY()
	float TargetIntensity = 0.0f;

	UPROPERTY()
	float InitialIntensity = 0.0f;

	// TODO: Intensity/WindSpeed 블렌딩 로직 중복 -> 범용 Lerp 헬퍼로 분리 예정
	// TODO: 풍향(BaseWindDirectionDegrees) 보간 추가 - 각도 wrap 때문에 단순 Lerp 금지, LerpAngle 계열 사용

	UPROPERTY()
	float CurrentWindSpeed = 0.0f;

	UPROPERTY()
	float TargetWindSpeed = 0.0f;

	UPROPERTY()
	float InitialWindSpeed = 0.0f;

	UPROPERTY()
	float CurrentWindDirectionDegrees = 0.0f;

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
