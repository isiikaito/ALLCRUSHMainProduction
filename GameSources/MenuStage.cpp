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
		AddGameObject<MenuSprite1>(L"Stage1_TX", true,
			//テクスチャの大きさ　　　　位置
			Vec2(200.0f, 100.0f), Vec3(-50.0f, 50.0f, 0.0f));
	}

	//アイテムスプライト作成
	void MenuStage::CreateMenuSprite2() {
		AddGameObject<MenuSprite2>(L"Stage2_TX", true,
			//テクスチャの大きさ　　　　位置
			Vec2(200.0f, 100.0f), Vec3(-50.0f, -100.0f, 0.0f));
	}
	
	
	//初期化
	void MenuStage::OnCreate() {
		CreateViewLight();
		AddGameObject<TitleSprite>(L"MenuSelect_TX", false,
			Vec2(256.0f, 64.0f), Vec2(0.0f, 100.0f));
		CreateMenuSprite1();//Stage1スプライト
		CreateMenuSprite2();//Stage2スプライト
	}
	
	void MenuStage::SelectStage()
	{
		//sceneの取得
		auto scene = App::GetApp()->GetScene<Scene>();
		//ステージ番号の取得
		auto Select = scene->GetStageSelect();
		//今選んでいるステージ番号を渡す
		Select = StageNum;
		scene->SetStageSelect(Select);
	}

	//十字キー上
	void MenuStage:: OnPushUP() {

		StageNum--;
		if (StageNum <= m_UPlimit)
		{
			StageNum = m_UPlimit;
		}
	}
	//十字キー下
	void MenuStage::OnPushDOWN() {
		StageNum++;
		if (StageNum >= m_DOWNlimit)
		{
			StageNum = m_DOWNlimit;
		}
	}

	
	void MenuStage::StageSprite1()
	{
	    //menuSprite1を取得する
		auto ptrStage1 = GetSharedGameObject<MenuSprite1>(L"MenuSprite1");
		//elapsedTimeを取得することにより時間を使える
		float elapsedTime = App::GetApp()->GetElapsedTime();
		if (OnPushBCheck) {
			if (!OnPushBCheck1)
			{
				auto WalkSound = App::GetApp()->GetXAudio2Manager();
				WalkSound->Start(L"WalkSound", 0, 0.4f);
				OnPushBCheck1 = true;
			}
		}
		//時間を変数に足す
		m_idleTime += elapsedTime;
		//十字キーを利用してnumが０の時
		 if (StageNum == m_UPlimit)
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

	}

	//ステージスプライト２の処理
	void MenuStage::StageSprite2()
	{
         //menuSprite1を取得する
		 auto ptrStage2 = GetSharedGameObject<MenuSprite2>(L"MenuSprite2");
		
		 //時間を変数に足す
		
		 //十字キーを利用してnumが０の時
		 if (StageNum == m_DOWNlimit)
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
	//更新
	void MenuStage::OnUpdate() {
		SelectStage();
		//コントローラチェックして入力があればコマンド呼び出し
		m_InputHandler.PushHandle(GetThis<MenuStage>());

		auto& app = App::GetApp();

		float delta = app->GetElapsedTime();

		auto& device = app->GetInputDevice();
		const auto& pad = device.GetControlerVec()[0];
        //コントローラの取得
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		StageSprite1();
		StageSprite2();	
		
	}

	
	//Bボタンが押されていたら
	void MenuStage::OnPushB() {
		
		wstring stagename[]
		{  
			L"ToMovieStage",
			L"ToGameStage"
		};
		if (m_OnPushB==true)
		{
         //フェードアウトの作成
		AddGameObject<FadeOut>(true,
			Vec2(1290.0f, 960.0f), Vec3(0.0f, 0.0f, 0.0f));
		SelectStage();
		//次のステージへ移行
		PostEvent(XM_PI / 2, GetThis<MenuStage>(), App::GetApp()->GetScene<Scene>(), stagename[StageNum]);
		m_OnPushB = false;
		}
		
		OnPushBCheck = true;
	}
}

//end namespace basecross