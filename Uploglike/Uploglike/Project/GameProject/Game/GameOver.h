#pragma once
#include "../Base/Base.h"
class GameOver : public Base {
private:
	//�摜�I�u�W�F�N�g
	CImage m_img;
	CImage p_img;
public:
	GameOver();
	void Draw();
};