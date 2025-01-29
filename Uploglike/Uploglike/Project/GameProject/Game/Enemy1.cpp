#include "Enemy1.h"
#include "AnimData.h"
#include "Map.h"
#include"Slash.h"
#include"Effect.h"
#include "Menyu.h"
#include "ItemBag.h"
#include "Player.h"

void Enemy1::StateIdle()
{
	//移動量
	const float move_speed = 3;
	//移動フラグ
	bool move_flag = false;
	//ジャンプ力
	const float jump_pow = 12;
	
	Base* player = Base::FindObject(eType_Player);
	Map* m = dynamic_cast<Map*>(Base::FindObject(eType_Map));
	if (player) {
		CVector2D v = player->m_pos - m_pos;
		if (v.Length() <= 510) {
			//経路探索
			m_root_data = m->CalcRoot(m_pos, player->m_pos);
			if (v.Length() > 16) {
				CVector2D d(0, 0);
				//移動経路がある場合
				if (m_root_data.size > 1 && m_root_data.isFound) {
					CVector2D target = CVector2D(m_root_data.root[1].x, m_root_data.root[1].y) * MAP_TIP_SIZE + CVector2D(MAP_TIP_SIZE / 2, MAP_TIP_SIZE / 2);
					//次の経路の方向へ
					d = (target - m_pos).GetNormalize();
				}
				else {
					//プレイヤーが隣にいる場合
					//プレイヤーの方向へ
					d = v.GetNormalize();
				}
				float j = atan2(d.x, d.y);
				m_pos += d * move_speed;
				//経路探索でプレイヤーが下にいた場合は下を向く
				if (abs(j) < (DtoR(45))) {//ラジアンなためπが１８０
					AnimNunber = 0;
				}
				//経路探索でプレイヤーが上にいた場合は上を向く
				if (abs(j) > (DtoR(135))) {
					AnimNunber = 1;
				}
				//経路探索でプレイヤーが右にいた場合は右を向く
				if (j < (DtoR(135)) && j > DtoR(45)) {
					AnimNunber = 3;
				}
				//経路探索でプレイヤーが左にいた場合は左を向く
				if (j > (DtoR(-135)) && j < DtoR(-45)) {
					AnimNunber = 2;
				}
			}
			else {
				//左移動
				if (player->m_pos.x < m_pos.x - 90) { //32ドット離れていると移動
					//移動量を設定
					m_pos.x += -move_speed;
					AnimNunber = 3;
					//反転フラグ
					m_flip = false;
					move_flag = true;
				}
				//右移動
				if (player->m_pos.x > m_pos.x + 90) { //32ドット離れていると移動
					//移動量を設定
					m_pos.x += move_speed;
					AnimNunber = 2;
					//反転フラグ
					m_flip = false;
					move_flag = true;
				}

				//上移動
				if (v.y < -55) {//16ドット離れていると移動します
					//移動量を設定
					m_pos.y += -move_speed;
					AnimNunber = 1;
					move_flag = true;
				}
				//下移動
				if (v.y > +55) {
					//移動力を設定
					m_pos.y += move_speed;
					AnimNunber = 0;
					move_flag = true;
				}
			}
			float a = atan2(v.x, v.y);
			if (v.Length() < 95) {
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
void Enemy1::StateAttack()
{
	//攻撃アニメーションへ変更
	m_img.ChangeAnimation(eAnimAttackD + AnimNunber, false);

	if (m_img.GetIndex() == 3) {
		CVector2D pos[] = {
			//各方向に当たり判定をつける
		CVector2D(0,64),CVector2D(0,-64),CVector2D(64,0),CVector2D(-64,0),//左から順に下、上、右、左
		};
		Base::Add((new Slash(m_pos + pos[AnimNunber], m_flip, eType_Enemy_Attack, m_attack_no, lv = 2)));

	}
	//アニメーションが終了したら
	if (m_img.CheckAnimationEnd()) {
		//通常状態へ移行
		m_state = eState_Idle;
	}
}
void Enemy1::StateDamage()
{
	m_img.ChangeAnimation(eAnimDamage, false);
	if (m_img.CheckAnimationEnd()) {
		m_state = eState_Idle;
	}
}
void Enemy1::StateDown()
{
	m_img.ChangeAnimation(eAnimDown, false);
	if (m_img.CheckAnimationEnd()) {
		m_kill = true;
		Base* player = Base::FindObject(eType_Player);
		player->exp += 200;
	}
}
Enemy1::Enemy1(const CVector2D& p, bool flip) :Base(eType_Enemy1) {
	//画像複製
	m_img = COPY_RESOURCE("Enemy1", CImage);
	m_img.mp_texture->SetFilter(GL_NEAREST);
	//再生アニメーション設定
	m_img.ChangeAnimation(0);
	//座標設定
	m_pos = p;

	m_img.SetSize(100, 100);
	//中心位置設定
	m_img.SetCenter(50, 50);
	//当たり判定用矩形設定
	m_rect = CRect(-30, -20, 30, 35);
	m_rad = (50);
	//ヒットポイント
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

void Enemy1::Update()
{
	//メニューを生成したときにプレイヤーの動きを止める
	//if (m_menyu->hyouzi == true) {
	//	return;
//	}
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
	if (m_root_data.isFound) {
		for (int i = 1; i < m_root_data.root.size(); i++) {
			CVector2D s = CVector2D(m_root_data.root[i - 1].x, m_root_data.root[i - 1].y) * MAP_TIP_SIZE + CVector2D(MAP_TIP_SIZE / 2, MAP_TIP_SIZE / 2);
			CVector2D e = CVector2D(m_root_data.root[i].x, m_root_data.root[i].y) * MAP_TIP_SIZE + CVector2D(MAP_TIP_SIZE / 2, MAP_TIP_SIZE / 2);
			/*Utility::DrawLine(
				s - m_scroll,
				e - m_scroll,
				CVector4D(1, 1, 1, 1));*/
		}
	}
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
Enemy1::Enemy1() :
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
			Base::Add(new Enemy1(CVector2D(x * MAP_TIP_SIZE + 50, y * MAP_TIP_SIZE + 50), true));
		}
	}
}
static TexAnim enemy1IdleD[] = {

	{ 0,10 },
	{ 4,10 },
	{ 8,10 },
	{ 12,10 },
};
static TexAnim enemy1IdleU[] = {

	{ 1,10 },
	{ 5,10 },
	{ 9,10 },
	{ 13,10 },
};
static TexAnim enemy1IdleL[] = {

	{ 2,10 },
	{ 6,10 },
	{ 10,10 },
	{ 14,10 },
};
static TexAnim enemy1IdleR[] = {

	{ 3,10 },
	{ 7,10 },
	{ 11,10 },
	{ 15,10 },
};
static TexAnim enemy1Attack01[] = {
	{ 10,7 },
	{ 11,7 },
	{ 12,7 },
	{ 13,1 },
	{ 14,7 },
	{ 15,7 },
	{ 16,7 },
};
static TexAnim enemy1Damage[] = {
	{ 13,10 },
};
static TexAnim enemy1Down[] = {
	{ 13,18 },
};
TexAnimData Enemy1_anim_data[] = {
	ANIMDATA(enemy1IdleD),
	ANIMDATA(enemy1IdleU),
	ANIMDATA(enemy1IdleR),
	ANIMDATA(enemy1IdleL),
	ANIMDATA(enemy1Attack01),
	ANIMDATA(enemy1Attack01),
	ANIMDATA(enemy1Attack01),
	ANIMDATA(enemy1Attack01),
	ANIMDATA(enemy1Damage),
	ANIMDATA(enemy1Down),
};
//Enemy1