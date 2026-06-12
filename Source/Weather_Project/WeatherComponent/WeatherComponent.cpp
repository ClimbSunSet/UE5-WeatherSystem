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

	StartWeatherTimer(CurrentWeatherState);
}

void UWeatherComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UWeatherComponent::ChangeWeatherState(EWeatherState NewState)
{
	CurrentWeatherState = NewState;
	UE_LOG(LogTemp, Warning, TEXT("State: %s, TotalTimeValue: %f"),
		*UEnum::GetValueAsString(CurrentWeatherState), TotalTimeValue);
	OnWeatherStateChanged.Broadcast(NewState, TotalTimeValue);
}


void UWeatherComponent::OnWeatherTimerEnd()
{
	uint8 NextState = (uint8)CurrentWeatherState + 1;

	if (NextState > (uint8)EWeatherState::Decrease)
	{
		NextState = (uint8)EWeatherState::Calm;
	}

	StartWeatherTimer((EWeatherState)NextState);

	ChangeWeatherState((EWeatherState)NextState);
}

void UWeatherComponent::StartWeatherTimer(EWeatherState TargetState)
{
	const FWeatherStateRow* Row = UWeatherFunctionLibrary::GetWeatherStateData(TargetState, WeatherDataTable);

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
