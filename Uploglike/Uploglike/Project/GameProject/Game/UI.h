#pragma once
#include "../Base/Base.h"

class UI : public Base {
private:
	CImage m_img;
	CImage m_HP;
	//�����\���I�u�W�F�N�g
	CFont m_UI_text;
	std::list<std::string> message;
	int messagecnt;
public:
	void AddMessage(const char* str, ...);
	UI(const CVector2D& p);
	void Update();
	void Draw();
	//void Collision();
};
extern TexAnimData UI_anim_data[];