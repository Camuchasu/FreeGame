#pragma once
#include"../Base/Base.h"

class Slash : public Base {
private:
	//�摜�I�u�W�F�N�g
	CImage m_img;
	//�U���̌���
	bool m_flip;
	//�U���ԍ�
	int m_attack_no;
	
	int m_count;
public:
	Slash(const CVector2D& pos, bool flip, int type, int attack_no,int lv = 1);//������ǉ�����ƕʂ̃N���X�̃X���b�V���Ɉ�����ǉ����邱�Ƃ��ł���
	void Update();
	void Draw();
	int GetAttackNo() {
		return m_attack_no;
	}
};

extern TexAnimData Slash_anim_data[];