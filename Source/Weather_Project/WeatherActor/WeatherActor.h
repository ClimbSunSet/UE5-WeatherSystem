// WeatherActor.h

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeatherActor.generated.h"

class UWeatherComponent;
class UWeatherControlComponent;
class UNiagaraComponent;

UCLASS()
class WEATHER_PROJECT_API AWeatherActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AWeatherActor();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weather", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UWeatherComponent> WeatherComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weather", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UWeatherControlComponent> WeatherControlComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weather", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UNiagaraComponent> NiagaraComponent;
};
