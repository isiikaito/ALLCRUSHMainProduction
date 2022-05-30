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

	void TitleStage::CerateFadeOutBlack()
	{		
		AddGameObject<FadeOutBlack>(true,
			Vec2(1300.0f, 800.0f), Vec3(0.0f, 0.0f, 0.0f));
		
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
		auto WalkSound = App::GetApp()->GetXAudio2Manager();
		WalkSound->Start(L"WalkSound", 0, 0.5f);

			CerateFadeOutBlack();
	}
}

//end namespace basecross