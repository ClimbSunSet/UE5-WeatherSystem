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

	StartWeatherTimer();
}

void UWeatherComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UWeatherComponent::ChangeWeatherState(EWeatherState NewState)
{
	CurrentWeatherState = NewState;
	OnWeatherStateChanged.Broadcast(NewState, TotalTimeValue);
}


void UWeatherComponent::OnWeatherTimerEnd()
{
	uint8 NextState = (uint8)CurrentWeatherState + 1;

	if (NextState > (uint8)EWeatherState::Decrease)
	{
		NextState = (uint8)EWeatherState::Calm;
	}

	ChangeWeatherState((EWeatherState)NextState);

	StartWeatherTimer();
}

void UWeatherComponent::StartWeatherTimer()
{
	const FWeatherStateRow* Row = UWeatherFunctionLibrary::GetWeatherStateData(CurrentWeatherState, WeatherDataTable);

	float TimeValue = 0.0f;

	if (Row != nullptr)
	{
		float Min = Row->WeatherBaseDuration * (1.0f - Row->RandomScale);
		float Max = Row->WeatherBaseDuration * (1.0f + Row->RandomScale);
		TimeValue = FMath::FRandRange(Min, Max);

		TotalTimeValue = TimeValue;
	}
	else
	{
		return;
	}

	if (TimeValue <= 0.0f)
	{
		return;
	}

	GetWorld()->GetTimerManager().SetTimer(WeatherTimer, this, &UWeatherComponent::OnWeatherTimerEnd, TimeValue, false);
}

void UWeatherComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UWeatherComponent, CurrentWeatherState);
}
