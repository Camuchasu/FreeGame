#pragma once
#include "../Base/Base.h"
class Map;//�O�錾���ƃ|�C���^�݂̂ōs����B������cpp�ŃC���N���[�h�����Ȃ���΂Ȃ�Ȃ��B
enum {
	eItemType_Item,
	eItemType_soubi,
	eItemType_Item_kaihuku,
	//eItemType_soubiA,
};
struct ItemDate
{
	char name[128];
	std::string path;
	CVector2D size;
	CVector2D center;
	CRect hitrect;
	CRect drawrect;
	int Dihxend;
	int Attack;
	int Type;
};
enum {
	eItem_bougu,
	eItem_kaihuku,
	eItem_yumi,
	eItem_sukil,
	
	eItem_MAX
};
extern ItemDate Item_Date[eItem_MAX];
class Item : public Base {
private:
	CImage m_img;
public:
	int Itemnumber;
	bool motteru;
	Item(int itemID, const CVector2D& p, bool flip);
	void Update();
	void Draw();
	void Collision(Base* b);

};
class ItemManeger :public Base {
private:
	static ItemManeger* ms_instance;//ms�͐ÓI�ȃ����o�ϐ�
public:
	ItemManeger();
	static void CreateItems(Map* m);
};