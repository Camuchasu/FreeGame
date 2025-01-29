#pragma once
#include "../Base/Base.h"
class Bullet : public Base {
public:
    CImage m_img;
    bool m_flip;
public:
    Bullet(const CVector2D& pos, bool flip);
    void Update();
    void Draw();
};

