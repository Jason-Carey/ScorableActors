// https://github.com/Jason-Carey

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ScorableComponent.generated.h"

class UScorecard;

UCLASS(ClassGroup=(ScorableActors), meta=(BlueprintSpawnableComponent))
class SCORABLEACTORS_API UScorableComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UScorableComponent();

protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Instanced)
	TObjectPtr<UScorecard> Scorecard;
};