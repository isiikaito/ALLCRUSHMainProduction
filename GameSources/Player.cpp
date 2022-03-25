/*!
@file Player.cpp
@brief プレイヤーなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{
	void Player::OnCreate()
	{
		// オブジェクトの見た目を決定するドローコンポーネントを「追加」する
		auto drawComp = AddComponent<PNTStaticDraw>(); // 新規でコンポーネントを追加する
		drawComp->SetMeshResource(L"DEFAULT_CUBE"); // 形状を設定

				// トランスフォームコンポーネントを「取得」する（トランスフォームだけは初めから追加されている）
		auto transComp = GetComponent<Transform>(); // すでに追加されているコンポーネントを取得する
		transComp->SetPosition(-2.0f, 0.5f, 0.0f);


	}

	void Player::OnUpdate()
	{
		// アプリケーションオブジェクトを取得する
		auto& app = App::GetApp();

		// デルタタイムを取得する
		float delta = app->GetElapsedTime(); // 前フレームからの「経過時間」

		// カメラを取得する
		auto stage = GetStage(); // このオブジェクトが追加されているステージ
		auto camera = stage->GetView()->GetTargetCamera(); // カメラを取得する

		// カメラの回り込み
		float rad = 0.0f;

		// CameraオブジェクトをMainCameraオブジェクトに「ダウンキャスト」する
		auto mainCamera = dynamic_pointer_cast<MainCamera>(camera);
		if (mainCamera) // nullptr出なかったら、キャスト成功
		{
			rad = mainCamera->GetAngleY() + XMConvertToRadians(90.0f);
		}

		// ゲームコントローラーオブジェクトを取得する
		auto& device = app->GetInputDevice();
		const auto& pad = device.GetControlerVec()[0]; // ゼロ番目のコントローラーを取得する
		moveDir = Vec3(pad.fThumbLX, 0.0f, pad.fThumbLY); // 大きさが 0.0f ～ 1.0f;
		auto m = Mat3x3( // Y軸中心で回転させる行列
			Vec3(cosf(rad), 0.0f, sinf(rad)),  // X軸の向き
			Vec3(0.0f, 1.0f, 0.0f),  // Y軸の向き
			Vec3(-sinf(rad), 0.0f, cosf(rad))); // Z軸の向き
		moveDir = moveDir * m; // スティックの入力をangleYラジアン回転させる

		speed = MaxMoveSpeed * moveDir.length(); // 最大速×スティックベクトルの大きさ
		moveDir.normalize(); // 移動方向を正規化する

		auto transComp = GetComponent<Transform>();
		auto position = transComp->GetPosition(); // 現在の位置座標を取得する
		auto scale = transComp->GetScale();

		// プレイヤーの移動
		position += moveDir * speed * delta; // デルタタイムを掛けて「秒間」の移動量に変換する

		transComp->SetPosition(position); // 更新した値で再設定する
		if (speed > 0.0f) // スティックが倒れていたら・・
		{
			float rotY = atan2f(-moveDir.z, moveDir.x); // アークタンジェントを使うとベクトルを角度に変換できる
			transComp->SetRotation(0.0f, rotY, 0.0f); // ラジアン角で設定
		}

		auto ptrTarget = m_TargetObject.lock();
		if (pad.wPressedButtons & XINPUT_GAMEPAD_LEFT_SHOULDER)
		{
			auto pos = ptrTarget->GetComponent<Transform>()->GetPosition();
			SetAt(pos);
		}
	}

}
//end basecross

