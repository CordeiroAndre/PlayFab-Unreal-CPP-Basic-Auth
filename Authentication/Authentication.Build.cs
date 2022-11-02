using UnrealBuildTool;


public class Authentication : ModuleRules
{
	public Authentication(ReadOnlyTargetRules Target) : base(Target)
	{
		PublicDependencyModuleNames.AddRange(new []{"Core","CoreUObject", "Engine", "PlayFabTutorial", "PlayFabCommon", "PlayFabCpp"});
	}
} 