#pragma once

#include "hzpch.h"
#include "Hazel.h"
#include "Color.h"
#include "Random.h"
#include "ParticleSystem.h"
#include "GameMath.h"

class Player
{
public:
	Player();

	void LoadAssets();

	void OnUpdate(Hazel::Timestep ts);
	void OnRender();
	void OnImGuiRender();
	void Reset();
	float GetRotation() const { return GameMath::RotationFromVerticalVelocity(m_Velocity.y); }
	const glm::vec2& GetPosition() const { return m_Position; }

	uint32_t GetScore() const { return GameMath::ScoreFromPosition(m_Position.x); }
private:
	glm::vec2 m_Position = { -10.0f, 0.0f };
	glm::vec2 m_Velocity = { 5.0f, 0.0f };

	const float m_EngineAcceleration = 24.0f;
	const float m_Gravity = 18.0f;

	float m_Time = 0.0f;
	float m_SmokeEmitInterval = 0.4f;
	float m_SmokeNextEmitTime = m_SmokeEmitInterval;

	ParticleSystem m_ParticleSystem;
	ParticleProps m_SmokeParticle, m_EngineParticle;

	Hazel::Ref<Hazel::Texture2D> m_ShipTexture;
};
