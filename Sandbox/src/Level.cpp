#include "Level.h"

Level::Level()
{
}

void Level::Init()
{
	m_Player.LoadAssets();
}

void Level::OnUpdate(Hazel::Timestep ts)
{
	m_Player.OnUpdate(ts);
}

void Level::OnRender()
{
	m_Player.OnRender();
}

void Level::OnImGuiRender()
{
	m_Player.OnImGuiRender();
}
