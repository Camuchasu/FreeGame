#pragma once
#include "../Base/Base.h"

class Item : public Base {
private:
	CImage m_img;
	

public:
	bool motteru;
	Item(const CVector2D& p, bool flip);
	void Update();
	void Draw();
	void Collision(Base* b);

};
class ItemManeger :public Base {
public:
	ItemManeger();
};