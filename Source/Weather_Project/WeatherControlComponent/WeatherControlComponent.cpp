// WeatherControlComponent.cpp

#include "WeatherControlComponent/WeatherControlComponent.h"
#include "WeatherComponent/WeatherComponent.h"
#include "WeatherActor/WeatherActor.h"
#include "Enums/WeatherState/WeatherState.h"
#include "DataTable/WeatherStateRow.h"
#include "WeatherFunctionLibrary/WeatherFunctionLibrary.h"

#include "NiagaraComponent.h"

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
    
    TargetSpawnRate = WeatherEventPayload.ParticleSpawnRate;
    InitialSpawnRate = CurrentSpawnRate;
    ElapsedTime = 0.0f;
}

void UWeatherControlComponent::UpdateWeatherBlend(float DeltaTime)
{
    ElapsedTime += DeltaTime;

    CurrentSpawnRate = FMath::Lerp(InitialSpawnRate, TargetSpawnRate, ElapsedTime / BlendDuration);

    if (ElapsedTime / BlendDuration >= 1.0f)
    {
        CurrentSpawnRate = TargetSpawnRate;

        SetComponentTickEnabled(false);
    }

    OwnerNiagaraComponent->SetVariableFloat(FName("SpawnRate"), CurrentSpawnRate);
}
