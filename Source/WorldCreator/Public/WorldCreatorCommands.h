// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "WorldCreatorStyle.h"

class FWorldCreatorCommands : public TCommands<FWorldCreatorCommands>
{
public:

	FWorldCreatorCommands()
		: TCommands<FWorldCreatorCommands>(TEXT("WorldCreator"), NSLOCTEXT("Contexts", "WorldCreator", "WorldCreator Plugin"), NAME_None, FWorldCreatorStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenPluginWindow;
};