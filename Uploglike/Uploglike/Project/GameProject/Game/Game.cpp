#include "Base/Base.h" 
#include"Game/Field.h"
#include"Game/AnimData.h"
#include"Game/Map.h"
#include"Game/Player.h"
#include"Game/Game.h"
Game::Game() :Base(eType_Scene)
{
	Base::Add(new Player(CVector2D(300, 900), true));
	m_gamestate = 0;
}

Game::~Game()
{
}

void Game::Update()
{
	
}
