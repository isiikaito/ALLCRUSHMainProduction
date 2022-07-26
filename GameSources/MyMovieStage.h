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
		ResetHandler<MyMovieStage> ResetHandler;	   //リセットハンドラー
		void MovieSkip();
		float MovieTime;
		float m_Time;
	public:
		//構築と破棄
		MyMovieStage() :MovieStage(),
		MovieTime(43.6f),
		m_Time(0.0f){}
		virtual ~MyMovieStage() {}
		//初期化
		virtual void OnCreate()override;
		virtual void OnUpdate() override;
		void OnPushReset(){}
		void OnPushSkip();
	};
}
//end namespace basecross
