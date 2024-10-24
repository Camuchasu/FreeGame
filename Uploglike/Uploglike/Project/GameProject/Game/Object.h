#pragma once
#pragma once
#include"../Base/Base.h"
#include"CTimer.h"
#include"CParam.h"

class Object : public Base {
public:
	enum {
		//ePhase_TurnBegin,       //�^�[���J�n
		//�L�[���́@AI�̎w���҂�
		ePhase_InputBegin,		//���͂̊J�n
		ePhase_Input,			//�L�[���͑҂��B�������͑ҋ@��
		ePhase_Request_AI,

		//���A�N�V����
		ePhase_ReAct,

		//�A�N�V����
		ePhase_ActBegin,		//�J�n
		ePhase_Act,				//���s��
		ePhase_ActEnd,			//�I��

		//�ړ�
		ePhase_MoveBegin,		//�J�n
		ePhase_Move,			//�ړ���
		ePhase_MoveEnd,			//�I��

		ePhase_TurnEnd,//�^�[���I���@�s���̏I��
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