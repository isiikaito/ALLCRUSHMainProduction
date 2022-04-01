/*!
@file ClearObject.h
@brief ゲームクリアオブジェクト
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class ClearObject : public GameObject {
	public:
		//構築と破壊
		//コンストラクタ
		ClearObject(const shared_ptr<Stage>& StagePtr);
		//デストラクタ
		virtual ~ClearObject() {}
		virtual void OnCreate() override;
	};


}
//end namespace basecross

