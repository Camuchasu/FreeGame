#pragma once
#include "../Base/Base.h"
class Goal : public Base {
private:
	//�摜�I�u�W�F�N�g
	CImage m_img;
	CImage p_img;
public:
	Goal();
	void Draw();
};