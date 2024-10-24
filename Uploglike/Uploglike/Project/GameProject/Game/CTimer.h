#pragma once
#include<map>
#include<iostream>

class CTimer {
private:
	std::map<std::string, float> m_timer_map;
public:
	CTimer();
	~CTimer();
	/*
	//�J�E���g�J�n name:���O var:1F�̃J�E���g�ω��� set_cnt:�J�n���Ԃ��I������ �@
	*/
	bool SetTimer(const char* name, float delta, float set_time);
	float GetTimer(const char* name);
};