#pragma once

#include <Hazel.h>
#include <imgui.h>
#include "Level.h"

class GameLayer : public Hazel::Layer
{
public:
	GameLayer();
	virtual ~GameLayer() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(Hazel::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(Hazel::Event& e) override;
	bool OnWindowsResize(Hazel::WindowResizeEvent& e);
	bool OnMouseButtonPressed(Hazel::MouseButtonPressedEvent& e);
private:
	void CreateCamera(uint32_t width, uint32_t height);
private:
	Hazel::Scope<Hazel::OrthographicCamera> m_Camera;
	Level m_Level;
	ImFont* m_Font = nullptr;
	float m_Time = 0.0f;
	enum class GameState
	{
		Playing = 0, MainMenu = 1, GameOver = 2
	};

	GameState m_State = GameState::MainMenu;
};
