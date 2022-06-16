/*!
@file MenuStage.h
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
		//Stage1スプライト作成
		void CreateMenuSprite1();
		//Stage2プライト作成
		void CreateMenuSprite2();
		
		//Bボタンを押しているか
		bool m_OnPushB = true;
		//入力ハンドラー
		InputHandler2<MenuStage> m_InputHandler;

		float m_idleTime;
		int StageNum ;
		bool  OnPushBCheck = false;
		bool  OnPushBCheck1 = false;


	public:
		
		//構築と破棄
		MenuStage() :Stage() , m_idleTime(0.0f),StageNum(1){}
		virtual ~MenuStage() {}
		//初期化
		virtual void OnCreate()override;
		//更新
		virtual void OnUpdate()override;
		//ステージ選択
		void SelectStage();
		//入力イベントに応答する関数
		void OnPushB();
		void OnPushX() {}
		//Yボタン
		void OnPushY() {}
		//十字キー上
		void OnPushUP();
		//十字キー下
		void OnPushDOWN();
	};
}
//end namespace basecross
