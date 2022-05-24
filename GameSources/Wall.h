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
		
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;
		int m_HP;

		//���̓n���h���[
		InputHandler2<Wall> m_InputHandler;

		// �G�t�F�N�g�֘A
		float m_TotalTime2;
		bool m_isPlay2;
		Effekseer::Handle m_handle2;
		Effekseer::ManagerRef m_manager2;
		EffekseerRendererDX11::RendererRef m_renderer2;
		Effekseer::EffectRef m_effect2;
		void CreateEffect();
		//HP
		//int HP;
		//void CreateEffect();

	public:
		//�\�z�Ɣj��
		Wall(const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position,
			const int HP
		);
		//�A�N�Z�T
		
		
		//������
		virtual void OnCreate() override;
		//�Փ˔���
		virtual void OnCollisionEnter(shared_ptr<GameObject>& Other);
		virtual void OnDraw() override;

		//�R���g���[���[�̃{�^������X
		void OnPushX();
		void OnPushA() {}
		void OnPushUP() {}
		void OnPushDOWN() {}

		void OnPushB();

		void OnUpdate();
		public:
			
			int GetHP()const {
				return m_HP;
			}
			void SetHP(int HP) {
				m_HP = HP;
			}
	};

}
// namespace basecross
