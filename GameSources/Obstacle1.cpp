/**
*@file Obstacle1.cpp
*@brief 障害物オブジェクトが実装されているソースファイル
*@author Kaito Isii
*@details 障害物オブジェクトの実装
*/
#include "stdafx.h"
#include "Project.h"

/** basecross共通のネームスペース */
namespace basecross {
	//!パラメータの初期化
	Obstacle1::Obstacle1(const shared_ptr<Stage>& StagePtr, const Vec3& Scale, const Vec3& Rotation, const Vec3& Position) :
		GameObject(StagePtr),
		m_Scale(Scale),
		m_Rotation(Rotation),
		m_Position(Position)
	{}


	
	void Obstacle1::OnCreate() {
		//!初期位置などの設定

		//!衝突判定の設定
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_Scale);
		ptrTrans->SetRotation(m_Rotation);
		ptrTrans->SetPosition(m_Position);

		//!モデルとトランスフォームの間の差分行列
		Mat4x4 spanMat; 
		spanMat.affineTransformation(
			Vec3(0.5f, 0.5f, 0.5f),  //!大きさ
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),  //!回転
			Vec3(-0.4f, -0.5f, -0.6f)//!位置
		);
		
		
		auto group1 = GetStage()->GetSharedObjectGroup(L"Obstacle1_Group1");//!オブジェクトのグループを得る
		group1->IntoGroup(GetThis<Obstacle1>());                            //!グループに自分自身を追加
		auto ptrShadow = AddComponent<Shadowmap>();                         //!影をつける（シャドウマップを描画する）
        auto ptrDraw = AddComponent<PNTStaticModelDraw>();                  //!描画コンポーネント
        auto Coll = AddComponent<CollisionObb>();                           //!キューブ型の当たり判定の追加
		Coll->SetFixed(true);                                               //!ほかのオブジェクトの影響を受けない

		//!影の形（メッシュ）を設定 
		ptrShadow->SetMeshResource(L"OBSTACLE1_MESH");
		ptrShadow->SetMeshToTransformMatrix(spanMat);

		//!メッシュの読み込み
		ptrDraw->SetMeshResource(L"OBSTACLE1_MESH");
		ptrDraw->SetMeshToTransformMatrix(spanMat);

		//!RigidbodyBoxの追加
		PsBoxParam param(ptrTrans->GetWorldMatrix(), 0.0f, true, PsMotionType::MotionTypeFixed);
		auto PsPtr = AddComponent<RigidbodyBox>(param);
	}

}