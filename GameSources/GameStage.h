/*!
@file GameStage.h
@brief  Q [   X e [ W
*/

#pragma once
#include "stdafx.h"


namespace basecross {
	enum class CameraSelect {
		myCamera,
		objCamera,
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
	//カベの作成
	void CreateWall();		

		//MyCamera用のビュー
		shared_ptr<SingleView> m_MyCameraView;
		//ObjCamera用のビュー
		shared_ptr<SingleView> m_ObjCameraView;
		CameraSelect m_CameraSelect;
		//入力ハンドラー
		InputHandler<GameStage> m_InputHandler;
		//敵の作成
		void CreateEnemy();
		//キャラクターの作成
		void CreateChara();
		//プレイヤーの作成
		void CreatePlayer();
		//ボスの作成
		void CreateBoss();
		//カメラマンの作成
		void CreateCameraman();
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
		void OnPushB();
		CameraSelect GetCameraSelect() const {
			return m_CameraSelect;
		}
		void ToObjCamera();
		void ToMyCamera();
	};
}
//end basecross