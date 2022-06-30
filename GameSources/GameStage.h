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
		bool m_createGameOverObjectFlg = false;
	CsvFile m_CsvC;           //CSVファイルそのC
	void CreateViewLight();   //ビューの作成
	void CreateMultiSpark();  //スパークエフェクト1の作成
	void CreateMultiSpark1(); //スパークエフェクト2の作成
	void CreatePillar();      //柱
	void CreateStageWall();   //マヤによるステージの壁作成
	void CreateStageFloor();  //マヤによるステージの床作成
	void CreateWall();        //壊れる壁の作成
	void CreateObstacle1();   //障害物１
	void CreateObstacle2();   //障害物2
	void CreateFallingRock(); //落石
	void CreateMyitem1();     //アイテムスプライト作成
	void CreateXSprite();     //Xボタンスプライトの作成
	void CreateYSprite();     //Yボタンスプライトの作成
	void CreateMygage();      //ゲージの枠の作成
	void CreateGageSprite();  //ゲージのスプライトの作成
	void CreateGageSprite2(); //ゲージのスプライト2の作成
	void CreateGageSprite3(); //ゲージのスプライト3の作成
	void CreateGageWhite();   //ゲージの背景の作成
	void CreateExitWall();    //出口の作成
	void CreateTime();        //タイム作成
	void CreateTickerSprite();//テロップ0
	void CreateTelop();       //テロップ1
	void CreateTelop2();      //テロップ2
	void CreateTelop3();      //テロップ3
	void CreateTelop4();      //テロップ4
	void CreatePlayer();      //プレイヤーの作成
	void BGM();               //BGMの再生1
	void OnDestroy();         //音楽を止める
	void CreateCameraman();   //カメラマンの作成
	float m_idleTime;         //テロップの表示時間0
	float m_TelopTime;        //テロップの表示時間1
	float m_Telop2Time;       //テロップの表示時間2
	float m_Telop3Time;       //テロップの表示時間3
	float m_Telop4Time;       //テロップの表示時間4
	float m_TotalTime;        //トータル時間
	float m_ExitTime;         //出口からムービーへの移動時間
	int m_Exit;               //出口に触れているか
	
		
	shared_ptr<SingleView> m_OpeningCameraView;//OpeningCamera用のビュー
	shared_ptr<SingleView> m_MyCameraView;     //MyCamera用のビュー
	CameraSelect m_CameraSelect;               //カメラを切り替える
	InputHandler<GameStage> m_InputHandler;    //入力ハンドラー
	shared_ptr<SoundItem> m_BGM;               //BGM
		
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
		virtual void OnCreate()override;//初期化
		virtual void OnUpdate()override;//更新
		void OnPushA() {}               //Aボタンなにもしない

		CameraSelect GetCameraSelect() const {
			return m_CameraSelect;
		}

		void ToMyCamera();
	};

}
//end basecross