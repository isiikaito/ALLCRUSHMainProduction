/*!
@file FadeOutEnd.h
@brief フェードアウト
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	//ゲージ
	class FadeOutEnd : public GameObject
	{
		bool m_Trace;
		Vec2 m_StartScale;
		Vec3 m_StartPos;
		float m_TotalTime;
		int SceneCount;
		//バックアップ頂点データ
		vector<VertexPositionColor>m_BackupVertices;
	public:
		FadeOutEnd(const shared_ptr<Stage>& StagePtr, bool Trace,
			const Vec2& StartScale, const Vec3& StartPos);

		virtual ~FadeOutEnd();

		virtual void OnCreate() override;

		virtual void OnUpdate()override;
	};
}