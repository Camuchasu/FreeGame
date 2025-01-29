#pragma once
#include "../Base/Base.h"
class Goal : public Base {
private:
	//画像オブジェクト
	CImage m_img;
	CImage p_img;
public:
	Goal();
	void Draw();
};