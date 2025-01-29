#pragma once
#include "../Base/Base.h"

class Menyu : public Base {
private:
	CImage m_img;
	//文字表示オブジェクト
	CFont m_menyu_text;
	int stagenumber;
	int senntaku;
	CImage Itemmenyu_img;
	CImage m_img1;
	int Getlinecount()const;//const関数の後ろにつければ、メンバー変数の変更をうけない
	int Index;
public:
	int hyouzi;
	int hyouzi2;
	bool itemhyouzi;
	bool sukiruhyouzi;
	Menyu(const CVector2D& p);
	void Update();
	void Draw();

};
extern TexAnimData Menyu_anim_data[];
extern TexAnimData ItemMenyu_anim_data[];