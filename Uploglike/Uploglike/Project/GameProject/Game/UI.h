#pragma once
#include "../Base/Base.h"

class UI : public Base {
private:
	CImage m_img;
	//�����\���I�u�W�F�N�g
	CFont m_UI_text;
	std::list<std::string> message;
public:
	UI(const CVector2D& p);
	void Update();
	void Draw();
	
};
extern TexAnimData UI_anim_data[];