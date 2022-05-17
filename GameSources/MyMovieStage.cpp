/*!
@file GameStage.cpp
@brief ゲームステージ実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	ムービーステージクラス
	//--------------------------------------------------------------------------------------
	//初期化
	void MyMovieStage::OnCreate() {
		MovieStage::OnCreate();
		wstring dataDir;
		//サンプルのためアセットディレクトリを取得
		App::GetApp()->GetAssetsDirectory(dataDir);
		App::GetApp()->ClearMovie();
		wstring strMovie = dataDir + L"Entry.mp4";
		SetMovieFileName(strMovie);
		//再生
		Play();
	}

	void MyMovieStage::OnUpdate() {
		//コントローラチェックして入力があればコマンド呼び出し
		m_InputHandler.PushHandle(GetThis<MyMovieStage>());
		auto elps = App::GetApp()->GetElapsedTime();
		MovieTime += elps;
		if (MovieTime >= 16.0f) {
			SetAutoRepeat(true);
			PostEvent(0.0f, GetThis<ObjectInterface>(),
				App::GetApp()->GetScene<Scene>(), L"ToGameStage");
			return;
		}

	}


	//Aボタン
	void MyMovieStage::OnPushA() {
		//何もしない
	}
	//Bボタン
	void MyMovieStage::OnPushB() {
		//ゲームステージに移行
		//PostEvent(0.0f, GetThis<ObjectInterface>(),
		//	App::GetApp()->GetScene<Scene>(), L"ToGameStage");
	}
}
//end basecross
