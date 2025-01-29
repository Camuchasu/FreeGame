#include "ItemBag.h"
std::vector<int> ItemBag::m_item_list;
ItemBag::ItemBag()
{

}

void ItemBag::AddItem(Item* item)
{
	
	m_item_list.push_back(item->Itemnumber);
}

void ItemBag::DeleteItem(int index)
{
	m_item_list.erase(m_item_list.begin() + index);
}

void ItemBag::SearchItem()
{
}
