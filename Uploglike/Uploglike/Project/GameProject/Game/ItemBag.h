#pragma once
#include"Item.h"

class ItemBag {
public:
	//持っているアイテムを保存するリスト
	static std::list<Item*> m_item_list;
	//現在選択中のアイテムポインター
	static Item* m_select_item;
private:
	//アイテムの最大保持数
	static int m_invent_max;
public:
	ItemBag();
	//インベントリーに追加
	static void AddItem(Item* item);
	//インベントリーから削除
	static void DeleteItem();
	//インベントリーの中身を検索
	static void SearchItem();
};