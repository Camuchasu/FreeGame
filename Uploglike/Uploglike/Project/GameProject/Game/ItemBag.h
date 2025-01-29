#pragma once
#include"Item.h"

class ItemBag {
public:
	//持っているアイテムを保存するリスト
	static std::vector<int> m_item_list;//元々item型で宣言することでアイテムの名前で保存していたがTPでアイテムが消えることが判明したため、int型にして数字で保存することにした。
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
	static void DeleteItem(int index);
	//インベントリーの中身を検索
	static void SearchItem();
};