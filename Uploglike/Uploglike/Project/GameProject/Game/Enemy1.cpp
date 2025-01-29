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
	//�ړ���
	const float move_speed = 3;
	//�ړ��t���O
	bool move_flag = false;
	//�W�����v��
	const float jump_pow = 12;
	
	Base* player = Base::FindObject(eType_Player);
	Map* m = dynamic_cast<Map*>(Base::FindObject(eType_Map));
	if (player) {
		CVector2D v = player->m_pos - m_pos;
		if (v.Length() <= 510) {
			//�o�H�T��
			m_root_data = m->CalcRoot(m_pos, player->m_pos);
			if (v.Length() > 16) {
				CVector2D d(0, 0);
				//�ړ��o�H������ꍇ
				if (m_root_data.size > 1 && m_root_data.isFound) {
					CVector2D target = CVector2D(m_root_data.root[1].x, m_root_data.root[1].y) * MAP_TIP_SIZE + CVector2D(MAP_TIP_SIZE / 2, MAP_TIP_SIZE / 2);
					//���̌o�H�̕�����
					d = (target - m_pos).GetNormalize();
				}
				else {
					//�v���C���[���ׂɂ���ꍇ
					//�v���C���[�̕�����
					d = v.GetNormalize();
				}
				float j = atan2(d.x, d.y);
				m_pos += d * move_speed;
				//�o�H�T���Ńv���C���[�����ɂ����ꍇ�͉�������
				if (abs(j) < (DtoR(45))) {//���W�A���Ȃ��߃΂��P�W�O
					AnimNunber = 0;
				}
				//�o�H�T���Ńv���C���[����ɂ����ꍇ�͏������
				if (abs(j) > (DtoR(135))) {
					AnimNunber = 1;
				}
				//�o�H�T���Ńv���C���[���E�ɂ����ꍇ�͉E������
				if (j < (DtoR(135)) && j > DtoR(45)) {
					AnimNunber = 3;
				}
				//�o�H�T���Ńv���C���[�����ɂ����ꍇ�͍�������
				if (j > (DtoR(-135)) && j < DtoR(-45)) {
					AnimNunber = 2;
				}
			}
			else {
				//���ړ�
				if (player->m_pos.x < m_pos.x - 90) { //32�h�b�g����Ă���ƈړ�
					//�ړ��ʂ�ݒ�
					m_pos.x += -move_speed;
					AnimNunber = 3;
					//���]�t���O
					m_flip = false;
					move_flag = true;
				}
				//�E�ړ�
				if (player->m_pos.x > m_pos.x + 90) { //32�h�b�g����Ă���ƈړ�
					//�ړ��ʂ�ݒ�
					m_pos.x += move_speed;
					AnimNunber = 2;
					//���]�t���O
					m_flip = false;
					move_flag = true;
				}

				//��ړ�
				if (v.y < -55) {//16�h�b�g����Ă���ƈړ����܂�
					//�ړ��ʂ�ݒ�
					m_pos.y += -move_speed;
					AnimNunber = 1;
					move_flag = true;
				}
				//���ړ�
				if (v.y > +55) {
					//�ړ��͂�ݒ�
					m_pos.y += move_speed;
					AnimNunber = 0;
					move_flag = true;
				}
			}
			float a = atan2(v.x, v.y);
			if (v.Length() < 95) {
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
void Enemy1::StateAttack()
{
	//�U���A�j���[�V�����֕ύX
	m_img.ChangeAnimation(eAnimAttackD + AnimNunber, false);

	if (m_img.GetIndex() == 3) {
		CVector2D pos[] = {
			//�e�����ɓ����蔻�������
		CVector2D(0,64),CVector2D(0,-64),CVector2D(64,0),CVector2D(-64,0),//�����珇�ɉ��A��A�E�A��
		};
		Base::Add((new Slash(m_pos + pos[AnimNunber], m_flip, eType_Enemy_Attack, m_attack_no, lv = 2)));

	}
	//�A�j���[�V�������I��������
	if (m_img.CheckAnimationEnd()) {
		//�ʏ��Ԃֈڍs
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
	//�摜����
	m_img = COPY_RESOURCE("Enemy1", CImage);
	m_img.mp_texture->SetFilter(GL_NEAREST);
	//�Đ��A�j���[�V�����ݒ�
	m_img.ChangeAnimation(0);
	//���W�ݒ�
	m_pos = p;

	m_img.SetSize(100, 100);
	//���S�ʒu�ݒ�
	m_img.SetCenter(50, 50);
	//�����蔻��p��`�ݒ�
	m_rect = CRect(-30, -20, 30, 35);
	m_rad = (50);
	//�q�b�g�|�C���g
	m_hp = 10;
	//���]�t���O
	m_flip = flip;
	//���n�t���O
	m_is_ground = true;
	//�U���ԍ�
	m_attack_no = rand();
	//�_���[�W�ԍ�
	m_damage_no = -1;

}

void Enemy1::Update()
{
	//���j���[�𐶐������Ƃ��Ƀv���C���[�̓������~�߂�
	//if (m_menyu->hyouzi == true) {
	//	return;
//	}
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

void Enemy1::Draw()
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
Enemy1::Enemy1() :
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