// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AuthenticationSessionData.generated.h"

/**
 * 
 */
UCLASS()
class AUTHENTICATION_API UAuthenticationSessionData : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	FString GetPlayFabID() const
	{
		return _playFabID;
	}

	void SetPlayFabID(const FString& PlayFabID)
	{
		_playFabID = PlayFabID;
	}

	FString GetUsername() const
	{
		return _username;
	}

	void SetUsername(const FString& Username)
	{
		_username = Username;
	}

private:

	
	FString _playFabID;
	FString _username;
};
