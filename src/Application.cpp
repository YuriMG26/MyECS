#include "Application.h"

#include "../vendor/raylib/include/extras/IconsForkAwesome.h"

void StyleImGui();

Application::Application(int argc, char* argv[], const char* title, int width,
                         int height, bool lock_framerate_to_screen,
                         int target_fps)
    : m_Title(title), m_Width(width), m_Height(height) {
  this->parseArgs(argc, argv);
  Logger::log("Initializing window with dimensions %d x %d", width, height);
  InitWindow(width, height, title);

  SetWindowState(FLAG_WINDOW_RESIZABLE);
  SetWindowState(FLAG_MSAA_4X_HINT);

  if (lock_framerate_to_screen) {
    target_fps = GetMonitorRefreshRate(GetCurrentMonitor());
  }
  SetTargetFPS(target_fps);

  rlImGuiSetup(true);

  StyleImGui();

  m_Camera.zoom = 1.0f;
  m_Camera.offset = {(float)GetScreenWidth() / 2, (float)GetScreenHeight() / 2};
  m_Camera.target = {0};
  m_Camera.rotation = 0;

  Logger::log("Application created successfully!");
}

Application::~Application() {
  // TODO: Cleanup
  rlImGuiShutdown();
  CloseWindow();
}

void Application::run() {
  while (!WindowShouldClose()) {
    this->update();
    this->draw();
  }
}

void Application::setState(unsigned int flags) const { SetWindowState(flags); }

void Application::setTitle(const char* title) {
  SetWindowTitle(title);
  this->m_Title = title;
}

void Application::update() {
  // TODO: update
  // TODO: fixed update?
}

void Application::draw() {
  BeginDrawing();
  ClearBackground(RAYWHITE);

  EndDrawing();
}

void Application::parseArgs(int argc, char* argv[]) {
  if (argc > 64) {
    Logger::error("Invalid arg count!");
  }
}

void StyleImGui() {
  ImGuiIO& io = ImGui::GetIO();
  // io.Fonts->AddFontDefault();
  io.Fonts->AddFontFromFileTTF("../../../assets/fonts/roboto.ttf", 18.0f, NULL,
                               io.Fonts->GetGlyphRangesDefault());

  ImFontConfig config;
  config.MergeMode = true;
  config.GlyphMinAdvanceX = 20.0f;
  static const ImWchar iconRanges[] = {ICON_MIN_FK, ICON_MAX_16_FK, 0};
  io.Fonts->AddFontFromFileTTF("../../../assets/fonts/fa-regular-400.ttf",
                               13.0f, &config, iconRanges);
  io.Fonts->Build();
  io.FontDefault = io.Fonts->Fonts[1];
  rlImGuiReloadFonts();
  // Soft Cherry style by Patitotective from ImThemes
  ImGuiStyle& style = ImGui::GetStyle();

  style.Alpha = 1.0f;
  style.DisabledAlpha = 0.4000000059604645f;
  style.WindowPadding = ImVec2(10.0f, 10.0f);
  style.WindowRounding = 4.0f;
  style.WindowBorderSize = 0.0f;
  style.WindowMinSize = ImVec2(50.0f, 50.0f);
  style.WindowTitleAlign = ImVec2(0.5f, 0.5f);
  style.WindowMenuButtonPosition = ImGuiDir_Left;
  style.ChildRounding = 0.0f;
  style.ChildBorderSize = 1.0f;
  style.PopupRounding = 1.0f;
  style.PopupBorderSize = 1.0f;
  style.FramePadding = ImVec2(5.0f, 3.0f);
  style.FrameRounding = 3.0f;
  style.FrameBorderSize = 0.0f;
  style.ItemSpacing = ImVec2(6.0f, 6.0f);
  style.ItemInnerSpacing = ImVec2(3.0f, 2.0f);
  style.CellPadding = ImVec2(3.0f, 3.0f);
  style.IndentSpacing = 6.0f;
  style.ColumnsMinSpacing = 6.0f;
  style.ScrollbarSize = 13.0f;
  style.ScrollbarRounding = 16.0f;
  style.GrabMinSize = 20.0f;
  style.GrabRounding = 4.0f;
  style.TabRounding = 4.0f;
  style.TabBorderSize = 1.0f;
  style.TabMinWidthForCloseButton = 0.0f;
  style.ColorButtonPosition = ImGuiDir_Right;
  style.ButtonTextAlign = ImVec2(0.5f, 0.5f);
  style.SelectableTextAlign = ImVec2(0.0f, 0.0f);

  style.Colors[ImGuiCol_Text] =
      ImVec4(0.8588235378265381f, 0.929411768913269f, 0.886274516582489f, 1.0f);
  style.Colors[ImGuiCol_TextDisabled] = ImVec4(
      0.5215686559677124f, 0.5490196347236633f, 0.5333333611488342f, 1.0f);
  style.Colors[ImGuiCol_WindowBg] = ImVec4(
      0.1294117718935013f, 0.1372549086809158f, 0.168627455830574f, 1.0f);
  style.Colors[ImGuiCol_ChildBg] = ImVec4(
      0.1490196138620377f, 0.1568627506494522f, 0.1882352977991104f, 1.0f);
  style.Colors[ImGuiCol_PopupBg] = ImVec4(
      0.2000000029802322f, 0.2196078449487686f, 0.2666666805744171f, 1.0f);
  style.Colors[ImGuiCol_Border] = ImVec4(
      0.1372549086809158f, 0.1137254908680916f, 0.1333333402872086f, 1.0f);
  style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
  style.Colors[ImGuiCol_FrameBg] = ImVec4(
      0.168627455830574f, 0.1843137294054031f, 0.2313725501298904f, 1.0f);
  style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(
      0.4549019634723663f, 0.196078434586525f, 0.2980392277240753f, 1.0f);
  style.Colors[ImGuiCol_FrameBgActive] = ImVec4(
      0.4549019634723663f, 0.196078434586525f, 0.2980392277240753f, 1.0f);
  style.Colors[ImGuiCol_TitleBg] = ImVec4(
      0.2313725501298904f, 0.2000000029802322f, 0.2705882489681244f, 1.0f);
  style.Colors[ImGuiCol_TitleBgActive] = ImVec4(
      0.501960813999176f, 0.07450980693101883f, 0.2549019753932953f, 1.0f);
  style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(
      0.2000000029802322f, 0.2196078449487686f, 0.2666666805744171f, 1.0f);
  style.Colors[ImGuiCol_MenuBarBg] = ImVec4(
      0.2000000029802322f, 0.2196078449487686f, 0.2666666805744171f, 1.0f);
  style.Colors[ImGuiCol_ScrollbarBg] =
      ImVec4(0.239215686917305f, 0.239215686917305f, 0.2196078449487686f, 1.0f);
  style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(
      0.3882353007793427f, 0.3882353007793427f, 0.3725490272045135f, 1.0f);
  style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(
      0.6941176652908325f, 0.6941176652908325f, 0.686274528503418f, 1.0f);
  style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(
      0.6941176652908325f, 0.6941176652908325f, 0.686274528503418f, 1.0f);
  style.Colors[ImGuiCol_CheckMark] = ImVec4(
      0.658823549747467f, 0.1372549086809158f, 0.1764705926179886f, 1.0f);
  style.Colors[ImGuiCol_SliderGrab] = ImVec4(
      0.6509804129600525f, 0.1490196138620377f, 0.3450980484485626f, 1.0f);
  style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(
      0.7098039388656616f, 0.2196078449487686f, 0.2666666805744171f, 1.0f);
  style.Colors[ImGuiCol_Button] = ImVec4(
      0.6509804129600525f, 0.1490196138620377f, 0.3450980484485626f, 1.0f);
  style.Colors[ImGuiCol_ButtonHovered] = ImVec4(
      0.4549019634723663f, 0.196078434586525f, 0.2980392277240753f, 1.0f);
  style.Colors[ImGuiCol_ButtonActive] = ImVec4(
      0.4549019634723663f, 0.196078434586525f, 0.2980392277240753f, 1.0f);
  style.Colors[ImGuiCol_Header] = ImVec4(
      0.4549019634723663f, 0.196078434586525f, 0.2980392277240753f, 1.0f);
  style.Colors[ImGuiCol_HeaderHovered] = ImVec4(
      0.6509804129600525f, 0.1490196138620377f, 0.3450980484485626f, 1.0f);
  style.Colors[ImGuiCol_HeaderActive] = ImVec4(
      0.501960813999176f, 0.07450980693101883f, 0.2549019753932953f, 1.0f);
  style.Colors[ImGuiCol_Separator] = ImVec4(
      0.4274509847164154f, 0.4274509847164154f, 0.4980392158031464f, 1.0f);
  style.Colors[ImGuiCol_SeparatorHovered] = ImVec4(
      0.09803921729326248f, 0.4000000059604645f, 0.7490196228027344f, 1.0f);
  style.Colors[ImGuiCol_SeparatorActive] = ImVec4(
      0.09803921729326248f, 0.4000000059604645f, 0.7490196228027344f, 1.0f);
  style.Colors[ImGuiCol_ResizeGrip] = ImVec4(
      0.6509804129600525f, 0.1490196138620377f, 0.3450980484485626f, 1.0f);
  style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(
      0.4549019634723663f, 0.196078434586525f, 0.2980392277240753f, 1.0f);
  style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(
      0.4549019634723663f, 0.196078434586525f, 0.2980392277240753f, 1.0f);
  style.Colors[ImGuiCol_Tab] = ImVec4(0.1764705926179886f, 0.3490196168422699f,
                                      0.5764706134796143f, 1.0f);
  style.Colors[ImGuiCol_TabHovered] = ImVec4(
      0.2588235437870026f, 0.5882353186607361f, 0.9764705896377563f, 1.0f);
  style.Colors[ImGuiCol_TabActive] =
      ImVec4(0.196078434586525f, 0.407843142747879f, 0.6784313917160034f, 1.0f);
  style.Colors[ImGuiCol_TabUnfocused] = ImVec4(
      0.06666667014360428f, 0.1019607856869698f, 0.1450980454683304f, 1.0f);
  style.Colors[ImGuiCol_TabUnfocusedActive] = ImVec4(
      0.1333333402872086f, 0.2588235437870026f, 0.4235294163227081f, 1.0f);
  style.Colors[ImGuiCol_PlotLines] =
      ImVec4(0.8588235378265381f, 0.929411768913269f, 0.886274516582489f, 1.0f);
  style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(
      0.4549019634723663f, 0.196078434586525f, 0.2980392277240753f, 1.0f);
  style.Colors[ImGuiCol_PlotHistogram] = ImVec4(
      0.3098039329051971f, 0.7764706015586853f, 0.196078434586525f, 1.0f);
  style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(
      0.4549019634723663f, 0.196078434586525f, 0.2980392277240753f, 1.0f);
  style.Colors[ImGuiCol_TableHeaderBg] = ImVec4(
      0.1882352977991104f, 0.1882352977991104f, 0.2000000029802322f, 1.0f);
  style.Colors[ImGuiCol_TableBorderStrong] = ImVec4(
      0.3098039329051971f, 0.3098039329051971f, 0.3490196168422699f, 1.0f);
  style.Colors[ImGuiCol_TableBorderLight] = ImVec4(
      0.2274509817361832f, 0.2274509817361832f, 0.2470588237047195f, 1.0f);
  style.Colors[ImGuiCol_TableRowBg] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
  style.Colors[ImGuiCol_TableRowBgAlt] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
  style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(
      0.3843137323856354f, 0.6274510025978088f, 0.9176470637321472f, 1.0f);
  style.Colors[ImGuiCol_DragDropTarget] = ImVec4(1.0f, 1.0f, 0.0f, 1.0f);
  style.Colors[ImGuiCol_NavHighlight] = ImVec4(
      0.2588235437870026f, 0.5882353186607361f, 0.9764705896377563f, 1.0f);
  style.Colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
  style.Colors[ImGuiCol_NavWindowingDimBg] =
      ImVec4(0.800000011920929f, 0.800000011920929f, 0.800000011920929f, 1.0f);
  style.Colors[ImGuiCol_ModalWindowDimBg] =
      ImVec4(0.800000011920929f, 0.800000011920929f, 0.800000011920929f,
             0.300000011920929f);
}
