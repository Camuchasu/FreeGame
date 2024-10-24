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
		//�J�E���g�A�b�v
		m_timer_map[name] += delta;
		if (m_timer_map[name] >= set_time) {
			m_timer_map[name] = 0;
			return true;
		}
	}
	if (delta < 0) {
		//�J�E���g�_�E��
		//�L�[�����݂��Ȃ��Ȃ�^�C�}�[���Z�b�g����
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
	//�����J�E���g�Ώۂ�����Ȃ�
	if (m_timer_map.count(name) != 0) {
		return m_timer_map[name];
	}//�Ȃ��Ȃ�0��������
	return 0;
}
