#include "UI.h"
#include"../Base/Base.h"
UI::UI(const CVector2D& p) :
	Base(eType_UI), m_UI_text("C:\\Windows\\Fonts\\msgothic.ttc", 30)
{
	//画像複製
	m_img = COPY_RESOURCE("UI", CImage);
	m_img.mp_texture->SetFilter(GL_NEAREST);
	//再生アニメーション設定
	m_img.ChangeAnimation(0);
	//座標設定
	m_pos = p;
	//画像サイズ設定
	m_img.SetSize(700,400 );
	//中心位置設定
	m_img.SetCenter(500, 200);
	message.push_back("主人公は歩いている");
	message.push_back("敵からダメージを受けた！");
	message.push_back("主人公は回復をしている");
	message.erase(message.begin());
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
	int i = 0;
	for (auto& m : message) {
		m_UI_text.Draw(700, 800+i*60, 0, 0, 0, m.c_str());
		i++;
	}
}


static TexAnim UI_Idle[] = {

	{ 1,50 },
	{ 2,50 },
	
};



TexAnimData UI_anim_data[] = {
	ANIMDATA(UI_Idle),//前方向
	
};
