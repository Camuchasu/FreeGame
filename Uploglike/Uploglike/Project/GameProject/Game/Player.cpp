#include "Player.h"
#include "Map.h"
#include "Item.h"
#include "Menyu.h"
Player::Player(const CVector2D& p, bool flip) :
Base(eType_Player){ 
	//�摜����
	m_img = COPY_RESOURCE("Player", CImage);
	//�Đ��A�j���[�V�����ݒ�
	m_img.ChangeAnimation(0);
	//���W�ݒ�
	m_pos_old = m_pos = p;
	//���S�ʒu�ݒ�
	m_img.SetCenter(100, 100);
	m_img.SetSize(200, 200);
	m_rect = CRect(-30, -25, 30, 47);
	//���]�t���O
	//m_flip = flip;
	//�ʏ��Ԃ�
	m_state = eState_Idle;
	//���n�t���O
	m_is_ground = true;
	m_menyu = nullptr;
	//���j���[����
	Base::Add(m_menyu = new Menyu(CVector2D(225, 250)));
	Base::Add(m_menyu = new Menyu(CVector2D(225, 250)));
	}


void Player::StateIdle()
{
	

	//�ړ���
	const float move_speed = 8;//8
	//�ړ��t���O
	bool move_flag = false;
	//��ړ�
	if (HOLD(CInput::eDown)) {
		//�ړ��ʂ�ݒ�
		m_pos.y -= -move_speed;
		AnimNunber = 0;
		move_flag = true;
	}
	//���ړ�
	if (HOLD(CInput::eUp)) {
		//�ړ��ʂ�ݒ�
		m_pos.y += -move_speed;
		AnimNunber = 1;
		move_flag = true;
	}
	//���ړ�
	if (HOLD(CInput::eLeft)) {
		//�ړ��ʂ�ݒ�
		m_pos.x += -move_speed;
		AnimNunber = 3;
		move_flag = true;
	}
	//�E�ړ�
	if (HOLD(CInput::eRight)) {
		//�ړ��ʂ�ݒ�
		m_pos.x += move_speed;
		AnimNunber = 2;
		move_flag = true;
	}
	//�U��
	if (PUSH(CInput::eButton1)) {
		//�U����Ԃֈڍs
		
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
	//���j���[�𐶐������Ƃ��Ƀv���C���[�̓������~�߂�
	if (m_menyu->hyouzi == true) {
		return;
	}
	switch (m_state) {
		//�ʏ���
	case eState_Idle:
		StateIdle();
		break;
	
		//�U�����
	case eState_Attack01:
		StateAttack01();
		break;

		//�_���[�W���
	case eState_Damage:
		StateDamage();
		break;
		//�_�E�����
	case eState_Down:
		StateDown();
		break;
		//���Ⴊ�ݏ��
	case eState_Crouchi:
		StateCrouchi();
		break;
	}
	//�����Ă����痎������Ԃֈڍs
	if (m_is_ground && m_vec.y > GRAVITY * 4)
		m_is_ground = false;
	//�d�͂ɂ�闎��
	//m_vec.y += GRAVITY;
//	m_pos += m_vec;

	//�A�j���[�V�����X�V
	m_img.UpdateAnimation();
	//�X�N���[��
	m_scroll.x = m_pos.x - 1280 / 2;
	m_scroll.y = m_pos.y - 720 / 2;
	
}

void Player::Draw() {
	//�ʒu�ݒ�
	m_img.SetPos(GetScreenPos(m_pos));
	//���]�ݒ�
	m_img.SetFlipH(m_flip);
	//�`��
	m_img.Draw();
	//�����蔻���`�\��
	DrawRect();
}
void Player::Collision(Base* b)
{
	switch (b->m_type) {
	case eType_Map:
		if (Map* m = dynamic_cast<Map*>(b)) {//
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
	case eType_Item:
		if (Item* m = dynamic_cast<Item*>(b)) {
			if (Base::CollisionRect(this, b)) {
				m->motteru = true;
			}
		}
	}
	
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
	ANIMDATA(playerIdle),//�O����
	ANIMDATA(playerIdle1),//������
	ANIMDATA(playerIdle2),//������
	ANIMDATA(playerIdle3),//�E����
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
//hyouzi