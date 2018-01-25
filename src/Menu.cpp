#include "Menu.h"

Menu::Menu(Window& a) : window(a), options(_options) {
	//Attach ImGUI to our SDL window
	ImGui_ImplSdlGL3_Init(window.getSDL_Window());
}

void Menu::update(int dt, float width, float height) {
	ImGui_ImplSdlGL3_NewFrame(window.getSDL_Window());
	ImGuiIO& io = ImGui::GetIO();
	
	//ImGui::ShowTestWindow();
}

void Menu::render() {
	ImGui::Render();
}