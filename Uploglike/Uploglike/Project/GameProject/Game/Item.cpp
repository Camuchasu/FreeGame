#include "Item.h"
#include"../Base/Base.h"
#include"Map.h"
Item::Item(const CVector2D& p, bool flip):
Base(eType_Item)
{
	//画像複製
	m_img = COPY_RESOURCE("Item", CImage);
	//座標設定
	m_pos = p;
	//画像サイズ設定
	m_img.SetSize(180, 180);
	//中心位置設定
	m_img.SetCenter(90,90);
	m_rect = CRect(-28, -20, 28,35);//左，うえ、右、したた
	//turn = 0;
	motteru = false;
}

void Item::Update()
{
}

void Item::Draw()
{
	if (motteru == false) {
		m_img.SetRect(0, 0, 64, 64);
		m_img.SetPos(GetScreenPos(m_pos));
		m_img.Draw();
		//当たり判定矩形表示
		DrawRect();
	}
	
}

void Item::Collision(Base* b)
{
}

ItemManeger::ItemManeger():
Base(eType_ItemManeger)
{
	Map* m = dynamic_cast<Map*>(Base::FindObject(eType_Map));
	//アイテムの乱数
	for (int i = 0; i < 10; i++) {
		int x = rand() % 14;
		int y = rand() % 14;
		int t = m->GetTip(x, y);
		
		//床か壁かを判定する
		if (t == 1) {
			Base::Add(new Item(CVector2D(x * MAP_TIP_SIZE+50, y * MAP_TIP_SIZE+50), true));
		}
	}
}
