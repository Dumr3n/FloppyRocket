#pragma once

#include "hzpch.h"
#include "Player.h"
class Level
{
public:
	Level();

	void Init();

	void OnUpdate(Hazel::Timestep ts);
	void OnRender();

	void OnImGuiRender();
private:
	Player m_Player;
};