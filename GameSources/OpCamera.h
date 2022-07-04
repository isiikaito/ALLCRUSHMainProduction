/**
* @file OpCamera.h
* @brief �I�[�v�j���O�J�����N���X�̒�`���L�q����Ă���w�b�_�[�t�@�C��
*/

#pragma once
#include "stdafx.h"

namespace basecross{
	//--------------------------------------------------------------------------------------
	//�@���C���̃J�����}��
	//--------------------------------------------------------------------------------------
	class Cameraman : public GameObject {
		float m_ToPlayerLen;
		float m_PPdistance;
		int m_PillarCount;
		float m_TurnTime;
		int m_Turn;
	public:
		//�\�z�Ɣj��
		Cameraman(const shared_ptr<Stage>& StagePtr,
			float ToPlayerLen
		);
		virtual ~Cameraman();
		//������
		virtual void OnCreate() override;
		//����
		virtual void OnUpdate() override;
	};
	//--------------------------------------------------------------------------------------
	//�@�I�[�v�j���O�J�����}��
	//--------------------------------------------------------------------------------------
	class OpeningCameraman : public GameObject {
		Vec3 m_StartPos;
		Vec3 m_EndPos;
		Vec3 m_AtStartPos;
		Vec3 m_AtEndPos;
		Vec3 m_AtPos;
		float m_TotalTime;
		
		//�X�e�[�g�}�V�[��
		unique_ptr< StateMachine<OpeningCameraman> >  m_StateMachine;
	public:
		//�\�z�Ɣj��
		OpeningCameraman(const shared_ptr<Stage>& StagePtr);
		virtual ~OpeningCameraman();
		//������
		virtual void OnCreate() override;
		//����
		virtual void OnUpdate() override;
		//�A�N�Z�T
		const unique_ptr<StateMachine<OpeningCameraman>>& GetStateMachine() {
			return m_StateMachine;
		}

		Vec3 GetAtPos() const {
			return m_AtPos;
		}
		void ToGoalEnterBehavior();
		void ToStartEnterBehavior();
		bool ExcuteBehavior(float totaltime);
		void EndStateEnterBehavior();
	};

	//--------------------------------------------------------------------------------------
	//	class OpeningCameramanToGoalState : public ObjState<OpeningCameraman>;
	//--------------------------------------------------------------------------------------
	class OpeningCameramanToGoalState : public ObjState<OpeningCameraman>
	{
		OpeningCameramanToGoalState() {}
	public:
		static shared_ptr<OpeningCameramanToGoalState> Instance();
		virtual void Enter(const shared_ptr<OpeningCameraman>& Obj)override;
		virtual void Execute(const shared_ptr<OpeningCameraman>& Obj)override;
		virtual void Exit(const shared_ptr<OpeningCameraman>& Obj)override;
	};

	//--------------------------------------------------------------------------------------
	//	class OpeningCameramanToStartState : public ObjState<OpeningCameraman>;
	//--------------------------------------------------------------------------------------
	class OpeningCameramanToStartState : public ObjState<OpeningCameraman>
	{
		OpeningCameramanToStartState() {}
	public:
		static shared_ptr<OpeningCameramanToStartState> Instance();
		virtual void Enter(const shared_ptr<OpeningCameraman>& Obj)override;
		virtual void Execute(const shared_ptr<OpeningCameraman>& Obj)override;
		virtual void Exit(const shared_ptr<OpeningCameraman>& Obj)override;
	};

	//--------------------------------------------------------------------------------------
	//	class OpeningCameramanEndState : public ObjState<OpeningCameraman>;
	//--------------------------------------------------------------------------------------
	class OpeningCameramanEndState : public ObjState<OpeningCameraman>
	{
		OpeningCameramanEndState() {}
	public:
		static shared_ptr<OpeningCameramanEndState> Instance();
		virtual void Enter(const shared_ptr<OpeningCameraman>& Obj)override;
		virtual void Execute(const shared_ptr<OpeningCameraman>& Obj)override;
		virtual void Exit(const shared_ptr<OpeningCameraman>& Obj)override;
	};
}
//end basecross
