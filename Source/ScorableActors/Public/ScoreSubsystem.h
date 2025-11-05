// https://github.com/Jason-Carey

#pragma once

#include "CoreMinimal.h"
#include "ScoreData.h"
#include "Subsystems/WorldSubsystem.h"
#include "ScoreSubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnSystemScoreSet, int32, PrevScore, int32, NewScore);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnSystemScoreMaxSet, int32, PrevScore, int32, NewScore);

UCLASS()
class SCORABLEACTORS_API UScoreSubsystem : public UWorldSubsystem, public IScoreDataListener
{
	GENERATED_BODY()

public:
	/** Create an object to include in the score calculations. */
	UFUNCTION(BlueprintCallable)
	FScoreDataId DeclareScoreData(TScriptInterface<IScoreData> ScoreData);
	
	/** Remove this object from the score calculations. */
	UFUNCTION(BlueprintCallable)
	bool RemoveScoreData(const FScoreDataId& ScoreDataId);
	
	UFUNCTION(BlueprintCallable)
	int32 GetSystemScore() const;
	
	UFUNCTION(BlueprintCallable)
	int32 GetSystemScoreMax() const;
	
	UPROPERTY(BlueprintAssignable)
	FOnSystemScoreSet OnSystemScoreSet;

	UPROPERTY(BlueprintAssignable)
	FOnSystemScoreMaxSet OnSystemScoreMaxSet;

private:
	/** Set the system score when an entry is updated. */
	UFUNCTION()
	virtual void OnScoreSet(int32 PrevScore, int32 NewScore) override;
	
	/** Sets the current score and preforms a callback. */
	void SetSystemScore(const int32 Value);
	
	/** Sets the maximum score and preforms a callback. */
	void SetSystemScoreMax(const int32 Value);
	
	UPROPERTY(Transient)
	TMap<FScoreDataId, TScriptInterface<IScoreData>> ScoreDataMap;
	
	UPROPERTY(Transient)
	int32 SystemScore;
	
	UPROPERTY(Transient)
	int32 SystemScoreMax;
};
