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
		//初期位置の設定
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_Scale);
		ptrTrans->SetRotation(m_Rotation);
		ptrTrans->SetPosition(m_Position);

		//モデルの見た目を決める
		// モデルとトランスフォームの間の差分行列
		Mat4x4 spanMat; 
		spanMat.affineTransformation(
			Vec3(0.045f, 1.0f, 0.13f),//大きさ
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),   //回転
			Vec3(0.0f, 0.0f, -0.05f)  //位置
		);

		//影をつける（シャドウマップを描画する）
		auto ptrShadow = AddComponent<Shadowmap>();

		//影の形（メッシュ）を設定
		ptrShadow->SetMeshResource(L"STAGEFLOOR_MESH");
		ptrShadow->SetMeshToTransformMatrix(spanMat);

		//描画コンポーネント
		auto ptrDraw = AddComponent<PNTStaticModelDraw>();

		//メッシュの設定
		ptrDraw->SetMeshResource(L"STAGEFLOOR_MESH");
		ptrDraw->SetMeshToTransformMatrix(spanMat);

		//RigidbodyBoxの追加
		PsBoxParam param(ptrTrans->GetWorldMatrix(), 0.0f, true, PsMotionType::MotionTypeFixed);
		auto PsPtr = AddComponent<RigidbodyBox>(param);

		//キューブ型の当たり判定の追加
		auto Coll = AddComponent<CollisionObb>();

		//ほかのオブジェクトの影響を受けない（例プレイヤーに当たったら消えるなどの処理）
		Coll->SetFixed(true);
	}

}