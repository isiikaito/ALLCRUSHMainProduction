/*!
@file ClearStage.h
@brief ゲームクリアステージ
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	ゲームステージクラス
	//--------------------------------------------------------------------------------------
	class ClearStage : public Stage {

		//ビューの作成
		void CreateViewLight();

	public:
		//構築と破棄
		ClearStage() :Stage() {}
		virtual ~ClearStage() {}
		//初期化
		virtual void OnCreate()override;

	};
}
//end namespace basecross

