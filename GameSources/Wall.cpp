/*!
@file Wall.cpp
@brief カベの実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	Wall::Wall(const shared_ptr<Stage>& StagePtr,
		const Vec3& Scale,
		const Vec3& Rotation,
		const Vec3& Position,
		const int HP

	) :
		GameObject(StagePtr),
		m_Scale(Scale),
		m_Rotation(Rotation),
		m_Position(Position),
		m_HP(HP)
	{}


	void Wall::OnCreate() {
		
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_Scale);
		ptrTrans->SetRotation(m_Rotation);
		ptrTrans->SetPosition(m_Position);

		Mat4x4 spanMat; // モデルとトランスフォームの間の差分行列
		spanMat.affineTransformation(
			Vec3(0.2f, 0.1f, 0.06f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, XM_PI * -0.5f, 0.0f),
			Vec3(0.0f, -0.5f, 0.0f)
		);

		
		//オブジェクトのグループを得る
		auto group = GetStage()->GetSharedObjectGroup(L"Wall_Group");
		//グループに自分自身を追加
		group->IntoGroup(GetThis<Wall>());

		//影をつける
		auto ptrShadow = AddComponent<Shadowmap>();
		ptrShadow->SetMeshResource(L"UNBREAKWALL_MESH");
		//影をつける（シャドウマップを描画する）
		ptrShadow->SetMeshToTransformMatrix(spanMat);

		auto WallHP = GetHP();
		auto ptrDraw1 = AddComponent<PNTStaticModelDraw>();
		if (WallHP >= 4)
		{
			ptrDraw1->SetMeshResource(L"UNBREAKWALL_MESH");
		}
		//壁の残り耐久値についての処理
		if (WallHP >= 4)
		{
			ptrDraw1->SetMeshResource(L"UNBREAKWALL_MESH");
		}
		else if (WallHP >= 3)
		{
			ptrDraw1->SetMeshResource(L"DAMAGEWALL1_MESH");
		}
		else if (WallHP >= 2)
		{
			ptrDraw1->SetMeshResource(L"DAMAGEWALL2_MESH");
		}
		else if (WallHP >= 1)
		{
			ptrDraw1->SetMeshResource(L"DAMAGEWALL3_MESH");
		}

		ptrDraw1->SetMeshToTransformMatrix(spanMat);
		//auto ptrDraw = AddComponent<BcPNTStaticDraw>();
		/*ptrDraw->SetFogEnabled(false);
		ptrDraw->SetOwnShadowActive(true);*/

		//auto ptrDraw2 = AddComponent<BcPNTStaticDraw>();
		//ptrDraw2->SetFogEnabled(true);
		//ptrDraw2->SetMeshResource(L"DEFAULT_CUBE");
		//ptrDraw2->SetOwnShadowActive(true);
		//ptrDraw2->SetTextureResource(L"WALL_TX");
		//PsBoxParam param(ptrTrans->GetWorldMatrix(), 0.0f, true, PsMotionType::MotionTypeFixed);
		//auto PsPtr = AddComponent<RigidbodyBox>(param);
		//PsPtr->SetDrawActive(false);

		//Obbの衝突判定をつける
		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetDrawActive(true);
		//auto obb = ptrColl->GetObb();
		//GetStage()->SetSharedGameObject(L"Wall_Group",GetThis<Wall>());
				//読み込みの設定をする
		//GetStage()->SetSharedGameObject(L"BREAKWALL", GetThis<Wall>());
			//ほかのオブジェクトの影響を受けない（例プレイヤーに当たったら消えるなどの処理）
		ptrColl->SetFixed(true);
	}
	void Wall::OnUpdate()
	{
		m_InputHandler.PushHandle(GetThis<Wall>());

		//コントローラの取得
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();

		//Bボタンが押されているとき
		if (cntlVec[0].wButtons & XINPUT_GAMEPAD_B) {
			//表示
			SetDrawActive(false);
		}
		//Bボタンが押されていないとき
		else {
			SetDrawActive(true);
		}
	}


	void  Wall::OnPushB() {
	}

	//Xボタンをおしたら
	void Wall::OnPushX()
	{
		
	}

	//壁に当たったら
	void Wall::OnCollisionEnter(shared_ptr<GameObject>& Other) {
				}
			
}
//end basecross
