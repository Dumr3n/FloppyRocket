#include "GameLayer.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cfloat>
#include <cmath>

using namespace Hazel;

namespace {
	void DrawCenteredText(ImDrawList* drawList, ImFont* font, float size, float centerX, float y, ImU32 color, const char* text)
	{
		const ImVec2 textSize = font->CalcTextSizeA(size, FLT_MAX, 0.0f, text);
		drawList->AddText(font, size, { centerX - textSize.x * 0.5f, y }, color, text);
	}
}

GameLayer::GameLayer()
	: Layer("FloppyRocket")
{
	auto& window = Application::Get().GetWindow();
	CreateCamera(window.GetWidth(), window.GetHeight());

	Random::Init();
}

void GameLayer::OnAttach()
{
	m_Level.Init();
	ImGuiIO io = ImGui::GetIO();
	m_Font = io.Fonts->AddFontFromFileTTF("Resources/OpenSans-Regular.ttf", 64.0f);
}

void GameLayer::OnDetach()
{
}

void GameLayer::OnUpdate(Hazel::Timestep ts)
{
	m_Time += static_cast<float>(ts);

	
	if (m_Level.IsGameOver())
		m_State = GameState::GameOver;

	switch (m_State)
	{
	case GameState::Playing:
		m_Level.OnUpdate(ts);

		const auto& playerPos = m_Level.GetPlayer().GetPosition();
		m_Camera->SetPosition({ playerPos.x, playerPos.y, 0.0f });
		break;
	}
	
	

	Hazel::RenderCommand::SetClearColor({ 0.0f, 0.0f, 0.0f, 1 });
	Hazel::RenderCommand::Clear();
	
	Hazel::Renderer2D::BeginScene(*m_Camera);
	m_Level.OnRender();
	Hazel::Renderer2D::EndScene();	
}

void GameLayer::OnImGuiRender()
{
	if (!m_Font)
		return;

	ImDrawList* drawList = ImGui::GetForegroundDrawList();
	const float width = static_cast<float>(Application::Get().GetWindow().GetWidth());
	const float height = static_cast<float>(Application::Get().GetWindow().GetHeight());
	const float centerX = width * 0.5f;
	const bool showPrompt = std::fmod(m_Time, 1.2f) < 0.85f;

	switch (m_State)
	{
	case GameState::Playing:
	{
		const std::string score = "SCORE  " + std::to_string(m_Level.GetPlayer().GetScore());
		drawList->AddRectFilled({ 24.0f, 20.0f }, { 250.0f, 82.0f }, IM_COL32(5, 10, 28, 210), 12.0f);
		drawList->AddText(m_Font, 36.0f, { 42.0f, 31.0f }, IM_COL32(255, 255, 255, 255), score.c_str());
		break;
	}
	case GameState::MainMenu:
	{
		drawList->AddRectFilled({ centerX - 360.0f, height * 0.18f }, { centerX + 360.0f, height * 0.58f }, IM_COL32(5, 10, 28, 220), 24.0f);
		DrawCenteredText(drawList, m_Font, 64.0f, centerX, height * 0.25f, IM_COL32(255, 184, 76, 255), "FLOPPY ROCKET");
		DrawCenteredText(drawList, m_Font, 30.0f, centerX, height * 0.39f, IM_COL32(205, 216, 255, 255), "Hold SPACE to fire the thruster");
		if (showPrompt)
			DrawCenteredText(drawList, m_Font, 36.0f, centerX, height * 0.49f, IM_COL32(255, 255, 255, 255), "CLICK TO LAUNCH");
		break;
	}
	case GameState::GameOver:
	{
		const std::string score = "FINAL SCORE  " + std::to_string(m_Level.GetPlayer().GetScore());
		drawList->AddRectFilled({ centerX - 310.0f, height * 0.22f }, { centerX + 310.0f, height * 0.62f }, IM_COL32(5, 10, 28, 230), 24.0f);
		DrawCenteredText(drawList, m_Font, 58.0f, centerX, height * 0.29f, IM_COL32(255, 105, 105, 255), "MISSION FAILED");
		DrawCenteredText(drawList, m_Font, 38.0f, centerX, height * 0.42f, IM_COL32(255, 255, 255, 255), score.c_str());
		if (showPrompt)
			DrawCenteredText(drawList, m_Font, 30.0f, centerX, height * 0.53f, IM_COL32(205, 216, 255, 255), "CLICK TO TRY AGAIN");
		break;
	}
	}
	
}

void GameLayer::OnEvent(Hazel::Event& e)
{
	EventDispatcher dispatcher(e);
	dispatcher.Dispatch<WindowResizeEvent>(HZ_BIND_EVENT_FN(GameLayer::OnWindowsResize));
	dispatcher.Dispatch<MouseButtonPressedEvent>(HZ_BIND_EVENT_FN(GameLayer::OnMouseButtonPressed));
}

bool GameLayer::OnWindowsResize(Hazel::WindowResizeEvent& e)
{
	CreateCamera(e.GetWidth(), e.GetHeight());
	return false;
}

bool GameLayer::OnMouseButtonPressed(Hazel::MouseButtonPressedEvent& e)
{
	if (m_State == GameState::GameOver)
		m_Level.Reset();

	m_State = GameState::Playing;
	return false;
}

void GameLayer::CreateCamera(uint32_t width, uint32_t height)
{
	float aspectRatio = (float)width / (float)height;

	float camWidht = 8.0f;
	float bottom = -camWidht;
	float top = camWidht;
	float left = bottom * aspectRatio;
	float right = top * aspectRatio;
	m_Camera = CreateScope<OrthographicCamera>(left, right, bottom, top);
}
