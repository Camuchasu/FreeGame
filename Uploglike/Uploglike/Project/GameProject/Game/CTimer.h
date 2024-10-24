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
	//カウント開始 name:名前 var:1Fのカウント変化量 set_cnt:開始時間か終了時間 　
	*/
	bool SetTimer(const char* name, float delta, float set_time);
	float GetTimer(const char* name);
};