/*!
@file OnPushButtonXTelop.h
@brief Xボタン押してねスプライト
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	OnPushButtonXスプライトクラス
	//--------------------------------------------------------------------------------------
	class PushButtonXTelop : public GameObject {
		bool m_Trace;        //透明になるかどうか
		Vec2 m_StartScale;   //スケーリング
		Vec3 m_StartPos;     //場所
		wstring m_TextureKey;//テクスチャの名前
	public:
		PushButtonXTelop(const shared_ptr<Stage>& StagePtr,
			const wstring& TextureKey,
			bool Trace,
			const Vec2& StartScale,
			const Vec3& StartPos);
		//破壊
		virtual ~PushButtonXTelop();
		//初期化
		virtual void OnCreate()override;
		//更新
		virtual void OnUpdate()override {}
	};
}
//end namespace basecross
