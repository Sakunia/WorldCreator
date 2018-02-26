// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "WorldCreatorCommands.h"

#define LOCTEXT_NAMESPACE "FWorldCreatorModule"

void FWorldCreatorCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "WorldCreator", "Bring up WorldCreator window", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE
