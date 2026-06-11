// WeatherActor.cpp

#include "WeatherActor/WeatherActor.h"
#include "WeatherComponent/WeatherComponent.h"
#include "WeatherControlComponent/WeatherControlComponent.h"

#include "NiagaraComponent.h"

AWeatherActor::AWeatherActor()
{
	PrimaryActorTick.bCanEverTick = false;

	NiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraComponent"));
	SetRootComponent(NiagaraComponent);

	WeatherComponent = CreateDefaultSubobject<UWeatherComponent>(TEXT("WeatherComponent"));
	WeatherControlComponent = CreateDefaultSubobject<UWeatherControlComponent>(TEXT("WeatherControlComponent"));
	
}

void AWeatherActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AWeatherActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

