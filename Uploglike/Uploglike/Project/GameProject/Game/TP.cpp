#include "TP.h"

Tp::Tp(const CVector2D& pos) :Base(eType_TP)
{
    humu = false;
    m_img = COPY_RESOURCE("Tp", CImage);
    //画像がきれいに見える！
    m_img.mp_texture->SetFilter(GL_NEAREST);
    s_img = COPY_RESOURCE("sirusi", CImage);
    s_img.mp_texture->SetFilter(GL_NEAREST);
    a_img = COPY_RESOURCE("a", CImage);
    a_img.mp_texture->SetFilter(GL_NEAREST);
    //中央位置
    m_img.SetCenter(48, 48);
    //画像表示サイズ
    m_img.SetSize(95, 95);
    s_img.SetSize(95, 95);
    a_img.SetSize(95, 95);
    m_img.ChangeAnimation(0);
    //座標
    m_pos = pos;
    m_rect = CRect(-50, -50, 50, 50);

}

void Tp::Draw()
{
    
    if (humu == true) {
        a_img.SetPos(GetScreenPos(m_pos + CVector2D(-50, -240)));
        a_img.Draw();
        s_img.SetPos(GetScreenPos(m_pos + CVector2D(-50, -150)));
        s_img.Draw();
    }
  
    m_img.SetPos(GetScreenPos(m_pos));
    m_img.Draw();
    //当たり判定矩形表示
   // DrawRect();
}
void Tp::Update()
{
    m_img.ChangeAnimation(0);
    m_img.UpdateAnimation();
    m_img.UpdateAnimation();
}
void Tp::Collision()
{

}
static TexAnim TP[] = {
    { 0,20 },
    { 1,20 },
    { 2,20 },
    { 3,20 },
    { 4,20 },
    { 5,20 },
    { 6,20 },
    { 7,20 },
};
TexAnimData TP_anim_data[] = {
    ANIMDATA(TP),
};
