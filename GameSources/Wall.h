/*!
@file Wall.h
@brief �ǂ̎���
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	class Wall : public GameObject {
		
		Vec3 m_Scale;     //�傫��
		Vec3 m_Rotation;  //��]
		Vec3 m_Position;  //�ʒu
		int m_HP;         //�ǂ�HP

		//���̓n���h���[
		InputHandler2<Wall> m_InputHandler;

	public:
		//�\�z�Ɣj��
		Wall(const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position,
			const int HP
		);
		
		//������
		virtual void OnCreate() override;

		
		void OnPushX(){}     //�R���g���[���[�̃{�^������X
		void OnPushA() {}    //�R���g���[���[�̃{�^������A
		void OnPushUP() {}   //�R���g���[���[�̃{�^������\���L�[��
		void OnPushDOWN() {} //�R���g���[���[�̃{�^������\���L�[��
		void OnPushY(){}     //�R���g���[���[�̃{�^������Y
		void OnPushB(){}     //�R���g���[���[�̃{�^������B

		void OnUpdate();
		public:
			//HP�̎擾
			int GetHP()const {
				return m_HP;
			}
			//HP�̊Ǘ�
			void SetHP(int HP) {
				m_HP = HP;
			}
	};

}
// namespace basecross
