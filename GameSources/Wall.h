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
		InputHandler2<Wall> m_InputHandler;

		// �G�t�F�N�g�֘A
		float m_TotalTime;
		bool m_isPlay;
		Effekseer::Handle m_handle;
		Effekseer::ManagerRef m_manager;
		EffekseerRendererDX11::RendererRef m_renderer;
		Effekseer::EffectRef m_effect;

		void CreateEffect();

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
		//�`��
		virtual void OnDraw() override;
		//�Փ˔���
		virtual void OnCollisionEnter(shared_ptr<GameObject>& Other);
		//�R���g���[���[�̃{�^������X
		void OnPushX();
		void OnPushA() {}

		void OnPushB();

		void OnUpdate();
	};
	


}
// namespace basecross
