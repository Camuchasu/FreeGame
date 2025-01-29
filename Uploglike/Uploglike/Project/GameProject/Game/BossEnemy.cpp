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
			/*if (player->m_pos.x < m_pos.x - 90) { //32�h�b�g����Ă���ƈړ�
				//�ړ��ʂ�ݒ�
				m_pos.x += -move_speed;
				AnimNunber = 0;
				//���]�t���O
				m_flip = false;
				move_flag = true;
			}
			//�E�ړ�
			if (player->m_pos.x > m_pos.x + 90) { //32�h�b�g����Ă���ƈړ�
				//�ړ��ʂ�ݒ�
				m_pos.x += move_speed;
				AnimNunber = 1;
				//���]�t���O
				m_flip = false;
				move_flag = true;
			}

			//��ړ�
			if (v.y < -55) {//16�h�b�g����Ă���ƈړ����܂�
				//�ړ��ʂ�ݒ�
				m_pos.y += -move_speed;
				AnimNunber = 2;
				move_flag = true;
			}
			//���ړ�
			if (v.y > +55) {
				//�ړ��͂�ݒ�
				m_pos.y += move_speed;
				AnimNunber = 3;
				move_flag = true;
			}
		}*/
			float a = atan2(v.x, v.y);
			if (v.Length() < 1980) {
				//���U��
				if (a > (DtoR(-135)) && a < DtoR(-45)) {
					//�U����Ԃֈڍs
					m_state = eState_Attack;
					m_attack_no++;  //���i�q�b�g�΍�
					//m_flip = true;  //���]�t���O
					AnimNunber = 3;
				}
				//�E�U��
				if (a < (DtoR(135)) && a > DtoR(45)) {
					//�U����Ԃֈڍs
					m_state = eState_Attack;
					m_attack_no++;  //���i�q�b�g�΍�
					//m_flip = true;  //���]�t���O
					AnimNunber = 2;
				}
				//��U��
				if (abs(a) > (DtoR(135))) {
					//�U����Ԃֈڍs
					m_state = eState_Attack;
					m_attack_no++;  //���i�q�b�g�΍�
					//m_flip = true;  //���]�t���O
					AnimNunber = 1;
				}
				//���U��
				if (abs(a) < (DtoR(45))) {//���W�A���Ȃ��߃΂��P�W�O
					//�U����Ԃֈڍs
					m_state = eState_Attack;
					m_attack_no++;  //���i�q�b�g�΍�
					//m_flip = true;  //���]�t���O
					AnimNunber = 0;
				}
			}
			m_img.ChangeAnimation(eAnimIdleD + AnimNunber);

		}
	}
}

void BossEnemy::StateAttack()
{
	//�U���A�j���[�V�����֕ύX
	m_img.ChangeAnimation(eAnimAttackD + AnimNunber, false);

	if (m_img.GetIndex() == 3) {
		CVector2D pos[] = {
			//�e�����ɓ����蔻�������
		CVector2D(0,64),CVector2D(0,-64),CVector2D(64,0),CVector2D(-64,0),//�����珇�ɉ��A��A�E�A��
		};
		Base::Add((new Slash(m_pos + pos[AnimNunber], m_flip, eType_Enemy_Attack, m_attack_no, lv)));

	}
	//�A�j���[�V�������I��������
	if (m_img.CheckAnimationEnd()) {
		//�ʏ��Ԃֈڍs
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
	//�摜����
	m_img = COPY_RESOURCE("BossEnemy", CImage);
	m_img.mp_texture->SetFilter(GL_NEAREST);
	//�Đ��A�j���[�V�����ݒ�
	m_img.ChangeAnimation(0);
	//���W�ݒ�
	m_pos = p;

	m_img.SetSize(100, 100);
	//���S�ʒu�ݒ�
	m_img.SetCenter(50, 50);
	//�����蔻��p��`�ݒ�
	m_rect = CRect(-30, -30, 30, 35);
	m_rad = (50);
	//�q�b�g�|�C���g
	m_hp = 150;
	//���]�t���O
	m_flip = flip;
	//���n�t���O
	m_is_ground = true;
	//�U���ԍ�
	m_attack_no = rand();
	//�_���[�W�ԍ�
	m_damage_no = -1;

}

void BossEnemy::Update()
{
	//m_img.ChangeAnimation(5);
	//m_img.UpdateAnimation();
	m_pos_old = m_pos;
	//���j���[��T�����A�^�ϊ����ăG�l�~�[�ɂ����j���[���J�����Ƃ��������~�߂鏈��������
	if (Menyu* menyu = dynamic_cast<Menyu*>(Base::FindObject(eType_Menyu))) {
		//���j���[�𐶐������Ƃ��Ƀv���C���[�̓������~�߂�
		if (menyu->hyouzi != 0) {//���j���[�̕\�����O�ȊO�������~�߂�
			return;
		}
	}
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

void BossEnemy::Draw()
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
	//�A�C�e���̗���
	for (int i = 0; i < 10; i++) {
		int x = rand() % 14;
		int y = rand() % 14;
		int t = m->GetTip(x, y);

		//�����ǂ��𔻒肷��
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