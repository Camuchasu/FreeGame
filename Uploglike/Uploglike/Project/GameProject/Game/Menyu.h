#pragma once
#include "../Base/Base.h"

class Menyu : public Base {
private:
	CImage m_img;
	//�����\���I�u�W�F�N�g
	CFont m_menyu_text;
	int stagenumber;
	int senntaku;
	CImage Itemmenyu_img;
	CImage m_img1;
	int Getlinecount()const;//const�֐��̌��ɂ���΁A�����o�[�ϐ��̕ύX�������Ȃ�
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