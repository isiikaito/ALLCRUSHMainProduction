/*!
@file FadeOutBlack.h
@brief フェードアウト
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	//ゲージ
	class FadeOutBlack1 : public GameObject
	{
		bool m_Trace;
		Vec2 m_StartScale;
		Vec3 m_StartPos;
		float m_TotalTime;
		int SceneCount;
		//バックアップ頂点データ
		vector<VertexPositionColor>m_BackupVertices;


	public:
		FadeOutBlack1(const shared_ptr<Stage>& StagePtr, bool Trace,
			const Vec2& StartScale, const Vec3& StartPos);

		virtual ~FadeOutBlack1();

		virtual void OnCreate() override;

		virtual void OnUpdate()override;



	};
}