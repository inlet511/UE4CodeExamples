// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ContingencyPlanEditor : ModuleRules
{
    
	public ContingencyPlanEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicIncludePaths.Add(ModuleDirectory);
        PublicIncludePaths.AddRange(
			new string[] {

            }
			);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
				// ... add other private include paths required here ...
                "ContingencyPlanEditor/Public",
                "ContingencyPlanEditor/Public/ContingencyPlan",
                "ContingencyPlanEditor/Public/RescurePhase",
                "ContingencyPlanEditor/Public/Scenario",
                "ContingencyPlanEditor/Public/Task",
                "ContingencyPlanEditor/Public/TaskSequence",

                "ContingencyPlanEditor/Private",
                "ContingencyPlanEditor/Private/ContingencyPlan",
                "ContingencyPlanEditor/Private/RescurePhase",
                "ContingencyPlanEditor/Private/Scenario",
                "ContingencyPlanEditor/Private/Task",
                "ContingencyPlanEditor/Private/TaskSequence"
            }
			);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"ContingencyPlan"
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"Projects",
				"InputCore",
				"UnrealEd",
				"LevelEditor",
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
                "PropertyEditor"

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
