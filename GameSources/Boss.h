/*!
@file Bos.h
@brief ボス
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class Boss : public GameObject {
	public:
		Boss(const shared_ptr<Stage>& StagePtr);
		virtual ~Boss() {}
		//アクセサ
		//初期化
		virtual void OnCreate() override;
		//更新
		virtual void OnUpdate() override;
	};
}