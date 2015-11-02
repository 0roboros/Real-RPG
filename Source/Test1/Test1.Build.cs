// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.IO;

public class Test1 : ModuleRules
{

    private string ModulePath
    {
        get { return Path.GetDirectoryName(RulesCompiler.GetModuleFilename(this.GetType().Name)); }
    }

    private string ThirdPartyPath
    {
        get { return Path.GetFullPath(Path.Combine(ModulePath, "../../ThirdParty/")); }
    }

	public Test1(TargetInfo Target)
	{
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "AIModule" });

        LoadSqlite3(Target);
	}

    public bool LoadSqlite3(TargetInfo Target)
    {
        bool isLibrarySupported = false;

        if ((Target.Platform == UnrealTargetPlatform.Win64) || (Target.Platform == UnrealTargetPlatform.Win32))
        {
            isLibrarySupported = true;

            
            string PlatformString = (Target.Platform == UnrealTargetPlatform.Win64) ? "x64" : "x86";
            string LibrariesPath = Path.Combine(ThirdPartyPath, "Sqlite3", "Libraries");

            PublicLibraryPaths.Add(LibrariesPath);
            PublicAdditionalLibraries.Add(Path.Combine(LibrariesPath, "sqlite3." + PlatformString + ".lib"));
        }

        if (isLibrarySupported)
        {
            // Include path
            PublicIncludePaths.Add(Path.Combine(ThirdPartyPath, "Sqlite3", "Includes"));
        }

        Definitions.Add(string.Format("WITH_SQLITE3_BINDING={0}", isLibrarySupported ? 1 : 0));

        return isLibrarySupported;
    }

}
