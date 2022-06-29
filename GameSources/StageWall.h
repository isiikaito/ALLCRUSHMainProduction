/*!
@file StageWall.h
@brief �X�e�[�W�̕�
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	class StageWall : public GameObject {
		Vec3 m_Scale;   //�傫��
		Vec3 m_Rotation;//��]
		Vec3 m_Position;//�ʒu
	public:
		//�\�z�Ɣj��
		StageWall(const shared_ptr<Stage>& StagePtr, const Vec3& Scale,const Vec3& Rotation,const Vec3& Position);
		virtual ~StageWall() {}
		
		//������
		virtual void OnCreate() override;

	};
}

