// https://github.com/Jason-Carey

#include "Impl/ScorableComponent.h"
#include "ScoreSubsystem.h"
#include "Impl/Scorecard.h"

UScorableComponent::UScorableComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	Scorecard = CreateDefaultSubobject<UScorecard>(TEXT("InstanceScorecard"));
}

void UScorableComponent::BeginPlay()
{
	UScoreSubsystem* ScoreSubsystem = GetWorld()->GetSubsystem<UScoreSubsystem>();
	check(ScoreSubsystem && Scorecard != nullptr);
	FScoreDataId ScoreDataId = ScoreSubsystem->DeclareScoreData(Scorecard);
}
