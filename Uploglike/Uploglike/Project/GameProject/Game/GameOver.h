#pragma once
#include "../Base/Base.h"
class GameOver : public Base {
private:
	//画像オブジェクト
	CImage m_img;
	CImage p_img;
public:
	GameOver();
	void Draw();
};