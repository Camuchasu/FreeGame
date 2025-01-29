#include "Item.h"
#include"../Base/Base.h"
#include"Map.h"
Item::Item(int itemID,const CVector2D& p, bool flip):
Base(eType_Item),//�����o�ϐ��̏������̌p�����̃N���X�̃R���X�g���N�^�̌Ăяo��
Itemnumber(itemID)
{
	ItemDate& Date = Item_Date[Itemnumber];//&�̓R�s�[�ł͂Ȃ��Q�Ƃ��Ă���鏈�����x�𑁂����Ă����B
	//�摜����
	m_img = COPY_RESOURCE(Date.path, CImage);//�X�g�����O��char�|�C���^���g���Ƃ���c_str�֐����g��
	m_img.mp_texture->SetFilter(GL_NEAREST);
	//���W�ݒ�
	m_pos = p;
	//�摜�T�C�Y�ݒ�
	m_img.SetSize(Date.size);
	//���S�ʒu�ݒ�
	m_img.SetCenter(Date.center);
	m_rect = Date.hitrect;
	//turn = 0;
	motteru = false;
}

void Item::Update()
{
	//if(Item1)
}

void Item::Draw()
{
	if (motteru == false) {
		ItemDate& Date = Item_Date[Itemnumber];
		CRect& r = Date.drawrect;
		m_img.SetRect(r.m_left,r.m_top,r.m_right,r.m_bottom);
		m_img.SetPos(GetScreenPos(m_pos));
		m_img.Draw();
		//�����蔻���`�\��
		//DrawRect();
	}
	
}

void Item::Collision(Base* b)
{
}
ItemManeger* ItemManeger::ms_instance = nullptr;//�ÓI�ȃ����o�[��cpp�Œ�`����,�}�l�[�W���[�֘A�͂P�������Ȃ��Ƃ��̂ݎg����B���̑���ǂ�����ł��g�p���邱�Ƃ��ł���B
ItemManeger::ItemManeger():
Base(eType_ItemManeger)
{
	ms_instance = this;//�������g�̃A�h���X
	Map* m = dynamic_cast<Map*>(Base::FindObject(eType_Map));//FindObject���֐����������d����
	CreateItems(m);
}
void ItemManeger::CreateItems(Map* m)
{	
	//�A�C�e���̗���
	for (int i = 0; i < 5; i++) {
		while (true)
		{
			int x = rand() % 14;
			int y = rand() % 14;
			int t = m->GetTip(x, y);
			int obj = m->GetObj(x, y);
			//�����ǂ��𔻒肷��
			if (t == 1 && obj == -1) {
				int id = rand() % eItem_MAX;
				Base::Add(new Item(id, CVector2D(x * MAP_TIP_SIZE + 50, y * MAP_TIP_SIZE + 50), true));
				m->AddObj(x, y, eType_Item);
				break;
			}
		}
	}
}
ItemDate Item_Date[eItem_MAX] = {
	{"���̃A�[�}�[", "Item",CVector2D(200,200),CVector2D(100,100),CRect(-28, -20, 28,35),CRect(0,0,64,64),1,0,eItemType_soubi},
	{"�񕜖�", "Item1",CVector2D(100,100),CVector2D(50,50),CRect(-28, -20, 28,35),CRect(0,0,32,32),0,0,eItemType_Item_kaihuku},
	{"�񕜖�", "Item1",CVector2D(100,100),CVector2D(50,50),CRect(-28, -20, 28,35),CRect(0,0,32,32),0,0,eItemType_Item_kaihuku},
	{"�S�̌�", "Item3",CVector2D(100,100),CVector2D(50,50),CRect(-28, -20, 28,35),CRect(0,0,32,32),0,1,eItemType_soubi},
};