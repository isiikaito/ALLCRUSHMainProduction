/*!
@file TitleStage.cpp
@brief タイトルステージ実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	タイトルステージクラス実体
	//--------------------------------------------------------------------------------------
	void TitleStage::CreateViewLight() {

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
	void TitleStage::OnCreate() {
		CreateViewLight();
		AddGameObject<TitleSprite>(L"TITLLE_TX", false,
			Vec2(256.0f, 64.0f), Vec2(0.0f, 100.0f));
	}
	//更新
	void TitleStage::OnUpdate() {
		//コントローラチェックして入力があればコマンド呼び出し
		m_InputHandler.PushHandle(GetThis<TitleStage>());

	}
	void TitleStage::OnPushB() {
		PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToMovieStage");

	}
}

//end namespace basecross