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
		bool m_Trace;
		Vec2 m_StartScale;
		Vec3 m_StartPos;
		float m_TotalTime;
		float m_ColwUP;//ゲージ上の透明度
		float m_ColwDOWN;//ゲージ下の透明度
		//バックアップ頂点データ
		vector<VertexPositionColor>m_BackupVertices;

		
	public:
		GageSprite(const shared_ptr<Stage>& StagePtr, bool Trace,
			const Vec2& StartScale, const Vec3& StartPos);

		virtual ~GageSprite();

		virtual void OnCreate() override;

		virtual void OnUpdate()override;

		////ゲージ上の透明度取得
		//float GetColwUP()const {
		//	return m_ColwUP;
		//}
		//void SetColwUP(float ColwUP) {
		//	m_ColwUP = ColwUP;
		//}

		////ゲージ下の透明度取得
		//float GetColwDOWN()const {
		//	return m_ColwDOWN;
		//}
		//void SetColwDOWN(float ColwDOWN) {
		//	m_ColwDOWN = ColwDOWN;
		//}
	};
}