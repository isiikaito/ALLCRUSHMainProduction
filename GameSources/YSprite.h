/*!
@file YSprite.h
@brief パワーボタン
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	class YSprite : public GameObject {
		bool m_Trace;         //透明
		Vec2 m_StartScale;    //大きさ
		Vec3 m_StartPos;      //位置
		wstring m_TextureKey; //テクスチャ
		float m_TotalTime;    //時間の取得
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