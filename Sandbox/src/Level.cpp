#include "Level.h"
#include "GameMath.h"
#include <glm/gtc/matrix_transform.hpp>

using namespace Hazel;

void Level::Init()
{
	m_TriangleTexture = Texture2D::Create("Resources/textures/Triangle.png");
	m_Player.LoadAssets();

	m_Pillars.resize(5);
	for (int i = 0; i < 5; i++)
		CreatePillar(i, i * 10.0f);
}

void Level::OnUpdate(Hazel::Timestep ts)
{
	m_Player.OnUpdate(ts);

	if (CollisionTest())
	{
		GameOver();
		return;
	}

	m_PillarHSV.x += 0.1f * ts;
	if (m_PillarHSV.x >= 1.0f)
		m_PillarHSV.x = 0.0f;

	if (m_Player.GetPosition().x > m_PillarTarget)
	{
		CreatePillar(m_PillarIndex, m_PillarTarget + 20.0f);
		m_PillarIndex = ++m_PillarIndex % m_Pillars.size();
		m_PillarTarget += 10.0f;
	}
}

void Level::OnRender()
{
	const auto& playerPos = m_Player.GetPosition();

	const glm::vec4 color = GameMath::HSVToRGB(m_PillarHSV);

	// Layered deep-space background and a subtle horizon band.
	Renderer2D::DrawQuad({ playerPos.x, 0.0f, -0.9f }, { 50.0f, 50.0f }, { 0.025f, 0.035f, 0.09f, 1.0f });
	// Renderer2D::DrawQuad({ playerPos.x, -6.5f, -0.85f }, { 50.0f, 6.0f }, { 0.08f, 0.05f, 0.18f, 1.0f });
	
	//Floor and ceiling
	Renderer2D::DrawQuad({ playerPos.x,  34.0f }, { 50.0f, 50.0f }, color);
	Renderer2D::DrawQuad({ playerPos.x, -34.0f }, { 50.0f, 50.0f }, color);
	
	for (auto& pillar : m_Pillars)
	{
		Renderer2D::DrawRotatedQuad(pillar.TopPosition, pillar.TopScale, glm::radians(180.0f), m_TriangleTexture, 1.0f, color);
		Renderer2D::DrawQuad(pillar.BottomPosition, pillar.BottomScale, m_TriangleTexture, 1.0f, color);
	}
	m_Player.OnRender();

}

void Level::OnImGuiRender()
{
	m_Player.OnImGuiRender();
}

void Level::CreatePillar(int index, float offset)
{
	Pillar& pillar = m_Pillars[index];
	pillar.TopPosition.x = offset;
	pillar.TopPosition.z = index * 0.1f - 0.5f;
	pillar.BottomPosition.x = offset;
	pillar.BottomPosition.z = index * 0.1f - 0.5f;
	

	float center = Random::Float() * 5.0f - 2.5f;
	float gap = Random::Float() * 3.0f - 1.5f;

	pillar.TopPosition.y = 10.0f + center + gap * 0.5f;
	pillar.BottomPosition.y = -10.0f + center + gap * 0.5f;
}

bool Level::CollisionTest()
{

	glm::vec4 playerVertices[4] = {
		{ -0.5f, -0.5f, 0.0f, 1.0f },
		{  0.5f, -0.5f, 0.0f, 1.0f },
		{  0.5f,  0.5f, 0.0f, 1.0f },
		{ -0.5f,  0.5f, 0.0f, 1.0f }
	};

	const auto& pos = m_Player.GetPosition();
	glm::vec4 playerTransformedVertices[4];

	for (int i = 0; i < 4; i++)
	{
		playerTransformedVertices[i] = glm::translate(glm::mat4(1.0f), {pos.x, pos.y, 0.0f})
			* glm::rotate(glm::mat4(1.0f), glm::radians(m_Player.GetRotation()), {0.0f, 0.0f, 1.0f})
				* glm::scale(glm::mat4(1.0f), {1.0f, 1.3f, 1.0f})
			* playerVertices[i];

	}

	glm::vec4 pillarVertices[3] = {
		{ -0.5f + 0.1f, -0.5f + 0.1f, 0.0f, 1.0f },
		{  0.5f - 0.1f, -0.5f + 0.1f, 0.0f, 1.0f },
		{  0.0f + 0.0f,  0.5f - 0.1f, 0.0f, 1.0f }
	};

	for (auto& p : m_Pillars)
	{
		glm::vec2 tri[3];

		//Top pillars
		for (int i = 0; i < 3; i++)
		{
			tri[i] = glm::translate(glm::mat4(1.0f), { p.TopPosition.x, p.TopPosition.y, 0.0f })
				* glm::rotate(glm::mat4(1.0f), glm::radians(180.0f), { 0.0f, 0.0f, 1.0f })
				* glm::scale(glm::mat4(1.0f), { p.TopScale.x, p.TopScale.y, 1.0f })
				* pillarVertices[i];

		}

		for (auto& vert : playerTransformedVertices)
		{
			if (GameMath::PointInTriangle({vert.x, vert.y}, tri[0], tri[1], tri[2]))
				return true;
		}
		

		//Bottom pillars
		for (int i = 0; i < 3; i++)
		{
			tri[i] = glm::translate(glm::mat4(1.0f), { p.BottomPosition.x, p.BottomPosition.y, 0.0f })
				* glm::scale(glm::mat4(1.0f), { p.BottomScale.x, p.BottomScale.y, 1.0f })
				* pillarVertices[i];

		}
		for (auto& vert : playerTransformedVertices)
		{
			if (GameMath::PointInTriangle({ vert.x, vert.y }, tri[0], tri[1], tri[2]))
				return true;
		}

	}

	return false;
}

void Level::GameOver()
{
	m_GameOver = true;
}

void Level::Reset()
{

	m_GameOver = false;
	m_Player.Reset();

	m_PillarTarget = 30.0f;
	m_PillarIndex = 0;

	for (int i = 0; i < 5; i++)
		CreatePillar(i, i * 10.0f);
}
