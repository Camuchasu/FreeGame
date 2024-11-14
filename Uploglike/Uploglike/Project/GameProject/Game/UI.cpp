#include "UI.h"
#include"../Base/Base.h"
UI::UI(const CVector2D& p) :
	Base(eType_UI)
{
	//画像複製
	m_img = COPY_RESOURCE("UI", CImage);
	m_img.mp_texture->SetFilter(GL_NEAREST);
	//再生アニメーション設定
	m_img.ChangeAnimation(0);
	//座標設定
	m_pos = p;
	//画像サイズ設定
	m_img.SetSize(1000,400 );
	//中心位置設定
	m_img.SetCenter(500, 200);
	//turn = 0;
}

void UI::Update()
{

	//アニメーション更新
	m_img.UpdateAnimation();
}

void UI::Draw()
{
	m_img.SetColor(1, 1, 1, 0.5);
	m_img.SetPos(m_pos);
	m_img.Draw();
	//当たり判定矩形表示
	DrawRect();
}


static TexAnim UI_Idle[] = {

	{ 1,50 },
	{ 2,50 },
	
};



TexAnimData UI_anim_data[] = {
	ANIMDATA(UI_Idle),//前方向
	
};
