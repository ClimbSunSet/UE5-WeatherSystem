// WeatherComponent.cpp

#include "WeatherComponent/WeatherComponent.h"
#include "Enums/WeatherState/WeatherState.h"
#include "WeatherFunctionLibrary/WeatherFunctionLibrary.h"

#include "Net/UnrealNetwork.h"

UWeatherComponent::UWeatherComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	CurrentWeatherState = EWeatherState::Calm;
}

void UWeatherComponent::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimerForNextTick([this]()
		{
			ChangeWeatherState(StartWeatherTimer(CurrentWeatherState));
		});
}

void UWeatherComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UWeatherComponent::ChangeWeatherState(FWeatherEventPayload NewWeatherEventPayload)
{
	CurrentWeatherState = NewWeatherEventPayload.WeatherState;
	UE_LOG(LogTemp, Warning, TEXT("State: %s, TotalTimeValue: %f"),
		*UEnum::GetValueAsString(NewWeatherEventPayload.WeatherState), NewWeatherEventPayload.TotalTimeValue);
	
	OnWeatherStateChanged.Broadcast(NewWeatherEventPayload);
}


void UWeatherComponent::OnWeatherTimerEnd()
{
	uint8 NextState = (uint8)CurrentWeatherState + 1;

	if (NextState >= (uint8)EWeatherState::Max)
	{
		NextState = (uint8)EWeatherState::Calm;
	}
	
	ChangeWeatherState(StartWeatherTimer((EWeatherState)NextState));
}

FWeatherEventPayload UWeatherComponent::StartWeatherTimer(EWeatherState TargetState)
{
	FWeatherEventPayload WeatherEventPayload;

	WeatherEventPayload.WeatherState = TargetState;

	const FWeatherStateRow* Row = UWeatherFunctionLibrary::GetWeatherStateData(WeatherEventPayload.WeatherState, WeatherDataTable);

	float TimeValue = 0.0f;

	if (Row != nullptr)
	{
		float Min = Row->WeatherBaseDuration * (1.0f - Row->RandomScale);
		float Max = Row->WeatherBaseDuration * (1.0f + Row->RandomScale);
		TimeValue = FMath::FRandRange(Min, Max);

		WeatherEventPayload.WeatherIntensity = Row->WeatherIntensity;
		WeatherEventPayload.BlendTime = Row->BlendTime;
		WeatherEventPayload.TotalTimeValue = TimeValue;
	}
	else
	{
		return WeatherEventPayload;
	}

	if (TimeValue <= 0.0f)
	{
		return WeatherEventPayload;
	}

	GetWorld()->GetTimerManager().SetTimer(WeatherTimer, this, &UWeatherComponent::OnWeatherTimerEnd, WeatherEventPayload.TotalTimeValue, false);
	
	return WeatherEventPayload;
}

void UWeatherComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UWeatherComponent, CurrentWeatherState);
}
