/*!
@file Wall.h
@brief �ǂ̎���
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	///	�����v�Z����Œ�̃{�b�N�X
	//--------------------------------------------------------------------------------------
	class Wall : public GameObject {
		unique_ptr< StateMachine<Wall> > m_StateMachine;
		Vec3 m_Scale;
		Quat m_Qt;
		Vec3 m_Position;
		Vec3 m_ActionVelocity;
	public:
		//�\�z�Ɣj��
		Wall(const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Quat& Qt,
			const Vec3& Position
		);
		//�A�N�Z�T
		void brakeWall();
		Vec3 GetActionVelocity()const {
			return m_ActionVelocity;
		}
		//
		//virtual void OnCollisionEnter(shared_ptr<GameObject>& Other);
		//������
		virtual void OnCreate() override;
		virtual void OnCollisionEnter(shared_ptr<GameObject>& Other);
	};
	//class brakeWallState : public ObjState<Wall>
	//{
	//public:
	//	brakeWallState() {}
	//public:
		//static shared_ptr<brakeWallState> Instance();
		//virtual void Enter(const shared_ptr<Wall>& Obj)override;

	//};


}
// namespace basecross
