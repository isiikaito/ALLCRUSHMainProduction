/*!
@file Boss.cpp
@brief ボス実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//　ボス
	//--------------------------------------------------------------------------------------
	Boss::Boss(const shared_ptr<Stage>& StagePtr) :
		GameObject(StagePtr)
	{}

	void Boss::OnCreate() {
		auto ptr = GetComponent<Transform>();
		ptr->SetScale(0.25f, 0.75f, 0.25f);
		ptr->SetRotation(0.0f, 0.0f, 0.0f);
		ptr->SetPosition(0.0f, 0.375f, -5.0f);

		//描画コンポーネントの設定
		auto ptrDraw = AddComponent<BcPNTStaticDraw>();
		//描画するメッシュを設定
		ptrDraw->SetMeshResource(L"DEFAULT_CUBE");
		ptrDraw->SetDiffuse(Col4(0.0f, 0.0f, 0.0f, 1.0f));

	}

	void Boss::OnUpdate() {
	}

}