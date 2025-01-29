#pragma once
#include "../Base/Base.h"
//横
#define MAP_WIDTH  25  //250   
//縦
#define MAP_HEIGHT 17  //250
//大きさ
#define MAP_TIP_SIZE  100 //128
// <summary>
/// マス用構造体
/// </summary>
struct CELL {
	int x;	//列
	int y;	//行
	bool operator ==(const CELL& c)const {
		return (x == c.x && y == c.y);
	}
	CELL operator +(const CELL& c)const {
		return { x + c.x,y + c.y };
	}
};
/// <summary>
/// 移動経路用構造体
/// </summary>
struct RootData {
	std::vector<CELL> root;	//経路の配列
	bool isFound;			//経路が見つかったか
	int size;				//経路の数
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
	std::vector<MapObjData> m_ObjList;//ベクターを使うことで要素数を増減することができる
	 
public:
	//static int cnt;
	Map(int stageNunber);
	void Draw();
	//指定座標のチップ番号取得
	int GetTip(const CVector2D& pos, int* tx = nullptr, int* ty = nullptr);
	//指定列、指定行のマップチップを取得
	int GetTip(int x, int y);
	void AddObj(int x, int y, int type);
	int GetObj(int x, int y);
	//マップとの当たり判定
	int CollisionPoint(const CVector2D& pos);
	//マップとの当たり判定
	int CollisionRect(const CVector2D& pos, const CRect& rect);
	int stage[MAP_HEIGHT][MAP_WIDTH];
	/// <summary>
/// 経路探索（再帰的呼び出し用）
/// </summary>
/// <param name="pod">現在の位置</param>
/// <param name="end">目的地</param>
/// <param name="step">出発地からの距離</param>
/// <param name="step_data">距離の記録用</param>
/// <param name="root">移動経路記録用</param>
/// <returns>ゴールにたどり着けるか</returns>
	bool CalcRoot(const CELL pos, const CELL& end, int step, int step_data[MAP_HEIGHT][MAP_WIDTH], RootData& root);
	/// <summary>
	/// 経路探索
	/// </summary>
	/// <param name="start">出発地</param>
	/// <param name="end">目的地</param>
	/// <returns>経路のデータ</returns>
	RootData CalcRoot(const CVector2D& start, const CVector2D& end);

	/// <summary>
	/// 座標から何行何列に変換
	/// </summary>
	/// <param name="pos">位置</param>
	/// <returns>何行何列目かの構造体</returns>
	CELL GetCell(const CVector2D& pos);

};


