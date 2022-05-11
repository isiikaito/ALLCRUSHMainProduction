/*!
@file MenuStage.cpp
@brief メニューステージ実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	メニューステージクラス実体
	//--------------------------------------------------------------------------------------
	void MenuStage::CreateViewLight() {

		auto ptrView = CreateView<SingleView>();
		//ビューのカメラの設定
		auto ptrCamera = ObjectFactory::Create<Camera>();
		ptrView->SetCamera(ptrCamera);
		//マルチライトの作成
		auto ptrMultiLight = CreateLight<MultiLight>();
		//デフォルトのライティングを指定
		ptrMultiLight->SetDefaultLighting();
	}

//アイテムスプライト作成
	void MenuStage::CreatemenuSprite1() {
		AddGameObject<memuSprite1>(L"STAGE1_TX", true,
			//テクスチャの大きさ　　　　位置
			Vec2(180.0f, 180.0f), Vec3(-130.0f, 210.0f, 0.0f));
	}

	//初期化
	void MenuStage::OnCreate() {
		CreateViewLight();
		AddGameObject<TitleSprite>(L"MEMU_TX", false,
			Vec2(256.0f, 64.0f), Vec2(0.0f, 100.0f));
		//アイテムスプライト
		CreatemenuSprite1();
	}
	//十字キー上
	void MenuStage:: OnPushUP() {
		num--;
		if (num < 0)
		{
			num = 0;
		}
	}
	//十字キー下
	void MenuStage::OnPushDOUN() {
		num++;
		if (num > 2)
		{
			num = 2;
		}
	}
	//更新
	void MenuStage::OnUpdate() {
		//コントローラチェックして入力があればコマンド呼び出し
		m_InputHandler.PushHandle(GetThis<MenuStage>());
		auto& app = App::GetApp();

		float delta = app->GetElapsedTime();

		auto& device = app->GetInputDevice();
		const auto& pad = device.GetControlerVec()[0];
          //コントローラの取得
				auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		auto ptrStage1 = GetSharedGameObject<memuSprite1>(L"memuSprite1");
				float elapsedTime = App::GetApp()->GetElapsedTime();
				m_idleTime += elapsedTime;
				if (num == 0)
				{
					if (m_idleTime >= 1.0f)
					{
						
                        ptrStage1->SetDrawActive(false);
						if (m_idleTime >= 1.5f)
						{
						ptrStage1->SetDrawActive(true);
							m_idleTime = 0;
						}

						return;
					}
				}
				else{ ptrStage1->SetDrawActive(true); }


				
				
				
	}

	
	
	void MenuStage::OnPushB() {
		
		switch (num)
		{
			case 0:
				PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToMovieStage");
				break;
			case 1:
				PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameStage");
				break;
			case 2:
				PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameStage2");
				break;
		
		}
		
	}
}

//end namespace basecross