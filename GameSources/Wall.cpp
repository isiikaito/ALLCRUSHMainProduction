/*!
@file Wall.cpp
@brief ÉJÉxÇÃé¿ëÃ
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

		//âeÇÇ¬ÇØÇÈ
		auto ptrShadow = AddComponent<Shadowmap>();
		ptrShadow->SetMeshResource(L"DEFAULT_CUBE");

		auto ptrDraw = AddComponent<BcPNTStaticDraw>();
		ptrDraw->SetFogEnabled(true);
		ptrDraw->SetMeshResource(L"DEFAULT_CUBE");
		ptrDraw->SetOwnShadowActive(true);
		ptrDraw->SetTextureResource(L"SKY_TX");

		PsBoxParam param(ptrTrans->GetWorldMatrix(), 0.0f, true, PsMotionType::MotionTypeFixed);
		auto PsPtr = AddComponent<RigidbodyBox>(param);
		PsPtr->SetDrawActive(true);
		auto Coll = AddComponent<CollisionObb>();
		Coll->SetFixed(true);
		//if ()
		//{
			GetStage()->RemoveGameObject<Wall>(GetThis<Wall>());
		//}
		//if(Coll(true))
		//{

		//ObbÇÃè’ìÀîªíËÇÇ¬ÇØÇÈ
		auto ptrColl = AddComponent<CollisionObb>();
		/*auto Coll = AddComponent<CollisionObb>();
		Coll->SetFixed(true);*/
		//Coll->SetAfterCollision(AfterCollision::None);
		//}
	}
	//void Wall::OnCollisionEnter(shared_ptr<GameObject>& Other) {
	//	auto ptr = dynamic_pointer_cast<Player>(Other);
	//	if (ptr) {
	//		auto ptrTrans = ptr->GetComponent<Transform>();
	//		m_ActionVelocity = ptrTrans->GetVelocity();
	//		m_ActionVelocity.y = 5.0f;
	//		m_StateMachine->ChangeState(brakeWallState::Instance());
	//	}
	void Wall::OnCollisionEnter(shared_ptr<GameObject>& Other) {
		auto ptr = dynamic_pointer_cast<Player>(Other);
		if (ptr) {
			SetUpdateActive(false);
			SetDrawActive(false);
		}
		

	}
}
	//void brakeWallState::Enter(const shared_ptr<Wall>& Obj) {
	//}

//end basecross
