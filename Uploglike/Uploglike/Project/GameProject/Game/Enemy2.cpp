#include "Enemy2.h"
#include "Map.h"
#include "../Base/Base.h"
#include "Slash.h"

static TexAnim Enemy2Step[] = {//0

	{ 16,8 },
	{ 17,8 },
	{ 18,8 },
	{ 19,8 },



};
static TexAnim Enemy2Attack[] = {//1
	{ 0,8 },
	{ 1,8 },
	{ 2,10 },
	{ 3,10 },
	{ 4,6 },
	{ 5,6 },
	{ 6,1 },
	{ 7,6 },
};
static TexAnim Enemy2die[] = {//2
	{ 8,5 },
	{ 9,30 },
	{ 10,60 },
	{ 11,60 },
};
static TexAnim Enemy2ran[] = {//3
	{ 24,4 },
	{ 25,4 },
	{ 26,4 },
	{ 27,4 },
	{ 28,4 },
	{ 29,4 },
	{ 30,4 },
	{ 31,4 },


};
static TexAnim Enemy2Hit[] = {//4
	{ 32,5 },
	{33,5 },
	{ 34,5 },
	{ 35,5 },
};
TexAnimData Enemy2_anim_data[] = {
	ANIMDATA(Enemy2Step),//0
	ANIMDATA(Enemy2Attack),//1
	ANIMDATA(Enemy2die),//2
	ANIMDATA(Enemy2ran),//3
	ANIMDATA(Enemy2Hit),//4
};

void Enemy2::StateIdle()//ジャンプなし
{
	//移動量
	const float move_speed = 3;
	//移動フラグ
	bool move_flag = false;

	Base* player = Base::FindObject(eType_Player);
	if (player) {
		CVector2D v = player->m_pos - m_pos;
		if (abs(v.x) <= 510) {

			//左移動
			if (player->m_pos.x < m_pos.x - 32) { //32ドット離れていると移動
				//移動量を設定
				m_pos.x += -move_speed;
				//反転フラグ
				m_flip = true;
				move_flag = true;
			}
			//右移動
			if (player->m_pos.x > m_pos.x + 32) { //32ドット離れていると移動
				//移動量を設定
				m_pos.x += move_speed;
				//反転フラグ
				m_flip = false;
				move_flag = true;
			}


			//左攻撃
			if (player->m_pos.x < m_pos.x && player->m_pos.x > m_pos.x - 64) {
				//攻撃状態へ移行
				m_state = eState_Attack;
				m_attack_no++;  //多段ヒット対策
				m_flip = true;  //反転フラグ

			}
			//右攻撃
			if (player->m_pos.x > m_pos.x && player->m_pos.x < m_pos.x + 64) { //player->m_pos.x（プレイヤー） > m_pos.x(敵）
				//攻撃状態へ移行
				m_state = eState_Attack;
				m_attack_no++;
				m_flip = false;
			}
		}
		if (move_flag) {
			//走るアニメーション
			m_img.ChangeAnimation(e2AnimRun);
		}
		else {
			//待機アニメーション
			m_img.ChangeAnimation(e2step);
		}
	}
}

void Enemy2::StateAttack()
{
	//攻撃アニメーションへ変更
	m_img.ChangeAnimation(e2Anim_Attack, false);
	//6番目のアニメーションの時発動
	if (m_img.GetIndex() == 6) {
		if (m_flip) {
			Base::Add((new Slash(m_pos + CVector2D(-64, -64), m_flip, eType_Enemy_Attack, m_attack_no)));
		}
		else {
			Base::Add((new Slash(m_pos + CVector2D(64, -64), m_flip, eType_Enemy_Attack, m_attack_no)));
		}
	}
	//アニメーションが終了したら
	if (m_img.CheckAnimationEnd()) {
		//通常状態へ移行
		m_state = eState_Idle;
	}
}

void Enemy2::StateDamage()
{
	m_img.ChangeAnimation(e2Anim_Attack, false);
	if (m_img.CheckAnimationEnd()) {
		m_state = eState_Idle;
	}
}

void Enemy2::StateDown()
{
	m_img.ChangeAnimation(e2Animdie, false);
	if (m_img.CheckAnimationEnd()) {
		m_kill = true;
	}
}

Enemy2::Enemy2(const CVector2D& pos, bool flip)
	:Base(eType_Enemy2)
{
	m_img = COPY_RESOURCE("Enemy2", CImage);
	//再生アニメーション設定
	m_img.ChangeAnimation(0);
	//座標
	m_pos_old = m_pos = pos;
	//画像表示サイズ 
	m_img.SetSize(300, 300);
	//中心位置
	m_img.SetCenter(150, 200);
	//矩形
	m_rect = CRect(-30, -98, 30, 0);
	//hp
	m_hp = 10;
	//反転フラグ
	m_flip = flip;
	//着地フラグ
	m_is_ground = true;
	//攻撃番号
	m_attack_no = rand();
	//ダメージ番号
	m_damage_no = -1;
}

void Enemy2::Update()
{
	//m_img.ChangeAnimation(4);
	//m_img.UpdateAnimation();
	//return;
	m_pos_old = m_pos;
	switch (m_state) {
		//通常
	case eState_Idle:
		StateIdle();
		break;
		//攻撃
	case eState_Attack:
		StateAttack();
		break;
		//ダメージ
	case eState_Damage:
		StateDamage();
		break;
		//ダウン
	case eState_Down:
		StateDown();
		break;
	}
	
	

	//アニメーション更新
	m_img.UpdateAnimation();
}

void Enemy2::Draw()
{
	//位置
	m_img.SetPos(GetScreenPos(m_pos));
	//反転設定
	m_img.SetFlipH(m_flip);
	//描画
	m_img.Draw();
	//当たり判定矩形表示
	//DrawRect();

}

void Enemy2::Collision(Base* b)
{
	switch (b->m_type) {
	case eType_Map:
		if (Map* m = dynamic_cast<Map*> (b)) {
			int t;
			t = m->CollisionRect(CVector2D(m_pos.x, m_pos_old.y), m_rect);
			if (t != 0) {
				m_pos.x = m_pos_old.x;
			}
			t = m->CollisionRect(CVector2D(m_pos_old.x, m_pos.y), m_rect);
			if (t != 0) {
				m_pos.y = m_pos_old.y;
				
			}
		}
		break;

	case eType_Player_Attack:
		//Slash型へキャスト、型変換できたら
		if (Slash* s = dynamic_cast<Slash*>(b)) {
			if (Base::CollisionRect(this, s)) {


				m_hp -= 5;
				if (m_hp <= 0) {
					m_state = eState_Down;
				}
				else {
					m_state = eState_Damage;
				}
				//Base::Add(new Effect("Effect_Blood", m_pos + CVector2D(0, -128), m_flip));
			}
		}

		break;

	
	}

}
