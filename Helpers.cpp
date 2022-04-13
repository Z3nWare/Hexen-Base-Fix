#pragma once
#include "Helpers.hpp"
#include "ClassPointers.hpp"

IMGUI_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

void Helpers::GetGTAWindow() {
	pGTAWindow = FindWindowA("grcWindow", "Grand Theft Auto V");
	printfnl("FindWindow Status Code: [200 -> OK]");
}

void Helpers::WndProc(HWND hWnd, uint32_t msg, WPARAM wPrm, LPARAM lPrm) {
	if (ImGui::GetCurrentContext())
		ImGui_ImplWin32_WndProcHandler(hWnd, msg, wPrm, lPrm);
}