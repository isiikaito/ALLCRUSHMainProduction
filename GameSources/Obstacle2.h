/*!
@file Obstacle2.h
@brief@áŠQ•¨
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	class Obstacle2 : public GameObject {
		Vec3 m_Scale;    //‘å‚«‚³
		Vec3 m_Rotation; //‰ñ“]
		Vec3 m_Position; //ˆÊ’u
	public:
		//\’z‚Æ”jŠü
		Obstacle2(const shared_ptr<Stage>& StagePtr, const Vec3& Scale, const Vec3& Rotation, const Vec3& Position);
		virtual ~Obstacle2() {}

		//‰Šú‰»
		virtual void OnCreate() override;

	};
}
