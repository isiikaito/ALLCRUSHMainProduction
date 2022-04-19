/*!
@file StageWall.h
@brief ゲームステージの壁
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	class StageWall : public GameObject {
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;
	public:
		//構築と破棄
		StageWall(const shared_ptr<Stage>& StagePtr, const Vec3& Scale,const Vec3& Rotation,const Vec3& Position);
		virtual ~StageWall() {}
		
		//初期化
		virtual void OnCreate() override;

	};
}

