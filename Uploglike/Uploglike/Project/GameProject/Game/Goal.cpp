#include "Goal.h"
#include "GameData.h"
#include "Title/Title.h"
#include "ItemBag.h"
Goal::Goal()
	:Base(eType_Goal)
{
	//‰æ‘œ•¡»
	m_img = COPY_RESOURCE("Goal", CImage);
	m_img.mp_texture->SetFilter(GL_NEAREST);
	m_img.SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	//p_img = COPY_RESOURCE("goalplayer", CImage);
	//p_img.mp_texture->SetFilter(GL_NEAREST);
}

void Goal::Draw()
{
	//•\Ž¦
	m_img.Draw();
	if (PUSH(CInput::eButton1)) {
		Base::Add(new Title());
		GameData::stage = 0;
		ItemBag::m_item_list.clear();
	}
	//p_img.Draw();
	//“–‚½‚è”»’è‹éŒ`‚Ì•\Ž¦
	//DrawRect();
	//Utility::DrawCircle(GetScreenPos(m_pos), m_rad, CVector4D(1, 1, 1, 1));
}
//Goal