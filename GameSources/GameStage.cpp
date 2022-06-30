/*!
@file GameStage.cpp
@brief ゲームステージ実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	ゲームステージクラス実体
	//--------------------------------------------------------------------------------------
	void GameStage::CreateViewLight() {
		const Vec3 eye(0.0f, 5.0f, -5.0f);
		const Vec3 at(0.0f);
		auto PtrView = CreateView<SingleView>();

		//OpeningCameraView用のビュー
		m_OpeningCameraView = ObjectFactory::Create<SingleView>(GetThis<Stage>());
		auto ptrOpeningCamera = ObjectFactory::Create<OpeningCamera>();
		m_OpeningCameraView->SetCamera(ptrOpeningCamera);
		//MyCamera用のビュー
		m_MyCameraView = ObjectFactory::Create<SingleView>(GetThis<Stage>());
		auto ptrMyCamera = ObjectFactory::Create<MyCamera>();
		ptrMyCamera->SetEye(Vec3(0.0f, 5.0f, -5.0f));
		ptrMyCamera->SetAt(Vec3(0.0f, 0.0f, 0.0f));
		m_MyCameraView->SetCamera(ptrMyCamera);
		//初期状態ではm_OpeningCameraViewを使う
		SetView(m_OpeningCameraView);
		m_CameraSelect = CameraSelect::openingCamera;
		//マルチライトの作成
		auto PtrMultiLight = CreateLight<MultiLight>();

		//デフォルトのライティングを指定
		PtrMultiLight->SetDefaultLighting();
	}

	void GameStage::CreateMultiSpark() {
		auto MultiSparkPtr = AddGameObject<ImpactSmoke>();
		//共有オブジェクトにスパークを登録
		SetSharedGameObject(L"MultiSpark", MultiSparkPtr);
	}

	void GameStage::CreateMultiSpark1() {
		auto MultiSparkPtr = AddGameObject<ImpactSmoke>();
		//共有オブジェクトにスパークを登録
		SetSharedGameObject(L"MultiSpark1", MultiSparkPtr);
	}

	
	//壊れる壁の作成
	void GameStage::CreateWall() {
		//グループの取得
		auto group = CreateSharedObjectGroup(L"Wall_Group");
		//CSVの行単位の配列
		vector<wstring>LineVec;
		//0番目のカラムがL"BreakWall"である行を抜き出す
		m_CsvC.GetSelect(LineVec, 0, L"Wall");
		for (auto& v : LineVec) {
			//トークン（カラム）の配置
			vector<wstring>Tokens;
			//トークン（カラム）単位で文字列を抽出（L','）
			Util::WStrToTokenVector(Tokens, v, L',');
			//トークン（カラム）をスケール、回転、位置に読み込む
			Vec3 Scale(
				(float)_wtof(Tokens[1].c_str()),
				(float)_wtof(Tokens[2].c_str()),
				(float)_wtof(Tokens[3].c_str())

			);
			Vec3 Rot;
			//回転は「XM_PLDIV2」の文字列になっている場合がある
			Rot.x = (Tokens[4] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[4].c_str());
			Rot.y = (Tokens[5] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[5].c_str());
			Rot.z = (Tokens[6] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[6].c_str());

			Vec3 Pos(
				(float)_wtof(Tokens[7].c_str()),
				(float)_wtof(Tokens[8].c_str()),
				(float)_wtof(Tokens[9].c_str())
			);
			//HPの取得
			int HP(
				(int)_wtof(Tokens[10].c_str())
				);
			//各値が揃ったのでオブジェクトの作成
			AddGameObject<Wall>(Scale, Rot, Pos,HP);
		}
	}
	//ステージの壁の作成
	void GameStage::CreateStageWall() {
    //CSVの行単位の配列
	vector<wstring>LineVec;
	//0番目のカラムがL"stageObject"である行を抜き出す
	m_CsvC.GetSelect(LineVec, 0, L"StageWall");
		for (auto& v : LineVec) {
			//トークン（カラム）の配置
			vector<wstring>Tokens;
			//トークン（カラム）単位で文字列を抽出（L','）
			Util::WStrToTokenVector(Tokens, v, L',');
			//トークン（カラム）をスケール、回転、位置に読み込む
			Vec3 Scale(
				(float)_wtof(Tokens[1].c_str()),
				(float)_wtof(Tokens[2].c_str()),
				(float)_wtof(Tokens[3].c_str())

			);
			Vec3 Rot;
			//回転は「XM_PLDIV2」の文字列になっている場合がある
			Rot.x = (Tokens[4] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[4].c_str());
			Rot.y = (Tokens[5] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[5].c_str());
			Rot.z = (Tokens[6] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[6].c_str());

			Vec3 Pos(
				(float)_wtof(Tokens[7].c_str()),
				(float)_wtof(Tokens[8].c_str()),
				(float)_wtof(Tokens[9].c_str())
			);
			//各値が揃ったのでオブジェクトの作成
			AddGameObject<StageWall>(Scale, Rot, Pos);
			

		}

	}

	//マヤの壁の作成
	void GameStage::CreateExitWall() {
		//CSVの行単位の配列
		vector<wstring>LineVec;
		//0番目のカラムがL"stageObject"である行を抜き出す
		m_CsvC.GetSelect(LineVec, 0, L"ExitWall");
		for (auto& v : LineVec) {
			//トークン（カラム）の配置
			vector<wstring>Tokens;
			//トークン（カラム）単位で文字列を抽出（L','）
			Util::WStrToTokenVector(Tokens, v, L',');
			//トークン（カラム）をスケール、回転、位置に読み込む
			Vec3 Scale(
				(float)_wtof(Tokens[1].c_str()),
				(float)_wtof(Tokens[2].c_str()),
				(float)_wtof(Tokens[3].c_str())

			);
			Vec3 Rot;
			//回転は「XM_PLDIV2」の文字列になっている場合がある
			Rot.x = (Tokens[4] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[4].c_str());
			Rot.y = (Tokens[5] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[5].c_str());
			Rot.z = (Tokens[6] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[6].c_str());

			Vec3 Pos(
				(float)_wtof(Tokens[7].c_str()),
				(float)_wtof(Tokens[8].c_str()),
				(float)_wtof(Tokens[9].c_str())
			);
			//各値が揃ったのでオブジェクトの作成
			AddGameObject<ExitWall>(Scale, Rot, Pos);


		}

	}

	//マヤの床の作成
	void GameStage::CreateStageFloor() {
		//CSVの行単位の配列
		vector<wstring>LineVec;
		//0番目のカラムがL"stageObject"である行を抜き出す
		m_CsvC.GetSelect(LineVec, 0, L"StageFloor");
		for (auto& v : LineVec) {
			//トークン（カラム）の配置
			vector<wstring>Tokens;
			//トークン（カラム）単位で文字列を抽出（L','）
			Util::WStrToTokenVector(Tokens, v, L',');
			//トークン（カラム）をスケール、回転、位置に読み込む
			Vec3 Scale(
				(float)_wtof(Tokens[1].c_str()),
				(float)_wtof(Tokens[2].c_str()),
				(float)_wtof(Tokens[3].c_str())

			);
			Vec3 Rot;
			//回転は「XM_PLDIV2」の文字列になっている場合がある
			Rot.x = (Tokens[4] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[4].c_str());
			Rot.y = (Tokens[5] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[5].c_str());
			Rot.z = (Tokens[6] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[6].c_str());

			Vec3 Pos(
				(float)_wtof(Tokens[7].c_str()),
				(float)_wtof(Tokens[8].c_str()),
				(float)_wtof(Tokens[9].c_str())
			);
			//各値が揃ったのでオブジェクトの作成
			AddGameObject<StageFloor>(Scale, Rot, Pos);
		}
		


	}
	//障害物１作成
	void GameStage::CreateObstacle1() {
		auto group1 = CreateSharedObjectGroup(L"Obstacle1_Group1");
		//CSVの行単位の配列
		vector<wstring>LineVec;
		//0番目のカラムがL"stageObject"である行を抜き出す
		m_CsvC.GetSelect(LineVec, 0, L"Obstacle1");
		for (auto& v : LineVec) {
			//トークン（カラム）の配置
			vector<wstring>Tokens;
			//トークン（カラム）単位で文字列を抽出（L','）
			Util::WStrToTokenVector(Tokens, v, L',');
			//トークン（カラム）をスケール、回転、位置に読み込む
			Vec3 Scale(
				(float)_wtof(Tokens[1].c_str()),
				(float)_wtof(Tokens[2].c_str()),
				(float)_wtof(Tokens[3].c_str())

			);
			Vec3 Rot;
			//回転は「XM_PLDIV2」の文字列になっている場合がある
			Rot.x = (Tokens[4] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[4].c_str());
			Rot.y = (Tokens[5] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[5].c_str());
			Rot.z = (Tokens[6] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[6].c_str());

			Vec3 Pos(
				(float)_wtof(Tokens[7].c_str()),
				(float)_wtof(Tokens[8].c_str()),
				(float)_wtof(Tokens[9].c_str())
			);
			//各値が揃ったのでオブジェクトの作成
			AddGameObject<Obstacle1>(Scale, Rot, Pos);
		}
	}

	//障害物2作成
	void GameStage::CreateObstacle2() {
		//CSVの行単位の配列
		vector<wstring>LineVec;
		//0番目のカラムがL"stageObject"である行を抜き出す
		m_CsvC.GetSelect(LineVec, 0, L"Obstacle2");
		for (auto& v : LineVec) {
			//トークン（カラム）の配置
			vector<wstring>Tokens;
			//トークン（カラム）単位で文字列を抽出（L','）
			Util::WStrToTokenVector(Tokens, v, L',');
			//トークン（カラム）をスケール、回転、位置に読み込む
			Vec3 Scale(
				(float)_wtof(Tokens[1].c_str()),
				(float)_wtof(Tokens[2].c_str()),
				(float)_wtof(Tokens[3].c_str())

			);
			Vec3 Rot;
			//回転は「XM_PLDIV2」の文字列になっている場合がある
			Rot.x = (Tokens[4] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[4].c_str());
			Rot.y = (Tokens[5] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[5].c_str());
			Rot.z = (Tokens[6] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[6].c_str());

			Vec3 Pos(
				(float)_wtof(Tokens[7].c_str()),
				(float)_wtof(Tokens[8].c_str()),
				(float)_wtof(Tokens[9].c_str())
			);
			//各値が揃ったのでオブジェクトの作成
			AddGameObject<Obstacle2>(Scale, Rot, Pos);
		}
	}

	//柱の作成
	void GameStage::CreatePillar() {
		auto group2 = CreateSharedObjectGroup(L"Pillar_Group1");
		//CSVの行単位の配列
		vector<wstring>LineVec;
		//0番目のカラムがL"stageObject"である行を抜き出す
		m_CsvC.GetSelect(LineVec, 0, L"Pillar");
		for (auto& v : LineVec) {
			//トークン（カラム）の配置
			vector<wstring>Tokens;
			//トークン（カラム）単位で文字列を抽出（L','）
			Util::WStrToTokenVector(Tokens, v, L',');
			//トークン（カラム）をスケール、回転、位置に読み込む
			Vec3 Scale(
				(float)_wtof(Tokens[1].c_str()),
				(float)_wtof(Tokens[2].c_str()),
				(float)_wtof(Tokens[3].c_str())

			);
			Vec3 Rot;
			//回転は「XM_PLDIV2」の文字列になっている場合がある
			Rot.x = (Tokens[4] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[4].c_str());
			Rot.y = (Tokens[5] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[5].c_str());
			Rot.z = (Tokens[6] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[6].c_str());

			Vec3 Pos(
				(float)_wtof(Tokens[7].c_str()),
				(float)_wtof(Tokens[8].c_str()),
				(float)_wtof(Tokens[9].c_str())
			);
			//各値が揃ったのでオブジェクトの作成
			AddGameObject<Pillar>(Scale, Rot, Pos);
		}
	}

	//落石の作成
	void GameStage::CreateFallingRock() {
		
		//CSVの行単位の配列
		vector<wstring>LineVec;
		auto group3 = CreateSharedObjectGroup(L"FallingRock_Group1");
		//0番目のカラムがL"stageObject"である行を抜き出す
		m_CsvC.GetSelect(LineVec, 0, L"FallingRock");
		for (auto& v : LineVec) {
			//トークン（カラム）の配置
			vector<wstring>Tokens;
			//トークン（カラム）単位で文字列を抽出（L','）
			Util::WStrToTokenVector(Tokens, v, L',');
			//トークン（カラム）をスケール、回転、位置に読み込む
			Vec3 Scale(
				(float)_wtof(Tokens[1].c_str()),
				(float)_wtof(Tokens[2].c_str()),
				(float)_wtof(Tokens[3].c_str())

			);
			Vec3 Rot;
			//回転は「XM_PLDIV2」の文字列になっている場合がある
			Rot.x = (Tokens[4] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[4].c_str());
			Rot.y = (Tokens[5] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[5].c_str());
			Rot.z = (Tokens[6] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[6].c_str());

			Vec3 Pos(
				(float)_wtof(Tokens[7].c_str()),
				(float)_wtof(Tokens[8].c_str()),
				(float)_wtof(Tokens[9].c_str())
			);
			//各値が揃ったのでオブジェクトの作成
			AddGameObject<FallingRock>(Scale, Rot, Pos);
		}
	}

	//タイムスプライト作成
	void GameStage::CreateTime() {
		AddGameObject<MyTime>(4,
			L"NUMBER_TX",
			true,
			Vec2(80.0f, 80.0f),
			Vec3(600.0f, 340.0f, 0.0f));
	}

	//アイテムスプライト作成
	void GameStage::CreateMyitem1() {
		AddGameObject<Myitem1>(L"SPEED_TX", true,
			//テクスチャの大きさ　　　　位置
			Vec2(180.0f, 180.0f), Vec3(-530.0f, -280.0f, 0.0f));
	}
	//Xボタンスプライト
	void GameStage::CreateXSprite() {
		AddGameObject<XSprite>(L"XButton_TX", true,
			//テクスチャの大きさ　　　　位置
			Vec2(80.0f, 80.0f), Vec3(-520.0f, -190.0f, 0.0f));
	}
	//Yボタンスプライト
	void GameStage::CreateYSprite() {
		AddGameObject<YSprite>(L"YButton_TX", true,
			//テクスチャの大きさ　　　　位置
			Vec2(80.0f, 80.0f), Vec3(550.0f, -90.0f, 0.0f));
	}

	//ゲージの枠作成
	void GameStage::CreateMygage() {
		AddGameObject<Mygage>(L"GAGE_TX", true,
			Vec2(240.0f, 240.0f), Vec3(550.0f, -220.0f, 0.0f));
	}
	//ゲージのバーの作成
	void GameStage::CreateGageSprite()
	{
		AddGameObject<GageSprite>(true,
			Vec2(40.0f,40.0f), Vec3(550.0f, -320.0f, 0.1f));
	}
	void GameStage::CreateGageSprite2()
	{
		AddGameObject<GageSprite2>(true,
			Vec2(40.0f, 40.0f), Vec3(550.0f, -280.0f, 0.1f));
	}
	void GameStage::CreateGageSprite3()
	{
		AddGameObject<GageSprite3>(true,
			Vec2(40.0f, 50.0f), Vec3(550.0f, -235.0f, 0.1f));
	}

	void GameStage::CreateGageWhite()
	{
		AddGameObject<GageSpriteWhite>(true,
			Vec2(40.0f, 130.0f), Vec3(550.0f, -274.0f, 0.2f));
	}

	



	//プレイヤーの作成
	void GameStage::CreatePlayer() {
		//プレーヤーの作成
		auto PlayerPtr = AddGameObject<Player>();
		//シェア配列にプレイヤーを追加
		SetSharedGameObject(L"Player", PlayerPtr);
	}

	// 逃げるテロップ
	void GameStage::CreateTickerSprite()
	{
		AddGameObject<TickerSprite>(L"FLEE_TX", true,
			Vec2(500.0f, 700.0f), Vec2(0.0f, 0.0f));
	}

	// 柱を壊すテロップ
	void GameStage::CreateTelop()
	{
		AddGameObject<Telop>(L"PillarBrake_TX", true,
			Vec2(500.0f, 700.0f), Vec2(0.0f, 0.0f));
	}

	// 柱を壊すタイミングテロップ
	void GameStage::CreateTelop2()
	{
		AddGameObject<Telop2>(L"JustTiming_TX", true,
			Vec2(500.0f, 700.0f), Vec2(0.0f, 0.0f));
	}

	// 出口前テロップ
	void GameStage::CreateTelop3()
	{
		AddGameObject<Telop3>(L"ClearNear_TX", true,
			Vec2(500.0f, 700.0f), Vec2(0.0f, 0.0f));
	}

	// 壁を壊せ！！テロップ
	void GameStage::CreateTelop4()
	{
		AddGameObject<Telop4>(L"WallBrake_TX", true,
			Vec2(500.0f, 700.0f), Vec2(0.0f, 0.0f));
	}

	

	void GameStage::BGM() {
		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		m_BGM = XAPtr->Start(L"BGM", XAUDIO2_LOOP_INFINITE, 0.4f);
	}

	//カメラマンの作成
	void GameStage::CreateCameraman() {
		auto ptrPlayer = GetSharedGameObject<Player>(L"Player");
		auto ptrCameraman = AddGameObject<Cameraman>(2.0f);
		//シェア配列にCameramanを追加
		SetSharedGameObject(L"Cameraman", ptrCameraman);
		//シェア配列にOpeningCameramanを追加
		auto ptrOpeningCameraman = AddGameObject<OpeningCameraman>();
		SetSharedGameObject(L"OpeningCameraman", ptrOpeningCameraman);

		auto ptrOpeningCamera = dynamic_pointer_cast<OpeningCamera>(m_OpeningCameraView->GetCamera());
		if (ptrOpeningCamera) {
			ptrOpeningCamera->SetCameraObject(ptrOpeningCameraman);
			SetView(m_OpeningCameraView);
			m_CameraSelect = CameraSelect::openingCamera;
		}

	}

	void GameStage::OnCreate() {
		try {
			
			auto  Select = App::GetApp()->GetScene<Scene>()->GetStageSelect();

			SetPhysicsActive(true);//物理計算有効
			
			// 「アプリ」オブジェクトのインスタンスを取得する（インスタンス：クラスの実態、オブジェクト指向のオブジェクトのこと）
			auto& app = App::GetApp();
			wstring DataDir;
			App::GetApp()->GetDataDirectory(DataDir);
			//CSVファイルその読み込みC
			m_CsvC.SetFileName(DataDir + L"stage"+ Util::IntToWStr(Select)+L".csv");
			m_CsvC.ReadCsv();

			
			CreateViewLight();           //ビューとライトの作成
			CreateMultiSpark();          //エフェクト0の作成
			CreateMultiSpark1();         //エフェクト1の作成
			CreatePlayer();              //プレーヤーの作成
			BGM();                       //BGMの再生
			CreatePillar();              //柱の作成
			AddGameObject<EnemyObject>();//敵の作成
			CreateStageWall();           //ステージの壁の追加	
			CreateStageFloor();          //床の追加
			CreateObstacle1();           //障害物１の追加
			CreateFallingRock();         //落石
			CreateExitWall();            //マヤでつくった出口
			CreateTime();                //タイムスプライト作成
			CreateWall();                //壊れる壁の作成
			CreateMyitem1();             //アイテムスプライト
			CreateXSprite();             //Xボタンのスプライトの作成
			CreateYSprite();             //Yボタンのスプライトの作成
			CreateMygage();              //ゲージの枠の作成
			CreateGageSprite();          //ゲージのスプライト1の作成
			CreateGageSprite2();         //ゲージのスプライト2の作成
			CreateGageSprite3();         //ゲージのスプライト3の作成
			CreateGageWhite();           //ゲージの背景の作成
			CreateTickerSprite();        //テロップ0の作成
			CreateTelop();               //テロップ1の作成
			CreateTelop2();              //テロップ2の作成
			CreateTelop3();              //テロップ3の作成
			CreateTelop4();              //テロップ4の作成
			CreateCameraman();           //カメラマンの作成

		}
		catch (...) {
			throw;
		}
	}

	void GameStage::ToMyCamera() {
		auto ptrPlayer = GetSharedGameObject<Player>(L"Player");
		//MyCameraに変更
		auto ptrMyCamera = dynamic_pointer_cast<MyCamera>(m_MyCameraView->GetCamera());
		if (ptrMyCamera) {
			ptrMyCamera->SetTargetObject(ptrPlayer);
			//m_MyCameraViewを使う
			SetView(m_MyCameraView);
			m_CameraSelect = CameraSelect::myCamera;
		}
	}

	void GameStage::OnUpdate() {
		//コントローラチェックして入力があればコマンド呼び出し
		m_InputHandler.PushHandle(GetThis<GameStage>());
		float elapsedTime = App::GetApp()->GetElapsedTime();
		m_TotalTime += elapsedTime;
		if (m_TotalTime >= 10000.0f) {
			m_TotalTime = 0.0f;
		}
		//タイムを更新する
		auto ptrScor = GetSharedGameObject<MyTime>(L"Time");
		ptrScor->SetScore(m_TotalTime);

		auto ptrPlayer = GetSharedGameObject<Player>(L"Player");
		auto Exit = ptrPlayer->GetExitCount();
		auto GameOver = ptrPlayer->GetGameOver();
		auto state = ptrPlayer->GetGameState();
		static shared_ptr<FadeOut> fadeOut = nullptr;
		static float FadeTime = 0.0f;
		switch (state)
		{
		case GameState::Game:
			break;
		case GameState::Down:
			ptrPlayer->SetGameState(GameState::FadeStart);
			break;
		case GameState::FadeStart:
			fadeOut = AddGameObject<FadeOut>(true,
				Vec2(1290.0f, 960.0f), Vec3(0.0f, 0.0f, 0.0f));
			ptrPlayer->SetGameState(GameState::FadeOut);
		case GameState::FadeOut:
			FadeTime += elapsedTime;
			if (FadeTime >= 1.0f)
			{
				AddGameObject<GameOverSprite>(L"GAMEOVERTELOP_TX", true,
					Vec2(500.0f, 500.0f), Vec3(0.0f, 0.0f, 0.0f));
				AddGameObject<PushButtonXTelop>(L"PushButtonX_TX", true,
					Vec2(500.0f, 500.0f), Vec3(0.0f, -250.0f, 0.0f));
				ptrPlayer->SetGameState(GameState::ChangeStage);
			}
			break;
		case GameState::ChangeStage:
			break;

			//フェードアウトの作成
			AddGameObject<GameOverSprite>(L"GAMEOVERTELOP_TX", true,
				Vec2(1290.0f, 960.0f), Vec3(0.0f, 0.0f, 0.0f));

			m_createGameOverObjectFlg = true;
		case GameState::GameExit:
			//フェードアウトの作成
			AddGameObject<FadeOut>(true,
				Vec2(1290.0f, 960.0f), Vec3(0.0f, 0.0f, 0.0f));
			float elapsedTime1 = App::GetApp()->GetElapsedTime();
			m_ExitTime += elapsedTime1;
			if (m_ExitTime >= 1.0f)
			{
				PostEvent(0.0, GetThis<GameStage>(), App::GetApp()->GetScene<Scene>(), L"ToClearStage");
			}
	}
		ptrPlayer->SetExitCount(Exit);
        ptrPlayer->SetGameOver(GameOver);
		// テロップの時間
		auto ptrStage = GetSharedGameObject<TickerSprite>(L"TickerSprite");
		// 時間の変数に足す
		m_idleTime += elapsedTime;
		if (m_idleTime >= 2.0f)
		{
			// 1秒後に表示がオフになる
			ptrStage->SetDrawActive(false);
		}
	}

	void GameStage::OnDestroy() {
		//BGMのストップ
		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		XAPtr->Stop(m_BGM);
	}

}
//end basecross
