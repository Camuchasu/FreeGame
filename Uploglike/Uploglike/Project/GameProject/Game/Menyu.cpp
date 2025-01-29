#include "Menyu.h"
#include"../Base/Base.h"
#include"ItemBag.h"
#include"Item.h"
#include "Player.h"
#include "UI.h"

Menyu::Menyu(const CVector2D& p) :
	Base(eType_Menyu), m_menyu_text("C:\\Windows\\Fonts\\msgothic.ttc", 64)
{
	//�摜����
	m_img = COPY_RESOURCE("menyu-", CImage);
	m_img.mp_texture->SetFilter(GL_NEAREST);
	//�Đ��A�j���[�V�����ݒ�
	m_img.ChangeAnimation(0);
	//�摜����
	Itemmenyu_img = COPY_RESOURCE("Itemmenyu-", CImage);
	Itemmenyu_img.mp_texture->SetFilter(GL_NEAREST);
	//�Đ��A�j���[�V�����ݒ�
	Itemmenyu_img.ChangeAnimation(0);
	//�摜����
	m_img1 = COPY_RESOURCE("menyu-", CImage);
	m_img1.mp_texture->SetFilter(GL_NEAREST);
	//�Đ��A�j���[�V�����ݒ�
	m_img1.ChangeAnimation(0);
	//���W�ݒ�
	m_pos = p;
	//�摜�T�C�Y�ݒ�
	m_img.SetSize(450, 450);
	//���S�ʒu�ݒ�
	m_img.SetCenter(225, 225);
	//�摜�T�C�Y�ݒ�
	Itemmenyu_img.SetSize(900, 900);
	//���S�ʒu�ݒ�
	Itemmenyu_img.SetCenter(225, 225);
	stagenumber = 0;
	//�摜�T�C�Y�ݒ�
	m_img1.SetSize(450, 450);
	//���S�ʒu�ݒ�
	m_img1.SetCenter(225, 225);
	Index = 0;
}

int Menyu::Getlinecount() const
{
	if (hyouzi == 0) return 0;
	if (hyouzi == 1) return 4;
	if (hyouzi == 2) return ItemBag::m_item_list.size();
	return 0;
}

void Menyu::Update()
{
	//�{�^�����������Ƃ��Ƀ��j���[�𐶐�����
	if (PUSH(CInput::eButton2)) {
		if (hyouzi == 0) {
			hyouzi = 1;
		}
		else if (hyouzi == 4) {
			hyouzi = 2;
		}
		else if (hyouzi == 3) {
			hyouzi = 2;
		}
		else if (hyouzi == 2) {
			hyouzi = 1;
		}
		else if (hyouzi = 1 && stagenumber == 1 && PUSH(CInput::eButton1)) {
			Player* p = dynamic_cast<Player*>(Base::FindObject(eType_Player));
			UI* u = dynamic_cast<UI*>(Base::FindObject(eType_UI));
			u->AddMessage("�Z�[�u���������ǂȂ�...������@��������˂��I�����I");
			hyouzi = 0;

		}
		
		else{	
			hyouzi = 0;
		}

	}

	if (hyouzi == 1 && stagenumber == 0 && PUSH(CInput::eButton1)) {
		hyouzi = 2;
	}
	else if (hyouzi == 2 && PUSH(CInput::eButton1)) {
		if (ItemBag::m_item_list.size() > 0) {//�T�C�Y���O��葽����΃A�C�e���������Ă��邱�Ƃ��킩��
			int item = ItemBag::m_item_list[stagenumber+Index];
			ItemDate* d = &Item_Date[item];
			if (d->Type== eItemType_Item || d->Type == eItemType_Item_kaihuku) {
				hyouzi = 3;
			}
			if (d->Type == eItemType_soubi ) {
				hyouzi = 4;
			}
		}
	}
	else if (hyouzi == 3 && PUSH(CInput::eButton1)) {
		if (senntaku == 0) {
			int item = ItemBag::m_item_list[stagenumber+Index];//�A�C�e���ԍ����Q�Ƃ���
			ItemDate* d = &Item_Date[item];//�A�C�e���f�[�^��������
			if (d->Type == eItemType_Item_kaihuku) {
				Player* p = dynamic_cast<Player*>(Base::FindObject(eType_Player));
				if (p->m_hp != p->MAXHP) {
					p->m_hp += 5;
					ItemBag::DeleteItem(stagenumber+Index);
					
					hyouzi = 0;
				}
			}
		}
	}
	else if (hyouzi == 4 && PUSH(CInput::eButton1)) {
		if (senntaku == 0) {
			int IDX = stagenumber + Index;
			Player* p = dynamic_cast<Player*>(Base::FindObject(eType_Player));
			p->soubi[0] = IDX;
			UI* u = dynamic_cast<UI*>(Base::FindObject(eType_UI));
			int item = ItemBag::m_item_list[stagenumber + Index];//item�̒��g�Ɋi�[����Ă���̂�m_item_list��item�̎��
			ItemDate* d = &Item_Date[item];
			u->AddMessage("%s�𑕔�����!",d->name);
			hyouzi = 0;

		}
	}
	
	if (hyouzi <= 2) {
		int linecount = Getlinecount();
		//�����
		if (PUSH(CInput::eUp)) {
			stagenumber -= 1;
			if (stagenumber < 0) {
				stagenumber = linecount - 1;
			}

		}
		// ������
		if (PUSH(CInput::eDown)) {
			stagenumber += 1;
			if (stagenumber >= linecount) {
				stagenumber = 0;
			}
		}
		if (Index > 0) {
			// ������
			if (PUSH(CInput::eLeft)) {
				Index -= 8;
				if (Index < 0) {
					Index = linecount - 1;
				}
			}
		}
		if(Index+8 <=ItemBag::m_item_list.size())
		// �E����
		if (PUSH(CInput::eRight)) {
			Index += 8;
			if (Index >= linecount) {
				Index = 0;
			}
		}
	}
	else if (hyouzi == 3|| hyouzi == 4) {
		int linecount = 4;
		//�����
		if (PUSH(CInput::eUp)) {
			senntaku -= 1;
			if (senntaku < 0) {
				senntaku = linecount - 1;
			}

		}
		// ������
		if (PUSH(CInput::eDown)) {
			senntaku += 1;
			if (senntaku >= linecount) {
				senntaku = 0;
			}
		}
	}
	
	//�A�j���[�V�����X�V
	m_img.UpdateAnimation();
}

void Menyu::Draw()
{
	if (hyouzi == 0) {
		return;
	}
	
	if (hyouzi == 1) {
		m_img.SetColor(1, 1, 1, 0.5);
		m_img.SetPos(m_pos);
		m_img.Draw();

		char Menyuname[4][13] = {
			"�A�C�e��",//0
			"�Z�[�u",//1
			"�X�L��",//2
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
	if (hyouzi == 2 || hyouzi == 3 || hyouzi == 4) {
		Itemmenyu_img.SetColor(1, 1, 1, 0.5);
		Itemmenyu_img.SetPos(500, 300);
		Itemmenyu_img.Draw();
		
		for (int i = 0; i < 8; i++){
			if (i + Index >= ItemBag::m_item_list.size()) {
				break;
			}
			//�E�����A�C�e�����o�b�N�Ɏ��[����B
			int item = ItemBag::m_item_list[i+Index];
			ItemDate* d = &Item_Date[item];
			//�E�����A�C�e���̖��O���A�C�e���o�b�N���X�g�ɎQ�Ƃ���
			m_menyu_text.Draw( 400- 25, 175 + i * 100, 0, 0, 0, "%s",d->name);
			if (hyouzi == 2) {
				Player* p = dynamic_cast<Player*>(Base::FindObject(eType_Player));
				int IDX = stagenumber + Index;
				if (i + Index == p->soubi[0] ) {
					m_menyu_text.Draw(370 - 60, 175 + i * 100, 0, 0, 0, "E");
					if (hyouzi = 4) {
						hyouzi = 2;
					}
					
				}
				if (i == stagenumber) {
					m_menyu_text.Draw(370 - 25, 175 + i * 100, 0, 0, 0, ">");
				}
			}
		}
	}
	if (hyouzi == 3) {
		m_img1.SetColor(1, 1, 1, 0.5);
		m_img1.SetPos(700+300, 300);
		m_img1.Draw();

		char Menyuname[4][16] = {
			"�g�p����",//0
			"�̂Ă�",//1
			"������",//2
			"�������Ȃ�"
			//"�^�x��",
		};
		for (int i = 0; i < 4; i++) {
			//�����\��
			m_menyu_text.Draw(700 + 150, 170 + i * 100, 0, 0, 0, Menyuname[i]);

			if (i == senntaku) {
				m_menyu_text.Draw(850 -25, 170 + i * 100, 0, 0, 0, ">");
			}
		}
	}
	if (hyouzi == 4) {
		m_img.SetColor(1, 1, 1, 0.5);
		m_img.SetPos(700 + 300, 300);
		m_img.Draw();

		char Menyuname[4][16] = {
			"��������",//0
			"�̂Ă�",//1
			"������",//2
			"�������Ȃ�"
			//"�H�ׂ�H���⊨�ق���...",
		};
		for (int i = 0; i < 4; i++) {
			//�����\��
			m_menyu_text.Draw(700 + 150, 170 + i * 100, 0, 0, 0, Menyuname[i]);
			if (i == senntaku) {
				m_menyu_text.Draw(850 - 25, 170 + i * 100, 0, 0, 0, ">");
			}
		}
	}
	//�����蔻���`�\��
	//DrawRect();
}

static TexAnim Menyu_Idle[] = {

	{ 1,10 },
	{ 2,10 },
	{ 3,10 },
	{ 4,10 },

};
static TexAnim ItemMenyu_Idle[] = {

	{ 1,10 },
	{ 2,10 },
	{ 3,10 },
	{ 4,10 },

};


TexAnimData Menyu_anim_data[] = {
	ANIMDATA(Menyu_Idle),//�O����
};
TexAnimData ItemMenyu_anim_data[] = {
	ANIMDATA(ItemMenyu_Idle),//�O����
};
//itemhyouzi
//stagenumber