/*!
@file Pillar.h
@brief@áŠQ•¨
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	class Pillar : public GameObject {
		Vec3 m_Scale;    //‘å‚«‚³
		Vec3 m_Rotation; //‰ñ“]
		Vec3 m_Position; //ˆÊ’u
	public:
		//\’z‚Æ”jŠü
		Pillar(const shared_ptr<Stage>& StagePtr, const Vec3& Scale, const Vec3& Rotation, const Vec3& Position);
		virtual ~Pillar() {}

		//‰Šú‰»
		virtual void OnCreate() override;

	};
}
