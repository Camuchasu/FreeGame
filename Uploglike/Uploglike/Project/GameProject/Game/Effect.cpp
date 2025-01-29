#include "Effect.h"

Effect::Effect(const char* name, const CVector2D& pos, bool flip) :
	Base(eType_Effect)
{
	//�摜����
	m_img = COPY_RESOURCE(name, CImage);
	//���W�ݒ�
	m_pos = pos;
	//�\���T�C�Y�ݒ�
	m_img.SetSize(128, 128);
	//���S�ʒu�ݒ�
	m_img.SetCenter(64, 64);
	//�Đ��A�j���[�V�����ݒ�(�񃋁[�v)
	m_img.ChangeAnimation(0, false);
	//���]�t���O
	m_flip = flip;
}
void Effect::Update()
{
	//�A�j���[�V�����X�V
	m_img.UpdateAnimation();
	//�A�j���[�V�����I���`�F�b�N
	if (m_img.CheckAnimationEnd()) {
		//�G�t�F�N�g���폜
		SetKill();
	}
}

void Effect::Draw() {
	m_img.SetPos(GetScreenPos(m_pos));
	m_img.SetFlipH(m_flip);
	m_img.Draw();
}
static TexAnim panci[] = {

	{ 0,2 },
	{ 1,2 },
	{ 2,2 },
	{ 3,2 },
	{ 4,2 },
	{ 5,2 },
	{ 6,2 },
	{ 7,2 },
	{ 8,2 },
	{ 9,2 },
};
TexAnimData Effect_anim_data[] = {
	ANIMDATA(panci),
	
};