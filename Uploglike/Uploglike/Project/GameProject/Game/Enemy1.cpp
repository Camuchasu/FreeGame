#include "Enemy1.h"
#include "AnimData.h"
#include "Map.h"
#include"Slash.h"
void Enemy1::StateIdle()
{
	//移動量
	const float move_speed = 5;
	//移動フラグ
	bool move_flag = false;
	//ジャンプ力
	const float jump_pow = 12;
	Base* player = Base::FindObject(eType_Player);
	if (player) {
		CVector2D v = player->m_pos + CVector2D(0, -64) - m_pos;
		if (abs(v.x) <= 510) {


			//左移動
			if (v.x < -16) {//64ドット離れていると移動します
				//移動量を設定
				m_pos.x += -move_speed;
				//反転フラグ
				m_flip = true;
				move_flag = true;
			}
			//右移動
			if (v.x > +16) {
				//移動力を設定
				m_pos.x += move_speed;
				//反転フラグ
				m_flip = false;
				move_flag = true;
			}
			//上移動
			if (v.y < -16) {//64ドット離れていると移動します
				//移動量を設定
				m_pos.y += -move_speed;
				move_flag = true;
			}
			//下移動
			if (v.y > +16) {
				//移動力を設定
				m_pos.y += move_speed;
				move_flag = true;
			}
		}
		//左攻撃
		if (v.Length() < 24) {
			//攻撃状態へ移行
			m_state = eState_Attack;
			m_attack_no++;  //多段ヒット対策
			//m_flip = true;  //反転フラグ

		}
		m_img.ChangeAnimation(eState_Idle);
	}
}
void Enemy1::StateAttack()
{
	//攻撃アニメーションへ変更
	m_img.ChangeAnimation(eState_Attack, false);
	//?番目のアニメーションの時発動
	/*if (m_img.GetIndex() == ? ) {
		if (m_flip) {
			Base::Add(new Slash(m_pos + CVector2D(-64, -64), m_flip, eType_Enemmy_Attack, m_attack_no));
		}
		else {
			Base::Add(new Slash(m_pos + CVector2D(64, -64), m_flip, eType_Enemmy_Attack, m_attack_no));
		}
	}*/
	//アニメーションが終了したら
	if (m_img.CheckAnimationEnd()) {
		//通常状態へ移行
		m_state = eState_Idle;
	}
}
void Enemy1::StateDamage()
{
	//m_img.ChangeAnimation(eAnimDamage, false);
	if (m_img.CheckAnimationEnd()) {
		m_state = eState_Idle;
	}
}
void Enemy1::StateDown()
{
	//m_img.ChangeAnimation(eAnimDown, false);
}
Enemy1::Enemy1(const CVector2D& p, bool flip) :Base(eType_Enemy) {
	//画像複製
	m_img = COPY_RESOURCE("Enemy1", CImage);
	//再生アニメーション設定
	m_img.ChangeAnimation(0);
	//座標設定
	m_pos = p;

	m_img.SetSize(400, 400);
	//中心位置設定
	m_img.SetCenter(100, 100);
	//当たり判定用矩形設定
	m_rect = CRect(-45, -15, 45, 15);

	//ヒットポイント
	m_hp = 5;
	//反転フラグ
	m_flip = flip;
	//着地フラグ
	m_is_ground = true;
	//攻撃番号
	m_attack_no = rand();
	//ダメージ番号
	m_damage_no = -1;

}

void Enemy1::Update()
{
	//m_img.ChangeAnimation(5);
	//m_img.UpdateAnimation();
	m_pos_old = m_pos;
	switch (m_state) {
		//通常状態
	case eState_Idle:
		StateIdle();
		break;
		//攻撃状態
	case eState_Attack:
		StateAttack();
		break;
		//ダメージ状態
	case eState_Damage:
		StateDamage();
		break;

		//ダウン状態
	case eState_Down:
		StateDown();
		break;
	}
	//落ちていたら落下中状態へ移行
	//if (m_is_ground && m_vec.y > GRAVITY * 4)
	//	m_is_ground = false;
	//重力による落下
	//m_vec.y += GRAVITY;
	//m_pos += m_vec;

	//アニメーション更新
	m_img.UpdateAnimation();


}

void Enemy1::Draw()
{
	//位置設定
	m_img.SetPos(GetScreenPos(m_pos));
	//反転設定
	m_img.SetPos(GetScreenPos(m_pos));
	//反転設定
	m_img.SetFlipH(m_flip);
	//描画
	m_img.Draw();
	//当たり判定矩形表示
	//DrawRect();
}

void Enemy1::Collision(Base* b)
{
	switch (b->m_type) {
	case eType_Map:
		if (Map* m = dynamic_cast<Map*>(b)) {
			int t;
			t = m->CollisionRect(CVector2D(m_pos.x, m_pos_old.y), m_rect);
			if (t != 0) {
				m_pos.x = m_pos_old.x;
			}
			t = m->CollisionRect(CVector2D(m_pos_old.x, m_pos.y), m_rect);
			if (t != 0) {
				m_pos.y = m_pos_old.y;
				//落下速度リセット
				m_vec.y = 0;
				//接地フラグON
				m_is_ground = true;
			}
		}
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
static TexAnim enemy1Idle[] = {

	{ 1,6 },
	{ 2,6 },
	{ 3,6 },
	{ 4,6 },
	{ 5,6 },
	{ 6,6 },
	{ 7,6 },
	{ 8,6 },
	{ 9,6 },
};

static TexAnim enemy1Attack01[] = {
	{ 10,7 },
	{ 11,7 },
	{ 12,7 },
	{ 13,7 },
	{ 14,7 },
	{ 15,7 },
	{ 16,7 },
};
static TexAnim enemy1Damage[] = {
	{ 16,10 },
	{ 17,10 },
};
static TexAnim enemy1Down[] = {
	{ 18,18 },
	{ 19,18 },
	{ 20,18 },
	{ 21,18 },
	{ 22,18 },
	{ 23,18 },
	{ 24,18 },
};
TexAnimData Enemy1_anim_data[] = {
	ANIMDATA(enemy1Idle),
	ANIMDATA(enemy1Attack01),
	ANIMDATA(enemy1Damage),
	ANIMDATA(enemy1Down),
};