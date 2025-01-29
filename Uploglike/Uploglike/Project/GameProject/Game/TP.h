#pragma once
#include "../Base/Base.h"
class Tp :public Base {
private:
    //�摜
    CImage m_img;
    CImage s_img;
    CImage a_img;
    //�ړ��ʒu
    CVector2D m_next_pos;
    
public:
    bool humu;//�p�u���b�N�Ɍ��J���Ȃ��ƃA�N�Z�X���ł��Ȃ��Ȃ�
    Tp(const CVector2D& pos);
    void Draw();
    void Update();
    void Collision();
    CVector2D GetNextPos() {
        return m_next_pos;
    }
};
extern TexAnimData Tp_anim_data[];
