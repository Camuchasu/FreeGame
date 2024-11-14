#pragma once
#include "../Base/Base.h"

class UI : public Base {
private:
	CImage m_img;
	
public:
	UI(const CVector2D& p);
	void Update();
	void Draw();
	
};
extern TexAnimData UI_anim_data[];