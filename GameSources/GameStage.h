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
		//objCamera,
		//mainCamera,
		//backCamera
	};
	//--------------------------------------------------------------------------------------
	// ゲームステージクラス
	//--------------------------------------------------------------------------------------
	class GameStage : public Stage {
	//CSVファイルそのC
	CsvFile m_CsvC;
	//ビューの作成
	void CreateViewLight();
	
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
	void CreateXSprite();
	void CreateYSprite();
	//ゲージの追加
	void CreateMygage();
	void CreateGageSprite();
	void CreateGageSprite2();
	void CreateGageSprite3();
	void CreateGageWhite();
	
	
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

	//出口からムービーへの移動時間
	float m_ExitTime;
	//出口に触れているか
	int m_Exit;
	
		//OpeningCamera用のビュー
		shared_ptr<SingleView> m_OpeningCameraView;
		//MyCamera用のビュー
		shared_ptr<SingleView> m_MyCameraView;
		//ObjCamera用のビュー
		//shared_ptr<SingleView> m_ObjCameraView;
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
		GameStage() :Stage(),
			m_TotalTime(0),
			m_CameraSelect(),
			m_Exit(0),
			m_TelopTime(0.0f),
			m_Telop2Time(0.0f),
			m_Telop3Time(0.0f),
			m_Telop4Time(0.0f),
			m_idleTime(0.0f),
			m_ExitTime(0.0f)


		{}
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

		//void ToObjCamera();
		void ToMyCamera();
		//void ToMainCamera();
		//void ToBackCamera();
	};

}
//end basecross