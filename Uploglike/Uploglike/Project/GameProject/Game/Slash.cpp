#include "Slash.h"
Slash::Slash(const CVector2D& pos, bool flip, int type, int attack_no) : Base(type)
{
	//UŒ‚‚ÌŒü‚«
	m_flip = flip;
	//UŒ‚”­¶ˆÊ’u
	m_pos = pos;
	//“–‚½‚è”»’è—p‹éŒ`
	m_rect = CRect(-30, -32, 30, 32); //-30, -98, 30, 0
	//UŒ‚”Ô†
	m_attack_no = attack_no;

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
