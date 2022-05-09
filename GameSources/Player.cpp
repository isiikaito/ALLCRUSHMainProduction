/*!
@file Player.cpp
@brief プレイヤーなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void Player::OnCreate()
	{

		//初期位置などの設定
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(0.1f,0.1f, 0.1f);
		ptrTrans->SetRotation(0.0f, 0.0f, 0.0f);
		ptrTrans->SetPosition(40.0f, 0.25f, 0.0f);



		//CollisionSphere衝突判定を付ける
		auto ptrColl = AddComponent<CollisionSphere>();
		/*ptrColl->SetDrawActive(true);*/
		//衝突判定を表示
		/*ptrColl->SetDrawActive(true);*/
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
		ptrDraw->AddAnimation(L"Default", 0, 10, true, 15.0f);
		ptrDraw->AddAnimation(L"Move", 10, 30, true, 50.0f);
		ptrDraw->AddAnimation(L"Action", 40, 35, false, 35.0f);
		ptrDraw->AddAnimation(L"ActionPull", 40, 20, false, 35.0f);
		ptrDraw->AddAnimation(L"ActionPush", 60, 15, false, 35.0f);
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
		moveDir = Vec3(pad.fThumbLX, 0.0f, pad.fThumbLY); // 大きさが 0.0f ～ 1.0f;
		auto m = Mat3x3( // Y軸中心で回転させる行列
			Vec3(cosf(rad), 0.0f, sinf(rad)),  // X軸の向き
			Vec3(0.0f, 1.0f, 0.0f),  // Y軸の向き
			Vec3(-sinf(rad), 0.0f, cosf(rad))); // Z軸の向き
		moveDir = moveDir * m; // スティックの入力をangleYラジアン回転させる

		speed = MaxMoveSpeed * moveDir.length() * moveStop; // 最大速×スティックベクトルの大きさ×停止させるかどうかの判定
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
			//if (move != L"Move") {
			if (move == L"Default") {
				ptrDraw->ChangeCurrentAnimation(L"Move");
				//サウンドの再生
				auto ptrXA = App::GetApp()->GetXAudio2Manager();
				m_BGM = ptrXA->Start(L"run", 0, 0.5f);
			}
		}
		else {
			//立ち止まるアニメーション
			if (move == L"Move") {
					ptrDraw->ChangeCurrentAnimation(L"Default");
					auto ptrXA = App::GetApp()->GetXAudio2Manager();
					ptrXA->Stop(m_BGM);
					moveStop = 1.0f;//移動停止解除
			}
		}

		//コントローラチェックして入力があればコマンド呼び出し
		m_InputHandler.PushHandle(GetThis<Player>());
		//MovePlayer();
		m_InputHandler2.PushHandle(GetThis<Player>());

	}

	//Aボタン
	void Player::OnPushA() {		
		//ハンマーを振るアニメーション

		auto ptrDraw = GetComponent<BcPNTnTBoneModelDraw>();
		auto action = ptrDraw->GetCurrentAnimation();
		//if (action == L"Default") {
		auto transComp = GetComponent<Transform>();
		auto position = transComp->GetPosition(); // 現在の位置座標を取得する

		if (action != L"ActionPull") {
			ptrDraw->ChangeCurrentAnimation(L"ActionPull");			

			auto ptrXA = App::GetApp()->GetXAudio2Manager();
			ptrXA->Stop(m_BGM);//bgm(足音の停止)

			moveStop = 0.0f;//移動の停止
		}

		SPHERE playerSp(position, 2.0f);
		auto group = GetStage()->GetSharedObjectGroup(L"Wall_Group");
		auto vec = group->GetGroupVector();
		for (auto& v : vec) {
			auto shPtr = v.lock();
			Vec3 ret;
			auto ptrWall = dynamic_pointer_cast<Wall>(shPtr);
			 
			if (ptrWall) {
				auto WallObb = ptrWall->GetComponent<CollisionObb>()->GetObb();
				if (/*近づいたら*/
					HitTest::SPHERE_OBB(playerSp, WallObb, ret)) { 
					//壁との距離が2.0以下になった
					auto ctrlVec = App::GetApp()->GetInputDevice().GetControlerVec();
					if (ctrlVec[0].wButtons & XINPUT_GAMEPAD_A) {
						//コントローラのボタンが押されていたら、shPtrを消す
						GetStage()->RemoveGameObject<Wall>(shPtr);
					}
				}
			}
		}

		//auto group1 = GetStage()->GetSharedObjectGroup(L"Obstacle1_Group1");
		//auto vec1 = group1->GetGroupVector();
		//for (auto& v1 : vec1) {
		//	auto shPtr = v1.lock();
		//	Vec3 ret;
		//	auto ptrObstacle1 = dynamic_pointer_cast<Obstacle1>(shPtr);

		//	if (ptrObstacle1) {
		//		auto Obstacle1Obb = ptrObstacle1->GetComponent<CollisionObb>()->GetObb();
		//		if (/*近づいたら*/
		//			HitTest::SPHERE_OBB(playerSp, Obstacle1Obb, ret)) {
		//			//壁との距離が2.0以下になった
		//			auto ctrlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		//			if (ctrlVec[0].wButtons & XINPUT_GAMEPAD_A) {
		//				//コントローラのボタンが押されていたら、shPtrを消す
		//				GetStage()->RemoveGameObject<Obstacle1>(shPtr);
		//			}
		//		}
		//	}
		//}
		//auto grav = GetComponent<Gravity>();
		//grav->StartJump(Vec3(0, 4.0f, 0));
	}

	



	//プレイヤーがゴールにたどり着いたら
	void Player::OnUpdate2() {
		//auto ptrTrans = GetComponent<Transform>();
		//Vec3 pos = ptrTrans->GetPosition();
		//if (pos.x < -45.0f) {
		//	PostEvent(0.0f, GetThis<Player>(), App::GetApp()->GetScene<Scene>(), L"ToClearStage");
		//}

		auto ptrDraw = GetComponent<BcPNTnTBoneModelDraw>();
		float elapsedTime = App::GetApp()->GetElapsedTime();
		auto now = ptrDraw->UpdateAnimation(elapsedTime);

		auto action = ptrDraw->GetCurrentAnimation();

		if (action == L"ActionPull") {

			if (ptrDraw->IsTargetAnimeEnd()) {
				//ActionPullのときこのif文に入ったら、ChangeCurrentAnimationをActionPuhにする
				ptrDraw->ChangeCurrentAnimation(L"ActionPush");

				auto ptrXA = App::GetApp()->GetXAudio2Manager();
				//サウンドの再生
				ptrXA->Start(L"Hammer", 0, 0.5f);
			}
		}
		else {
			if (now) {
				ptrDraw->ChangeCurrentAnimation(L"Default");
				auto ptrXA = App::GetApp()->GetXAudio2Manager();
				ptrXA->Stop(m_BGM);

				moveStop = 1.0f;//移動停止解除
			}
		}
	}
	//プレイヤーがEnemyに当たったら
	void Player::OnCollisionEnter(shared_ptr<GameObject>& Other) {
		
		auto ptr = dynamic_pointer_cast<EnemyObject>(Other);
		if (ptr) {
			PostEvent(0.0f, GetThis<Player>(), App::GetApp()->GetScene<Scene>(), L"ToGameOverStage");
		}
		auto ptr1 = dynamic_pointer_cast<ExitWall>(Other);
		if (ptr1) {
			PostEvent(0.0f, GetThis<Player>(), App::GetApp()->GetScene<Scene>(), L"ToClearStage");
		}

		//アイテムの表示
		itemCount = 0;
		auto ptr3 = dynamic_pointer_cast<Obstacle1>(Other);
		if (ptr3) {	
			//Myitem1cppで設定読み込みをしたやつをこちらで読み込む
			auto Shitem = GetStage()->GetSharedGameObject<Myitem1>(L"Myitem1");
			Shitem->SetDrawActive(true);
			itemCount=1;
			/*drawPtr->SetMeshResource(L"SHIELD_TX");*/
			{
             //SetDrawActive(true);
			}
			
		}
		
	}

    //Bボタン
    void Player::OnPushX() {
	     auto Shitem = GetStage()->GetSharedGameObject<Myitem1>(L"Myitem1");
		 if (itemCount == 1) {
			 Shitem->SetDrawActive(false);
			 itemCount = 0;
		}

	}
	void Player::OnDestroy() {
		//BGMのストップ
		auto PtrXA = App::GetApp()->GetXAudio2Manager();
		PtrXA->Stop(m_BGM);
	}

}
	//end basecross

