/*!
@file Pillar.h
@brief�@��Q��
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	class Pillar : public GameObject {
		Vec3 m_Scale;    //�傫��
		Vec3 m_Rotation; //��]
		Vec3 m_Position; //�ʒu
	public:
		//�\�z�Ɣj��
		Pillar(const shared_ptr<Stage>& StagePtr, const Vec3& Scale, const Vec3& Rotation, const Vec3& Position);
		virtual ~Pillar() {}

		//������
		virtual void OnCreate() override;

	};
}
