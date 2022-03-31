/*!
@file GameStage.h
@brief ゲームステージ
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class stageObject :public GameObject {
		Vec3 m_scale;
		Vec3 m_rotation;
		Vec3 m_position;
		float m_UPic;
		float m_VPic;
		wstring m_textureName;
	public:
		stageObject(const shared_ptr<Stage>& stagePtr,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position,
			float UPic,
			float VPic,
			const wstring& Texname

		);
		virtual ~stageObject() {}
		virtual void OnCreate() override;
	};
}

