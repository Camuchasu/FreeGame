#include "CParam.h"

CParam::CParam(std::string _id, std::string _name)
{
	m_string_map["id"] = _id;
	m_string_map["name"] = _name;
}

void CParam::SetParam(std::string _key, int _data)
{
	m_value_map[_key] = _data;
}

int CParam::GetParam(std::string _key)
{
	return m_value_map[_key];
}

int CParam::ChangeParam(std::string _key, int _delta)
{
	float m = GetParam(_key);
	m += _delta;
	SetParam(_key, m);
	return GetParam(_key);
}
