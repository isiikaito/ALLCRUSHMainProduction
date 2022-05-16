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
	void MenuStage::CreateMenuSprite1() {
		AddGameObject<MenuSprite1>(L"STAGE1_TX", true,
			//テクスチャの大きさ　　　　位置
			Vec2(180.0f, 180.0f), Vec3(-130.0f, 210.0f, 0.0f));
	}

	//アイテムスプライト作成
	void MenuStage::CreateMenuSprite2() {
		AddGameObject<MenuSprite2>(L"STAGE2_TX", true,
			//テクスチャの大きさ　　　　位置
			Vec2(200.0f, 200.0f), Vec3(-130.0f, 110.0f, 0.0f));
	}

	//初期化
	void MenuStage::OnCreate() {
		CreateViewLight();
		AddGameObject<TitleSprite>(L"MEMU_TX", false,
			Vec2(256.0f, 64.0f), Vec2(0.0f, 100.0f));
		//Stage1スプライト
		CreateMenuSprite1();

		//Stage2スプライト
		CreateMenuSprite2();
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
	void MenuStage::OnPushDOWN() {
		num++;
		if (num > 1)
		{
			num = 1;
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

		//ステージ選択処理

		//menuSprite1を取得する
		auto ptrStage1 = GetSharedGameObject<MenuSprite1>(L"MenuSprite1");
		//elapsedTimeを取得することにより時間を使える
		float elapsedTime = App::GetApp()->GetElapsedTime();
		//時間を変数に足す
		m_idleTime += elapsedTime;
		//十字キーを利用してnumが０の時
		 if (num == 0)
		    {   //時間が1秒後に表示がオフになる
				if (m_idleTime >= 1.0f)
				  {
                     ptrStage1->SetDrawActive(false);
					  //時間が1.5秒後にオンになる
					  if (m_idleTime >= 1.5f)
					   {
						 ptrStage1->SetDrawActive(true);
						 //m_idleTimeを0にすることにより元に戻ってループする。
						 m_idleTime = 0;
					   }
						return;
				  }
		   }
		 //選択されてないときは表示されたまま
		else{ ptrStage1->SetDrawActive(true); }


		 //menuSprite1を取得する
		 auto ptrStage2 = GetSharedGameObject<MenuSprite2>(L"MenuSprite2");
		
		 //時間を変数に足す
		
		 //十字キーを利用してnumが０の時
		 if (num == 1)
		 {   //時間が1秒後に表示がオフになる
			 if (m_idleTime >= 1.0f)
			 {
				 ptrStage2->SetDrawActive(false);
				 //時間が1.5秒後にオンになる
				 if (m_idleTime >= 1.5f)
				 {
					 ptrStage2->SetDrawActive(true);
					 //m_idleTimeを0にすることにより元に戻ってループする。
					 m_idleTime = 0;
				 }
				 return;
			 }
		 }
		 //選択されてないときは表示されたまま
		 else { ptrStage2->SetDrawActive(true); }
				
				
				
	}

	
	
	void MenuStage::OnPushB() {
		
		switch (num)
		{
			case 0:
				PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameStage");
				break;
			case 1:
				PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameStage2");
				break;
			/*case 2:
				PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameStage2");
				break;*/
		
		}
		
	}
}

//end namespace basecross