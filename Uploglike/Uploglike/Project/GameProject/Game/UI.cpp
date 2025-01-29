#include "UI.h"
#include"../Base/Base.h"
#include"Player.h"
#include"Menyu.h"
#include<cstdarg>
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
void UI::AddMessage(const char* format, ...)
{
	message.clear();
	va_list ap;
	va_start(ap, format,);
	char allocatedBuffer[512];
	int size = vsprintf_s(allocatedBuffer,512, format, ap);
	va_end(ap);
	message.push_back(allocatedBuffer);
	messagecnt = 120;
	
}
UI::UI(const CVector2D& p) :
	Base(eType_UI), m_UI_text("C:\\Windows\\Fonts\\msgothic.ttc", 30)
{
	//画像複製
	m_img = COPY_RESOURCE("UI", CImage);
	m_img.mp_texture->SetFilter(GL_NEAREST);
	m_HP = COPY_RESOURCE("HP", CImage);
	m_HP.mp_texture->SetFilter(GL_NEAREST);
	//再生アニメーション設定
	m_img.ChangeAnimation(0);
	//座標設定
	m_pos = p;
	//UIの画像サイズ設定
	m_img.SetSize(700,400 );
	//HPの画像サイズ設定
	m_HP.SetSize(500,100);
	
	//中心位置設定
	m_img.SetCenter(500, 200);
	message.push_back("主人公は歩いている");
	message.push_back("敵からダメージを受けた！");
	message.push_back("主人公は回復をしている");
	message.erase(message.begin());
	//turn = 0;
	messagecnt = 0;
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
	m_HP.SetPos(860,40);
	
	//ベースをプレイヤーに代入してUIに持ってくる
	Base* player = Base::FindObject(eType_Player);
	if (player) {//プレイヤーを探し出す
		Player* p = dynamic_cast<Player*>(player);
		float HP = p->m_hp;//HPをプレイヤーに紐づける
		float MAXHP = 20;//最大HP
		float s = HP / MAXHP;
		//ゲージの幅
		int width = 256;
		//ゲージの高さ
		int height = 64;

		//ゲージ背景(赤)
		int q = width * p->m_hp / MAXHP;
		m_HP.SetSize(width, height);
		m_HP.SetRect(0, 64, width, 128);
		m_HP.Draw();

		//ゲージの幅を計算(緑)
		int w = width * p->m_hp / MAXHP;
		m_HP.SetSize(w, height);
		m_HP.SetRect(0, 0, w, 64);
		m_HP.Draw();
		m_HP.SetSize(500 * s, 100);
		//m_HP.Draw();
	}
	//当たり判定矩形表示
	//DrawRect();
	if (messagecnt > 0) {
		int i = 0;
		m_img.Draw();
		for (auto& m : message) {
			
			m_UI_text.Draw(700, 800 + i * 60, 0, 0, 0, m.c_str());
			i++;
		}
		messagecnt -= 1;
	}
	if (player) {
		m_UI_text.Draw(750, 100, 100, 0, 0, "lv%d", (player->lv));
	}
	if (player) {
		//m_UI_text.Draw(900, 140, 100, 100, 100, "HP15", (player->HP));
	}
}


static TexAnim UI_Idle[] = {

	{ 1,50 },
	{ 2,50 },
	
};



TexAnimData UI_anim_data[] = {
	ANIMDATA(UI_Idle),//前方向
	
};
