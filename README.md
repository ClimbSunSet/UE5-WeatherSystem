### UE5-WeatherSystem

언리얼 엔진 5 기반 나이아가라 날씨 시스템 포트폴리오 프로젝트

A Niagara-based dynamic weather system portfolio project built with Unreal Engine 5.



##### 기능 / Features



* DataTable 기반 날씨 상태 관리 (Calm → Warning → Peak → Decrease)
DataTable-driven weather state management (Calm → Warning → Peak → Decrease)
* 상태 전환 시 SpawnRate 선형 보간 (FMath::Lerp)
Linear interpolation of SpawnRate on state transition using FMath::Lerp
* 델리게이트 기반 옵저버 패턴으로 컴포넌트 간 통신 
Component communication via Delegate-based Observer pattern
* Tick 동적 활성화/비활성화로 성능 최적화
Performance optimization through dynamic Tick enable/disable
* 랜덤 스케일 적용된 상태별 지속 시간
Per-state duration with randomized scale



##### 기술 스택 / Tech Stack



Unreal Engine 5.5

C++

Niagara Particle System

DataTable

