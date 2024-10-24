#include "CTimer.h"

CTimer::CTimer()
{
}

CTimer::~CTimer()
{
	m_timer_map.clear();
}

bool CTimer::SetTimer(const char* name, float delta, float set_time)
{
	if (delta > 0) {
		//カウントアップ
		m_timer_map[name] += delta;
		if (m_timer_map[name] >= set_time) {
			m_timer_map[name] = 0;
			return true;
		}
	}
	if (delta < 0) {
		//カウントダウン
		//キーが存在しないならタイマーをセットする
		m_timer_map[name] =
			(m_timer_map.count(name) == 0) ?
			set_time + delta : m_timer_map[name] + delta;

		if (m_timer_map[name] <= 0) {
			m_timer_map[name] = set_time;
			return true;
		}
	}
	return false;
}

float CTimer::GetTimer(const char* name)
{
	//もしカウント対象があるなら
	if (m_timer_map.count(name) != 0) {
		return m_timer_map[name];
	}//ないなら0をかえす
	return 0;
}
