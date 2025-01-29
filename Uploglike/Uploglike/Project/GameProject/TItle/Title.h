#pragma once
#include "../Base/Base.h"
class Title : public Base {
	//画像オブジェクト
	CImage m_img;
	//画像オブジェクト
	CImage h_img;
	//画像オブジェクト
	CImage g_img;
	//文字表示オブジェクト
	CFont m_title_text;
	int m_cnt;
public:
	Title();
	void Update();
	void Draw();
};