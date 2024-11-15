#include "UI.h"
#include"../Base/Base.h"
UI::UI(const CVector2D& p) :
	Base(eType_UI), m_UI_text("C:\\Windows\\Fonts\\msgothic.ttc", 30)
{
	//�摜����
	m_img = COPY_RESOURCE("UI", CImage);
	m_img.mp_texture->SetFilter(GL_NEAREST);
	//�Đ��A�j���[�V�����ݒ�
	m_img.ChangeAnimation(0);
	//���W�ݒ�
	m_pos = p;
	//�摜�T�C�Y�ݒ�
	m_img.SetSize(700,400 );
	//���S�ʒu�ݒ�
	m_img.SetCenter(500, 200);
	message.push_back("��l���͕����Ă���");
	message.push_back("�G����_���[�W���󂯂��I");
	message.push_back("��l���͉񕜂����Ă���");
	message.erase(message.begin());
	//turn = 0;
}

void UI::Update()
{

	//�A�j���[�V�����X�V
	m_img.UpdateAnimation();
}

void UI::Draw()
{
	m_img.SetColor(1, 1, 1, 0.5);
	m_img.SetPos(m_pos);
	m_img.Draw();
	//�����蔻���`�\��
	DrawRect();
	int i = 0;
	for (auto& m : message) {
		m_UI_text.Draw(700, 800+i*60, 0, 0, 0, m.c_str());
		i++;
	}
}


static TexAnim UI_Idle[] = {

	{ 1,50 },
	{ 2,50 },
	
};



TexAnimData UI_anim_data[] = {
	ANIMDATA(UI_Idle),//�O����
	
};
