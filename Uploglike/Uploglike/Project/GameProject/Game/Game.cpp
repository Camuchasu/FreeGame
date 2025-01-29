#include"Game.h"
#include"Goal.h"
#include"Player.h"
#include"UI.h"
#include"Map.h"
#include"Item.h"
#include"Message.h"
#include"../TItle/Title.h"
#include "GameOver.h"

Game::Game() :Base(eType_Scene)
{
	Base::Add(new UI(CVector2D(1100, 900)));
	Base::Add(new Player(CVector2D(600, 1000), true));
	Base::Add(new Map(4));
	Base::Add(new ItemManeger());
	
	m_gamestate = 0;
}
Game::~Game()
{
}
void Game::Update()
{
	switch (m_gamestate) {
	case 0:
		break;
	case 1:
		
		break;
	case 2:
		if (PUSH(CInput::eButton1)) {
			//すべてのオブジェクトを破壊
			Base::KillAll();
			//タイトルシーンへ
			Base::Add(new Title());
		}
		break;
	}
	
	//プレイヤー死亡　ボタン１でゲームシーンを終了
	if (!Base::FindObject(eType_Player) && PUSH(CInput::eButton1)) {
		//すべてのオブジェクトを破壊
		Base::KillAll();
		//タイトルシーンへ
		//Base::Add(new Title());
	}
}

