#pragma once
#include"Item.h"

class ItemBag {
public:
	//�����Ă���A�C�e����ۑ����郊�X�g
	static std::list<Item*> m_item_list;
	//���ݑI�𒆂̃A�C�e���|�C���^�[
	static Item* m_select_item;
private:
	//�A�C�e���̍ő�ێ���
	static int m_invent_max;
public:
	ItemBag();
	//�C���x���g���[�ɒǉ�
	static void AddItem(Item* item);
	//�C���x���g���[����폜
	static void DeleteItem();
	//�C���x���g���[�̒��g������
	static void SearchItem();
};