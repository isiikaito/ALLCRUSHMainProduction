/*!
@file GameOverStage.h
@brief ゲームオーバーステージ
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	ゲームオーバーステージクラス
	//--------------------------------------------------------------------------------------
	class GameOverStage : public Stage {
		//ビューの作成
		void CreateViewLight();

		//入力ハンドラー
		InputHandler2<GameOverStage> m_InputHandler;

	public:
		//構築と破棄
		GameOverStage() :Stage() {}
		virtual ~GameOverStage() {}
		//初期化
		virtual void OnCreate()override;
		//更新
		virtual void OnUpdate()override;
		//入力イベントに応答する関数
		void OnPushB();
		void OnPushX(){}
		//十字キー上
		void OnPushUP() {}
		//十字キー下
		void OnPushDOUN() {}
	};
}
//end namespace basecross


