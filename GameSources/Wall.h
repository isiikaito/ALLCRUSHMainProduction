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
		//���̓n���h���[
		InputHandler<Wall> m_InputHandler;
	public:
		//�\�z�Ɣj��
		Wall(const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Quat& Qt,
			const Vec3& Position
		);
		//�A�N�Z�T
		
		Vec3 GetActionVelocity()const {
			return m_ActionVelocity;
		}
		
		//������
		virtual void OnCreate() override;
		//�Փ˔���
		virtual void OnCollisionEnter(shared_ptr<GameObject>& Other);
		//�R���g���[���[�̃{�^������X
		void OnPushX(shared_ptr<GameObject>& Other);
		void OnPushA() {}

		void OnPushB() {}

		void OnUpdate();
	};
	


}
// namespace basecross
