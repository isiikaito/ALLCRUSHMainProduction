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
		
		void CreateViewLight();  //ビューの作成
		void CreateMenuSprite1();//Stage1スプライト作成
		void CreateMenuSprite2();//Stage2プライト作成

       float m_idleTime;    //時間
		bool m_OnPushB;     //Bボタンを押しているか
		bool OnPushBCheck;  //Bボタンの判定
		bool OnPushBCheck1; //Bボタンの判定
		int m_UPlimit;      //ステージ選択の上限(上)
		int m_DOWNlimit;    //ステージ上限(下)
        int StageNum ;      //ステージの番号

		InputHandler2<MenuStage> m_InputHandler;//入力ハンドラー

	public:
		
		//構築と破棄
		MenuStage() :Stage() ,
			OnPushBCheck(false),
			OnPushBCheck1(false),
			m_OnPushB(true),
			m_idleTime(0.0f),
			StageNum(0),
		    m_UPlimit(0),
		    m_DOWNlimit(1){}
			
		virtual ~MenuStage() {}
		
		virtual void OnCreate()override;//初期化
		virtual void OnUpdate()override;//更新
		void StageSprite1();            //ステージスプライト1の処理
		void StageSprite2();            //ステージスプライト2の処理
		void SelectStage();             //ステージ選択
		void OnPushX() {}               //コントローラーのボタン判定X
		void OnPushA() {}               //コントローラーのボタン判定A
		void OnPushUP();                //コントローラーのボタン判定十字キー上
		void OnPushDOWN();              //コントローラーのボタン判定十字キー下
		void OnPushY() {}               //コントローラーのボタン判定Y
		void OnPushB();                 //コントローラーのボタン判定B
	};
}
//end namespace basecross
