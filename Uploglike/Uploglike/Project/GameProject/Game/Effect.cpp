#include "Effect.h"

Effect::Effect(const char* name, const CVector2D& pos, bool flip) :
	Base(eType_Effect)
{
	//画像複製
	m_img = COPY_RESOURCE(name, CImage);
	//座標設定
	m_pos = pos;
	//表示サイズ設定
	m_img.SetSize(128, 128);
	//中心位置設定
	m_img.SetCenter(64, 64);
	//再生アニメーション設定(非ループ)
	m_img.ChangeAnimation(0, false);
	//反転フラグ
	m_flip = flip;
}
void Effect::Update()
{
	//アニメーション更新
	m_img.UpdateAnimation();
	//アニメーション終了チェック
	if (m_img.CheckAnimationEnd()) {
		//エフェクトを削除
		SetKill();
	}
}

void Effect::Draw() {
	m_img.SetPos(GetScreenPos(m_pos));
	m_img.SetFlipH(m_flip);
	m_img.Draw();
}
static TexAnim panci[] = {

	{ 0,2 },
	{ 1,2 },
	{ 2,2 },
	{ 3,2 },
	{ 4,2 },
	{ 5,2 },
	{ 6,2 },
	{ 7,2 },
	{ 8,2 },
	{ 9,2 },
};
TexAnimData Effect_anim_data[] = {
	ANIMDATA(panci),
	
};