/*!
@file Player.h
@brief プレイヤーなど
*/

#pragma once
#include "stdafx.h"

namespace basecross{
	class Player : public GameObject
	{
		const float MaxMoveSpeed; // 移動の最大速

		Vec3 moveDir; // 移動方向ベクトル（単位ベクトル）
		float speed; // 移動の速さ

		float accel; // 加速度

		Vec3 GetMoveVector() const;

		InputHandler<Player> m_InputHandler;
		//void MovePlayer();


	public:
		// ステージを渡せるコンストラクタが必須
		Player(const std::shared_ptr<Stage>& stage)
			: GameObject(stage), // ステージは親クラスに投げる
			MaxMoveSpeed(6.0f),
			moveDir(0.0f, 0.0f, 0.0f),
			speed(0.0f),
			accel(0.0f)
		{
		}
		//Aボタン
		void OnPushA();
		//Bボタンなにもしない
		void OnPushB() {}


		void OnCreate() override; // オブジェクトの初期化用関数（UnityのStart関数）
		void OnUpdate() override; // オブジェクトのフレームごとの処理（UnityのUpdate関数）
		void OnUpdate2() override; // オブジェクトのフレームごとの処理（UnityのUpdate関数）
	};


}
//end basecross

