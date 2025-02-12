#include "Player.h"
#include "Map.h"
#include "Item.h"
#include "Menyu.h"
#include "Slash.h"
#include "Effect.h"
#include "TP.h"
#include "GameData.h"
#include "UI.h"
#include"Goal.h"
#include "ItemBag.h"
#include "GameOver.h"
#include "Title/Title.h"
Player::Player(const CVector2D& p, bool flip) :
	Base(eType_Player) {
	//画像複製
	m_img = COPY_RESOURCE("Player", CImage);
	m_img.mp_texture->SetFilter(GL_NEAREST);
	//再生アニメーション設定
	m_img.ChangeAnimation(0);
	//座標設定
	m_pos_old = m_pos = p;
	//中心位置設定
	m_img.SetCenter(50, 50);
	m_img.SetSize(100, 100);
	m_rect = CRect(-30, -25, 30, 47);
	m_rad = (30);
	//反転フラグ
	//m_flip = flip;
	//通常状態へ
	m_state = eState_Idle;
	//攻撃番号
	m_attack_no = rand();
	//着地フラグ
	m_is_ground = true;
	m_menyu = nullptr;
	//メニュー生成
	Base::Add(m_menyu = new Menyu(CVector2D(225, 250)));
	m_hp = 20;
	MAXHP = 20;
	soubi[0] = -1;
	soubi[1] = +1;

}



void Player::StateIdle()
{
	//移動量
	const float move_speed = 8;//8
	//移動フラグ
	bool move_flag = false;
	//上移動
	if (HOLD(CInput::eDown)) {
		//移動量を設定
		m_pos.y -= -move_speed;
		AnimNunber = 0;
		move_flag = true;
	}
	//下移動
	if (HOLD(CInput::eUp)) {
		//移動量を設定
		m_pos.y += -move_speed;
		AnimNunber = 1;
		move_flag = true;
	}
	//左移動
	if (HOLD(CInput::eLeft)) {
		//移動量を設定
		m_pos.x += -move_speed;
		AnimNunber = 3;
		move_flag = true;
	}
	//右移動
	if (HOLD(CInput::eRight)) {
		//移動量を設定
		m_pos.x += move_speed;
		AnimNunber = 2;
		move_flag = true;
	}
	//攻撃
	if (PUSH(CInput::eButton1)) {
		//攻撃状態へ移行
		
		m_state = eState_Attack01;
	}
	m_img.ChangeAnimation(eAnimIdle0 + AnimNunber);
}

void Player::StateAttack01()
{
	m_img.ChangeAnimation(eAnimAttackD + AnimNunber, false);
	if (m_img.GetIndex() == 0) {
		CVector2D pos[] = {
			//各方向に当たり判定をつける
		CVector2D(0,64),CVector2D(0,-64),CVector2D(64,0),CVector2D(-64,0),
		};
			Base::Add((new Slash(m_pos + pos[AnimNunber], m_flip, eType_Player_Attack, m_attack_no,lv)));
		
	}
	if (m_img.CheckAnimationEnd()) {
		m_state = eState_Idle;
	}
}
void Player::StateDamage()
{
	m_img.ChangeAnimation(eAnimDmg, false);
	if (m_img.CheckAnimationEnd()) {
		m_state = eState_Idle;
	}
}
void Player::StateDown()
{
	m_img.ChangeAnimation(eAnimDown, false);
	if (m_img.CheckAnimationEnd()) {
		m_kill = true;
	}
}

void Player::StateCrouchi()
{
	m_img.ChangeAnimation(eAnimCrouchi, false);
	if (m_img.CheckAnimationEnd()) {
		m_state = eState_Idle;

	}
}


void Player::Update() {

	m_pos_old = m_pos;
	//メニューを生成したときにプレイヤーの動きを止める
	if (m_menyu->hyouzi != 0 ) {//メニューの表示が０以外動きを止める
			return;
	}
	switch (m_state) {
		//通常状態
	case eState_Idle:
		StateIdle();
		break;
	
		//攻撃状態
	case eState_Attack01:
		StateAttack01();
		break;

		//ダメージ状態
	case eState_Damage:
		StateDamage();
		break;
		//ダウン状態
	case eState_Down:
		StateDown();
		break;
		//しゃがみ状態
	case eState_Crouchi:
		StateCrouchi();
		break;
	}
	//落ちていたら落下中状態へ移行
	//if (m_is_ground && m_vec.y > GRAVITY * 4)
	//	m_is_ground = false;
	//重力による落下
	//m_vec.y += GRAVITY;
//	m_pos += m_vec;

	//アニメーション更新
	m_img.UpdateAnimation();
	
	
	m_scroll.x = m_pos.x - 1280 / 2;
	m_scroll.y = m_pos.y - 720 / 2;
	//左方向をマップに合わせる
	if (m_scroll.x < 0) {
		m_scroll.x = 0;
	}
	//右方向をマップに合わせる
	if (m_scroll.x > 500) {
		m_scroll.x = 500;
	}
	//上方向をマップに合わせる
	if (m_scroll.y < 0) {
		m_scroll.y = 0;
	}
	//下方向をマップに合わせる
	if (m_scroll.y > 350) {
		m_scroll.y = 350;
	}
	//レベルアップの処理
	if (exp >= 100*lv) {
		exp -= 100 * lv;
		lv++;
		//m_HP = 15;
		m_hp++;
	}
}

void Player::Draw() {
	//位置設定
	m_img.SetPos(GetScreenPos(m_pos));
	//反転設定
	m_img.SetFlipH(m_flip);
	//描画
	m_img.Draw();
	//当たり判定矩形表示
	//DrawRect();
}
void Player::Collision(Base* b)
{
	switch (b->m_type) {
	case eType_Map:
		if (Map* m = dynamic_cast<Map*>(b)) {
			int t;
			t = m->CollisionRect(CVector2D(m_pos.x, m_pos_old.y), m_rect);
			if (t >= 5) {
				m_pos.x = m_pos_old.x;
			}
			t = m->CollisionRect(CVector2D(m_pos_old.x, m_pos.y), m_rect);
			if (t >= 5) {
				m_pos.y = m_pos_old.y;

			}
		}
		break;
	case eType_Enemy_Attack:
		//Slash型へキャスト、型変換できたら
		if (Slash* s = dynamic_cast<Slash*>(b)) {
			//矩形同士の判定を行う
			if (Base::CollisionRect(this, s)) {
				int Damage = s->lv;
				if (soubi[0] >= 0) {
					int item = ItemBag::m_item_list[soubi[0]];
					ItemDate* d = &Item_Date[item];
					Damage -= d->Dihxend;
				}
				m_hp -= Damage;
				if (m_hp <= 0) {
					m_state = eState_Down;
					if (!Base::FindObject(eType_GameOver)) {
						KillAll();
						Base::Add(new GameOver());
					}
				}
				else {
					m_state = eState_Damage;
				}
				Base::Add(new Effect("Effect", m_pos + CVector2D(0, 0), m_flip));
			}
		}
		break;
	case eType_Item:
		if (Item* m = dynamic_cast<Item*>(b)) {//アイテムに型変換
			if (m->motteru == false) {
				if (Base::CollisionRect(this, b)) {//アイテムの当たり判定
					m->motteru = true;
					m->SetKill();
					ItemBag::AddItem(m);

				}
			}

		}
		break;
	case eType_HP:
		if (Base::CollisionRect(this, b)) {
			float MAXHP = 15;
			if(eItemType_Item_kaihuku)
			if (m_hp <= MAXHP) {
				m_hp += 1;
				b->SetKill();
			}
		}
	case eType_Goal:
		if (Base::CollisionRect(this, b)) {
			b->SetKill();

		}
		break;
	case eType_TP:
		if (Tp* t = dynamic_cast<Tp*>(b)) {//アイテムに型変換
			if (Base::CollisionRect(this, b)) {
				t->humu = true;
				if (PUSH(CInput::eButton6)) {//ボタンをおしたらワープ可能
					Base::Kill(
						~(1 << eType_Player//~←をつけることで逆になるこの二つ以外は消すになる
							| 1 << eType_Scene
							| 1 << eType_Menyu
							| 1 << eType_ItemMenyu
							| 1 << eType_ItemManeger
							| 1 << eType_UI));

					GameData::stage++;
					if (GameData::stage < 5) {
						Map* m = new Map(rand() % 4 + 1);
						Base::Add(m);
						ItemManeger::CreateItems(m);
					}
					else if (GameData::stage == 5) {
						Base::Add(new Map(5));
					}
					else {
						KillAll();
						Base::Add(new Goal());
						/*if (PUSH(CInput::eButton1)) {
							Base::Add(new Title());
							GameData::stage = 0;
						}*/
					}
				}

			}
			else {
				t->humu = false;
			}
		}
		break;
	}
}
static TexAnim playerIdle[] = {//前

	{ 0,10 },
	{ 4,10 },
	{ 8,10 },
	{ 12,10 },
};
static TexAnim playerIdle1[] = {//下

	{ 1,10 },
	{ 5,10 },
	{ 9,10 },
	{ 13,10 },
};
static TexAnim playerIdle2[] = {//右

	{ 3,10 },
	{ 7,10 },
	{ 11,10 },
	{ 15,10 },
};
static TexAnim playerIdle3[] = {//左

	{ 2,10 },
	{ 6,10 },
	{ 10,10 },
	{ 14,10 },
};
static TexAnim playerBattou[] = {

	{ 38,10 },
	{ 39,10 },
	{ 40,10 },
	{ 41,10 },

};
static TexAnim playerStep[] = {
	{ 8,7 },
	{ 9,7 },
	{ 10,7 },
	{ 11,7 },
	{ 12,7 },
	{ 13,7 },

};
static TexAnim playerAttackD[] = {
	{ 20,1 },
	{ 20,15 },
};
static TexAnim playerAttackU[] = {
	{ 18,1 },
	{ 18,10 },
};
static TexAnim playerAttackL[] = {
	{ 17,1 },
	{ 17,15 },
};
static TexAnim playerAttackR[] = {
	{ 19,1 },
	{ 19,15 },
};
static TexAnim playerAttack02[] = {
	{ 23,5 },
	{ 24,5 },

};
static TexAnim playerCrouchi[] = {
	{ 4,2 },
	{ 5,2 },
	{ 6,2 },
	{ 7,2 },

};
static TexAnim playerDown[] = {
	{ 24,18 },
};
static TexAnim playerJumpup[] = {
	{ 15,3 },
	{ 16,3 },
	{ 17,3 },
	{ 18,3 },
};
static TexAnim playerJumpDown[] = {
	{ 19,3 },
	{ 20,3 },
	{ 21,3 },
	{ 22,3 },
	{ 23,3 },
};
static TexAnim playerDmgD[] = {
	{ 28,2 },
	{ 32,2 },
};
TexAnimData player_anim_data[] = {
	ANIMDATA(playerIdle),//前方向
	ANIMDATA(playerIdle1),//後ろ方向
	ANIMDATA(playerIdle2),//左方向
	ANIMDATA(playerIdle3),//右方向
	ANIMDATA(playerStep),//2
	ANIMDATA(playerJumpup),//7
	ANIMDATA(playerJumpDown),//8
	ANIMDATA(playerAttackD),//3
	ANIMDATA(playerAttackL),
	ANIMDATA(playerAttackR),
	ANIMDATA(playerAttackU),
	ANIMDATA(playerCrouchi),//5
	ANIMDATA(playerBattou),//1
	ANIMDATA(playerAttack02),//4
	ANIMDATA(playerDown),//6
	ANIMDATA(playerDmgD),//6
};
//m_menyu
//MAXHP
//soubi