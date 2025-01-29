#pragma once
#include "../Base/Base.h"
class Menyu;
class Player : public Base {
private:
	//���
	enum {
		eState_Idle,
		eState_Attack01,
		eState_Attack02,
		eState_Damage,
		eState_Down,
		eState_Crouchi,

	};
	enum {
		eAnimIdle0,
		eAnimIdle1,
		eAnimIdle2,
		eAnimIdle3,
		eAnimRun,
		eAnimJumpUp,
		eAnimJumpDown,
		eAnimAttackD,
		eAnimAttackL,
		eAnimAttackR,
		eAnimAttackU,
		eAnimCrouchi,
		eAnimBattou,
		eAnimAttack02,
		eAnimDown,
		eAnimDmg,
	};
	int AnimNunber = 0;
	//��ԕϐ�
	int m_state;
	CImage m_img;
	bool m_flip;
	//���n�t���O
	bool m_is_ground;
	//�U���ԍ�
	int m_attack_no;
	//�_���[�W�ԍ�
	int m_damage_no;
	
	//�e��Ԃł̋���
	void StateIdle();
	void StateAttack01();
	void StateDamage();
	void StateDown();
	void StateCrouchi();
	
public:
	//�q�b�g�|�C���g
	int m_hp;
	int MAXHP;
	Player(const CVector2D& p, bool flip);
	void Update();
	void Draw();
	void Collision(Base* b);
	Menyu* m_menyu;
	int soubi[2];
};
extern TexAnimData player_anim_data[];