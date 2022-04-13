#pragma once
#include "threadtable.hpp"
#include "../Natives.hpp"
#include <imgui.h>

/*Main Thread for DirectX Drawing*/
void CreatedThreads::GraphicsThread() {
	if (ClassPointers::cDX->bGuiOpen) {		
		ImGui::Begin("Hexen");
		if (ImGui::Button("Test"))
			printfnl("Name: %s", PLAYER::GET_PLAYER_NAME(PLAYER::PLAYER_ID()));
		ImGui::SameLine();
		if (ImGui::Button("Remove Hexen from GTA Module (aka Unload/Uninject)"))
			bUnInject = true;
		ImGui::End();
	}
}