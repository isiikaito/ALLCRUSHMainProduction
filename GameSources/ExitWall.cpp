/**
*@file StageWall.cpp
*@brief出口の壁の実体が実装されているソースファイル
*@author Kaito Isii
*@details 出口の壁の実体の実装
*/

#include "stdafx.h"
#include "Project.h"

/** basecross共通のネームスペース */
namespace basecross {
	//!パラメータの初期化
	ExitWall::ExitWall(const shared_ptr<Stage>& StagePtr, const Vec3& Scale, const Vec3& Rotation, const Vec3& Position) :
		GameObject(StagePtr),
		m_Scale(Scale),
		m_Rotation(Rotation),
		m_Position(Position)
	{}


	
	void ExitWall::OnCreate() {
		//!初期位置などの設定

		//!衝突判定の設定
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_Scale);      //!大きさ
		ptrTrans->SetRotation(m_Rotation);//!回転
		ptrTrans->SetPosition(m_Position);//!位置

        //!モデルとトランスフォームの間の差分行列
		Mat4x4 spanMat; 
		spanMat.affineTransformation(
			Vec3(1.0f, 0.15f, 0.08),//!大きさ
			Vec3(0.0f, 5.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f), //!回転
			Vec3(0.0f, -0.8f, 0.0f) //!位置
		);
		
		auto ptrShadow = AddComponent<Shadowmap>();       //!影をつける（シャドウマップを描画する）
        auto Coll = AddComponent<CollisionObb>();         //!キューブ型の当たり判定
		auto ptrDraw = AddComponent<PNTStaticModelDraw>();//!描画コンポーネント
		Coll->SetFixed(true);                             //!他のオブジェクトの影響を受けない

		//!影の形（メッシュ）を設定
		ptrShadow->SetMeshResource(L"EXITWALL_MESH");
		ptrShadow->SetMeshToTransformMatrix(spanMat);

		//!メッシュの設定
		ptrDraw->SetMeshResource(L"EXITWALL_MESH");
		ptrDraw->SetMeshToTransformMatrix(spanMat);

		//!RigidbodyBoxの追加
		PsBoxParam param(ptrTrans->GetWorldMatrix(), 0.0f, true, PsMotionType::MotionTypeFixed);
		auto PsPtr = AddComponent<RigidbodyBox>(param);
	
	}

}