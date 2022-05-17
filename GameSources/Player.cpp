/*!
@file Player.cpp
@brief プレイヤーなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
#pragma comment(lib, "Effekseer.lib")
#pragma comment(lib, "EffekseerRendererDX11.lib")

	//Player::Player(const shared_ptr<Stage>& StagePtr) :
	//	GameObject(StagePtr),
	//	MaxMoveSpeed(6.0f),
	//	moveStop(1.0f),	
	//	moveDir(0.0f, 0.0f, 0.0f),
	//	speed(0.0f),
	//	accel(0.0f),
	//	itemCount(0.0f),
	//	m_TotalTime(0.0f), m_isPlay(false), m_handle(0),
	//	m_manager(nullptr), m_renderer(nullptr), m_effect(nullptr)
	//{}

	void Player::CreateEffect() {
		auto d3D11Device = App::GetApp()->GetDeviceResources()->GetD3DDevice();
		auto d3D11DeviceContext = App::GetApp()->GetDeviceResources()->GetD3DDeviceContext();;
		// エフェクトのレンダラーの作成
		m_renderer = ::EffekseerRendererDX11::Renderer::Create(d3D11Device, d3D11DeviceContext, 8000);


		// エフェクトのマネージャーの作成
		m_manager = ::Effekseer::Manager::Create(8000);
		// 描画モジュールの設定
		m_manager->SetSpriteRenderer(m_renderer->CreateSpriteRenderer());
		m_manager->SetRibbonRenderer(m_renderer->CreateRibbonRenderer());
		m_manager->SetRingRenderer(m_renderer->CreateRingRenderer());
		m_manager->SetTrackRenderer(m_renderer->CreateTrackRenderer());
		m_manager->SetModelRenderer(m_renderer->CreateModelRenderer());

		// テクスチャ、モデル、カーブ、マテリアルローダーの設定する。
		// ユーザーが独自で拡張できる。現在はファイルから読み込んでいる。
		m_manager->SetTextureLoader(m_renderer->CreateTextureLoader());
		m_manager->SetModelLoader(m_renderer->CreateModelLoader());
		m_manager->SetMaterialLoader(m_renderer->CreateMaterialLoader());
		m_manager->SetCurveLoader(Effekseer::MakeRefPtr<Effekseer::CurveLoader>());

		// 視点位置を確定
		auto g_position = ::Effekseer::Vector3D(10.0f, 5.0f, 20.0f);

		// 投影行列を設定
		float w = (float)App::GetApp()->GetGameWidth();
		float h = (float)App::GetApp()->GetGameHeight();
		m_renderer->SetProjectionMatrix(::Effekseer::Matrix44().PerspectiveFovRH(
			90.0f / 180.0f * 3.14f, w / h, 1.0f, 500.0f));
		// カメラ行列を設定
		m_renderer->SetCameraMatrix(
			::Effekseer::Matrix44().LookAtRH(g_position, ::Effekseer::Vector3D(0.0f, 0.0f, 0.0f), ::Effekseer::Vector3D(0.0f, 1.0f, 0.0f)));

		wstring dataDir;
		App::GetApp()->GetDataDirectory(dataDir);
		dataDir += L"effect\\";
		//wstring wstrEfk = dataDir + L"Laser01.efk";
		wstring wstrEfk = dataDir + L"BrakeSmoke.efkefc";

		m_effect = ::Effekseer::Effect::Create(m_manager, (const char16_t*)wstrEfk.c_str());

	}

	void Player::OnCreate()
	{

		//初期位置などの設定
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(0.5f, 0.5f, 0.5f);
		ptrTrans->SetRotation(0.0f, 0.0f, 0.0f);
		ptrTrans->SetPosition(40.0f, 0.25f, 0.0f);
		itemCount = 0;


		//CollisionSphere衝突判定を付ける
		auto ptrColl = AddComponent<CollisionCapsule>();
		/*ptrColl->SetDrawActive(true);*/
		//衝突判定を表示
		ptrColl->SetDrawActive(true);
		Mat4x4 spanMat; // モデルとトランスフォームの間の差分行列
		spanMat.affineTransformation(
			Vec3(0.2f, 0.2f, 0.2f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, XM_PI * -0.5f, 0.0f),
			Vec3(0.0f, -1.0f, 0.0f)
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

		CreateEffect();

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
		position += moveDir * speed * delta * speed2; // デルタタイムを掛けて「秒間」の移動量に変換する



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
		SPHERE playerSp(position, 2.0f);
		auto group = GetStage()->GetSharedObjectGroup(L"Wall_Group");
		auto vec = group->GetGroupVector();
		if (action != L"ActionPull") {
			ptrDraw->ChangeCurrentAnimation(L"ActionPull");

			auto ptrXA = App::GetApp()->GetXAudio2Manager();
			ptrXA->Stop(m_BGM);//bgm(足音の停止)

			moveStop = 0.0f;//移動の停止

			for (auto& v : vec) {
				auto shPtr = v.lock();
				Vec3 ret;
				auto ptrWall = dynamic_pointer_cast<Wall>(shPtr);
				if (ptrWall) {
					auto WallObb = ptrWall->GetComponent<CollisionObb>()->GetObb();
					auto WallHP = ptrWall->GetHP();

					if (/*近づいたら*/
						HitTest::SPHERE_OBB(playerSp, WallObb, ret)) {
						//壁との距離が2.0以下になった
						auto ctrlVec = App::GetApp()->GetInputDevice().GetControlerVec();
						if (ctrlVec[0].wButtons & XINPUT_GAMEPAD_A) {
							//while (WallHP >= 1) {
								//コントローラーのボタンが押されていたら、耐久値を１減らす
							if (WallHP > 1) {
								int a = 1;
							}
						}

						//GetStage()->RemoveGameObject<Wall>(shPtr);
						if (!m_isPlay) {
							//auto pos = ptr->GetComponent<Transform>()->GetWorldPosition();
							m_handle = m_manager->Play(m_effect, 0, 0, 0);
							m_isPlay = true;
						}
						WallHP--;
						////サウンドの再生
						//ptrXA->Start(L"AttackWall", 0, 0.5f);
						ptrWall->SetHP(WallHP);
					}
					if (WallHP <= 0)
					{
						auto ptrXA = App::GetApp()->GetXAudio2Manager();
						GetStage()->RemoveGameObject<Wall>(shPtr);
						//サウンドの再生
						ptrXA->Start(L"BrakeWall", 0, 0.5f);
					}
				}

			}
		}

		//障害物１の破壊

		auto group1 = GetStage()->GetSharedObjectGroup(L"Obstacle1_Group1");
		auto vec1 = group1->GetGroupVector();
		for (auto& v1 : vec1) {
			auto shPtr1 = v1.lock();
			Vec3 ret1;
			auto ptrObstacle1 = dynamic_pointer_cast<Obstacle1>(shPtr1);

			if (ptrObstacle1) {
				auto Obstacle1Obb = ptrObstacle1->GetComponent<CollisionObb>()->GetObb();
				if (/*近づいたら*/
					HitTest::SPHERE_OBB(playerSp, Obstacle1Obb, ret1)) {
					//壁との距離が2.0以下になった
					auto ctrlVec1 = App::GetApp()->GetInputDevice().GetControlerVec();
					if (ctrlVec1[0].wButtons & XINPUT_GAMEPAD_A) {
						//コントローラのボタンが押されていたら、shPtrを消す
						GetStage()->RemoveGameObject<Obstacle1>(shPtr1);
						auto Shitem = GetStage()->GetSharedGameObject<Myitem1>(L"Myitem1");
						Shitem->SetDrawActive(true);
						itemCount = 1;
					}

				}
			}
		}
		//柱
		auto group2 = GetStage()->GetSharedObjectGroup(L"Pillar_Group1");
		auto vec2 = group2->GetGroupVector();
		for (auto& v2 : vec2) {
			auto shPtr2 = v2.lock();
			Vec3 ret2;
			auto ptrPillar = dynamic_pointer_cast<Pillar>(shPtr2);

			auto ptrFallingRock = GetStage()->GetSharedGameObject<FallingRock>(L"FallingRock");
			if (ptrPillar) {
				auto PillarObb = ptrPillar->GetComponent<CollisionObb>()->GetObb();
				auto Falling1 = ptrFallingRock->GetFalling();
				if (/*近づいたら*/
					HitTest::SPHERE_OBB(playerSp, PillarObb, ret2)) {
					//壁との距離が2.0以下になった
					auto ctrlVec1 = App::GetApp()->GetInputDevice().GetControlerVec();
					if (ctrlVec1[0].wButtons & XINPUT_GAMEPAD_A) {
						//コントローラのボタンが押されていたら、shPtrを消す
						GetStage()->RemoveGameObject<Pillar>(shPtr2);
						//落石の処理
						Falling1 = 1;
						ptrFallingRock->SetFalling(Falling1);

					}

				}
			}
		}
	}
	void Player::OnDraw() {
		GameObject::OnDraw();
		if (m_isPlay) {
			auto elps = App::GetApp()->GetElapsedTime();
			m_TotalTime += elps;
			if (m_TotalTime >= 2.0f) {
				m_manager->StopEffect(m_handle);
				m_TotalTime = 0.0f;
				m_isPlay = false;
				return;
			}
			else {
				// マネージャーの更新
				m_manager->Update();
				// 時間を更新する
				m_renderer->SetTime(elps);
				// エフェクトの描画開始処理を行う。
				m_renderer->BeginRendering();
				// エフェクトの描画を行う。
				m_manager->Draw();
				// エフェクトの描画終了処理を行う。
				m_renderer->EndRendering();
			}

		}
	}


	//プレイヤーがゴールにたどり着いたら
	void Player::OnAttack() {
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
				ptrXA->Start(L"Hammer", 0, 0.f);
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

		

	}

	//Bボタン
	void Player::OnPushX() {
		auto Shitem = GetStage()->GetSharedGameObject<Myitem1>(L"Myitem1");
		if (itemCount == 1) {
			Shitem->SetDrawActive(false);
			speed2 = 2;
			itemCount = 0;

		}
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
	
	void Player::OnDestroy() {
		//BGMのストップ
		auto PtrXA = App::GetApp()->GetXAudio2Manager();
		PtrXA->Stop(m_BGM);
	}
}
	//end basecross

