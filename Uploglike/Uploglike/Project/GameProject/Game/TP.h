#pragma once
#include "../Base/Base.h"
class Tp :public Base {
private:
    //画像
    CImage m_img;
    CImage s_img;
    CImage a_img;
    //移動位置
    CVector2D m_next_pos;
    
public:
    bool humu;//パブリックに公開しないとアクセスができなくなる
    Tp(const CVector2D& pos);
    void Draw();
    void Update();
    void Collision();
    CVector2D GetNextPos() {
        return m_next_pos;
    }
};
extern TexAnimData Tp_anim_data[];
