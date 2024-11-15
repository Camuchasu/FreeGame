#include "Enemy3.h"

#include "AnimData.h"
#include "Map.h"
#include"Slash.h"
void Enemy3::StateIdle()
{
	//�ړ���
	const float move_speed = 5;
	//�ړ��t���O
	bool move_flag = false;
	//�W�����v��
	const float jump_pow = 12;
	Base* player = Base::FindObject(eType_Player);
	if (player) {
		CVector2D v = player->m_pos - m_pos;
		if (abs(v.x) <= 510) {

			//���ړ�
			if (player->m_pos.x < m_pos.x - 32) { //32�h�b�g����Ă���ƈړ�
				//�ړ��ʂ�ݒ�
				m_pos.x += -move_speed;
				AnimNunber = 0;
				//���]�t���O
				m_flip = true;
				move_flag = true;
			}
			//�E�ړ�
			if (player->m_pos.x > m_pos.x + 32) { //32�h�b�g����Ă���ƈړ�
				//�ړ��ʂ�ݒ�
				m_pos.x += move_speed;
				AnimNunber = 1;
				//���]�t���O
				m_flip = false;
				move_flag = true;
			}
	
			//��ړ�
			if (v.y < -32) {//16�h�b�g����Ă���ƈړ����܂�
				//�ړ��ʂ�ݒ�
				m_pos.y += -move_speed;
				AnimNunber = 2;
				move_flag = true;
			}
			//���ړ�
			if (v.y > +32) {
				//�ړ��͂�ݒ�
				m_pos.y += move_speed;
				AnimNunber = 3;
				move_flag = true;
			}
		}
		//���U��
		if (v.Length() < 24) {
			//�U����Ԃֈڍs
			m_state = eState_Attack;
			m_attack_no++;  //���i�q�b�g�΍�
			//m_flip = true;  //���]�t���O

		}
		m_img.ChangeAnimation(eState_Idle);
	}
}
void Enemy3::StateAttack()
{
	//�U���A�j���[�V�����֕ύX
	m_img.ChangeAnimation(eState_Attack, false);
	//?�Ԗڂ̃A�j���[�V�����̎�����
	/*if (m_img.GetIndex() == ? ) {
		if (m_flip) {
			Base::Add(new Slash(m_pos + CVector2D(-64, -64), m_flip, eType_Enemmy_Attack, m_attack_no));
		}
		else {
			Base::Add(new Slash(m_pos + CVector2D(64, -64), m_flip, eType_Enemmy_Attack, m_attack_no));
		}
	}*/
	//�A�j���[�V�������I��������
	if (m_img.CheckAnimationEnd()) {
		//�ʏ��Ԃֈڍs
		m_state = eState_Idle;
	}
}
void Enemy3::StateDamage()
{
	//m_img.ChangeAnimation(eAnimDamage, false);
	if (m_img.CheckAnimationEnd()) {
		m_state = eState_Idle;
	}
}
void Enemy3::StateDown()
{
	//m_img.ChangeAnimation(eAnimDown, false);
}
Enemy3::Enemy3(const CVector2D& p, bool flip) :Base(eType_Enemy) {
	//�摜����
	m_img = COPY_RESOURCE("Enemy3", CImage);
	m_img.mp_texture->SetFilter(GL_NEAREST);
	//�Đ��A�j���[�V�����ݒ�
	m_img.ChangeAnimation(0);
	//���W�ݒ�
	m_pos = p;

	m_img.SetSize(100, 100);
	//���S�ʒu�ݒ�
	m_img.SetCenter(50, 50);
	//�����蔻��p��`�ݒ�
	m_rect = CRect(-30, -15, 30, 35);

	//�q�b�g�|�C���g
	m_hp = 5;
	//���]�t���O
	m_flip = flip;
	//���n�t���O
	m_is_ground = true;
	//�U���ԍ�
	m_attack_no = rand();
	//�_���[�W�ԍ�
	m_damage_no = -1;

}

void Enemy3::Update()
{
	//m_img.ChangeAnimation(5);
	//m_img.UpdateAnimation();
	m_pos_old = m_pos;
	switch (m_state) {
		//�ʏ���
	case eState_Idle:
		StateIdle();
		break;
		//�U�����
	case eState_Attack:
		StateAttack();
		break;
		//�_���[�W���
	case eState_Damage:
		StateDamage();
		break;

		//�_�E�����
	case eState_Down:
		StateDown();
		break;
	}
	//�����Ă����痎������Ԃֈڍs
	//if (m_is_ground && m_vec.y > GRAVITY * 4)
	//	m_is_ground = false;
	//�d�͂ɂ�闎��
	//m_vec.y += GRAVITY;
	//m_pos += m_vec;

	//�A�j���[�V�����X�V
	m_img.UpdateAnimation();


}

void Enemy3::Draw()
{
	//�ʒu�ݒ�
	m_img.SetPos(GetScreenPos(m_pos));
	//���]�ݒ�
	m_img.SetPos(GetScreenPos(m_pos));
	//���]�ݒ�
	m_img.SetFlipH(m_flip);
	//�`��
	m_img.Draw();
	//�����蔻���`�\��
	DrawRect();
}

void Enemy3::Collision(Base* b)
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
				//�������x���Z�b�g
				m_vec.y = 0;
				//�ڒn�t���OON
				m_is_ground = true;
			}
		}
	case eType_Player_Attack:
		//Slash�^�փL���X�g�A�^�ϊ��ł�����
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
static TexAnim enemy3IdleD[] = {

	{ 0,6 },
	{ 4,6 },
	{ 8,6 },
	{ 12,6 },
};
static TexAnim enemy3IdleU[] = {

	{ 0,6 },
	{ 4,6 },
	{ 8,6 },
	{ 12,6 },
};
static TexAnim enemy3IdleL[] = {

	{ 0,6 },
	{ 4,6 },
	{ 8,6 },
	{ 12,6 },
};
static TexAnim enemy3IdleR[] = {

	{ 3,6 },
	{ 7,6 },
	{ 11,6 },
	{ 15,6 },
};
static TexAnim enemy3Attack01[] = {
	{ 10,7 },
	{ 11,7 },
	{ 12,7 },
	{ 13,7 },
	{ 14,7 },
	{ 15,7 },
	{ 16,7 },
};
static TexAnim enemy3Damage[] = {
	{ 16,10 },
	{ 17,10 },
};
static TexAnim enemy3Down[] = {
	{ 18,18 },
	{ 19,18 },
	{ 20,18 },
	{ 21,18 },
	{ 22,18 },
	{ 23,18 },
	{ 24,18 },
};
TexAnimData Enemy3_anim_data[] = {
	ANIMDATA(enemy3IdleD),
	ANIMDATA(enemy3IdleU),
	ANIMDATA(enemy3IdleL),
	ANIMDATA(enemy3IdleR),
	ANIMDATA(enemy3Attack01),
	ANIMDATA(enemy3Damage),
	ANIMDATA(enemy3Down),
};
//Enemy1