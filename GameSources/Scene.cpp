/*!
@file Scene.cpp
@brief シーン実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	///	ゲームシーン
	//--------------------------------------------------------------------------------------
	void Scene::CreateResourses() {
		wstring dataDir;
		//サンプルのためアセットディレクトリを取得
		App::GetApp()->GetAssetsDirectory(dataDir);
		//各ゲームは以下のようにデータディレクトリを取得すべき
		wstring strTexture = dataDir + L"trace.png";
		App::GetApp()->RegisterTexture(L"TRACE_TX", strTexture);
		strTexture = dataDir + L"wall.jpg";
		App::GetApp()->RegisterTexture(L"WALL_TX", strTexture);
		strTexture = dataDir + L"doukutu.png";
		App::GetApp()->RegisterTexture(L"DOUKUTU_TX", strTexture);

		strTexture = dataDir + L"TITLE.png";
		App::GetApp()->RegisterTexture(L"TITLLE_TX", strTexture);

		//strTexture = dataDir + L"GameOver.png";
		//App::GetApp()->RegisterTexture(L"GAMEOVER_TX", strTexture);

		strTexture = dataDir + L"GameOver.jpg";
		App::GetApp()->RegisterTexture(L"GAMEOVER_TX", strTexture);

		strTexture = dataDir + L"flee.png";
		App::GetApp()->RegisterTexture(L"FLEE_TX", strTexture);

		strTexture = dataDir + L"PillarBrake.png";
		App::GetApp()->RegisterTexture(L"PillarBrake_TX", strTexture);

		strTexture = dataDir + L"JustTiming.png";
		App::GetApp()->RegisterTexture(L"JustTiming_TX", strTexture);

		strTexture = dataDir + L"ClearNear.png";
		App::GetApp()->RegisterTexture(L"ClearNear_TX", strTexture);

		strTexture = dataDir + L"WallBrake.png";
		App::GetApp()->RegisterTexture(L"WallBrake_TX", strTexture);

		//モデル
		//ボーンモデルの通常リソース
		auto multiModelMesh = MeshResource::CreateBoneModelMesh(dataDir, L"player06.bmf");
		App::GetApp()->RegisterResource(L"Object_WalkAnimation_MESH", multiModelMesh);

		//ボーンモデルのタンジェント付きリソース
		multiModelMesh = MeshResource::CreateBoneModelMeshWithTangent(dataDir, L"player06.bmf");
		App::GetApp()->RegisterResource(L"Object_WalkAnimation_MESH_WITH_TAN", multiModelMesh);

		//ボーンモデル(マルチメッシュ)の通常リソース
		auto EnemyModelMesh = MeshResource::CreateBoneModelMesh(dataDir, L"EnemyBoss1.bmf");
		App::GetApp()->RegisterResource(L"EnemyRun_MESH", EnemyModelMesh);

		//ボーンモデル(マルチメッシュ)のタンジェント付きリソース
		EnemyModelMesh = MeshResource::CreateBoneModelMeshWithTangent(dataDir, L"EnemyBoss1.bmf");
		App::GetApp()->RegisterResource(L"EnemyRun_MESH_WITH_TAN", EnemyModelMesh);

		//法線マップ
		strTexture = dataDir + L"Tx_Checker_Normal.png";
		App::GetApp()->RegisterTexture(L"OBJECT_NORMAL_TX", strTexture);

		//壁のモデル読み込み
		auto staticModelMesh1 = MeshResource::CreateStaticModelMesh(dataDir, L"StageWall.bmf");
		App::GetApp()->RegisterResource(L"STAGEWALL_MESH", staticModelMesh1);

		//床のモデル読み込み
		auto staticModelMesh2 = MeshResource::CreateStaticModelMesh(dataDir, L"yuka2.bmf");
		App::GetApp()->RegisterResource(L"STAGEFLOOR_MESH", staticModelMesh2);

        //出口のモデル読み込み
		auto staticModelMesh3 = MeshResource::CreateStaticModelMesh(dataDir, L"ExitWall.bmf");
		App::GetApp()->RegisterResource(L"EXITWALL_MESH", staticModelMesh3);

        //障害物１の読み込み
		auto staticModelMesh4 = MeshResource::CreateStaticModelMesh(dataDir, L"Obuject.KU2.bmf");
		App::GetApp()->RegisterResource(L"OBSTACLE1_MESH", staticModelMesh4);

		//障害物2の読み込み
		auto staticModelMesh5 = MeshResource::CreateStaticModelMesh(dataDir, L"Obuject05.bmf");
		App::GetApp()->RegisterResource(L"OBSTACLE2_MESH", staticModelMesh5);

		//柱読み込み
		auto staticModelMesh6 = MeshResource::CreateStaticModelMesh(dataDir, L"pillar.bmf");
		App::GetApp()->RegisterResource(L"PILLAR_MESH", staticModelMesh6);

		//落石読み込み
		auto staticModelMesh7 = MeshResource::CreateStaticModelMesh(dataDir, L"Foring.bmf");
		App::GetApp()->RegisterResource(L"IWA_MESH", staticModelMesh7);

		//壊す壁Maya読み込み
		auto staticModelMesh8 = MeshResource::CreateStaticModelMesh(dataDir, L"WallHPMax.bmf");
		App::GetApp()->RegisterResource(L"UNBREAKWALL_MESH", staticModelMesh8);


		//
		auto staticModelMesh9 = MeshResource::CreateStaticModelMesh(dataDir, L"BreakWall02.bmf");
		App::GetApp()->RegisterResource(L"DAMAGEWALL1_MESH", staticModelMesh9);

		//
		auto staticModelMesh10 = MeshResource::CreateStaticModelMesh(dataDir, L"BreakeWall01.bmf");
		App::GetApp()->RegisterResource(L"DAMAGEWALL2_MESH", staticModelMesh10);

		//
		auto staticModelMesh11 = MeshResource::CreateStaticModelMesh(dataDir, L"BerakWall03.bmf");
		App::GetApp()->RegisterResource(L"DAMAGEWALL3_MESH", staticModelMesh11);

		//タイムのテクスチャ
		strTexture = dataDir + L"number.png";
		App::GetApp()->RegisterTexture(L"NUMBER_TX", strTexture);
		//アイテムテクスチャ
		strTexture = dataDir + L"SPEED.png";
		App::GetApp()->RegisterTexture(L"SPEED_TX", strTexture);
		//Xボタンテクスチャ
		strTexture = dataDir + L"XButton.png";
		App::GetApp()->RegisterTexture(L"XButton_TX", strTexture);
		//Yボタンテクスチャ
		strTexture = dataDir + L"YButton.png";
		App::GetApp()->RegisterTexture(L"YButton_TX", strTexture);
		//ハンマーゲージ
		strTexture = dataDir + L"GAGE.png";
		App::GetApp()->RegisterTexture(L"GAGE_TX", strTexture);

		//文字テクスチャ
		strTexture = dataDir + L"go.png";
		App::GetApp()->RegisterTexture(L"Stage1_TX", strTexture);

		//文字テクスチャ
		strTexture = dataDir + L"Stage2.png";
		App::GetApp()->RegisterTexture(L"Stage2_TX", strTexture);
		
		//メニューテクスチャ
		strTexture = dataDir + L"MenuSelect.png";
		App::GetApp()->RegisterTexture(L"MenuSelect_TX", strTexture);
		
		//エフェクト関連
		strTexture = dataDir + L"Splash.png";
		App::GetApp()->RegisterTexture(L"SPARK_TX", strTexture);
		strTexture = dataDir + L"spark.png";
		App::GetApp()->RegisterTexture(L"SPARK_TX1", strTexture);
		strTexture = dataDir + L"SpeedUp.png";
		App::GetApp()->RegisterTexture(L"SPEEDUP_TX", strTexture);
		strTexture = dataDir + L"Impact.png";
		App::GetApp()->RegisterTexture(L"IMPACT_TX", strTexture);
		strTexture = dataDir + L"PowerUp.png";
		App::GetApp()->RegisterTexture(L"POWERUP_TX1", strTexture);

		//サウンド
		wstring CursorWav = dataDir + L"music.mp3";
		App::GetApp()->RegisterWav(L"BGM", CursorWav);
		//敵の声
		CursorWav = dataDir + L"WalkSound.wav";
		App::GetApp()->RegisterWav(L"WalkSound", CursorWav);
		//走るサウンド	
		CursorWav = dataDir + L"run.wav";
		App::GetApp()->RegisterWav(L"run", CursorWav);
		//スピードアップのサウンド
		CursorWav = dataDir + L"SpeedUp.wav";
		App::GetApp()->RegisterWav(L"SpeedUp", CursorWav);
		//スピードアップのサウンド
		CursorWav = dataDir + L"PowerUp.wav";
		App::GetApp()->RegisterWav(L"PowerUp", CursorWav);
		//ハンマーを振るサウンド
		CursorWav = dataDir + L"Hammer.wav";
		App::GetApp()->RegisterWav(L"Hammer", CursorWav);
		//壁を攻撃を行った時のサウンド
		CursorWav = dataDir + L"AttackWall.wav";
		App::GetApp()->RegisterWav(L"AttackWall", CursorWav);
		//壁が壊れたときのサウンド
		CursorWav = dataDir + L"BrakeWall.wav";
		App::GetApp()->RegisterWav(L"BrakeWall", CursorWav);
		//敵の声
		CursorWav = dataDir + L"EnemyVoice.wav";
		App::GetApp()->RegisterWav(L"EnemyVoice", CursorWav);
		//敵に岩が当たる音
		CursorWav = dataDir + L"RockAttack.wav";
		App::GetApp()->RegisterWav(L"RockAttack", CursorWav);


	}
	void Scene::OnCreate() {
		try {
			//リソース作成
			CreateResourses();
			//クリアする色を設定
			Col4 Col;
			Col.set(31.0f / 255.0f, 30.0f / 255.0f, 71.0f / 255.0f, 255.0f / 255.0f);
			SetClearColor(Col);
			//自分自身にイベントを送る
			//最初のシーンに設定できる
			PostEvent(0.0f, GetThis<ObjectInterface>(), GetThis<Scene>(), L"ToTitleStage");

		}

		catch (...) {
			throw;
		}
	}

	Scene::~Scene() {
	}

	void Scene::OnEvent(const shared_ptr<Event>& event) {
		if (event->m_MsgStr == L"ToTitleStage") {
			//タイトルステージの設定
			ResetActiveStage<TitleStage>();
		}

		else if (event->m_MsgStr == L"ToGameStage") {
			//ゲームステージの設定
			ResetActiveStage<GameStage>();
		}

		else if (event->m_MsgStr == L"ToGameStage2") {
			//ゲームステージ2の設定
			ResetActiveStage<GameStage2>();
		}
		else if (event->m_MsgStr == L"ToMenuStage") {
			//メニューステージの設定
			ResetActiveStage<MenuStage>();
		}
		else if (event->m_MsgStr == L"ToClearStage") {
			//クリアステージの設定
			ResetActiveStage<MyClearStage>();
		}

		else if (event->m_MsgStr == L"ToGameOverStage") {
			//ゲームオーバーステージの設定
			ResetActiveStage<GameOverStage>();
		}
		
		else if (event->m_MsgStr == L"ToMovieStage") {
			m_MovieActive = true;
			//ボスの登場シーンステージの設定
			ResetActiveStage<MyMovieStage>();
		}
	}

}
//end basecross
