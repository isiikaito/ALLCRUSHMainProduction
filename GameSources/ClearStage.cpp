/*!
@file ClearStage.cpp
@brief クリアステージ実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	クリアステージクラス実体
	//--------------------------------------------------------------------------------------
	void ClearStage::CreateViewLight() {

		auto ptrView = CreateView<SingleView>();
		//ビューのカメラの設定
		auto ptrCamera = ObjectFactory::Create<Camera>();
		ptrView->SetCamera(ptrCamera);

		//マルチライトの作成
		auto ptrMultiLight = CreateLight<MultiLight>();
		//デフォルトのライティングを指定
		ptrMultiLight->SetDefaultLighting();
	}



	//初期化
	void ClearStage::OnCreate() {
		CreateViewLight();
		AddGameObject<ClearSprite>(L"GAMECREA_TX", false,
			Vec2(1300.0f, 800.0f), Vec2(0.0f, 0.0f));
	}
	//更新
	void ClearStage::OnUpdate() {
		//コントローラチェックして入力があればコマンド呼び出し
		m_InputHandler.PushHandle(GetThis<ClearStage>());

	}
	void ClearStage::OnPushB() {
		PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToTitleStage");

	}
}

//end namespace basecross
