/*!
@file GameOverStage.cpp
@brief ゲームオーバーステージ
*/



#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	タイトルステージクラス実体
	//--------------------------------------------------------------------------------------
	void GameOverStage::CreateViewLight() {

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
	void GameOverStage::OnCreate() {
		CreateViewLight();
		AddGameObject<GameOverSprite>(L"GAMEOVER_TX", false,
			Vec2(1300.0f, 800.0f), Vec2(0.0f, 0.0f));
	}
	////更新
	//void GameOverStage::OnUpdate() {
	//	//コントローラチェックして入力があればコマンド呼び出し
	//	m_InputHandler.PushHandle(GetThis<GameOverStage>());

	//}
	/*void GameOverStage::OnPushB() {
		PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameStage");

	}*/
}

//end namespace basecross