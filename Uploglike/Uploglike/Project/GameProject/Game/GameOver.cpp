#include "GameOver.h"
#include"TItle/Title.h"
GameOver::GameOver()
	:Base(eType_GameOver)
{
	//画像複製
	m_img = COPY_RESOURCE("GameOver", CImage);
	m_img.mp_texture->SetFilter(GL_NEAREST);
	m_img.SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	//p_img = COPY_RESOURCE("goalplayer", CImage);
	//p_img.mp_texture->SetFilter(GL_NEAREST);
}

void GameOver::Draw()
{
	//表示
	m_img.Draw();
	if (PUSH(CInput::eButton1)) {
		//すべてのオブジェクトを破壊
		Base::KillAll();
		//タイトルシーンへ
		Base::Add(new Title());
	}

	//p_img.Draw();
	//当たり判定矩形の表示
	//DrawRect();
	//Utility::DrawCircle(GetScreenPos(m_pos), m_rad, CVector4D(1, 1, 1, 1));
}
