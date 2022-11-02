// Fill out your copyright notice in the Description page of Project Settings.


#include "Authentication/Public/AuthenticationService.h"

#include "AuthenticationSessionData.h"
#include "PlayFabClientAPI.h"

UAuthenticationService* UAuthenticationService::SignIn(UObject* WorldContextObject,const FString& username)
{
	UAuthenticationService* AuthenticationService = NewObject<UAuthenticationService>();
	AuthenticationService->_worldContextObject = WorldContextObject;
	AuthenticationService->_worldContextObject->GetWorld()->GetGameInstance()->GetSubsystem<UAuthenticationSessionData>()->SetUsername(username);

	PlayFab::ClientModels::FLoginWithCustomIDRequest Request;
	Request.CreateAccount = true;
	Request.CustomId = username;

	
	PlayFab::UPlayFabClientAPI::FLoginWithCustomIDDelegate OnSuccess;
	OnSuccess.BindUObject(AuthenticationService, &UAuthenticationService::LoginSuccess);
	PlayFab::FPlayFabErrorDelegate OnError;
	OnError.BindUObject(AuthenticationService, &UAuthenticationService::LoginError);
	
	PlayFab::UPlayFabClientAPI().LoginWithCustomID(Request, OnSuccess, OnError);
	
	return AuthenticationService;
}

void UAuthenticationService::LoginSuccess(const PlayFab::ClientModels::FLoginResult& Result)
{
	auto AuthSessionData = _worldContextObject->GetWorld()->GetGameInstance()->GetSubsystem<UAuthenticationSessionData>();
	if(Result.NewlyCreated)
	{
		PlayFab::ClientModels::FUpdateUserTitleDisplayNameRequest Request;
		Request.DisplayName =  AuthSessionData->GetUsername();
		PlayFab::UPlayFabClientAPI().UpdateUserTitleDisplayName(Request);
	}
	AuthSessionData->SetPlayFabID(Result.PlayFabId);
	OnSuccess.Broadcast();
}

void UAuthenticationService::LoginError(const PlayFab::FPlayFabCppError& Result)
{
	_worldContextObject->GetWorld()->GetGameInstance()->GetSubsystem<UAuthenticationSessionData>()->SetUsername(FString(""));
	OnFailure.Broadcast();
}
