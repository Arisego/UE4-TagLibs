#pragma once

class TagLibAgent{
public:
	FString GetTestString();
	bool GetMusicInfo(FString MusicFullPath, FString& aAlubmName, FString& aArtistName, FString& aDisplayName);
};