/*!
@file menuStage.h
@brief メニューステージ
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	メニューステージクラス
	//--------------------------------------------------------------------------------------
	class MenuStage : public Stage {
		//ビューの作成
		void CreateViewLight();

		//入力ハンドラー
		InputHandler2<MenuStage> m_InputHandler;
		int num = 0;


	public:
		//構築と破棄
		MenuStage() :Stage() {}
		virtual ~MenuStage() {}
		//初期化
		virtual void OnCreate()override;
		//更新
		virtual void OnUpdate()override;
		//入力イベントに応答する関数
		void OnPushB();
		void OnPushX() {}
		//十字キー上
		void OnPushUP();
		//十字キー下
		void OnPushDOUN();
	};
}
//end namespace basecross
