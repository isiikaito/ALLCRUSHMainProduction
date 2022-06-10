/*!
@file GageSprite.h
@brief ゲージ
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	//ゲージ
	class GageSprite : public GameObject
	{
		bool m_Trace;      //透明
		Vec2 m_StartScale; //大きさ
		Vec3 m_StartPos;   //位置
		float m_TotalTime; //時間の取得
		
		//バックアップ頂点データ
		vector<VertexPositionColor>m_BackupVertices;

		
	public:
		GageSprite(const shared_ptr<Stage>& StagePtr, bool Trace,
			const Vec2& StartScale, const Vec3& StartPos);

		virtual ~GageSprite();

		virtual void OnCreate() override;

		virtual void OnUpdate()override;

	};
}