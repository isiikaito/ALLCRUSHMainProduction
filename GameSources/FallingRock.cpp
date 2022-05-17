/*!
@file FallingRock.cpp
@brief 落石実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//構築と破棄
	FallingRock::FallingRock(const shared_ptr<Stage>& StagePtr, const Vec3& Scale, const Vec3& Rotation, const Vec3& Position) :
		GameObject(StagePtr),
		m_Scale(Scale),
		m_Rotation(Rotation),
		m_Position(Position),
		m_Falling(0)
	{}


	//初期化
	void FallingRock::OnCreate() {
		//衝突判定エリアを決める
		//初期位置などの設定
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_Scale);
		ptrTrans->SetRotation(m_Rotation);
		ptrTrans->SetPosition(m_Position);



		//モデルの見た目を決める
		Mat4x4 spanMat; // モデルとトランスフォームの間の差分行列
		spanMat.affineTransformation(
			Vec3(0.2f, 0.3f, 0.3f),//スケール
			Vec3(0.0f, 5.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),//回転
			Vec3(0.0f, -0.5f, -0.7f)//ポジション
		);

		

		//影をつける（シャドウマップを描画する）
		auto ptrShadow = AddComponent<Shadowmap>();
		//影の形（メッシュ）を設定
		ptrShadow->SetMeshResource(L"IWA_MESH");
		ptrShadow->SetMeshToTransformMatrix(spanMat);

		
		auto ptrDraw = AddComponent<PNTStaticModelDraw>();

		ptrDraw->SetMeshResource(L"IWA_MESH");
		ptrDraw->SetMeshToTransformMatrix(spanMat);
		//RigidbodyBoxの追加
		/*PsBoxParam param(ptrTrans->GetWorldMatrix(), 0.0f, true, PsMotionType::MotionTypeFixed);
		auto PsPtr = AddComponent<RigidbodyBox>(param);*/
		////当たり判定を見せる
		//PsPtr->SetDrawActive(true);

		auto Coll = AddComponent<CollisionObb>();
		
		//衝突判定を表示
		Coll->SetDrawActive(true);
		//ほかのオブジェクトの影響を受けない（例プレイヤーに当たったら消えるなどの処理）
		Coll->SetFixed(true);
        
		//読み込みの設定をする
		GetStage()->SetSharedGameObject(L"FallingRock", GetThis<FallingRock>());
	}

	void FallingRock::OnUpdate()
	{
		if (m_Falling==1)
		{
			//重力をつける
			auto ptrGra = AddComponent<Gravity>();
		}

	}

	
		
}