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
		AddGameObject<Wall>(Vec3(1.0f, 10.0f, 10.0f), Quat(), Vec3(-5.0f, 1.0f, 0.0f));
		AddGameObject<Wall>(Vec3(1.0f, 10.0f, 10.0f), Quat(), Vec3(-13.0f, 1.0f, 0.0f));
		AddGameObject<Wall>(Vec3(1.0f, 10.0f, 10.0f), Quat(), Vec3(-21.0f, 1.0f, 0.0f));
		AddGameObject<Wall>(Vec3(1.0f, 10.0f, 10.0f), Quat(), Vec3(-29.0f, 1.0f, 0.0f));
		AddGameObject<Wall>(Vec3(1.0f, 10.0f, 10.0f), Quat(), Vec3(-37.0f, 1.0f, 0.0f));

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
		//プレーヤーの作成
		auto EnemyPtr = AddGameObject<EnemyObject>();
		//シェア配列にプレイヤーを追加
		SetSharedGameObject(L"Enemy", EnemyPtr);
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
			m_CsvC.SetFileName(DataDir + L"stageObject.csv");
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

			AddGameObject<EnemyObject>();
			//オブジェクトの追加
			CreatestageObject();
			//
			CreateWall();
		}
		catch (...) {
			throw;
		}
	}
	void GameStage::OnUpdate() {
		//コントローラチェックして入力があればコマンド呼び出し
		m_InputHandler.PushHandle(GetThis<GameStage>());
	}

	void GameStage::OnDestroy() {
		//BGMのストップ
		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		XAPtr->Stop(m_BGM);
	}
}
//end basecross
