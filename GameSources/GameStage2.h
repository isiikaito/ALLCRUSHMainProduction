/*!
@file GameStage.h
@brief  Q [   X e [ W
*/

#pragma once
#include "stdafx.h"


namespace basecross {
	//--------------------------------------------------------------------------------------
	// ゲームステージ2クラス
	//--------------------------------------------------------------------------------------
	class GameStage2 : public Stage {
		//CSVファイルそのC
		CsvFile m_CsvC;
		//ビューの作成
		void CreateViewLight();
		void CreatestageObject();
		//マヤによるステージの壁作成
		void CreateStageWall();
		//マヤによるステージの床作成
		void CreateStageFloor();
		//カベの作成
		void CreateWall();
		//障害物１
		void CreateObstacle1();
		//障害物2
		void CreateObstacle2();
		//アイテムスプライト作成
		void CreateMyitem1();
		//ゲージの追加
		void CreateMygage();
		void CreateExitWall();
		//タイム作成
		void CreateTime();
		//トータル時間
		float m_TotalTime;

		//MyCamera用のビュー
		shared_ptr<SingleView> m_MyCameraView;
		//入力ハンドラー
		InputHandler<GameStage> m_InputHandler;
		//BGM
		shared_ptr<SoundItem> m_BGM;
		//敵の作成
		void CreateEnemy();
		//キャラクターの作成
		void CreateChara();
		//プレイヤーの作成
		void CreatePlayer();
		//BGMの再生
		void BGM();
		void OnDestroy();
	public:
		//構築と破棄
		GameStage2() :Stage(), m_TotalTime(0) {}
		virtual ~GameStage2() {}
		//初期化
		virtual void OnCreate()override;
		//更新
		virtual void OnUpdate()override;
		//Aボタンなにもしない
		void OnPushA() {}
		//Bボタンカメラの変更
		void OnPushB() {}
	};

}
//end basecross
