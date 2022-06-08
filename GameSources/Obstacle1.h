/*!
@file Obstacle1.h
@brief@αQ¨
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	class Obstacle1 : public GameObject {
		Vec3 m_Scale;   //ε«³
		Vec3 m_Rotation;//ρ]
		Vec3 m_Position;//Κu
	public:
		//\zΖjό
		Obstacle1(const shared_ptr<Stage>& StagePtr, const Vec3& Scale, const Vec3& Rotation, const Vec3& Position);
		virtual ~Obstacle1() {}

		//ϊ»
		virtual void OnCreate() override;

	};
}
