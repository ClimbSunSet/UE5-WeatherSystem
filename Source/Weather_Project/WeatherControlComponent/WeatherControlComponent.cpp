// WeatherControlComponent.cpp

#include "WeatherControlComponent/WeatherControlComponent.h"
#include "WeatherComponent/WeatherComponent.h"
#include "WeatherActor/WeatherActor.h"
#include "Enums/WeatherState/WeatherState.h"
#include "DataTable/WeatherStateRow.h"
#include "WeatherFunctionLibrary/WeatherFunctionLibrary.h"

#include "NiagaraComponent.h"
#include "Curves/CurveFloat.h"

UWeatherControlComponent::UWeatherControlComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UWeatherControlComponent::BeginPlay()
{
	Super::BeginPlay();

    OwnerNiagaraComponent = GetOwner()->GetComponentByClass<UNiagaraComponent>();

    if (!IsValid(OwnerNiagaraComponent))
    {
        return;
    }

    UWeatherComponent* WeatherComponent = GetOwner()->GetComponentByClass<UWeatherComponent>();
	
    if (IsValid(WeatherComponent))
	{
		WeatherComponent->OnWeatherStateChanged.AddDynamic(this, &UWeatherControlComponent::ChangeWeatherState);
	}
}

void UWeatherControlComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    UpdateWeatherBlend(DeltaTime);
}

void UWeatherControlComponent::ChangeWeatherState(FWeatherEventPayload WeatherEventPayload)
{
	WeatherState = WeatherEventPayload.WeatherState;
    BlendDuration = WeatherEventPayload.BlendTime;

    StartWeatherBlend(WeatherEventPayload);
}

void UWeatherControlComponent::StartWeatherBlend(FWeatherEventPayload WeatherEventPayload)
{
    SetComponentTickEnabled(true);
    
    TargetIntensity = WeatherEventPayload.WeatherIntensity;
    InitialIntensity = CurrentIntensity;

    TargetWindSpeed = WeatherEventPayload.WindSpeed;
    InitialWindSpeed = CurrentWindSpeed;

    TargetWindDirectionDegrees = WeatherEventPayload.BaseWindDirectionDegrees;
    InitialWindDirectionDegrees = CurrentWindDirectionDegrees;

    ElapsedTime = 0.0f;
}

void UWeatherControlComponent::UpdateWeatherBlend(float DeltaTime)
{
    if (BlendDuration <= 0)
    {
        CurrentIntensity = TargetIntensity;
        CurrentWindSpeed = TargetWindSpeed;
        CurrentWindDirectionDegrees = TargetWindDirectionDegrees;

        SetComponentTickEnabled(false);
    }
    else
    {
        ElapsedTime += DeltaTime;

        float Alpha = ElapsedTime / BlendDuration;

        CurrentIntensity = FMath::Lerp(InitialIntensity, TargetIntensity, Alpha);
        CurrentWindSpeed = FMath::Lerp(InitialWindSpeed, TargetWindSpeed, Alpha);
        CurrentWindDirectionDegrees = LerpAngleDegrees(InitialWindDirectionDegrees, TargetWindDirectionDegrees, Alpha);

        if (Alpha >= 1.0f)
        {
            CurrentIntensity = TargetIntensity;
            CurrentWindSpeed = TargetWindSpeed;

            SetComponentTickEnabled(false);
        }
    }
    
    if (!IsValid(CurveFloat))
    {
        return;
    }

    float ParticleSpawnRate = CurveFloat->GetFloatValue(CurrentIntensity);
    float TotalSpawnRate = ParticleSpawnRate * SpawnRateScale;

    OwnerNiagaraComponent->SetVariableFloat(FName("SpawnRate"), TotalSpawnRate);
    OwnerNiagaraComponent->SetVariableFloat(FName("WindSpeed"), CurrentWindSpeed);
    OwnerNiagaraComponent->SetVariableFloat(FName("WindDirection"), CurrentWindDirectionDegrees);
}

float UWeatherControlComponent::LerpAngleDegrees(float Initial, float Target, float Alpha) const
{
    float DeltaAngle = FMath::FindDeltaAngleDegrees(Initial, Target);
    float DegreesValue = Initial + DeltaAngle * Alpha;
    
    return DegreesValue;
}

