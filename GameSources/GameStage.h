/*!
@file GameStage.h
@brief  Q [   X e [ W
*/

#pragma once
#include "stdafx.h"


namespace basecross {
	//--------------------------------------------------------------------------------------
	// ゲームステージクラス
	//--------------------------------------------------------------------------------------
	class GameStage : public Stage {
	//CSVファイルそのC
	CsvFile m_CsvC;
	//ビューの作成
	void CreateViewLight();
	void CreatestageObject();
	//カベの作成
	void CreateWall();		

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
		GameStage() :Stage() {}
		virtual ~GameStage() {}
		//初期化
		virtual void OnCreate()override;
		//更新
		virtual void OnUpdate()override;
		//Aボタンなにもしない
		void OnPushA() {}
		//Bボタンカメラの変更
		void OnPushB(){}
	};
}
//end basecross