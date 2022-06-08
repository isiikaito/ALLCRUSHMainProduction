/*!
@file FallingRock.h
@brief@—Î
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	class FallingRock : public GameObject {
		Vec3 m_Scale;    //‘å‚«‚³
		Vec3 m_Rotation; //‰ñ“]
		Vec3 m_Position; //ˆÊ’u
		int m_Falling;   //’Œ‚ª‰ó‚ê‚½‚©‚Ç‚¤‚©
	public:
		//\’z‚Æ”jŠü
		FallingRock(const shared_ptr<Stage>& StagePtr, const Vec3& Scale, const Vec3& Rotation, const Vec3& Position);
		virtual ~FallingRock() {}

		
		//‰Šú‰»
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
		int GetFalling()const {
			return m_Falling;
		}
		void SetFalling(int Falling) {
			m_Falling = Falling;
		}
	};
}
