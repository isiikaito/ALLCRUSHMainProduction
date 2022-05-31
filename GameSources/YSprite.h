/*!
@file YSprite.h
@brief パワー
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	class YSprite : public GameObject {
		bool m_Trace;
		Vec2 m_StartScale;
		Vec3 m_StartPos;
		wstring m_TextureKey;
		float m_TotalTime;
		//バックアップ頂点データ
		vector<VertexPositionTexture> m_BackupVertices;
	public:

		YSprite(const shared_ptr<Stage>& StagePtr, const wstring& TextureKey, bool Trace,
			const Vec2& StartScale, const Vec3& StartPos);

		virtual ~YSprite();

		virtual void OnCreate() override;
		//更新
		virtual void OnUpdate()override;

	};
}