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
		//ObjCamera用のビュー
		m_ObjCameraView = ObjectFactory::Create<SingleView>(GetThis<Stage>());
		auto ptrObjCamera = ObjectFactory::Create<ObjCamera>();
		m_ObjCameraView->SetCamera(ptrObjCamera);
		//初期状態で使うView
		SetView(m_MyCameraView);
		m_CameraSelect = CameraSelect::myCamera;
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

	//カメラマンの作成
	void GameStage::CreateCameraman() {
		auto ptrCameraman = AddGameObject<Cameraman>(2.0f);
		//シェア配列にCameramanを追加
		SetSharedGameObject(L"Cameraman", ptrCameraman);
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
			//カメラマンの作成
			CreateCameraman();
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

	void GameStage::ToObjCamera() {
		auto ptrEnemy = GetSharedGameObject<EnemyObject>(L"Enemy");
		//ObjCameraに変更
		auto ptrCameraman = GetSharedGameObject<Cameraman>(L"Cameraman");
		auto ptrObjCamera = dynamic_pointer_cast<ObjCamera>(m_ObjCameraView->GetCamera());
		if (ptrObjCamera) {
			ptrObjCamera->SetCameraObject(ptrCameraman);
			ptrObjCamera->SetTargetObject(ptrEnemy);
			//m_ObjCameraViewを使う
			SetView(m_ObjCameraView);
			m_CameraSelect = CameraSelect::objCamera;
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


	//Bボタンカメラの変更
	void GameStage::OnPushB() {
		switch (m_CameraSelect) {
		case CameraSelect::myCamera:
		{
			ToObjCamera();
		}
		break;
		case CameraSelect::objCamera:
		{
			ToMyCamera();
		}
		break;
		}
	}

}
//end basecross
