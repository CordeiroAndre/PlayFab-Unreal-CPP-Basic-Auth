// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayFabClientDataModels.h"
#include "PlayFabError.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "AuthenticationService.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class AUTHENTICATION_API UAuthenticationService : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAuthenticationResponse);
	UPROPERTY(BlueprintAssignable)
	FAuthenticationResponse OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FAuthenticationResponse OnFailure;


	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext="WorldContextObject"), Category="Authentication")
	static UAuthenticationService* SignIn(UObject* WorldContextObject, const FString& Username);

private:
	UObject* _worldContextObject;
	void LoginSuccess(const PlayFab::ClientModels::FLoginResult& Result);
	void LoginError(const PlayFab::FPlayFabCppError& Result);
};
