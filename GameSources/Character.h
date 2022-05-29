/*!
@file Character.h
@brief キャラクターなど
*/

#pragma once
#include "stdafx.h"

namespace basecross{
	//--------------------------------------------------------------------------------------
	//　球体のカメラマン
	//--------------------------------------------------------------------------------------
	class Cameraman : public GameObject {
		float m_ToPlayerLen;
	public:
		//構築と破棄
		Cameraman(const shared_ptr<Stage>& StagePtr,
			float ToPlayerLen
		);
		virtual ~Cameraman();
		//初期化
		virtual void OnCreate() override;
		//操作
		virtual void OnUpdate() override;
	};
	//--------------------------------------------------------------------------------------
	//　オープニングカメラマン
	//--------------------------------------------------------------------------------------
	class OpeningCameraman : public GameObject {
		Vec3 m_StartPos;
		Vec3 m_EndPos;
		Vec3 m_AtStartPos;
		Vec3 m_AtEndPos;
		Vec3 m_AtPos;
		float m_TotalTime;
		//ステートマシーン
		unique_ptr< StateMachine<OpeningCameraman> >  m_StateMachine;
	public:
		//構築と破棄
		OpeningCameraman(const shared_ptr<Stage>& StagePtr);
		virtual ~OpeningCameraman();
		//初期化
		virtual void OnCreate() override;
		//操作
		virtual void OnUpdate() override;
		//アクセサ
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

	//--------------------------------------------------------------------------------------
	//　エンディングカメラマン
	//--------------------------------------------------------------------------------------
	//class EndingCameraman : public GameObject {
	//	Vec3 m_StartPos;
	//	Vec3 m_EndPos;
	//	Vec3 m_AtStartPos;
	//	Vec3 m_AtEndPos;
	//	Vec3 m_AtPos;
	//	float m_TotalTime;
	//	//ステートマシーン
	//	unique_ptr< StateMachine<EndingCameraman> >  m_StateMachine;
	//public:
	//	//構築と破棄
	//	EndingCameraman(const shared_ptr<Stage>& StagePtr);
	//	virtual ~EndingCameraman();
	//	//初期化
	//	virtual void OnCreate() override;
	//	//操作
	//	virtual void OnUpdate() override;
	//	//アクセサ
	//	const unique_ptr<StateMachine<EndingCameraman>>& GetStateMachine() {
	//		return m_StateMachine;
	//	}

	//	Vec3 GetAtPos() const {
	//		return m_AtPos;
	//	}
	//	//void ToGoalEnterBehavior();
	//	//void ToStartEnterBehavior();
	//	//bool ExcuteBehavior(float totaltime);
	//	//void EndStateEnterBehavior();
	//};

	////--------------------------------------------------------------------------------------
	////	class EndingCameramanToGoalState : public ObjState<EndingCameraman>;
	////--------------------------------------------------------------------------------------
	//class EndingCameramanToGoalState : public ObjState<EndingCameraman>
	//{
	//	EndingCameramanToGoalState() {}
	//public:
	//	static shared_ptr<EndingCameramanToGoalState> Instance();
	//	virtual void Enter(const shared_ptr<EndingCameraman>& Obj)override;
	//	virtual void Execute(const shared_ptr<EndingCameraman>& Obj)override;
	//	virtual void Exit(const shared_ptr<EndingCameraman>& Obj)override;
	//};

	////--------------------------------------------------------------------------------------
	////	class EndingCameramanToStartState : public ObjState<EndingCameraman>;
	////--------------------------------------------------------------------------------------
	//class EndingCameramanToStartState : public ObjState<EndingCameraman>
	//{
	//	EndingCameramanToStartState() {}
	//public:
	//	static shared_ptr<EndingCameramanToStartState> Instance();
	//	virtual void Enter(const shared_ptr<EndingCameraman>& Obj)override;
	//	virtual void Execute(const shared_ptr<EndingCameraman>& Obj)override;
	//	virtual void Exit(const shared_ptr<EndingCameraman>& Obj)override;
	//};

	////--------------------------------------------------------------------------------------
	////	class EndingCameramanEndState : public ObjState<EndingCameraman>;
	////--------------------------------------------------------------------------------------
	//class EndingCameramanEndState : public ObjState<EndingCameraman>
	//{
	//	EndingCameramanEndState() {}
	//public:
	//	static shared_ptr<EndingCameramanEndState> Instance();
	//	virtual void Enter(const shared_ptr<EndingCameraman>& Obj)override;
	//	virtual void Execute(const shared_ptr<EndingCameraman>& Obj)override;
	//	virtual void Exit(const shared_ptr<EndingCameraman>& Obj)override;
	//};

}
//end basecross
