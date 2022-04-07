/*!
@file ClearStage.h
@brief ゲームクリアステージ
*/



#pragma once
#include "stdafx.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	タイトルステージクラス
	//--------------------------------------------------------------------------------------
	class ClearStage : public Stage {
		//ビューの作成
		void CreateViewLight();

		//入力ハンドラー
		InputHandler2<ClearStage> m_InputHandler;

	public:
		//構築と破棄
		ClearStage() :Stage() {}
		virtual ~ClearStage() {}
		//初期化
		virtual void OnCreate()override;
		//更新
		virtual void OnUpdate()override;
		//入力イベントに応答する関数
		void OnPushB();
	};
}
//end namespace basecross


