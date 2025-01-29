#pragma once
#include "../Base/Base.h"
#include"Map.h"
class Menyu;
class Enemy : public Base {
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
	//移動ルートデータ
	RootData m_root_data;
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
	Enemy(const CVector2D& p, bool flip);
	void Update();
	void Draw();
	void Collision(Base* b);
	Enemy();
	Menyu* m_menyu;
	
};
extern TexAnimData Enemy_anim_data[];