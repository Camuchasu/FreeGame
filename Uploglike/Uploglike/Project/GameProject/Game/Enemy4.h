#pragma once
#include "../Base/Base.h"
#include "Map.h"
class Menyu;
class Enemy4 : public Base {
private:
	enum {
		eState_Idle,
		eState_Attack,
		eState_Damage,
		eState_Down,
	};
	enum {
		eAnimIdleD,
		eAnimIdleU,
		eAnimIdleL,
		eAnimIdleR,
		eAnimAttackD,
		eAnimAttackL,
		eAnimAttackR,
		eAnimAttackU,
		eAnimDamage,
		eAnimDown,
	};
	int AnimNunber = 0;
	//��ԕϐ�
	int m_state;
	CImage m_img;
	bool m_flip;
	//�̗�
	int m_hp;
	//�ړ����[�g�f�[�^
	RootData m_root_data;
	//�e��Ԃł̋���
	void StateIdle();
	void StateStep();
	void StateAttack();
	void StateDamage();
	void StateDown();
	//���n�t���O
	bool m_is_ground;
	//�U���ԍ�
	int m_attack_no;
	//�_���[�W�ԍ�

	int m_damage_no;

public:
	Enemy4(const CVector2D& p, bool flip);
	void Update();
	void Draw();
	void Collision(Base* b);

	Enemy4();
	Menyu* m_menyu;
	
};
extern TexAnimData Enemy4_anim_data[];