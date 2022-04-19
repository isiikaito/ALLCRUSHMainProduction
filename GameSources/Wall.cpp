/*!
@file Wall.cpp
@brief カベの実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	Wall::Wall(const shared_ptr<Stage>& StagePtr,
		const Vec3& Scale,
		const Quat& Qt,
		const Vec3& Position
	) :
		GameObject(StagePtr),
		m_Scale(Scale),
		m_Qt(Qt),
		m_Position(Position)
	{}

	void Wall::OnCreate() {
		auto ptrTrans = GetComponent<Transform>();

		ptrTrans->SetScale(m_Scale);
		ptrTrans->SetQuaternion(m_Qt);
		ptrTrans->SetPosition(m_Position);

		//影をつける
		auto ptrShadow = AddComponent<Shadowmap>();
		ptrShadow->SetMeshResource(L"DEFAULT_CUBE");

		auto ptrDraw = AddComponent<BcPNTStaticDraw>();
		ptrDraw->SetFogEnabled(true);
		ptrDraw->SetMeshResource(L"DEFAULT_CUBE");
		ptrDraw->SetOwnShadowActive(true);
		ptrDraw->SetTextureResource(L"WALL_TX");

		PsBoxParam param(ptrTrans->GetWorldMatrix(), 0.0f, true, PsMotionType::MotionTypeFixed);
		auto PsPtr = AddComponent<RigidbodyBox>(param);
		PsPtr->SetDrawActive(true);
		
		//Obbの衝突判定をつける
		auto ptrColl = AddComponent<CollisionObb>();
		
	}
	//コントローラの取得
	auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();

	//Xボタンをおしたら
	void Wall::OnPushX(shared_ptr<GameObject>& Other)
	{
		//if (cntlVec[0].wButtons & XINPUT_GAMEPAD_X) {
		//	SetUpdateActive(false);
		//	SetDrawActive(false);
		//}
	}
	//壁に当たったら
	void Wall::OnCollisionEnter(shared_ptr<GameObject>& Other) {
		auto ptr = dynamic_pointer_cast<Player>(Other);
			if (ptr) {
				SetUpdateActive(false);
				SetDrawActive(false);
				auto ptrDraw = AddComponent<BcPNTStaticDraw>();
				ptrDraw->SetTextureResource(L"DAMAGEWALL_TX");
		}
	}
}
	
//end basecross
