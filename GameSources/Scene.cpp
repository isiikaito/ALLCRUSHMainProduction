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
		//App::GetApp()->GetDataDirectory(DataDir);
		wstring strTexture = dataDir + L"sky.jpg";
		App::GetApp()->RegisterTexture(L"SKY_TX", strTexture);
		strTexture = dataDir + L"trace.png";
		App::GetApp()->RegisterTexture(L"TRACE_TX", strTexture);
		strTexture = dataDir + L"wall.jpg";
		App::GetApp()->RegisterTexture(L"WALL_TX", strTexture);
		strTexture = dataDir + L"doukutu.png";
		App::GetApp()->RegisterTexture(L"DOUKUTU_TX", strTexture);
		strTexture = dataDir + L"Titlle.jpg";
		App::GetApp()->RegisterTexture(L"TITLLE_TX", strTexture);

		strTexture = dataDir + L"ゲームオーバー.jpg";
		App::GetApp()->RegisterTexture(L"GAMEOVER_TX", strTexture);

		//モデル
		//ボーンモデルの通常リソース
		auto multiModelMesh = MeshResource::CreateBoneModelMesh(dataDir, L"Walkman.bmf");
		App::GetApp()->RegisterResource(L"Object_WalkAnimation_MESH", multiModelMesh);

		//ボーンモデルのタンジェント付きリソース
		multiModelMesh = MeshResource::CreateBoneModelMeshWithTangent(dataDir, L"Walkman.bmf");
		App::GetApp()->RegisterResource(L"Object_WalkAnimation_MESH_WITH_TAN", multiModelMesh);

		//ボーンモデル(マルチメッシュ)の通常リソース
		auto EnemyModelMesh = MeshResource::CreateBoneModelMesh(dataDir, L"EnemyRun.bmf");
		App::GetApp()->RegisterResource(L"EnemyRun_MESH", EnemyModelMesh);

		//ボーンモデル(マルチメッシュ)のタンジェント付きリソース
		EnemyModelMesh = MeshResource::CreateBoneModelMeshWithTangent(dataDir, L"EnemyRun.bmf");
		App::GetApp()->RegisterResource(L"EnemyRun_MESH_WITH_TAN", EnemyModelMesh);

		//法線マップ
		strTexture = dataDir + L"Tx_Checker_Normal.png";
		App::GetApp()->RegisterTexture(L"OBJECT_NORMAL_TX", strTexture);

		//サウンド
		wstring CursorWav = dataDir + L"music.mp3";
		App::GetApp()->RegisterWav(L"BGM", CursorWav);

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
			//最初のアクティブステージの設定
			ResetActiveStage<GameStage>();
		}

		else if (event->m_MsgStr == L"ToClearStage") {
			//最初のアクティブステージの設定
			ResetActiveStage<ClearStage>();
		}

		else if (event->m_MsgStr == L"ToGameOverStage") {
			//最初のアクティブステージの設定
			ResetActiveStage<GameOverStage>();
		}
		


	}

}
//end basecross
