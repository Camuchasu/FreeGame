#include "BossEnemy.h"
#include "AnimData.h"
#include "Map.h"
#include"Slash.h"
#include"Effect.h"
#include"TP.h"
#include"Menyu.h"
#include "Player.h"
#include "ItemBag.h"
void BossEnemy::StateIdle()
{
	//移動量
	const float move_speed = 5;
	//移動フラグ
	bool move_flag = false;
	//ジャンプ力
	const float jump_pow = 12;
	Base* player = Base::FindObject(eType_Player);
	if (player) {
		CVector2D v = player->m_pos - m_pos;
		if (abs(v.x) <= 510) {

			//左移動
			/*if (player->m_pos.x < m_pos.x - 90) { //32ドット離れていると移動
				//移動量を設定
				m_pos.x += -move_speed;
				AnimNunber = 0;
				//反転フラグ
				m_flip = false;
				move_flag = true;
			}
			//右移動
			if (player->m_pos.x > m_pos.x + 90) { //32ドット離れていると移動
				//移動量を設定
				m_pos.x += move_speed;
				AnimNunber = 1;
				//反転フラグ
				m_flip = false;
				move_flag = true;
			}

			//上移動
			if (v.y < -55) {//16ドット離れていると移動します
				//移動量を設定
				m_pos.y += -move_speed;
				AnimNunber = 2;
				move_flag = true;
			}
			//下移動
			if (v.y > +55) {
				//移動力を設定
				m_pos.y += move_speed;
				AnimNunber = 3;
				move_flag = true;
			}
		}*/
			float a = atan2(v.x, v.y);
			if (v.Length() < 1980) {
				//左攻撃
				if (a > (DtoR(-135)) && a < DtoR(-45)) {
					//攻撃状態へ移行
					m_state = eState_Attack;
					m_attack_no++;  //多段ヒット対策
					//m_flip = true;  //反転フラグ
					AnimNunber = 3;
				}
				//右攻撃
				if (a < (DtoR(135)) && a > DtoR(45)) {
					//攻撃状態へ移行
					m_state = eState_Attack;
					m_attack_no++;  //多段ヒット対策
					//m_flip = true;  //反転フラグ
					AnimNunber = 2;
				}
				//上攻撃
				if (abs(a) > (DtoR(135))) {
					//攻撃状態へ移行
					m_state = eState_Attack;
					m_attack_no++;  //多段ヒット対策
					//m_flip = true;  //反転フラグ
					AnimNunber = 1;
				}
				//下攻撃
				if (abs(a) < (DtoR(45))) {//ラジアンなためπが１８０
					//攻撃状態へ移行
					m_state = eState_Attack;
					m_attack_no++;  //多段ヒット対策
					//m_flip = true;  //反転フラグ
					AnimNunber = 0;
				}
			}
			m_img.ChangeAnimation(eAnimIdleD + AnimNunber);

		}
	}
}

void BossEnemy::StateAttack()
{
	//攻撃アニメーションへ変更
	m_img.ChangeAnimation(eAnimAttackD + AnimNunber, false);

	if (m_img.GetIndex() == 3) {
		CVector2D pos[] = {
			//各方向に当たり判定をつける
		CVector2D(0,64),CVector2D(0,-64),CVector2D(64,0),CVector2D(-64,0),//左から順に下、上、右、左
		};
		Base::Add((new Slash(m_pos + pos[AnimNunber], m_flip, eType_Enemy_Attack, m_attack_no, lv)));

	}
	//アニメーションが終了したら
	if (m_img.CheckAnimationEnd()) {
		//通常状態へ移行
		m_state = eState_Idle;
	}
}
void BossEnemy::StateDamage()
{
	m_img.ChangeAnimation(eAnimDamage, false);
	if (m_img.CheckAnimationEnd()) {
		m_state = eState_Idle;
	}
}
void BossEnemy::StateDown()
{
	m_img.ChangeAnimation(eAnimDown, false);
	if (m_img.CheckAnimationEnd()) {
		m_kill = true;
		Base::Add(new Tp(CVector2D(960,540)));
		Base* player = Base::FindObject(eType_Player);
		player->exp += 10000;
	}
}
BossEnemy::BossEnemy(const CVector2D& p, bool flip) :Base(eType_Enemy) {
	//画像複製
	m_img = COPY_RESOURCE("BossEnemy", CImage);
	m_img.mp_texture->SetFilter(GL_NEAREST);
	//再生アニメーション設定
	m_img.ChangeAnimation(0);
	//座標設定
	m_pos = p;

	m_img.SetSize(100, 100);
	//中心位置設定
	m_img.SetCenter(50, 50);
	//当たり判定用矩形設定
	m_rect = CRect(-30, -30, 30, 35);
	m_rad = (50);
	//ヒットポイント
	m_hp = 150;
	//反転フラグ
	m_flip = flip;
	//着地フラグ
	m_is_ground = true;
	//攻撃番号
	m_attack_no = rand();
	//ダメージ番号
	m_damage_no = -1;

}

void BossEnemy::Update()
{
	//m_img.ChangeAnimation(5);
	//m_img.UpdateAnimation();
	m_pos_old = m_pos;
	//メニューを探索し、型変換してエネミーにもメニューを開いたとき動きを止める処理をする
	if (Menyu* menyu = dynamic_cast<Menyu*>(Base::FindObject(eType_Menyu))) {
		//メニューを生成したときにプレイヤーの動きを止める
		if (menyu->hyouzi != 0) {//メニューの表示が０以外動きを止める
			return;
		}
	}
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

void BossEnemy::Draw()
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

void BossEnemy::Collision(Base* b)
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
				int Damage = s->lv;
				Base* player = Base::FindObject(eType_Player);
				Player* p = dynamic_cast<Player*>(player);
				if (p->soubi[0] >= 0) {
					int item = ItemBag::m_item_list[p->soubi[0]];
					ItemDate* d = &Item_Date[item];
					Damage += d->Attack;
				}

				m_hp -= Damage;
				if (m_hp <= 0) {
					m_state = eState_Down;
				}
				else {
					m_state = eState_Damage;
				}
				Base::Add(new Effect("Effect", m_pos + CVector2D(0, 0), m_flip));
			}
		}
		break;
	case eType_Player:
	case eType_Enemy:
	case eType_Enemy1:
	case eType_Enemy2:
	case eType_Enemy3:
	case eType_Enemy4:
	case eType_Enemy5:
		Base::CollisionCharctor(this, b);
		break;

	}
}
BossEnemy::BossEnemy() :
	Base(eType_ItemManeger)
{
	Map* m = dynamic_cast<Map*>(Base::FindObject(eType_Map));
	//アイテムの乱数
	for (int i = 0; i < 10; i++) {
		int x = rand() % 14;
		int y = rand() % 14;
		int t = m->GetTip(x, y);

		//床か壁かを判定する
		if (t == 1) {
			Base::Add(new BossEnemy(CVector2D(x * MAP_TIP_SIZE + 50, y * MAP_TIP_SIZE + 50), true));
		}
	}
}
static TexAnim BossEnemyIdleD[] = {

	{ 0,6 },
	{ 4,6 },
	{ 8,6 },
	{ 12,6 },
};
static TexAnim BossEnemyIdleU[] = {

	{ 1,6 },
	{ 5,6 },
	{ 9,6 },
	{ 13,6 },
};
static TexAnim BossEnemyIdleL[] = {

	{ 2,6 },
	{ 6,6 },
	{ 10,6 },
	{ 14,6 },
};
static TexAnim BossEnemyIdleR[] = {

	{ 3,6 },
	{ 7,6 },
	{ 11,6 },
	{ 15,6 },
};
static TexAnim BossEnemyAttack01[] = {
	{ 0,10 },
	{ 0,10 },
	{ 0,10 },
	{ 0,10 },
	{ 0,10 },
	{ 0,10 },
	{ 0,10 },
	{ 0,10 },
	{ 0,10 },
	{ 0,10 },
	{ 0,10 },
	{ 0,10 },
	{ 0,10 },
	{ 0,10 },
	{ 0,10 },
	{ 0,10 },
	{ 0,10 },
	{ 0,10 },
	{ 0,10 },
	{ 0,10 },
	{ 0,10 },
	{ 0,10 },
	{ 0,10 },
	{ 0,10 },
	{ 0,10 },
	{ 0,10 },
	{ 0,10 },
	{ 25,10 },
	{ 25,10 },
	{ 0,10 },
	{ 0,10 },
	{ 0,10 },
	{ 0,10 },
	{ 0,10 },
	{ 0,10 },
	{ 0,10 },
	{ 0,10 },
	{ 0,10 },
	{ 0,10 },
};
static TexAnim BossEnemyDamage[] = {
	{ 17,1 },
	{ 16,1 },
};
static TexAnim BossEnemyDown[] = {
	{ 13,2 },
	{ 18,2 },
	{ 13,2 },
	{ 18,2 },
};
TexAnimData BossEnemy_anim_data[] = {
	ANIMDATA(BossEnemyIdleD),
	ANIMDATA(BossEnemyIdleL),
	ANIMDATA(BossEnemyIdleR),
	ANIMDATA(BossEnemyIdleU),
	ANIMDATA(BossEnemyAttack01),
	ANIMDATA(BossEnemyAttack01),
	ANIMDATA(BossEnemyAttack01),
	ANIMDATA(BossEnemyAttack01),
	ANIMDATA(BossEnemyDamage),
	ANIMDATA(BossEnemyDown),
};
//Enemy1