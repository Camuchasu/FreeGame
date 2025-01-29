#pragma once
#include "../Base/Base.h"
class Menyu;
class BossEnemy : public Base {
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
	//状態変数
	int m_state;
	CImage m_img;
	bool m_flip;
	//体力
	int m_hp;
	//各状態での挙動
	void StateIdle();
	void StateStep();
	void StateAttack();
	void StateDamage();
	void StateDown();
	//着地フラグ
	bool m_is_ground;
	//攻撃番号
	int m_attack_no;
	//ダメージ番号
	int m_damage_no;
	
public:
	BossEnemy(const CVector2D& p, bool flip);
	void Update();
	void Draw();
	void Collision(Base* b);

	BossEnemy();
	Menyu* m_menyu;
};
extern TexAnimData BossEnemy_anim_data[];