// https://github.com/Jason-Carey

#pragma once

#include "CoreMinimal.h"
#include "ScoreData.h"
#include "Scorecard.generated.h"

/** Encapsulates all the information required for an object's score. */
UCLASS(EditInlineNew)
class UScorecard : public UObject, public IScoreData
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintSetter)
	virtual void SetScore(int32 Value) override;

	UFUNCTION(BlueprintGetter)
	virtual int32 GetScore() const override;

	UFUNCTION(BlueprintGetter)
	virtual int32 GetScoreMax() const override;
	
	UFUNCTION(BlueprintGetter)
	virtual FScoreDataId GetId() const override;

	UFUNCTION(BlueprintCallable)
	virtual void DeclareScoreListener(TScriptInterface<IScoreDataListener> Listener) override;
	
	UFUNCTION(BlueprintCallable)
	virtual void RemoveScoreListener(TScriptInterface<IScoreDataListener> Listener) override;
	
protected:
	/** Sends score change notifications. */
	UPROPERTY(BlueprintAssignable)
	FOnScoreSet OnScoreSet;
	
	/** Current score awarded by this object. */
	UPROPERTY(BlueprintGetter=GetScore, BlueprintSetter=SetScore)
	int32 Score;

	/** Maximum score this object awards. */
	UPROPERTY(EditDefaultsOnly, BlueprintGetter=GetScoreMax, meta=(ClampMin="0", DisplayName="Maximum Score"))
	int32 ScoreMax;

	/** Name of the object. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText Name;

	/** Description of this scorable object. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(MultiLine=true))
	FText Description;

	/** Image to display in the interface. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSoftObjectPtr<UTexture2D> Thumbnail;

	/** Unique identifier for this scorecard */
	UPROPERTY(BlueprintGetter=GetId)
	FScoreDataId Id = FScoreDataId::GenerateId();
};