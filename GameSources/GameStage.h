﻿/*!
@file GameStage.h
@brief �Q�[���X�e�[�W
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
	public:
	//構築と破棄
	GameStage() :Stage() {}
	virtual ~GameStage() {}
	//初期化
	virtual void OnCreate()override;
	//カベの作成
	void CreateWall();
	};
}
//end basecross

