#pragma once

#include "../Shared/Network/CRPC.h"
#include <stdafx.h>

class CRPCCallback
{
public:
	static void Initialize();

	static RPC_CALLBACK ToggleHUDComponent(RPC_ARGS);
	static RPC_CALLBACK SetRadioStation(RPC_ARGS);
	static RPC_CALLBACK SetWaveHeight(RPC_ARGS);
	static RPC_CALLBACK TogglePauseMenu(RPC_ARGS);

private:

};