// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#define TAGLIB_STATIC

namespace UnrealBuildTool.Rules
{
	public class TagLibs : ModuleRules
	{
		public TagLibs(TargetInfo Target)
		{
            bUseRTTI = true; // turn on RTTI

            PublicIncludePaths.AddRange(
				new string[] {
					// ... add public include paths required here ...
				}
                );

			PrivateIncludePaths.AddRange(
				new string[] {
					"TagLibs/Private","TagLibs/Private/taglib", "TagLibs/Private/taglib/toolkit", "TagLibs/Private/taglib/asf", "TagLibs/Private/taglib/mpeg", "TagLibs/Private/taglib/ogg", "TagLibs/Private/taglib/ogg/flac", "TagLibs/Private/taglib/flac", "TagLibs/Private/taglib/mpc", "TagLibs/Private/taglib/mp4", "TagLibs/Private/taglib/ogg/vorbis", "TagLibs/Private/taglib/ogg/speex", "TagLibs/Private/taglib/ogg/opus", "TagLibs/Private/taglib/mpeg/id3v2", "TagLibs/Private/taglib/mpeg/id3v2/frames", "TagLibs/Private/taglib/mpeg/id3v1", "TagLibs/Private/taglib/ape", "TagLibs/Private/taglib/wavpack", "TagLibs/Private/taglib/trueaudio", "TagLibs/Private/taglib/riff", "TagLibs/Private/taglib/riff/aiff", "TagLibs/Private/taglib/riff/wav", "TagLibs/Private/taglib/mod", "TagLibs/Private/taglib/s3m", "TagLibs/Private/taglib/it", "TagLibs/Private/taglib/xm"
					
                    // ... add other private include paths required here ...
				}
                );

			PublicDependencyModuleNames.AddRange(
				new string[]
				{
					"Core",
					"CoreUObject",
                     "Engine",
                    "InputCore",
                    "RHI",
					// ... add other public dependencies that you statically link with here ...
				}
				);

			PrivateDependencyModuleNames.AddRange(
				new string[]
				{
					// ... add private dependencies that you statically link with here ...
				}
				);

			DynamicallyLoadedModuleNames.AddRange(
				new string[]
				{
					// ... add any modules that your module loads dynamically here ...
				}
				);
		}
	}
}