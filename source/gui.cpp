#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <glad/glad.h>
#include <stdio.h>
#include <switch.h>
#include "windows.h"
#include "gui.h"

bool done = false;
int gui_mode = GUI_MODE_BROWSER;

namespace GUI
{
	static EGLDisplay s_display = EGL_NO_DISPLAY;
	static EGLContext s_context = EGL_NO_CONTEXT;
	static EGLSurface s_surface = EGL_NO_SURFACE;

	static bool InitEGL(NWindow *win)
	{
		s_display = eglGetDisplay(EGL_DEFAULT_DISPLAY);

		if (!s_display)
		{
			return false;
		}

		eglInitialize(s_display, nullptr, nullptr);

		if (eglBindAPI(EGL_OPENGL_API) == EGL_FALSE)
		{
			eglTerminate(s_display);
			s_display = nullptr;
		}

		EGLConfig config;
		EGLint num_configs;
		static const EGLint framebuffer_attr_list[] = {
			EGL_RENDERABLE_TYPE, EGL_OPENGL_BIT,
			EGL_RED_SIZE, 8,
			EGL_GREEN_SIZE, 8,
			EGL_BLUE_SIZE, 8,
			EGL_ALPHA_SIZE, 8,
			EGL_DEPTH_SIZE, 24,
			EGL_STENCIL_SIZE, 8,
			EGL_NONE};

		eglChooseConfig(s_display, framebuffer_attr_list, std::addressof(config), 1, std::addressof(num_configs));
		if (num_configs == 0)
		{
			eglTerminate(s_display);
			s_display = nullptr;
		}

		s_surface = eglCreateWindowSurface(s_display, config, win, nullptr);
		if (!s_surface)
		{
			eglTerminate(s_display);
			s_display = nullptr;
		}

		static const EGLint context_attr_list[] = {
			EGL_CONTEXT_OPENGL_PROFILE_MASK_KHR, EGL_CONTEXT_OPENGL_CORE_PROFILE_BIT_KHR,
			EGL_CONTEXT_MAJOR_VERSION_KHR, 4,
			EGL_CONTEXT_MINOR_VERSION_KHR, 3,
			EGL_NONE};

		s_context = eglCreateContext(s_display, config, EGL_NO_CONTEXT, context_attr_list);
		if (!s_context)
		{
			eglDestroySurface(s_display, s_surface);
			s_surface = nullptr;
		}

		eglMakeCurrent(s_display, s_surface, s_surface, s_context);
		return true;
	}

	static void ExitEGL(void)
	{
		if (s_display)
		{
			eglMakeCurrent(s_display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);

			if (s_context)
			{
				eglDestroyContext(s_display, s_context);
				s_context = nullptr;
			}

			if (s_surface)
			{
				eglDestroySurface(s_display, s_surface);
				s_surface = nullptr;
			}

			eglTerminate(s_display);
			s_display = nullptr;
		}
	}

	bool SwapBuffers(void)
	{
		return eglSwapBuffers(s_display, s_surface);
	}

	void SetDefaultTheme(void)
	{
		ImGuiIO &io = ImGui::GetIO();
		io.MouseDrawCursor = false;
		auto &style = ImGui::GetStyle();

		style.AntiAliasedLinesUseTex = false;
		style.AntiAliasedLines = true;
		style.AntiAliasedFill = true;
		style.WindowRounding = 0.0f;
		style.FrameRounding = 2.0f;
		style.GrabRounding = 2.0f;

		ImVec4 *colors = ImGui::GetStyle().Colors;
		colors[ImGuiCol_Text] = ImVec4(0.95f, 0.96f, 0.98f, 1.00f);
		colors[ImGuiCol_TextDisabled] = ImVec4(0.36f, 0.42f, 0.47f, 1.00f);
		colors[ImGuiCol_WindowBg] = ImVec4(0.11f, 0.15f, 0.17f, 1.00f);
		colors[ImGuiCol_ChildBg] = ImVec4(0.15f, 0.18f, 0.22f, 1.00f);
		colors[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
		colors[ImGuiCol_Border] = ImVec4(0.08f, 0.10f, 0.12f, 1.00f);
		colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		colors[ImGuiCol_FrameBg] = ImVec4(0.20f, 0.25f, 0.29f, 1.00f);
		colors[ImGuiCol_FrameBgHovered] = ImVec4(0.12f, 0.20f, 0.28f, 1.00f);
		colors[ImGuiCol_FrameBgActive] = ImVec4(0.09f, 0.12f, 0.14f, 1.00f);
		colors[ImGuiCol_TitleBg] = ImVec4(0.09f, 0.12f, 0.14f, 0.65f);
		colors[ImGuiCol_TitleBgActive] = ImVec4(0.08f, 0.10f, 0.12f, 1.00f);
		colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
		colors[ImGuiCol_MenuBarBg] = ImVec4(0.15f, 0.18f, 0.22f, 1.00f);
		colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.39f);
		colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.20f, 0.25f, 0.29f, 1.00f);
		colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.18f, 0.22f, 0.25f, 1.00f);
		colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.09f, 0.21f, 0.31f, 1.00f);
		colors[ImGuiCol_CheckMark] = ImVec4(0.00f, 0.50f, 0.50f, 1.0f);
		colors[ImGuiCol_SliderGrab] = ImVec4(0.28f, 0.56f, 1.00f, 1.00f);
		colors[ImGuiCol_SliderGrabActive] = ImVec4(0.37f, 0.61f, 1.00f, 1.00f);
		colors[ImGuiCol_Button] = ImVec4(0.20f, 0.25f, 0.29f, 1.00f);
		colors[ImGuiCol_ButtonHovered] = ImVec4(0.00f, 0.50f, 0.50f, 1.0f);
		colors[ImGuiCol_ButtonActive] = ImVec4(0.00f, 0.50f, 0.50f, 1.0f);
		colors[ImGuiCol_Header] = ImVec4(0.20f, 0.25f, 0.29f, 0.55f);
		colors[ImGuiCol_HeaderHovered] = ImVec4(0.00f, 0.50f, 0.50f, 1.0f);
		colors[ImGuiCol_HeaderActive] = ImVec4(0.00f, 0.50f, 0.50f, 1.0f);
		colors[ImGuiCol_Separator] = ImVec4(0.20f, 0.25f, 0.29f, 1.00f);
		colors[ImGuiCol_SeparatorHovered] = ImVec4(0.10f, 0.40f, 0.75f, 0.78f);
		colors[ImGuiCol_SeparatorActive] = ImVec4(0.10f, 0.40f, 0.75f, 1.00f);
		colors[ImGuiCol_ResizeGrip] = ImVec4(0.26f, 0.59f, 0.98f, 0.25f);
		colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
		colors[ImGuiCol_ResizeGripActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
		colors[ImGuiCol_Tab] = ImVec4(0.11f, 0.15f, 0.17f, 1.00f);
		colors[ImGuiCol_TabHovered] = ImVec4(0.00f, 0.50f, 0.50f, 1.0f);
		colors[ImGuiCol_TabActive] = ImVec4(0.00f, 0.50f, 0.50f, 1.0f);
		colors[ImGuiCol_TabUnfocused] = ImVec4(0.11f, 0.15f, 0.17f, 1.00f);
		colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.11f, 0.15f, 0.17f, 1.00f);
		colors[ImGuiCol_PlotLines] = ImVec4(0.00f, 0.50f, 0.50f, 1.0f);
		colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
		colors[ImGuiCol_PlotHistogram] = ImVec4(0.00f, 0.50f, 0.50f, 1.0f);
		colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
		colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
		colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
		colors[ImGuiCol_NavHighlight] = ImVec4(0.00f, 0.50f, 0.50f, 1.0f);
		colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
		colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
		colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
	}

	bool Init(FontType fontType)
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO &io = ImGui::GetIO(); (void)io;
		io.Fonts->Clear();

		io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

		if (!GUI::InitEGL(nwindowGetDefault()))
			return false;

		gladLoadGL();

		ImGui_ImplSwitch_Init("#version 130");

		// Load nintendo font
		PlFontData standard, extended, s_chinese, s_chinese_ext, t_chinese, korean;
		ImWchar extended_range[] = {0xe000, 0xe152};
		ImWchar others[] = {
			0x0020, 0x00FF, // Basic Latin + Latin Supplement
			0x0100, 0x024F, // Latin Extended
			0x0370, 0x03FF, // Greek
			0x0400, 0x052F, // Cyrillic + Cyrillic Supplement
			0x0590, 0x05FF, // Hebrew
			0x1E00, 0x1EFF, // Latin Extended Additional
			0x1F00, 0x1FFF, // Greek Extended
			0x2000, 0x206F, // General Punctuation
			0x2100, 0x214F, // Letterlike Symbols
			0x2460, 0x24FF, // Enclosed Alphanumerics
			0x2DE0, 0x2DFF, // Cyrillic Extended-A
			0x31F0, 0x31FF, // Katakana Phonetic Extensions
			0xA640, 0xA69F, // Cyrillic Extended-B
			0xFF00, 0xFFEF, // Half-width characters
			0,
		};
		ImWchar symbols[] = {
			0x2000, 0x206F, // General Punctuation
			0x2100, 0x214F, // Letterlike Symbols
			0x2460, 0x24FF, // Enclosed Alphanumerics
			0,
		};
		ImWchar simplified_chinese[] = {
			// All languages with chinese included
			0x3400, 0x4DBF, // CJK Rare
			0x4E00, 0x9FFF, // CJK Ideograms
			0xF900, 0xFAFF, // CJK Compatibility Ideographs
			0,
		};

		bool ok = R_SUCCEEDED(plGetSharedFontByType(&standard, PlSharedFontType_Standard)) &&
				  R_SUCCEEDED(plGetSharedFontByType(&extended, PlSharedFontType_NintendoExt));

		if (fontType & FONT_TYPE_SIMPLIFIED_CHINESE)
		{
			ok = ok && R_SUCCEEDED(plGetSharedFontByType(&s_chinese, PlSharedFontType_ChineseSimplified));
			ok = ok && R_SUCCEEDED(plGetSharedFontByType(&s_chinese_ext, PlSharedFontType_ExtChineseSimplified));
		}

		if (fontType & FONT_TYPE_TRADITIONAL_CHINESE)
		{
			ok = ok && R_SUCCEEDED(plGetSharedFontByType(&t_chinese, PlSharedFontType_ChineseTraditional));
		}

		if (fontType & FONT_TYPE_KOREAN)
		{
			ok = ok && R_SUCCEEDED(plGetSharedFontByType(&korean, PlSharedFontType_KO));
		}

		IM_ASSERT(ok);

		u8 *px = nullptr;
		int w = 0, h = 0, bpp = 0;
		ImFontConfig font_cfg;

		font_cfg.FontDataOwnedByAtlas = false;
		io.Fonts->AddFontFromMemoryTTF(standard.address, standard.size, 18.0f, &font_cfg, others);
		font_cfg.MergeMode = true;
		io.Fonts->AddFontFromMemoryTTF(extended.address, extended.size, 18.0f, &font_cfg, extended_range);

		if (fontType & FONT_TYPE_SIMPLIFIED_CHINESE)
		{
			io.Fonts->AddFontFromMemoryTTF(standard.address, standard.size, 18.0f, &font_cfg, symbols);
			io.Fonts->AddFontFromMemoryTTF(s_chinese.address, s_chinese.size, 18.0f, &font_cfg, simplified_chinese);
			io.Fonts->AddFontFromMemoryTTF(s_chinese_ext.address, s_chinese_ext.size, 18.0f, &font_cfg, simplified_chinese);
		}

		if (fontType & FONT_TYPE_TRADITIONAL_CHINESE)
		{
			io.Fonts->AddFontFromMemoryTTF(standard.address, standard.size, 18.0f, &font_cfg, symbols);
			io.Fonts->AddFontFromMemoryTTF(t_chinese.address, t_chinese.size, 18.0f, &font_cfg, io.Fonts->GetGlyphRangesChineseFull());
		}

		if (fontType & FONT_TYPE_KOREAN)
		{
			io.Fonts->AddFontFromMemoryTTF(standard.address, standard.size, 18.0f, &font_cfg, symbols);
			io.Fonts->AddFontFromMemoryTTF(korean.address, korean.size, 18.0f, &font_cfg, io.Fonts->GetGlyphRangesKorean());
		}

		if (fontType & FONT_TYPE_JAPANESE)
		{
			io.Fonts->AddFontFromMemoryTTF(standard.address, standard.size, 18.0f, &font_cfg, symbols);
			io.Fonts->AddFontFromMemoryTTF(standard.address, standard.size, 18.0f, &font_cfg, io.Fonts->GetGlyphRangesJapanese());
		}

		io.Fonts->Flags |= ImFontAtlasFlags_NoPowerOfTwoHeight;
		io.Fonts->Build();

		GUI::SetDefaultTheme();
		return true;
	}

	int RenderLoop(void)
	{
		if (!appletMainLoop())
            return false;

		Windows::Init();
		while (!done)
		{
			u64 up;

			if (gui_mode == GUI_MODE_BROWSER)
			{
				up = ImGui_ImplSwitch_NewFrame();
				ImGui::NewFrame();

				Windows::HandleWindowInput(up);
				Windows::MainWindow();
				Windows::ExecuteActions();

				ImGui::Render();

				ImGuiIO &io = ImGui::GetIO(); (void)io;
				glViewport(0, 0, static_cast<int>(io.DisplaySize.x), static_cast<int>(io.DisplaySize.y));
				glClearColor(0.00f, 0.00f, 0.00f, 1.00f);
				glClear(GL_COLOR_BUFFER_BIT);
				ImGui_ImplSwitch_RenderDrawData(ImGui::GetDrawData());
				GUI::SwapBuffers();
			}
			else if (gui_mode == GUI_MODE_IME)
			{
				Windows::HandleImeInput();
			}
		}

		return 0;
	}

    void Exit(void) {
        ImGui_ImplSwitch_Shutdown();
        GUI::ExitEGL();
    }
}
