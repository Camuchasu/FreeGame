#pragma once
#include"../Base/Base.h"

class Slash : public Base {
private:
	//画像オブジェクト
	CImage m_img;
	//攻撃の向き
	bool m_flip;
	//攻撃番号
	int m_attack_no;
	
	int m_count;
public:
	Slash(const CVector2D& pos, bool flip, int type, int attack_no,int lv = 1);//引数を追加すると別のクラスのスラッシュに引数を追加することができる
	void Update();
	void Draw();
	int GetAttackNo() {
		return m_attack_no;
	}
};

extern TexAnimData Slash_anim_data[];