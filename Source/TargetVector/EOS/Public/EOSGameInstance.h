// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OnlineSessionSettings.h"
#include "Engine/GameInstance.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "EOSGameInstance.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct TARGETVECTOR_API FSessionSettingsInput 
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bIsDedicated{ false };

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bShouldAdvertise{ true };

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bIsLANMatch{ false };

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int NumPublicConnections{ 5 };

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bAllowJoinInProgress{ true };

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bAllowJoinViaPresence{true};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bUsesPresence{ true };

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bUseLobbiesIfAvailable{ true };

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName GameName { "EOS_Lobby_Gipfel"	};
};

UENUM(BlueprintType)
enum class ECreateSessionExitExec : uint8
{
	OnSuccess,
	OnFailure,
	OnNotLoggedIn
};

UCLASS()
class TARGETVECTOR_API UEOSGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UEOSGameInstance();
	
	virtual void Init() override;

	void Login();
	void OnLoginComplete(int32 LocalUserNum, bool bWasSuccessful, const FUniqueNetId& UserId, const FString& Error);

	UFUNCTION(BlueprintCallable, Meta = (ExpandEnumAsExecs = "Branches"))
	void CreateSession(FSessionSettingsInput SessionSettingsInput, ECreateSessionExitExec& Branches);

	UFUNCTION(BlueprintCallable)
	void OnCreateSessionComplete(FName SessionName, bool bWasSuccessful);
	
	UFUNCTION(BlueprintCallable)
	void DestroySession();
	void OnDestroySessionComplete(FName SessionName, bool bWasSuccessful);
	
	UFUNCTION(BlueprintCallable)
	void FindFirstSession();
	void OnFindFirstSessionComplete(bool bWasSuccessful);

	UFUNCTION(BlueprintCallable)
	void FindAllSessions();
	void OnFindAllSessionsComplete(bool bWasSuccessful);

	UFUNCTION(BlueprintCallable)
	void JoinSessionByIndex(int32 SessionIndex);
	
	TSharedPtr<FOnlineSessionSearch> SearchSettings;

	void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);

	UFUNCTION(BlueprintCallable)
	void GetAllFriends();
	void OnGetAllFriendsComplete(int32 LocalUserNum, bool bWasSuccessful, const FString& ListName, const FString& ErrorStr);
	
	UFUNCTION(BlueprintCallable)
	void ShowFriendsList();

	UFUNCTION(BlueprintCallable)
	void ShowInviteUI();
	
	TArray<FOnlineSessionSearchResult> Sessions;
	
	UFUNCTION(BlueprintCallable)
	int32 GetNumOfSessions();

	UFUNCTION(BlueprintCallable)
	FString GetSessionID(int32 SessionIndex);

	UFUNCTION(BlueprintCallable)
	FString GetSessionOwnerName(int32 SessionIndex);

	UFUNCTION(BlueprintCallable)
	FString GetPlayerName();

	UFUNCTION(BlueprintCallable)
	int32 GetSessionPing(int32 SessionIndex);

	UFUNCTION(BlueprintCallable)
	int32 GetSessionMaxSlots(int32 SessionIndex);


protected:
	class IOnlineSubsystem* OnlineSubsystem;

	bool bIsLoggedIn;
};
