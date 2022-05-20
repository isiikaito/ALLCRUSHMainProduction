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
	void MyClearStage::OnCreate() {
		MovieStage::OnCreate();
		wstring dataDir;
		//サンプルのためアセットディレクトリを取得
		App::GetApp()->GetAssetsDirectory(dataDir);
		wstring strMovie = dataDir + L"GameClear1.mp4";
		SetMovieFileName(strMovie);
		//再生
		Play();
	}

	void MyClearStage::OnUpdate() {
		//コントローラチェックして入力があればコマンド呼び出し
		//m_InputHandler.PushHandle(GetThis<MyClearStage>());
		auto elps = App::GetApp()->GetElapsedTime();
		MovieTime += elps;
		if (MovieTime >= 19.0f) {
			SetAutoRepeat(true);
			PostEvent(0.0f, GetThis<ObjectInterface>(),
				App::GetApp()->GetScene<Scene>(), L"ToGameStage");
			return;
		}

	}


	//Aボタン
	void MyClearStage::OnPushA() {
		//何もしない
	}
	//Bボタン
	void MyClearStage::OnPushB() {
		//ゲームステージに移行
		//PostEvent(0.0f, GetThis<ObjectInterface>(),
		//	App::GetApp()->GetScene<Scene>(), L"ToGameStage");
	}
}
//end basecross
