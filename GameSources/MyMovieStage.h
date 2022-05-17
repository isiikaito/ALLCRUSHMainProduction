/*!
@file MyMovieStage.h
@brief  Q [   X e [ W
*/

#pragma once
#include "stdafx.h"


namespace basecross {
	//--------------------------------------------------------------------------------------
	//	ムービーステージクラス
	//--------------------------------------------------------------------------------------
	class MyMovieStage : public MovieStage {
		//入力ハンドラー
		InputHandler<MyMovieStage> m_InputHandler;
		float MovieTime = 0.0f;
	public:
		//構築と破棄
		MyMovieStage() :MovieStage() {}
		virtual ~MyMovieStage() {}
		//初期化
		virtual void OnCreate()override;
		virtual void OnUpdate() override;
		//Aボタン
		void OnPushA();
		//Bボタン
		void OnPushB();
	};
}
//end namespace basecross
