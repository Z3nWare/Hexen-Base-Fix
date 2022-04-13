#pragma once
#include "threadtable.hpp"
#include "../Natives.hpp"

/*Main Thread for Executing Natives*/
void CreatedThreads::NativeThread() {
	while (true)
	{
		if (ClassPointers::cDX->bGuiOpen) { PAD::DISABLE_ALL_CONTROL_ACTIONS(0); }
		Script::GetCurrent()->ScriptYield();
	}
}