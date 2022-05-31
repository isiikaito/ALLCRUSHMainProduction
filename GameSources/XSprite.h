/*!
@file XSprite.h
@brief アイテム
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	class XSprite : public GameObject {
		bool m_Trace;
		Vec2 m_StartScale;
		Vec3 m_StartPos;
		wstring m_TextureKey;
		float m_TotalTime;
		//バックアップ頂点データ
		vector<VertexPositionTexture> m_BackupVertices;
	public:

		XSprite(const shared_ptr<Stage>& StagePtr, const wstring& TextureKey, bool Trace,
			const Vec2& StartScale, const Vec3& StartPos);

		virtual ~XSprite();

		virtual void OnCreate() override;

	};
}
