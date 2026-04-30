#include "GameLayer.h"
#include "imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace Hazel;

GameLayer::GameLayer()
	: Layer("FloppyRocket")
{
	auto& window = Application::Get().GetWindow();
	CreateCamera(window.GetWidth(), window.GetHeight());
}

void GameLayer::OnAttach()
{
	m_Level.Init();
}

void GameLayer::OnDetach()
{
}

void GameLayer::OnUpdate(Hazel::Timestep ts)
{
	m_Level.OnUpdate(ts);
	Hazel::RenderCommand::SetClearColor({ 0.3f, 0.3f, 0.3f, 1 });
	Hazel::RenderCommand::Clear();
	
	Hazel::Renderer2D::BeginScene(*m_Camera);
	m_Level.OnRender();
	Hazel::Renderer2D::EndScene();	
}

void GameLayer::OnImGuiRender()
{
	ImGui::Begin("Settings");
	m_Level.OnImGuiRender();
	ImGui::End();
}

void GameLayer::OnEvent(Hazel::Event& e)
{
	EventDispatcher dispatcher(e);
	dispatcher.Dispatch<WindowResizeEvent>(HZ_BIND_EVENT_FN(GameLayer::OnWindowsResize));
}

bool GameLayer::OnWindowsResize(Hazel::WindowResizeEvent& e)
{
	CreateCamera(e.GetWidth(), e.GetHeight());
	return false;
}

void GameLayer::CreateCamera(uint32_t width, uint32_t height)
{
	float aspectRatio = (float)width / (float)height;

	float camWidht = 10.0f;
	float bottom = -camWidht;
	float top = camWidht;
	float left = bottom * aspectRatio;
	float right = top * aspectRatio;
	m_Camera = CreateScope<OrthographicCamera>(left, right, bottom, top);
}
