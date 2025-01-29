#pragma once
#include "../Base/Base.h"
//��
#define MAP_WIDTH  25  //250   
//�c
#define MAP_HEIGHT 17  //250
//�傫��
#define MAP_TIP_SIZE  100 //128
// <summary>
/// �}�X�p�\����
/// </summary>
struct CELL {
	int x;	//��
	int y;	//�s
	bool operator ==(const CELL& c)const {
		return (x == c.x && y == c.y);
	}
	CELL operator +(const CELL& c)const {
		return { x + c.x,y + c.y };
	}
};
/// <summary>
/// �ړ��o�H�p�\����
/// </summary>
struct RootData {
	std::vector<CELL> root;	//�o�H�̔z��
	bool isFound;			//�o�H������������
	int size;				//�o�H�̐�
	RootData() {
		root.clear();
		isFound = false;
		size = 999999;
	}
};
struct MapObjData {
	CELL cell;
	int type;
};
class Map : public Base {
private:
	CImage m_img;
	int m_stageNunber;
	CVector2D seisei(CELL* outcell = nullptr);
	int cnt = 0;
	std::vector<MapObjData> m_ObjList;//�x�N�^�[���g�����Ƃŗv�f���𑝌����邱�Ƃ��ł���
	 
public:
	//static int cnt;
	Map(int stageNunber);
	void Draw();
	//�w����W�̃`�b�v�ԍ��擾
	int GetTip(const CVector2D& pos, int* tx = nullptr, int* ty = nullptr);
	//�w���A�w��s�̃}�b�v�`�b�v���擾
	int GetTip(int x, int y);
	void AddObj(int x, int y, int type);
	int GetObj(int x, int y);
	//�}�b�v�Ƃ̓����蔻��
	int CollisionPoint(const CVector2D& pos);
	//�}�b�v�Ƃ̓����蔻��
	int CollisionRect(const CVector2D& pos, const CRect& rect);
	int stage[MAP_HEIGHT][MAP_WIDTH];
	/// <summary>
/// �o�H�T���i�ċA�I�Ăяo���p�j
/// </summary>
/// <param name="pod">���݂̈ʒu</param>
/// <param name="end">�ړI�n</param>
/// <param name="step">�o���n����̋���</param>
/// <param name="step_data">�����̋L�^�p</param>
/// <param name="root">�ړ��o�H�L�^�p</param>
/// <returns>�S�[���ɂ��ǂ蒅���邩</returns>
	bool CalcRoot(const CELL pos, const CELL& end, int step, int step_data[MAP_HEIGHT][MAP_WIDTH], RootData& root);
	/// <summary>
	/// �o�H�T��
	/// </summary>
	/// <param name="start">�o���n</param>
	/// <param name="end">�ړI�n</param>
	/// <returns>�o�H�̃f�[�^</returns>
	RootData CalcRoot(const CVector2D& start, const CVector2D& end);

	/// <summary>
	/// ���W���牽�s����ɕϊ�
	/// </summary>
	/// <param name="pos">�ʒu</param>
	/// <returns>���s����ڂ��̍\����</returns>
	CELL GetCell(const CVector2D& pos);

};


