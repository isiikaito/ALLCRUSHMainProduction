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
	void Wall::OnUpdate()
	{
		m_InputHandler.PushHandle(GetThis<Wall>());

		//auto ptrTrans = GetComponent<Transform>();
		//if (ptrTrans->GetPosition().y > m_ActiveMaxY) {
		//	float elapsedTime = App::GetApp()->GetElapsedTime();
		//	auto BeforePos = ptrTrans->GetBeforePosition();
		//	auto Pos = ptrTrans->GetPosition();
		//	Pos += m_Velocity * elapsedTime;
		//	ptrTrans->SetPosition(Pos);
		//	auto ptrColl = GetComponent<CollisionSphere>();
		//	auto ptrDraw = GetComponent<BcPNTStaticDraw>();
		//	if (ptrColl->IsSleep())
		//		ptrDraw->SetDiffuse(Col4(0.0f, 0.0f, 1.0f, 1.0f));
		//}
		//else {
		//	ptrDraw->SetDiffuse(Col4(1.0f, 1.0f,1.0f, 1.0));
		//	auto WallPtr = GetStage()->GetSharedGameObject<Wall>(L"Wall");
		//	Vec3 HitPoint;
		//	TRIANGLE tri;
		//	bool isModeHit = false;
		//	if (WallPtr->IsHitSegmentTriangles(BeforePos, Pos, Tri, HitPoint)) {
		//		isModeHit = true;
		//	}
		//}
	}

	bool Wall::IsHitSegmentTriangles(const Vec3& StartPos, const Vec3& EndPos, TRIANGLE& tri, Vec3& HitPoint) {
		SPHERE StartSp;
		StartSp.m_Center = StartPos;
		StartSp.m_Radius = 0.25f;
		SPHERE EndSp;
		EndSp.m_Center = EndPos;
		EndSp.m_Radius = 0.25f;
		SPHERE sp = HitTest::SphereEnclosingSphere(StartSp, EndSp);
		if (length(sp.m_Center - GetComponent<Transform>()->GetPosition()) >= 5.0f){
			return false;
		}
	}
	//コントローラの取得
	//auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();

	//Xボタンをおしたら
	void Wall::OnPushX()
	{
		//auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();

			SetUpdateActive(false);
			SetDrawActive(false);
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
