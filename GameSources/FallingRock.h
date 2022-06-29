/*!
@file FallingRock.h
@brief�@����
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	class FallingRock : public GameObject {
		Vec3 m_Scale;    //�傫��
		Vec3 m_Rotation; //��]
		Vec3 m_Position; //�ʒu
		int m_Falling;   //�����j�󂳂ꂽ���ǂ���
	public:
		//�\�z�Ɣj��
		FallingRock(const shared_ptr<Stage>& StagePtr, const Vec3& Scale, const Vec3& Rotation, const Vec3& Position);
		virtual ~FallingRock() {}

		
		//������
		virtual void OnCreate() override;
		virtual void OnUpdate() override;

		//�����j�󂳂ꂽ���ǂ����̎擾
		int GetFalling()const {
			return m_Falling;
		}

		//�����j�󂳂�Ă��邩�ǂ����̊Ǘ�
		void SetFalling(int Falling) {
			m_Falling = Falling;
		}
	};
}
