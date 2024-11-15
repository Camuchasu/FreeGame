#include "Menyu.h"
#include"../Base/Base.h"
Menyu::Menyu(const CVector2D& p) :
	Base(eType_Menyu), m_menyu_text("C:\\Windows\\Fonts\\msgothic.ttc", 64)
{
	//画像複製
	m_img = COPY_RESOURCE("menyu-", CImage);
	m_img.mp_texture->SetFilter(GL_NEAREST);
	//再生アニメーション設定
	m_img.ChangeAnimation(0);
	//座標設定
	m_pos = p;
	//画像サイズ設定
	m_img.SetSize(450, 450);
	//中心位置設定
	m_img.SetCenter(225, 225);
	stagenumber = 0;

}

void Menyu::Update()
{
	
	//ボタンを押したときにメニューを生成する
	if (PUSH(CInput::eButton2)) {
		if (hyouzi == true) {
			hyouzi = false;
		}
		else {
			hyouzi = true;
			
		}
	}
	
	//上方向
	if (PUSH(CInput::eUp)) {
		stagenumber -= 1;
		if (stagenumber < 0) {
			stagenumber = 3;
		}

	}
	// 下方向
	if (PUSH(CInput::eDown)) {
		stagenumber += 1;
		if (stagenumber >3) {
			stagenumber = 0;
		}
	}
	//アニメーション更新
	m_img.UpdateAnimation();
}

void Menyu::Draw()
{
	if (hyouzi == false) {
		return;
	}
	m_img.SetColor(1, 1, 1, 0.5);
	m_img.SetPos(m_pos);
	m_img.Draw();
	//当たり判定矩形表示
	DrawRect();

	char Menyuname[4][13] = {
		"アイテム",//0
		"セーブ",//1
		"ロード",//2
		"タイトル",//3
	};
	for (int i = 0; i < 4; i++) {
		//文字表示
		m_menyu_text.Draw(125, 125 + i * 100, 0, 0, 0, Menyuname[i]);

		if (i == stagenumber) {
			m_menyu_text.Draw(125 - 25, 125 + i * 100, 0, 0, 0, ">");
		}


	}
}

static TexAnim Menyu_Idle[] = {

	{ 1,10 },
	{ 2,10 },
	{ 3,10 },
	{ 4,10 },

};



TexAnimData Menyu_anim_data[] = {
	ANIMDATA(Menyu_Idle),//前方向

};
//hyouzi