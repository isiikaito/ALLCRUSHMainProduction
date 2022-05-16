/*!
@file Pillar.h
@brief@αQ¨
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	class Pillar : public GameObject {
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;
	public:
		//\zΖjό
		Pillar(const shared_ptr<Stage>& StagePtr, const Vec3& Scale, const Vec3& Rotation, const Vec3& Position);
		virtual ~Pillar() {}

		//ϊ»
		virtual void OnCreate() override;

	};
}
