/*!
@file XSprite.h
@brief アイテムボタン
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	class XSprite : public GameObject {
		bool m_Trace;        //透明
		Vec2 m_StartScale;   //大きさ
		Vec3 m_StartPos;     //位置
		wstring m_TextureKey;//テクスチャ
		float m_TotalTime;   //時間の取得
		//バックアップ頂点データ
		vector<VertexPositionTexture> m_BackupVertices;
	public:

		XSprite(const shared_ptr<Stage>& StagePtr, const wstring& TextureKey, bool Trace,
			const Vec2& StartScale, const Vec3& StartPos);

		virtual ~XSprite();

		virtual void OnCreate() override;

	};
}
