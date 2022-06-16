/*!
@file Player.cpp
@brief プレイヤーなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
//#pragma comment(lib, "Effekseer.lib")
//#pragma comment(lib, "EffekseerRendererDX11.lib")


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
		ptrDraw->AddAnimation(L"ActionPush", 60, 10, false, 35.0f);
		ptrDraw->AddAnimation(L"ActionEnd", 70, 5, false, 35.0f);
		ptrDraw->AddAnimation(L"GameOver", 75, 24, false, 15.0f);
		//ptrDraw->AddAnimation(L"GameOverFirst", 70, 10, false, 15.0f);
		//ptrDraw->AddAnimation(L"GameOverLast", 80, 14, false, 10.0f);
		ptrDraw->ChangeCurrentAnimation(L"Default");

		//CreateEffect();
		//CreateEffect1();

	}

	void Player::OnUpdate()
	{
		auto ptrGameStage = dynamic_pointer_cast<GameStage>(GetStage());
		float elapsedTime = App::GetApp()->GetElapsedTime();
		if (elapsedTime)
		{
			m_opningStop += elapsedTime;
			if (m_opningStop >= XM_PI) {
				m_opningStop = 0;
			}
			if (ptrGameStage->GetCameraSelect() == CameraSelect::openingCamera) {
				return;
			}
			if (m_opningStop == 1)
			{
				moveStop = true;
			}
		}
		//アニメーション
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
		float rad = XM_PI * 0.5f;
		// ゲームコントローラーオブジェクトを取得する
		auto& device = app->GetInputDevice();
		const auto& pad = device.GetControlerVec()[0]; // ゼロ番目のコントローラーを取得する
		moveDir = Vec3(pad.fThumbLX, 0.0f, pad.fThumbLY); // 大きさが 0.0f ～ 1.0f;
		auto m = Mat3x3( // Y軸中心で回転させる行列
			Vec3( cosf(rad), 0.0f, sinf(rad)),   // X軸の向き
			Vec3(      0.0f, 0.0f,      0.0f),   // Y軸の向き
			Vec3(-sinf(rad), 0.0f,  cosf(rad))); // Z軸の向き
		moveDir = moveDir * m; // スティックの入力をangleYラジアン回転させる
		speed = MaxMoveSpeed * moveDir.length() * moveStop; // 最大速×スティックベクトルの大きさ×停止させるかどうかの判定
		moveDir.normalize(); // 移動方向を正規化する
		auto transComp = GetComponent<Transform>();
		auto position = transComp->GetPosition(); // 現在の位置座標を取得する
		auto rotation = transComp->GetRotation();
		auto scale = transComp->GetScale();
		// プレイヤーの移動
		position += moveDir * speed * delta * speed2; // デルタタイムを掛けて「秒間」の移動量に変換する
		//ボスの座標取得
		auto ptrEnemy = GetStage()->GetSharedGameObject<EnemyObject>(L"EnemyObject");
		//クラスには（）が必要である引数があるときと無い時どっちでも必要
		auto EnemyPositon = ptrEnemy->GetComponent<Transform>()->GetPosition();

		//ボスとプレイヤーが一定の距離に達したら
		PBdistance = position.x - EnemyPositon.x;
		if (PBdistance >= -5)
		{
			position.z = EndPos;
			transComp->SetRotation(EndAngle, 0.0f, EndAngle);
			
			if (move != L"GameOver") {
				ptrDraw->ChangeCurrentAnimation(L"GameOver");
				GameOver = 1;
				moveStop = false;
			}
		}
		//柱が壊れていないとき
		if (PillarCount == 0)
		{
			//柱の座標取得
			auto ptrPillar = GetStage()->GetSharedGameObject<Pillar>(L"Pillar");
			//クラスには（）が必要である引数があるときと無い時どっちでも必要
			auto PillarPositon = ptrPillar->GetComponent<Transform>()->GetPosition();
			//柱とプレイヤーの距離
			PPdistance = position.x - PillarPositon.x;
			if (PPdistance <= 5)
			{
				moveStop = 0.0f;//移動の停止
				position.x = -80;
				position.z = 1;
				transComp->SetRotation(XM_PI, 0.0f, XM_PI);//プレイヤーの向きを前方に固定
				speed = 0;
				m_Event = true;
				m_Event = true;
			}
		}
		if (itemCount == 2)
		{
			float elapsedTime1 = App::GetApp()->GetElapsedTime();
			itemtime += elapsedTime1;
			if (itemtime >= 4)
			{
				speed2 = 1;
			}
		}
		
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
				moveStop = true;//移動停止解除
			}
		}
		//コントローラチェックして入力があればコマンド呼び出し
		m_InputHandler.PushHandle(GetThis<Player>());
		//MovePlayer();
		m_InputHandler2.PushHandle(GetThis<Player>());
		if (ptrGameStage->GetCameraSelect() == CameraSelect::openingCamera) {
			return;
		}
		//コントローラチェックして入力があればコマンド呼び出し
		m_InputHandler.PushHandle(GetThis<Player>());
		//moveStop = false;
	}
	

	//Aボタン
	void Player::OnPushA() 
	{
		//ハンマーを振るアニメーション
		auto ptrDraw = GetComponent<BcPNTnTBoneModelDraw>();
		auto action = ptrDraw->GetCurrentAnimation();

		if (action != L"ActionPull") {
			ptrDraw->ChangeCurrentAnimation(L"ActionPull");

			auto ptrXA = App::GetApp()->GetXAudio2Manager();
			ptrXA->Stop(m_BGM);//bgm(足音の停止)

			moveStop = false;//移動の停止
		}
	}

	//プレイヤーがゴールにたどり着いたら
	void Player::OnAttack() 
	{
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
				ptrXA->Start(L"Hammer", 0, 0.0f);

				moveStop = false;//移動の停止
			}
		}
		else {
			if (now) {
				ptrDraw->ChangeCurrentAnimation(L"Default");
				auto ptrXA = App::GetApp()->GetXAudio2Manager();
				ptrXA->Stop(m_BGM);

				moveStop = true;//移動停止解除
			}
		}
	}

	//プレイヤーがゴールにたどり着いたら
	void Player::OnUpdate2() {

		float elapsedTime = App::GetApp()->GetElapsedTime();
		//コントローラチェックして入力があればコマンド呼び出し
		m_InputHandler.PushHandle(GetThis<Player>());
		//moveStop = false;
		auto ptrXA = App::GetApp()->GetXAudio2Manager();
		auto ptrTrans = GetComponent<Transform>();
		Vec3 pos = ptrTrans->GetPosition();
		if (pos.x < -52.0f) {
			auto ptrStage1 = GetStage()->GetSharedGameObject<Telop>(L"Telop");
			ptrStage1->SetDrawActive(true);
			// 時間の変数に足す
			m_TelopTime += elapsedTime;
			if (m_TelopTime >= 2.0f)
			{
				// 1秒後に表示がオフになる
				ptrStage1->SetDrawActive(false);

			}
		}

		// 出口テロップ
		if (pos.x < -83.0f) {
			auto ptrStage3 = GetStage()->GetSharedGameObject<Telop3>(L"Telop3");
			ptrStage3->SetDrawActive(true);
			// 時間の変数に足す
			m_Telop3Time += elapsedTime;
			if (m_Telop3Time >= 2.0f)
			{
				// 1秒後に表示がオフになる
				ptrStage3->SetDrawActive(false);

			}
		}

		// 壁を壊せ！！テロップ
		if (pos.x < 22.0f) {
			auto ptrStage4 = GetStage()->GetSharedGameObject<Telop4>(L"Telop4");
			ptrStage4->SetDrawActive(true);
			// 時間の変数に足す
			m_Telop4Time += elapsedTime;
			if (m_Telop4Time >= 2.0f)
			{
				// 1秒後に表示がオフになる
				ptrStage4->SetDrawActive(false);

			}
		}
		//ゲームオーバーテロップ
		auto ptrDraw = GetComponent<BcPNTnTBoneModelDraw>();
		//float elapsedTime = App::GetApp()->GetElapsedTime();
		auto now = ptrDraw->UpdateAnimation(elapsedTime);
		auto action = ptrDraw->GetCurrentAnimation();

		if (action == L"ActionPull") {
			if (ptrDraw->IsTargetAnimeEnd()) {
				//ActionPullのときこのif文に入ったら、ChangeCurrentAnimationをActionPuhにする
				ptrDraw->ChangeCurrentAnimation(L"ActionPush");
				auto transComp = GetComponent<Transform>();
				auto position = transComp->GetPosition(); // 現在の位置座標を取得する
				SPHERE playerSp(position, 2.0f);
				auto group = GetStage()->GetSharedObjectGroup(L"Wall_Group");
				auto vec = group->GetGroupVector();
				ptrXA->Start(L"Hammer", 0, 0.5f);
				moveStop = 1.0f;//移動停止解除

				//壁の破壊処理
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
							//パワーアップ時の処理
							switch (Power)
							{
							case 0:
								WallHP -= 10;
								Power = 1;
								PowerCount = 0;
								Gageflash = 1;
								break;
								//パワーアップ前の処理
							case 1:
								WallHP -= 1;
								break;
							}
							ptrWall->SetHP(WallHP);
							if (WallHP <= 0)
							{
								ptrXA->Start(L"BrakeWall", 0, 0.5f);
								GetStage()->RemoveGameObject<Wall>(shPtr);
								PowerCount += 1;
								if (PowerCount >= 3)
								{
									PowerCount = 3;
								}
							}

							auto elps = App::GetApp()->GetElapsedTime();
							SoundTime += elps;
							if (WallHP >= 1)
							{
								auto AttackSound = App::GetApp()->GetXAudio2Manager();
								AttackSound->Start(L"AttackWall", 0, 0.5f);
								return;
							}

							if (WallHP <= 0)
							{
								auto PtrSpark = GetStage()->GetSharedGameObject<ImpactSmoke>(L"MultiSpark", false);
								if (PtrSpark) {
									auto pos = GetComponent<Transform>()->GetPosition();
									PtrSpark->InsertSpark(pos);
									PtrSpark->InsertSpark1(pos);
								}
								auto BrakeSound = App::GetApp()->GetXAudio2Manager();
								GetStage()->RemoveGameObject<Wall>(shPtr);
								//サウンドの再生
								BrakeSound->Start(L"BrakeWall", 0, 0.5f);
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
								//コントローラのボタンが押されていたら、shPtrを消す
							GetStage()->RemoveGameObject<Obstacle1>(shPtr1);
							auto Shitem = GetStage()->GetSharedGameObject<Myitem1>(L"Myitem1");
							Shitem->SetDrawActive(true);
							auto XSprite1 = GetStage()->GetSharedGameObject<XSprite>(L"XSprite");
							XSprite1->SetDrawActive(true);
							itemCount = 1;
						}
					}
				}
				//柱破壊処理
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
							GetStage()->RemoveGameObject<Pillar>(shPtr2);
							//落石の処理
							Falling1 = 1;
							ptrFallingRock->SetFalling(Falling1);
							PillarCount = 1;

						}
					}
				}
				return;
			}
		}
		//攻撃処理
		else if (action == L"ActionPull") {
			if (ptrDraw->IsTargetAnimeEnd()) {
				//ActionPushのときこのif文に入ったら、ChangeCurrentAnimationをActionPuhにする
				ptrDraw->ChangeCurrentAnimation(L"Default");
				auto ptrXA = App::GetApp()->GetXAudio2Manager();
				//サウンドの再生
				ptrXA->Start(L"Hammer", 0, 0.5f);
				moveStop = true;//移動停止解除
			}
		}
		else {
			if (now) {
				ptrDraw->ChangeCurrentAnimation(L"Default");
				ptrXA->Stop(m_BGM);

				moveStop = true;//移動停止解除
			}
		}

		if (action == L"GameOver") {
			if (now) {
				//PostEvent(0.0f, GetThis<Player>(), App::GetApp()->GetScene<Scene>(), L"ToGameOverStage");
			}
		}
		////文字列の表示
		//DrawStrings();
	}
	//プレイヤーがEnemyに当たったら
	void Player::OnCollisionEnter(shared_ptr<GameObject>& Other) {
      auto ptr = dynamic_pointer_cast<EnemyObject>(Other);
		if (ptr) {
			if (m_State == GameState::Game)
			{
				m_State = GameState::Down;
			}
		}
		auto ptr1 = dynamic_pointer_cast<ExitWall>(Other);
		if (ptr1) {
			if (ExitCount == 0)
			{
                ExitCount = 1;
			 }	
		}
	}
	void Player::OnPushY() {
		auto PtrSpark = GetStage()->GetSharedGameObject<ImpactSmoke>(L"MultiSpark", false);
		auto PowerUpSound = App::GetApp()->GetXAudio2Manager();
		//ゲージが溜まったら
		if (PowerCount >= 3)
		{
			auto pos = GetComponent<Transform>()->GetPosition();
			PowerUpSound->Start(L"PowerUp", 0, 0.5f);
			Power = 0;
			PtrSpark->InsertSpark4(pos);
		}
	}

	//Xボタン
	void Player::OnPushX() {
		auto Shitem = GetStage()->GetSharedGameObject<Myitem1>(L"Myitem1");
		auto PlayerPos = GetComponent<Transform>()->GetPosition();
		auto SpeedUpSound = App::GetApp()->GetXAudio2Manager();

		if (itemCount == 1) {
			speed2 = 2;
			itemCount = 2;

			auto XSprite1 = GetStage()->GetSharedGameObject<XSprite>(L"XSprite");
			XSprite1->SetDrawActive(false);

			Shitem->SetDrawActive(false);
			//サウンドの再生
			SpeedUpSound->Start(L"SpeedUp", 0, 0.5f);

			auto PtrSpark = GetStage()->GetSharedGameObject<ImpactSmoke>(L"MultiSpark", false);
			if (PtrSpark) {
				auto pos = GetComponent<Transform>()->GetPosition();
				PtrSpark->InsertSpark2(pos);
			}
		}
		if (GetGameState() == GameState::ChangeStage) {
			PostEvent(0.0f, GetThis<Player>(), App::GetApp()->GetScene<Scene>(), L"ToTitleStage");
		}
	}

	//文字列の表示
	void Player::DrawStrings() {
		auto pos = GetComponent<Transform>()->GetPosition();

		wstring positionStr(L"Position:\t");
		positionStr += L"X=" + Util::FloatToWStr(pos.x, 6, Util::FloatModify::Fixed) + L",\t";
		positionStr += L"Y=" + Util::FloatToWStr(pos.y, 6, Util::FloatModify::Fixed) + L",\t";
		positionStr += L"Z=" + Util::FloatToWStr(pos.z, 6, Util::FloatModify::Fixed) + L"\n";

		wstring str = positionStr;

		////文字列コンポーネントの取得
		//auto ptrString = GetComponent<StringSprite>();
		//ptrString->SetText(str);

	}

	void Player::OnDestroy() {
		//BGMのストップ
		auto PtrXA = App::GetApp()->GetXAudio2Manager();
		PtrXA->Stop(m_BGM);
	}
}
	//end basecross