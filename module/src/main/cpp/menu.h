#ifndef IMGUI_YOUR_MENU_H
#define IMGUI_YOUR_MENU_H

using namespace ImGui;

void DrawMenu() {
    static ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
  {
        Begin(OBFUSCATE("Mod Menu"));
        ImGuiTabBarFlags tab_bar_flags = ImGuiTabBarFlags_FittingPolicyResizeDown;
        if (BeginTabBar("Menu", tab_bar_flags)) {
            TextUnformatted(OBFUSCATE("Hello World!"));
            EndTabBar();
        }
        Patches();
        End();
    }
}

#endif // IMGUI_YOUR_MENU_H
