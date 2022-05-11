/*!
@file menuSprite1.h
@brief 文字
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	
	class memuSprite1 : public GameObject {
		bool m_Trace;
		Vec2 m_StartScale;
		Vec3 m_StartPos;
		wstring m_TextureKey;
		float m_idleTime;
		
		//バックアップ頂点データ
		vector< VertexPositionColorTexture> m_BackupVertices;
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief コンストラクタ
		@param[in]	StagePtr	ステージ
		@param[in]	TextureKey	テクスチャキー
		@param[in]	Trace	透明処理するかどうか
		@param[in]	StartScale	初期スケール
		@param[in]	StartPos	初期位置
		*/
		//--------------------------------------------------------------------------------------
		memuSprite1(const shared_ptr<Stage>& StagePtr, const wstring& TextureKey, bool Trace,
			const Vec2& StartScale, const Vec3& StartPos);
		
		virtual ~memuSprite1();
		
		virtual void OnCreate() override;
		
		virtual void OnUpdate()override;

		////入力イベントに応答する関数
		//void OnPushB();
		//void OnPushX(){}
		////十字キー上
		//void OnPushUP();
		////十字キー下
		//void OnPushDOUN();
	
	};
}
