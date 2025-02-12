#pragma once
#include "../Base/Base.h"
class Menyu;
class Player : public Base {
private:
	//状態
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
	//状態変数
	int m_state;
	CImage m_img;
	bool m_flip;
	//着地フラグ
	bool m_is_ground;
	//攻撃番号
	int m_attack_no;
	//ダメージ番号
	int m_damage_no;
	
	//各状態での挙動
	void StateIdle();
	void StateAttack01();
	void StateDamage();
	void StateDown();
	void StateCrouchi();
	
public:
	//ヒットポイント
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