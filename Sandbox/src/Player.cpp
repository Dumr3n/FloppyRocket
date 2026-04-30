#include "Player.h"
#include <imgui.h>

using namespace Hazel;

Player::Player()
{
}

void Player::LoadAssets()
{
	m_ShipTexture = Texture2D::Create(std::string(ASSET_PATH) + "/textures/Ship.png");
}

void Player::OnUpdate(Hazel::Timestep ts)
{
	if (Input::IsKeyPressed(HZ_KEY_SPACE))
	{
		m_Velocity.y += m_EnginePower;
		if (m_Velocity.y < 0.0f)
			m_Velocity.y += m_EnginePower * 2.0f;
	}
	else {
		m_Velocity.y -= m_Gravity;
	}
	
	m_Velocity.y = glm::clamp(m_Velocity.y, -20.0f, 20.0f);
	m_Position += m_Velocity * (float)ts;
}

void Player::OnRender()
{
	Renderer2D::DrawRotatedQuad(m_Position, {1.0f, 1.3f}, glm::radians(GetRotation()), m_ShipTexture);
}

void Player::OnImGuiRender()
{
	ImGui::DragFloat("Engine Power", &m_EnginePower, 0.1f);
	ImGui::DragFloat("Gravity", &m_Gravity, 0.1f);
}