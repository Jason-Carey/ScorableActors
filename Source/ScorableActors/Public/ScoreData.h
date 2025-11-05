// https://github.com/Jason-Carey

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ScoreData.generated.h"

/** Dependencies */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnScoreSet, int32, PrevScore, int32, NewScore);

USTRUCT(BlueprintType)
struct FScoreDataId
{
	GENERATED_BODY()

	bool operator==(const FScoreDataId& Other) const
	{
		return Other.Guid == Guid;
	}

	bool operator!=(const FScoreDataId& Other) const
	{
		return operator==(Other);
	}

	friend uint32 GetTypeHash(const FScoreDataId& Value)
	{
		return GetTypeHash(Value.Guid);
	}

	static FScoreDataId GenerateId()
	{
		FScoreDataId ScoreDataId;
		ScoreDataId.Guid = FGuid::NewGuid();
		return ScoreDataId;
	}
	
private:
	FGuid Guid;
};

/** Unreal interface declaration, these classes do not need to be modified. */

UINTERFACE(BlueprintType)
class UScoreDataListener : public UInterface
{
	GENERATED_BODY()
};

UINTERFACE(BlueprintType)
class UScoreData : public UInterface
{
	GENERATED_BODY()
};

/** C++ interface declaration */

/** */
class IScoreDataListener
{
	GENERATED_BODY()

public:
	/** */
	virtual void OnScoreSet(int32 PrevScore, int32 NewScore) = 0;
};

/** */
class SCORABLEACTORS_API IScoreData
{
	GENERATED_BODY()

public:
	/** Set the current score awarded by this object. */
	virtual void SetScore(int32 Value) = 0;

	/** Current score awarded by this object. */
	virtual int32 GetScore() const = 0;

	/** Maximum score this object awards. */
	virtual int32 GetScoreMax() const = 0;

	/** Add a listener for when the score is set. */
	virtual void DeclareScoreListener(TScriptInterface<IScoreDataListener> Listener) = 0;

	/** Remove a listener to when the score is set. */
	virtual void RemoveScoreListener(TScriptInterface<IScoreDataListener> Listener) = 0;
	
	/** Unique identifier for this scorecard */
	virtual FScoreDataId GetId() const = 0;
};
