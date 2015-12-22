#include "TagLibsPrivatePCH.h"
#include "Agent.h"

#include <string>
#include "fileref.h"
#include "tag.h"
#include "tpropertymap.h"

FString TagLibAgent::GetTestString()
{
	return "TagLib Agent. Test String. OK!";
}

bool TagLibAgent::GetMusicInfo(FString MusicFullPath, FString& aAlubmName, FString& aArtistName, FString& aDisplayName)
{
	bool ret = false;
	do {
		TagLib::FileRef TLFile(TCHAR_TO_UTF8(*MusicFullPath));
		if (TLFile.isNull()) break;

		TagLib::Tag *tag = TLFile.tag();
		if (!tag) break;

		aDisplayName = tag->title().toWString().c_str();
		aAlubmName = tag->album().toWString().c_str();
		aArtistName = tag->artist().toWString().c_str();

		ret = true;
	} while (false);
	return ret;
}
