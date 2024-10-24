#pragma once
#pragma once
#include <map>
#include <iostream>

class CParam {
private:
	std::map<std::string, std::string> m_string_map;
	std::map<std::string, int> m_value_map;
public:
	CParam(std::string _id, std::string _name);
	//パラメーターの設定
	void SetParam(std::string _key, int _data);
	int GetParam(std::string _key);
	int ChangeParam(std::string _key, int _delta);
};