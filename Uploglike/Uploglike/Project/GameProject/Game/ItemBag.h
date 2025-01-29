#pragma once
#include"Item.h"

class ItemBag {
public:
	//�����Ă���A�C�e����ۑ����郊�X�g
	static std::vector<int> m_item_list;//���Xitem�^�Ő錾���邱�ƂŃA�C�e���̖��O�ŕۑ����Ă�����TP�ŃA�C�e���������邱�Ƃ������������߁Aint�^�ɂ��Đ����ŕۑ����邱�Ƃɂ����B
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
	static void DeleteItem(int index);
	//�C���x���g���[�̒��g������
	static void SearchItem();
};