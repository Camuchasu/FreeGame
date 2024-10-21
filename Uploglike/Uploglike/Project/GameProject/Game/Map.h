#pragma once
#include "../Base/Base.h"
//横
#define MAP_WIDTH  150  //250   
//縦
#define MAP_HEIGHT 150  //250
//大きさ
#define MAP_TIP_SIZE  150 //128

class Map : public Base {
private:
	CImage m_img;
public:
	Map();
	void Draw();
	//指定座標のチップ番号取得
	int GetTip(const CVector2D& pos, int* tx = nullptr, int* ty = nullptr);
	//指定列、指定行のマップチップを取得
	int GetTip(int x, int y);
	//マップとの当たり判定
	int CollisionPoint(const CVector2D& pos);
	//マップとの当たり判定
	int CollisionRect(const CVector2D& pos, const CRect& rect);
	int stage[MAP_HEIGHT][MAP_WIDTH];

};

