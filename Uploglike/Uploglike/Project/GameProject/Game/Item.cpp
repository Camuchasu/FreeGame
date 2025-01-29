#include "Item.h"
#include"../Base/Base.h"
#include"Map.h"
Item::Item(int itemID,const CVector2D& p, bool flip):
Base(eType_Item),//メンバ変数の初期化の継承元のクラスのコンストラクタの呼び出し
Itemnumber(itemID)
{
	ItemDate& Date = Item_Date[Itemnumber];//&はコピーではなく参照してくれる処理速度を早くしてくれる。
	//画像複製
	m_img = COPY_RESOURCE(Date.path, CImage);//ストリングでcharポインタを使うときはc_str関数を使う
	m_img.mp_texture->SetFilter(GL_NEAREST);
	//座標設定
	m_pos = p;
	//画像サイズ設定
	m_img.SetSize(Date.size);
	//中心位置設定
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
		//当たり判定矩形表示
		//DrawRect();
	}
	
}

void Item::Collision(Base* b)
{
}
ItemManeger* ItemManeger::ms_instance = nullptr;//静的なメンバーはcppで定義する,マネージャー関連は１個しか作らないときのみ使える。その代わりどこからでも使用することができる。
ItemManeger::ItemManeger():
Base(eType_ItemManeger)
{
	ms_instance = this;//自分自身のアドレス
	Map* m = dynamic_cast<Map*>(Base::FindObject(eType_Map));//FindObject利便性が高いが重たい
	CreateItems(m);
}
void ItemManeger::CreateItems(Map* m)
{	
	//アイテムの乱数
	for (int i = 0; i < 5; i++) {
		while (true)
		{
			int x = rand() % 14;
			int y = rand() % 14;
			int t = m->GetTip(x, y);
			int obj = m->GetObj(x, y);
			//床か壁かを判定する
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
	{"金のアーマー", "Item",CVector2D(200,200),CVector2D(100,100),CRect(-28, -20, 28,35),CRect(0,0,64,64),1,0,eItemType_soubi},
	{"回復薬", "Item1",CVector2D(100,100),CVector2D(50,50),CRect(-28, -20, 28,35),CRect(0,0,32,32),0,0,eItemType_Item_kaihuku},
	{"回復薬", "Item1",CVector2D(100,100),CVector2D(50,50),CRect(-28, -20, 28,35),CRect(0,0,32,32),0,0,eItemType_Item_kaihuku},
	{"鉄の剣", "Item3",CVector2D(100,100),CVector2D(50,50),CRect(-28, -20, 28,35),CRect(0,0,32,32),0,1,eItemType_soubi},
};