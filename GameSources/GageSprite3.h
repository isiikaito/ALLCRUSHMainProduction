/*!
@file GageSprite3.h
@brief ゲージ
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	//ゲージ
	class GageSprite3 : public GameObject
	{
		bool m_Trace;
		Vec2 m_StartScale;
		Vec3 m_StartPos;
		float m_TotalTime;
		float m_ColwUP;//ゲージ上の透明度
		float m_ColwDOWN;//ゲージ下の透明度
		//バックアップ頂点データ
		vector<VertexPositionColor>m_BackupVertices;


	public:
		GageSprite3(const shared_ptr<Stage>& StagePtr, bool Trace,
			const Vec2& StartScale, const Vec3& StartPos);

		virtual ~GageSprite3();

		virtual void OnCreate() override;

		virtual void OnUpdate()override;

		
	};
}
