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
    ElapsedTime = 0.0f;
}

void UWeatherControlComponent::UpdateWeatherBlend(float DeltaTime)
{
    if (BlendDuration <= 0)
    {
        CurrentIntensity = TargetIntensity;

        SetComponentTickEnabled(false);
    }
    else
    {
        ElapsedTime += DeltaTime;

        float Alpha = ElapsedTime / BlendDuration;

        CurrentIntensity = FMath::Lerp(InitialIntensity, TargetIntensity, Alpha);

        if (Alpha >= 1.0f)
        {
            CurrentIntensity = TargetIntensity;

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
}
