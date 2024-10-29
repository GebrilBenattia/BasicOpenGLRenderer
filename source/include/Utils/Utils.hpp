#pragma once
#include <ImGui/imgui.h>
#include <ImGui/imgui_impl_glfw.h>
#include <ImGui/imgui_impl_opengl3.h>

#include "Window.hpp"

namespace Utils
{
	__forceinline void SetupImGui(GLFWwindow* window) noexcept
	{
        // Setup Dear ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.Fonts->AddFontFromFileTTF("assets/fonts/RobotoCondensed-Bold.ttf", 16.0f);
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;     // Enable Docking
        //io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
        io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
        io.ConfigWindowsResizeFromEdges = true;
        io.ConfigDockingWithShift = true;
        ImGui::StyleColorsDark();
        ImVec4* colors = ImGui::GetStyle().Colors;
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init("#version 330");

        ImGui::PushStyleColor(ImGuiCol_TitleBg, ImVec4(0.1f, 0.1f, 0.1f, 0.85f)); //colouring all window title bar color
        ImGui::PushStyleColor(ImGuiCol_TitleBgActive, ImVec4(0.13f, 0.13f, 0.13f, 0.85f)); //colouring selected window title bar color
        ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.2f, 0.2f, 0.2f, 0.85f)); //colouring the backgroudn of the window 

        ImGui::PushStyleColor(ImGuiCol_TabUnfocused, ImVec4(0.13f, 0.13f, 0.13f, 0.85f)); //colouring all Title background tab 
        ImGui::PushStyleColor(ImGuiCol_TabUnfocusedActive, ImVec4(0.13f, 0.13f, 0.13f, 0.85f)); //colouring selected non-hovered Title background tab  
        ImGui::PushStyleColor(ImGuiCol_TabActive, ImVec4(0.13f, 0.13f, 0.13f, 0.85f)); //colouring selected Title background tab  
        ImGui::PushStyleColor(ImGuiCol_TabHovered, ImVec4(0.25f, 0.25f, 0.25f, 0.85f)); //colouring hovered Title background tab  

        ImGui::PushStyleColor(ImGuiCol_Header, ImVec4(0.25f, 0.25f, 0.25f, 0.85f)); //colouring hovered Title background tab  
        ImGui::PushStyleColor(ImGuiCol_HeaderActive, ImVec4(0.30f, 0.30f, 0.30f, 0.85f)); //colouring hovered Title background tab  
        ImGui::PushStyleColor(ImGuiCol_HeaderHovered, ImVec4(0.35f, 0.35f, 0.35f, 0.85f)); //colouring hovered Title background tab  
        
        ImGui::PushStyleColor(ImGuiCol_SeparatorActive, ImVec4(1.f, 0.8f, 0.231f, 0.85f)); //colouring selected window border when resizing it 
        ImGui::PushStyleColor(ImGuiCol_SeparatorHovered, ImVec4(1.f, 0.8f, 0.231f, 0.85f)); //colouring selected window border when hovering it

        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.f, 0.f));
        ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(7.f, 7.f));
        ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 0.f);
        ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 0.f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);

        ImGui::GetStyle().Colors[ImGuiCol_MenuBarBg] = ImVec4(0.05f, 0.05f, 0.05f, 1.0f); // Définit la couleur de fond de la barre de menu principale
	}

    __forceinline void SetupDockSpace(Window& window) noexcept
    {
        // make the whole screen dockable
        ImGui::DockSpaceOverViewport(ImGui::GetMainViewport(), ImGuiDockNodeFlags_PassthruCentralNode);

        //ImGui::SetNextWindowPos(ImVec2(0, 0));
        //window.GetWindowSize();
        //ImGui::SetNextWindowSize(ImVec2((float)window.GetWidth(), (float)window.GetHeight()));
        //ImGui::Begin("DockSpace", NULL,
        //    ImGuiWindowFlags_NoTitleBar |
        //    ImGuiWindowFlags_NoResize |
        //    ImGuiWindowFlags_NoMove |
        //    ImGuiWindowFlags_NoScrollbar |
        //    ImGuiWindowFlags_NoScrollWithMouse |
        //    ImGuiWindowFlags_NoBringToFrontOnFocus
        //);
        //// Declare Central dockspace
        //auto dockspaceID = ImGui::GetID("HUD_DockSpace");
        //ImGui::DockSpace(dockspaceID, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_PassthruCentralNode/*|ImGuiDockNodeFlags_NoResize*/);
        //ImGui::End();
    }
}