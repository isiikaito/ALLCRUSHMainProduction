/*!
@file MyMovieStage.h
@brief 
*/

#pragma once
#include "stdafx.h"


namespace basecross {
	//--------------------------------------------------------------------------------------
	//	ムービーステージクラス
	//--------------------------------------------------------------------------------------
	class MyClearStage : public MovieStage {
		//入力ハンドラー
		InputHandler<MyMovieStage> m_InputHandler;
		float MovieTime;//動画時間
		float m_Time ;  //時間
	public:
		//構築と破棄
		MyClearStage() :MovieStage(),
			MovieTime(21.0f),
			m_Time(0.0f) {}
		virtual ~MyClearStage() {}
		//初期化
		virtual void OnCreate()override;
		virtual void OnUpdate() override;
		
		
	};
}
//end namespace basecross

