/*!
@file Obstacle.h
@brief�@��Q��
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	class Obstacle : public GameObject {
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;
	public:
		//�\�z�Ɣj��
		Obstacle(const shared_ptr<Stage>& StagePtr, const Vec3& Scale, const Vec3& Rotation, const Vec3& Position);
		virtual ~Obstacle() {}

		//������
		virtual void OnCreate() override;

	};
}
