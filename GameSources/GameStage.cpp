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

		//MyCamera用のビュー
		m_MyCameraView = ObjectFactory::Create<SingleView>(GetThis<Stage>());
		auto ptrMyCamera = ObjectFactory::Create<MyCamera>();
		ptrMyCamera->SetEye(Vec3(0.0f, 5.0f, -5.0f));
		ptrMyCamera->SetAt(Vec3(0.0f, 0.0f, 0.0f));
		m_MyCameraView->SetCamera(ptrMyCamera);
		//初期状態で使うView
		SetView(m_MyCameraView);
		//m_CameraSelect = CameraSelect::myCamera;
		//マルチライトの作成
		auto PtrMultiLight = CreateLight<MultiLight>();

		//デフォルトのライティングを指定
		PtrMultiLight->SetDefaultLighting();
	}

	void GameStage::CreatestageObject() {
		//CSVの行単位の配列
		vector<wstring>LineVec;
		//0番目のカラムがL"stageObject"である行を抜き出す
		m_CsvC.GetSelect(LineVec, 0, L"stageObject");
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
			AddGameObject<stageObject>(Scale, Rot, Pos, 1.0f, 1.0f, Tokens[10]);
		}
	}

	void GameStage::CreateWall() {
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
			int HP(
				(int)_wtof(Tokens[10].c_str())
				);
			//各値が揃ったのでオブジェクトの作成
			AddGameObject<Wall>(Scale, Rot, Pos,HP);
		}
		//HP
		//AddGameObject<Wall>(Vec3(1.0f, 10.0f, 10.0f), Vec3(), Vec3(-5.0f, 1.0f, 0.0f),1);
		//AddGameObject<Wall>(Vec3(1.0f, 10.0f, 10.0f), Vec3(), Vec3(-13.0f, 1.0f, 0.0f),3);
		//AddGameObject<Wall>(Vec3(1.0f, 10.0f, 10.0f), Vec3(), Vec3(-21.0f, 1.0f, 0.0f),1);
		//AddGameObject<Wall>(Vec3(1.0f, 10.0f, 10.0f), Vec3(), Vec3(-29.0f, 1.0f, 0.0f),2);
		//AddGameObject<Wall>(Vec3(1.0f, 10.0f, 10.0f), Vec3(), Vec3(-37.0f, 1.0f, 0.0f),4);

	}
	//マヤの壁の作成
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
			Vec2(180.0f, 180.0f), Vec3(-530.0f, -310.0f, 0.0f));
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
			Vec2(40.0f,50.0f), Vec3(550.0f, -310.0f, 0.1f));
	}
	void GameStage::CreateGageSprite2()
	{
		AddGameObject<GageSprite2>(true,
			Vec2(40.0f, 40.0f), Vec3(550.0f, -270.0f, 0.1f));
	}
	void GameStage::CreateGageSprite3()
	{
		AddGameObject<GageSprite3>(true,
			Vec2(40.0f, 40.0f), Vec3(550.0f, -230.0f, 0.1f));
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
	//敵の作成
	void GameStage::CreateEnemy() {
		////プレーヤーの作成
		//auto EnemyPtr = AddGameObject<EnemyObject>();
		////シェア配列にプレイヤーを追加
		//SetSharedGameObject(L"Enemy", EnemyPtr);
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
		AddGameObject<Telop>(L"柱を壊す_TX", true,
			Vec2(500.0f, 700.0f), Vec2(0.0f, 0.0f));
	}

	// 柱を壊すタイミングテロップ
	void GameStage::CreateTelop2()
	{
		AddGameObject<Telop2>(L"柱壊すタイミング_TX", true,
			Vec2(500.0f, 700.0f), Vec2(0.0f, 0.0f));
	}

	// 出口前テロップ
	void GameStage::CreateTelop3()
	{
		AddGameObject<Telop3>(L"出口前_TX", true,
			Vec2(500.0f, 700.0f), Vec2(0.0f, 0.0f));
	}

	// 壁を壊せ！！テロップ
	void GameStage::CreateTelop4()
	{
		AddGameObject<Telop4>(L"壁を壊せ！！_TX", true,
			Vec2(500.0f, 700.0f), Vec2(0.0f, 0.0f));
	}

	void GameStage::BGM() {
		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		m_BGM = XAPtr->Start(L"BGM", XAUDIO2_LOOP_INFINITE, 0.1f);
	}

	void GameStage::OnCreate() {
		try {


			//物理計算有効
			SetPhysicsActive(true);

			// 「アプリ」オブジェクトのインスタンスを取得する（インスタンス：クラスの実態、オブジェクト指向のオブジェクトのこと）
			auto& app = App::GetApp();
			wstring DataDir;
			App::GetApp()->GetDataDirectory(DataDir);
			//CSVファイルその読み込みC
			m_CsvC.SetFileName(DataDir + L"stage1.csv");
			m_CsvC.ReadCsv();

			//ビューとライトの作成
			CreateViewLight();

			// プレイヤーオブジェクトをステージに追加する
			//AddGameObject<Player>(); // 指定のゲームオブジェクトを生成してステージに追加し、そのポインタを返す

			//プレーヤーの作成
			CreatePlayer();
			//敵の作成
			CreateEnemy();
			//BGMの再生
			BGM();

			CreatePillar();
			AddGameObject<EnemyObject>();
			//オブジェクトの追加
			CreatestageObject();
			//マヤでつくったステージの壁の追加
			CreateStageWall(); 
			//マヤで作った床の追加
			CreateStageFloor();
			//障害物１の追加
			CreateObstacle1();
			//落石
			CreateFallingRock();
			//マヤでつくった出口
			CreateExitWall();
			//タイムスプライト作成
			CreateTime();
			//壊れる壁の作成
			CreateWall();
			//アイテムスプライト
			CreateMyitem1();
			//ゲージスプライト
			CreateMygage();
			CreateGageSprite();
			CreateGageSprite2();
			CreateGageSprite3();
			CreateGageWhite();
			// 逃げるテロップ
			CreateTickerSprite();

			CreateTelop();
			CreateTelop2();
			CreateTelop3();
			CreateTelop4();
		}
		catch (...) {
			throw;
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


		// テロップの時間
		auto ptrStage = GetSharedGameObject<TickerSprite>(L"TickerSprite");
		// 時間の変数に足す
		m_idleTime += elapsedTime;
		if (m_idleTime >= 2.0f)
		{
			// 1秒後に表示がオフになる
			ptrStage->SetDrawActive(false);
		}

		// テロップの時間
		auto ptrStage1 = GetSharedGameObject<Telop>(L"Telop");
		// 時間の変数に足す
		m_TelopTime += elapsedTime;
		if (m_TelopTime >= 1.6f)
		{
			// 1秒後に表示がオフになる
			ptrStage1->SetDrawActive(false);

		}

		// テロップの時間
		auto ptrStage2 = GetSharedGameObject<Telop2>(L"Telop2");
		// 時間の変数に足す
		m_Telop2Time += elapsedTime;
		if (m_Telop2Time >= 2.0f)
		{
			// 1秒後に表示がオフになる
			ptrStage2->SetDrawActive(false);

		}

		// テロップの時間
		auto ptrStage3 = GetSharedGameObject<Telop3>(L"Telop3");
		// 時間の変数に足す
		m_Telop3Time += elapsedTime;
		if (m_Telop3Time >= 2.0f)
		{
			// 1秒後に表示がオフになる
			ptrStage3->SetDrawActive(false);

		}

		// テロップの時間
		auto ptrStage4 = GetSharedGameObject<Telop4>(L"Telop4");
		// 時間の変数に足す
		m_Telop4Time += elapsedTime;
		if (m_Telop4Time >= 2.0f)
		{
			// 1秒後に表示がオフになる
			ptrStage4->SetDrawActive(false);

		}
		return;
	}

	void GameStage::OnDestroy() {
		//BGMのストップ
		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		XAPtr->Stop(m_BGM);
	}

}
//end basecross
