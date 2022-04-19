/*!
@file StageFloor.cpp
@briefステージの床実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//構築と破棄
	StageFloor::StageFloor(const shared_ptr<Stage>& StagePtr, const Vec3& Scale, const Vec3& Rotation, const Vec3& Position) :
		GameObject(StagePtr),
		m_Scale(Scale),
		m_Rotation(Rotation),
		m_Position(Position)
	{}


	//初期化
	void StageFloor::OnCreate() {
		//衝突判定エリアを決める
		//初期位置などの設定
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_Scale);
		ptrTrans->SetRotation(m_Rotation);
		ptrTrans->SetPosition(m_Position);

		//モデルと衝突判定を合わせなければならない

		//モデルの見た目を決める
		Mat4x4 spanMat; // モデルとトランスフォームの間の差分行列
		spanMat.affineTransformation(
			Vec3(0.045f, 1.0f, 0.13f),//スケールyuka
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),//回転
			Vec3(0.0f, 0.0f, -0.05f)//ポジションyuka
		);

		//影をつける（シャドウマップを描画する）
		auto ptrShadow = AddComponent<Shadowmap>();
		//影の形（メッシュ）を設定
		ptrShadow->SetMeshResource(L"STAGEFLOOR_MESH");
		ptrShadow->SetMeshToTransformMatrix(spanMat);

		auto ptrDraw = AddComponent<PNTStaticModelDraw>();

		ptrDraw->SetMeshResource(L"STAGEFLOOR_MESH");
		ptrDraw->SetMeshToTransformMatrix(spanMat);
		//RigidbodyBoxの追加
		PsBoxParam param(ptrTrans->GetWorldMatrix(), 0.0f, true, PsMotionType::MotionTypeFixed);
		auto PsPtr = AddComponent<RigidbodyBox>(param);
		//当たり判定を見せる
		/*PsPtr->SetDrawActive(true);*/

		auto Coll = AddComponent<CollisionObb>();

		Coll->SetFixed(true);


	}

}