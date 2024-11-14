#pragma once
#include "../Base/Base.h"

class Menyu : public Base {
private:
	CImage m_img;
	//文字表示オブジェクト
	CFont m_menyu_text;
	int stagenumber;
public:
	bool hyouzi;
	bool itemhyouzi;
	Menyu(const CVector2D& p);
	void Update();
	void Draw();

};
extern TexAnimData Menyu_anim_data[];