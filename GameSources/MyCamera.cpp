#include "stdafx.h"
#include "Project.h"

namespace basecross {

	shared_ptr<GameObject> MyCamera::GetTargetObject() const {
		if (!m_TargetObject.expired()) {
			return m_TargetObject.lock();
		}
		return nullptr;
	}

	void MyCamera::SetTargetObject(const shared_ptr<GameObject>&Obj) {
			m_TargetObject = Obj;
		}

	// カメラ
	void MyCamera::OnUpdate()
	{
		auto& app = App::GetApp();

		float delta = app->GetElapsedTime();

		auto& device = app->GetInputDevice();
		const auto& pad = device.GetControlerVec()[0];

		//auto rotate = GetCameraObject()->GetComponent<Transform>()->GetRotation();


		// プレイヤーの座標を取得する
		Vec3 playerPos(0.0f); // プレイヤーの座標（仮）
		Vec3 pillarPos(0.0f);
		int PillarCount(0);
		auto stage = app->GetScene<Scene>()->GetActiveStage(); // ステージオブジェクトを取得する
		auto objs = stage->GetGameObjectVec(); // ステージに追加されているすべてのオブジェクト
		for (auto& obj : objs)
		{
			// プレイヤーへのキャストを試みる
			auto player = dynamic_pointer_cast<Player>(obj);
			if (player)
			{
				// キャストに成功していたら座標を取得する
				auto playerTrans = player->GetComponent<Transform>();
				playerPos = playerTrans->GetPosition();
				PillarCount = player->GetPillarCount();
				player->SetPillarCount(PillarCount);
				break;
			}

			// プレイヤーへのキャストを試みる
			auto pillar = dynamic_pointer_cast<Pillar>(obj);
			if (pillar)
			{
				// キャストに成功していたら座標を取得する
				auto pillarTrans = pillar->GetComponent<Transform>();
				pillarPos = pillarTrans->GetPosition();
				break;
			}
		}
	
		

		//auto group = GetStage()->GetSharedGameObject();


		//カメラのスティック操作
		angleY += XMConvertToRadians(90.0f) * -pad.fThumbRX * delta;
		if (angleY < -XM_PIDIV4 * 3) {
			angleY = -XM_PIDIV4 * 3;//カメラの右回転の限界回転度
		}
		if (angleY > +XM_PIDIV4 * 3) {
			angleY = +XM_PIDIV4 * 3;//カメラの左回転の限界回転度
		}

		auto eye = playerPos + Vec3(cosf(angleY), 0.0f, sinf(angleY)) * distance; // プレイヤーの座標を中心に、angleY分回り込む（プレイヤーからの距離はdistance）
		eye.y = 2.0f;
		playerPos.y = 0.5f;

		SetEye(eye);
		SetAt(playerPos); // プレイヤーを中止するようにする
		//コントローラの取得
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();

		//auto rot = GetRot;

		//Bボタン
		if (cntlVec[0].wButtons & XINPUT_GAMEPAD_B) {

			auto CameraAngleY = XM_PI;

			auto eye = playerPos + Vec3(cosf(CameraAngleY), 0.0f, sinf(0.0f)) * distance;
			eye.y = 2.0f;
			SetEye(eye);
		}
		//プレイヤーと柱の位置が一定の距離になったら振り返る
		PPdistance = playerPos.x - pillarPos.x;
		if (PillarCount == 0)
		{
         if (PPdistance < -75)
		  {
			auto CameraAngleY = XM_PI;

			auto eye = playerPos + Vec3(cosf(CameraAngleY), 0.0f, sinf(0.0f)) * distance;
			eye.y = 2.0f;
			SetEye(eye);
		  }
		}
		

	}
}
//end basecross