/*!
@file Character.h
@brief キャラクターなど
*/

#pragma once
#include "stdafx.h"

namespace basecross{

	//--------------------------------------------------------------------------------------
//　球体のカメラマン
//--------------------------------------------------------------------------------------
	class Cameraman : public GameObject {
		float m_ToPlayerLen;
	public:
		//構築と破棄
		Cameraman(const shared_ptr<Stage>& StagePtr,
			float ToPlayerLen
		);
		virtual ~Cameraman();
		//初期化
		virtual void OnCreate() override;
		//操作
		virtual void OnUpdate() override;
	};

}
//end basecross
