/*!
@file GameStage.h
@brief  Q [   X e [ W
*/

#pragma once
#include "stdafx.h"


namespace basecross {
	enum class CameraSelect {
		openingCamera,
		myCamera,
		objCamera,
		//endingCamera,
	};
	//--------------------------------------------------------------------------------------
	// ゲームステージクラス
	//--------------------------------------------------------------------------------------
	class GameStage : public Stage {
	//CSVファイルそのC
	CsvFile m_CsvC;
	//ビューの作成
	void CreateViewLight();
	void CreatestageObject();
	//スパークエフェクトの作成
	void CreateMultiSpark();
	void CreateMultiSpark1();

	//柱
	void CreatePillar();
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
	//落石
	void CreateFallingRock();
	//アイテムスプライト作成
	void CreateMyitem1();
	//ゲージの追加
	void CreateMygage();
	void CreateGageSprite();
	void CreateGageSprite2();
	void CreateGageSprite3();
	void CreateGageWhite();
	//ゲームクリアFadeOut
	void CreateFadeOut();
	//出口の作成
	void CreateExitWall();
	//タイム作成
	void CreateTime();	
	// テロップ
	void CreateTickerSprite();
	float m_idleTime;

	void CreateTelop();
	float m_TelopTime;

	void CreateTelop2();
	float m_Telop2Time;

	void CreateTelop3();
	float m_Telop3Time;

	void CreateTelop4();
	float m_Telop4Time;

	//トータル時間
	float m_TotalTime;
	
		//OpeningCamera用のビュー
		shared_ptr<SingleView> m_OpeningCameraView;
		//MyCamera用のビュー
		shared_ptr<SingleView> m_MyCameraView;
		//ObjCamera用のビュー
		shared_ptr<SingleView> m_ObjCameraView;
		//EndingCamera用のビュー
		//shared_ptr<SingleView> m_EndingCameraView;
		CameraSelect m_CameraSelect;
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
		//カメラマンの作成
		void CreateCameraman();

	public:
		//構築と破棄
		GameStage() :Stage(), m_TotalTime(0) {}
		virtual ~GameStage() {}
		//初期化
		virtual void OnCreate()override;
		//更新
		virtual void OnUpdate()override;
		//Aボタンなにもしない
		void OnPushA() {}
		//Bボタンカメラの変更
		void OnPushB();

		CameraSelect GetCameraSelect() const {
			return m_CameraSelect;
		}
		void ToObjCamera();
		void ToMyCamera();
		//void ToEndingCamera();
		void GameOver();

	};

}
//end basecross