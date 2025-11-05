#include "Impl/Scorecard.h"

void UScorecard::SetScore(int32 Value)
{
	const int32 PrevScore = Score;
	Score = FMath::Clamp(Value, 0, ScoreMax);

	if (Score != PrevScore)
	{
		OnScoreSet.Broadcast(PrevScore, Score);
	}
}

int32 UScorecard::GetScore() const
{
	return Score;
}

int32 UScorecard::GetScoreMax() const
{
	return ScoreMax;
}

FScoreDataId UScorecard::GetId() const
{
	return Id;
}

void UScorecard::DeclareScoreListener(TScriptInterface<IScoreDataListener> Listener)
{
	if (Listener != nullptr)
	{
		TScriptDelegate<FOnScoreSet::ThreadSafetyMode> ScriptDelegate;
		ScriptDelegate.BindUFunction(Listener.GetObject(), FName("OnScoreSet"));
		OnScoreSet.Add(ScriptDelegate);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("DeclareScoreListener: %s does not implement %s"), *Listener.GetObject()->GetName(), *UScoreDataListener::StaticClass()->GetName());
	}
}

void UScorecard::RemoveScoreListener(TScriptInterface<IScoreDataListener> Listener)
{
	if (Listener != nullptr)
	{
		OnScoreSet.Remove(Listener.GetObject(), FName("OnScoreSet"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("RemoveScoreListener: %s does not implement %s"), *Listener.GetObject()->GetName(), *UScoreDataListener::StaticClass()->GetName());
	}
}
