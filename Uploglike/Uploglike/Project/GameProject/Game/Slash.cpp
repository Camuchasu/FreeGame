#include "Slash.h"
#include "Enemy.h"
Slash::Slash(const CVector2D& pos, bool flip, int type, int attack_no,int lv) : Base(type)
{
	//UŒ‚‚ÌŒü‚«
	m_flip = flip;
	//UŒ‚”­¶ˆÊ’u
	m_pos = pos;
	//“–‚½‚è”»’è—p‹éŒ`¦Še”»’è‚ð’†S‚ÉÝ’è‚µ‚½‚Ù‚¤‚ª—Ç‚¢
	m_rect = CRect(-30, -28, 30, 50); //-30, -98, 30, 0
	//UŒ‚”Ô†
	m_attack_no = attack_no;
	this->lv = lv;
	//Enemy lv = 2;
	m_count = 1;
}

void Slash::Update()
{
	m_count--;
	if (m_count == 0) {
		SetKill();
	}
}

void Slash::Draw()
{

	//DrawRect();

}
static TexAnim Slash[] = {//‘O

	{ 0,10 },
	{ 1,10 },
	{ 2,10 },
	{ 3,10 },
	{ 4,10 },
	{ 5,10 },
	{ 6,10 },
	{ 7,10 },
	{ 8,10 },
	{ 9,10 },
	{ 10,10 },
	{ 11,10 },
};
TexAnimData Slash_anim_data[] = {
	ANIMDATA(Slash),
	
};