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


		// プレイヤーの座標を取得する
		Vec3 playerPos(0.0f); // プレイヤーの座標（仮）
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
				break;
			}
		}

		//ngleY += XMConvertToRadians(90.0f) * -pad.fThumbRX * delta;

		auto eye = playerPos + Vec3(cosf(angleY), 0.0f, sinf(angleY)) * distance; // プレイヤーの座標を中心に、angleY分回り込む（プレイヤーからの距離はdistance）
		eye.y = 2.0f;

		SetEye(eye);
		SetAt(playerPos); // プレイヤーを中止するようにする

	}
	//--------------------------------------------------------------------------------------
//	オブジェクトカメラ（コンポーネントではない）
//--------------------------------------------------------------------------------------
//構築と破棄
	ObjCamera::ObjCamera() :
		Camera()
	{}
	ObjCamera::~ObjCamera() {}

	void ObjCamera::SetTargetObject(const shared_ptr<GameObject>& Obj) {
		m_TargetObject = Obj;
	}

	void ObjCamera::OnUpdate() {

		auto ptrTarget = m_TargetObject.lock();
		if (ptrTarget) {
			auto pos = ptrTarget->GetComponent<Transform>()->GetPosition();
			SetAt(pos);
		}


		//Camera::OnUpdate();
	}
}
//end basecross