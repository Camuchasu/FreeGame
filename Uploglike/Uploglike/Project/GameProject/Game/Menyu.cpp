#include "Menyu.h"
#include"../Base/Base.h"
Menyu::Menyu(const CVector2D& p) :
	Base(eType_Menyu), m_menyu_text("C:\\Windows\\Fonts\\msgothic.ttc", 64)
{
	//�摜����
	m_img = COPY_RESOURCE("menyu-", CImage);
	m_img.mp_texture->SetFilter(GL_NEAREST);
	//�Đ��A�j���[�V�����ݒ�
	m_img.ChangeAnimation(0);
	//���W�ݒ�
	m_pos = p;
	//�摜�T�C�Y�ݒ�
	m_img.SetSize(450, 450);
	//���S�ʒu�ݒ�
	m_img.SetCenter(225, 225);
	stagenumber = 0;

}

void Menyu::Update()
{
	
	//�{�^�����������Ƃ��Ƀ��j���[�𐶐�����
	if (PUSH(CInput::eButton2)) {
		if (hyouzi == true) {
			hyouzi = false;
		}
		else {
			hyouzi = true;
			
		}
	}
	
	//�����
	if (PUSH(CInput::eUp)) {
		stagenumber -= 1;
		if (stagenumber < 0) {
			stagenumber = 3;
		}

	}
	// ������
	if (PUSH(CInput::eDown)) {
		stagenumber += 1;
		if (stagenumber >3) {
			stagenumber = 0;
		}
	}
	//�A�j���[�V�����X�V
	m_img.UpdateAnimation();
}

void Menyu::Draw()
{
	if (hyouzi == false) {
		return;
	}
	m_img.SetColor(1, 1, 1, 0.5);
	m_img.SetPos(m_pos);
	m_img.Draw();
	//�����蔻���`�\��
	DrawRect();

	char Menyuname[4][13] = {
		"�A�C�e��",//0
		"�Z�[�u",//1
		"���[�h",//2
		"�^�C�g��",//3
	};
	for (int i = 0; i < 4; i++) {
		//�����\��
		m_menyu_text.Draw(125, 125 + i * 100, 0, 0, 0, Menyuname[i]);

		if (i == stagenumber) {
			m_menyu_text.Draw(125 - 25, 125 + i * 100, 0, 0, 0, ">");
		}


	}
}

static TexAnim Menyu_Idle[] = {

	{ 1,10 },
	{ 2,10 },
	{ 3,10 },
	{ 4,10 },

};



TexAnimData Menyu_anim_data[] = {
	ANIMDATA(Menyu_Idle),//�O����

};
//hyouzi