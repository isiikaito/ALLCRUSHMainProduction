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
			Vec3(0.09f, 0.095f, 0.3f),  //スケールkabe
			Vec3(0.0f, 5.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),     //回転
			Vec3(-0.1f, -0.7f, 0.3f)    //ポジション
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

		
		auto ptrDraw = AddComponent<PNTStaticModelDraw>();
		ptrDraw->SetMeshResource(L"UNBREAKWALL_MESH");
		ptrDraw->SetMeshToTransformMatrix(spanMat);
		
		//Obbの衝突判定をつける
		auto ptrColl = AddComponent<CollisionObb>();
		
	
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
		
		
		
		auto WallHP = GetHP();
		auto ptrDraw = GetComponent<PNTStaticModelDraw>();
		
		//壁の残り耐久値についての処理
		if (WallHP >= 4)
		{
			ptrDraw->SetMeshResource(L"UNBREAKWALL_MESH");

		}
		else if (WallHP >= 3)
		{
			Mat4x4 spanMat; // モデルとトランスフォームの間の差分行列
			spanMat.affineTransformation(
				Vec3(1.0f, 0.3f, 0.1f),//Scale
				Vec3(0.0f, 5.0f, 0.0f),//Position
				Vec3(0.0f, 0.0f, 0.0f),//回転
				Vec3(-0.5f, -0.6f, 0.0f)//Position
			);
			ptrDraw->SetMeshResource(L"DAMAGEWALL2_MESH");
			ptrDraw->SetMeshToTransformMatrix(spanMat);
			
		}
		else if (WallHP <= 1)
		{
		
			Mat4x4 spanMat; // モデルとトランスフォームの間の差分行列
			spanMat.affineTransformation(
				Vec3(1.0f, 0.1f, 0.1f),//Scale
				Vec3(0.0f, 5.0f, 0.0f),//Position
				Vec3(0.0f,0.0f, 0.0f),//回転
				Vec3(1.0f, -0.6f, 0.0f)//Position
			);
			ptrDraw->SetMeshResource(L"DAMAGEWALL1_MESH");
			ptrDraw->SetMeshToTransformMatrix(spanMat);
		}
		else if (WallHP >= 1)
		{
			Mat4x4 spanMat; // モデルとトランスフォームの間の差分行列
			spanMat.affineTransformation(
				Vec3(1.0f, 0.1f, 0.1f),//Scale
				Vec3(0.0f, 5.0f, 0.0f),//Position
				Vec3(0.0f, 0.0f, 0.0f),//回転
				Vec3(-0.2f, -0.6f, 0.0f)//Position
			);
			ptrDraw->SetMeshResource(L"DAMAGEWALL3_MESH");
		
			ptrDraw->SetMeshToTransformMatrix(spanMat);
			
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
