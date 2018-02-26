// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "WorldCreator.h"
#include "WorldCreatorStyle.h"
#include "WorldCreatorCommands.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"

static const FName WorldCreatorTabName("WorldCreator");

#define LOCTEXT_NAMESPACE "FWorldCreatorModule"

void FWorldCreatorModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FWorldCreatorStyle::Initialize();
	FWorldCreatorStyle::ReloadTextures();

	FWorldCreatorCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FWorldCreatorCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FWorldCreatorModule::PluginButtonClicked),
		FCanExecuteAction());
		
	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	
	{
		TSharedPtr<FExtender> MenuExtender = MakeShareable(new FExtender());
		MenuExtender->AddMenuExtension("WindowLayout", EExtensionHook::After, PluginCommands, FMenuExtensionDelegate::CreateRaw(this, &FWorldCreatorModule::AddMenuExtension));

		LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(MenuExtender);
	}
	
	{
		TSharedPtr<FExtender> ToolbarExtender = MakeShareable(new FExtender);
		ToolbarExtender->AddToolBarExtension("Settings", EExtensionHook::After, PluginCommands, FToolBarExtensionDelegate::CreateRaw(this, &FWorldCreatorModule::AddToolbarExtension));
		
		LevelEditorModule.GetToolBarExtensibilityManager()->AddExtender(ToolbarExtender);
	}
	
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(WorldCreatorTabName, FOnSpawnTab::CreateRaw(this, &FWorldCreatorModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("FWorldCreatorTabTitle", "WorldCreator"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);
}

void FWorldCreatorModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	FWorldCreatorStyle::Shutdown();

	FWorldCreatorCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(WorldCreatorTabName);
}

TSharedRef<SDockTab> FWorldCreatorModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	FText WidgetText = FText::Format(
		LOCTEXT("WindowWidgetText", "Add code to {0} in {1} to override this window's contents"),
		FText::FromString(TEXT("FWorldCreatorModule::OnSpawnPluginTab")),
		FText::FromString(TEXT("WorldCreator.cpp"))
		);

	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			// Put your tab content here!
			SNew(SBox)
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			[
				SNew(STextBlock)
				.Text(WidgetText)
			]
		];
}

void FWorldCreatorModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->InvokeTab(WorldCreatorTabName);
}

void FWorldCreatorModule::AddMenuExtension(FMenuBuilder& Builder)
{
	Builder.AddMenuEntry(FWorldCreatorCommands::Get().OpenPluginWindow);
}

void FWorldCreatorModule::AddToolbarExtension(FToolBarBuilder& Builder)
{
	Builder.AddToolBarButton(FWorldCreatorCommands::Get().OpenPluginWindow);
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FWorldCreatorModule, WorldCreator)