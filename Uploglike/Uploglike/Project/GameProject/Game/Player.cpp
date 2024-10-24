#include "Player.h"
#include "Map.h"
Player::Player(const CVector2D& p, bool flip) :
Base(eType_Player){ 
	//画像複製
	m_img = COPY_RESOURCE("Player", CImage);
	//再生アニメーション設定
	m_img.ChangeAnimation(0);
	//座標設定
	m_pos_old = m_pos = p;
	//中心位置設定
	m_img.SetCenter(50, 100);
	m_img.SetSize(200, 200);
	m_rect = CRect(-30, -80, 30, 0);
	//反転フラグ
	//m_flip = flip;
	//通常状態へ
	m_state = eState_Idle;
	//着地フラグ
	m_is_ground = true;
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
	m_img.ChangeAnimation(eAnimAttackD+AnimNunber, false);
	if (m_img.CheckAnimationEnd()) {
		m_state = eState_Idle;
	}
	}
void Player::StateAttack02()
{
	m_img.ChangeAnimation(eAnimAttack02, false);
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
	if (m_is_ground && m_vec.y > GRAVITY * 4)
		m_is_ground = false;
	//重力による落下
	//m_vec.y += GRAVITY;
//	m_pos += m_vec;

	//アニメーション更新
	m_img.UpdateAnimation();
	m_scroll.x = m_pos.x - 1280 / 2;

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


}

static TexAnim playerIdle[] = {

	{ 33,10 },
	{ 34,10 },
	{ 35,10 },
	{ 36,10 },
	{ 37,10 },
};
static TexAnim playerIdle1[] = {

	{ 41,10 },
	{ 42,10 },
	{ 43,10 },
	{ 44,10 },
	{ 45,10 },
	
};
static TexAnim playerIdle2[] = {

	{ 49,10 },
	{ 50,10 },
	{ 51,10 },
	{ 52,10 },
	{ 53,10 },
	
};
static TexAnim playerIdle3[] = {

	{ 57,10 },
	{ 58,10 },
	{ 59,10 },
	{ 60,10 },
	{ 61,10 },
	
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
	{ 7,15 },
};
static TexAnim playerAttackU[] = {
	
	{ 28,10 },
};
static TexAnim playerAttackL[] = {
	//{ 30,15 },
	{ 47,15 },
};
static TexAnim playerAttackR[] = {
	{ 20,15 },
	//{ 24,15 },
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
	{ 64,18 },
	{ 65,18 },
	{ 66,18 },
	{ 67,18 },
	{ 68,18 },
	{ 69,18 },
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
static TexAnim playerDmg[] = {
	{ 19,3 },

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
	ANIMDATA(playerDmg),//6
};
