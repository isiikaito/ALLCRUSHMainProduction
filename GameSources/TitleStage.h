/*!
@file TitleStage.h
@brief タイトルステージ
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	タイトルステージクラス
	//--------------------------------------------------------------------------------------
	class TitleStage : public Stage {
		//ビューの作成
		void CreateViewLight();
	
		int SceneCountbakc;
		bool  OnPushBCheck = false;
		bool  OnPushBCheck1 = false;
		bool m_OnPushB=true;
		//入力ハンドラー
		InputHandler2<TitleStage> m_InputHandler;

	public:
		//構築と破棄
		TitleStage() :Stage(),SceneCountbakc(0) {}
		virtual ~TitleStage() {}
		//初期化
		virtual void OnCreate()override;
		//更新
		virtual void OnUpdate()override;
		//入力イベントに応答する関数
		void OnPushB();
		void OnPushX(){}
		void OnPushY(){}
		void OnPushUP() {}
		void OnPushDOWN() {}

		
	};
}
//end namespace basecross
