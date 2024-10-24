#pragma once
#pragma once
#include"../Base/Base.h"
#include"CTimer.h"
#include"CParam.h"

class Object : public Base {
public:
	enum {
		//ePhase_TurnBegin,       //ターン開始
		//キー入力　AIの指示待ち
		ePhase_InputBegin,		//入力の開始
		ePhase_Input,			//キー入力待ち。もしくは待機中
		ePhase_Request_AI,

		//リアクション
		ePhase_ReAct,

		//アクション
		ePhase_ActBegin,		//開始
		ePhase_Act,				//実行中
		ePhase_ActEnd,			//終了

		//移動
		ePhase_MoveBegin,		//開始
		ePhase_Move,			//移動中
		ePhase_MoveEnd,			//終了

		ePhase_TurnEnd,//ターン終了　行動の終了
	};
	enum {
		eWaySouth = 0,
		eWaySouthEast,
		eWayEast,
		eWayNouthEast,
		eWayNouth,
		eWayNouthWest,
		eWayWest,
		eWaySouthWest,
	};
	static CVector2D way[8];
public:
	int m_phase;
	int m_old_phase;
	int m_obj_type;
	bool m_exit_list;
public:
	char m_chara_name[255];
	CTimer m_timer;
	CParam m_param;
public:
	Object(int type, int obj_type);
	virtual void Request_AI();
	virtual void MoveMove();
	virtual void ActAct();
	virtual void ReActReAct();
	virtual void InputBegin();
	virtual void Input();
	virtual void MoveDecision();
	virtual void ReAct();
	virtual void ActBegin();
	virtual void Act();
	virtual void ActEnd();
	virtual void MoveBegin();
	virtual void Move();
	virtual void MoveEnd();
	virtual void CollisionCheck_Obj(Object* b);
	void CollisionCheck_ObjSingle();
	void SetDrawPriority();
	CVector2D SearchDir(const CVector2D& p);

	static int DamageFormula(int atk, int def);
};