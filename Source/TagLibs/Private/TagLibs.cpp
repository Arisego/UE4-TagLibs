// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "TagLibsPrivatePCH.h"
#include "Agent.h"

class FTagLibs : public ITagLibs
{
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:
	TagLibAgent DAgent;

public:
	virtual FString GetTestString() override;
	virtual bool GetMusicInfo(FString MusicFullPath, FString& aAlubmName, FString& aArtistName, FString& aDisplayName) override;
};

IMPLEMENT_MODULE( FTagLibs, TagLibs )



void FTagLibs::StartupModule()
{
	// This code will execute after your module is loaded into memory (but after global variables are initialized, of course.)
}


void FTagLibs::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

FString FTagLibs::GetTestString()
{
	return DAgent.GetTestString();
}

bool FTagLibs::GetMusicInfo(FString MusicFullPath, FString& aAlubmName, FString& aArtistName, FString& aDisplayName)
{
	return DAgent.GetMusicInfo(MusicFullPath, aAlubmName, aArtistName, aDisplayName);
}

