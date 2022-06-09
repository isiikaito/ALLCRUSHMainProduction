/*!
@file Obstacle2.h
@brief�@��Q��
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	class Obstacle2 : public GameObject {
		Vec3 m_Scale;    //�傫��
		Vec3 m_Rotation; //��]
		Vec3 m_Position; //�ʒu
	public:
		//�\�z�Ɣj��
		Obstacle2(const shared_ptr<Stage>& StagePtr, const Vec3& Scale, const Vec3& Rotation, const Vec3& Position);
		virtual ~Obstacle2() {}

		//������
		virtual void OnCreate() override;

	};
}
