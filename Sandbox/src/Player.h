#pragma once

#include "hzpch.h"
#include "Hazel.h"

class Player
{
public:
	Player();

	void LoadAssets();

	void OnUpdate(Hazel::Timestep ts);
	void OnRender();
	void OnImGuiRender();
	float GetRotation() { return m_Velocity.y * 4.0f - 90.0f; }
private:
	glm::vec2 m_Position = { 0.0f, 0.0f };
	glm::vec2 m_Velocity = { 0.0f, 0.0f };

	float m_EnginePower = 1.0f;
	float m_Gravity = 0.8f;

	Hazel::Ref<Hazel::Texture2D> m_ShipTexture;
};