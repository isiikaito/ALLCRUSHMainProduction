/*!
@file Player.cpp
@brief プレイヤーなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{
	void Player::OnCreate()
	{

		//初期位置などの設定
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(0.5f, 0.5f, 0.5f);
		ptrTrans->SetRotation(0.0f, 0.0f, 0.0f);
		ptrTrans->SetPosition(0.0f, 0.25f, 0.0f);

		//CollisionSphere衝突判定を付ける
		auto ptrColl = AddComponent<CollisionSphere>();

		Mat4x4 spanMat; // モデルとトランスフォームの間の差分行列
		spanMat.affineTransformation(
			Vec3(1.0f, 1.0f, 1.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, XM_PI * -0.5f, 0.0f),
			Vec3(0.0f, -0.5f, 0.0f)
		);

		//重力をつける
		auto ptrGra = AddComponent<Gravity>();
		//影をつける（シャドウマップを描画する）
		auto ptrShadow = AddComponent<Shadowmap>();
		//影の形（メッシュ）を設定
		ptrShadow->SetMeshResource(L"Object_WalkAnimation_MESH");
		ptrShadow->SetMeshToTransformMatrix(spanMat);

		//描画コンポーネントの設定
		auto ptrDraw = AddComponent<BcPNTnTBoneModelDraw>();
		ptrDraw->SetFogEnabled(true);
		//描画するメッシュを設定
		ptrDraw->SetMeshResource(L"Object_WalkAnimation_MESH_WITH_TAN");
		ptrDraw->SetNormalMapTextureResource(L"OBJECT_NORMAL_TX");
		ptrDraw->SetMeshToTransformMatrix(spanMat);
		ptrDraw->AddAnimation(L"Default", 0, 10, false, 30.0f);
		ptrDraw->AddAnimation(L"Move", 10, 15, false, 30.0f);
		ptrDraw->AddAnimation(L"Action", 25, 15, false, 30.0f);
		ptrDraw->ChangeCurrentAnimation(L"Default");
	}

	void Player::OnUpdate()
	{
		//アニメション
		auto ptrDraw = GetComponent<BcPNTnTBoneModelDraw>();
		auto move = ptrDraw->GetCurrentAnimation();

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
		auto mainCamera = dynamic_pointer_cast<MyCamera>(camera);
		if (mainCamera) // nullptr出なかったら、キャスト成功
		{
			rad = mainCamera->GetAngleY() + XMConvertToRadians(90.0f);
		}

		// ゲームコントローラーオブジェクトを取得する
		auto& device = app->GetInputDevice();
		const auto& pad = device.GetControlerVec()[0]; // ゼロ番目のコントローラーを取得する
		moveDir = Vec3(pad.fThumbLX, 0.0f, pad.fThumbLY); // 大きさが 0.0f 〜 1.0f;
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
			//歩くアニメーション
			if (move == L"Default" || move == L"Action") {
				ptrDraw->ChangeCurrentAnimation(L"Move");
				if (ptrDraw->IsTargetAnimeEnd()) {
					ptrDraw->ChangeCurrentAnimation(L"Default");
				}
			}
		}
		//立ち止まるアニメーション
		if (move == L"Move" || move == L"Action") {
			if (ptrDraw->IsTargetAnimeEnd()) {
				ptrDraw->ChangeCurrentAnimation(L"Default");
			}
		}


		//コントローラチェックして入力があればコマンド呼び出し
		m_InputHandler.PushHandle(GetThis<Player>());
		//MovePlayer();

	}
	//Aボタン
	void Player::OnPushA() {
		//ハンマーを振るアニメーション
		auto ptrDraw = GetComponent<BcPNTnTBoneModelDraw>();
		auto action = ptrDraw->GetCurrentAnimation();
		if (action != L"Action" && action != L"Move") {
			ptrDraw->ChangeCurrentAnimation(L"Action");
		}

		//auto grav = GetComponent<Gravity>();
		//grav->StartJump(Vec3(0, 4.0f, 0));
	}
	//プレイヤーがゴールにたどり着いたら
	void Player::OnUpdate2() {
		auto ptrTrans = GetComponent<Transform>();
		Vec3 pos = ptrTrans->GetPosition();
		if (pos.x <-45.0f) {
			PostEvent(0.0f, GetThis<Player>(), App::GetApp()->GetScene<Scene>(), L"ToClearStage");
		}

		auto ptrDraw = GetComponent<BcPNTnTBoneModelDraw>();
		float elapsedTime = App::GetApp()->GetElapsedTime();
		ptrDraw->UpdateAnimation(elapsedTime);

	}
	//プレイヤーがEnemyに当たったら
	void Player::OnCollisionEnter(shared_ptr<GameObject>& Other) {
		auto ptr = dynamic_pointer_cast<EnemyObject>(Other);
		if (ptr) {
				PostEvent(0.0f, GetThis<Player>(), App::GetApp()->GetScene<Scene>(), L"ToGameOverStage");
		}
		
		
	}

}
//end basecross

