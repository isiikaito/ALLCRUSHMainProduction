/**
*@file Pillar.cpp
*@brief 柱オブジェクトが実装されているソースファイル
*@author Kaito Isii
*@details 柱オブジェクトの実装
*/

#include "stdafx.h"
#include "Project.h"

/** basecross共通のネームスペース */
namespace basecross {
	//!パラメータの初期化
	Pillar::Pillar(const shared_ptr<Stage>& StagePtr, const Vec3& Scale, const Vec3& Rotation, const Vec3& Position) :
		GameObject(StagePtr),
		m_Scale(Scale),
		m_Rotation(Rotation),
		m_Position(Position)
	{}


	void Pillar::OnCreate() {
		//!初期位置などの設定
		
		//!衝突判定の設定
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_Scale);      //!大きさ
		ptrTrans->SetRotation(m_Rotation);//!回転
		ptrTrans->SetPosition(m_Position);//!位置

        //!モデルとトランスフォームの間の差分行列
		Mat4x4 spanMat; 
		spanMat.affineTransformation(
			Vec3(0.5f, 0.5f, 0.5f),    //!大きさ
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),    //!回転
			Vec3(-0.4f, -0.5f, -0.6f)  //!位置
		);

		
		auto group2 = GetStage()->GetSharedObjectGroup(L"Pillar_Group1");//!オブジェクトのグループを得る		
		group2->IntoGroup(GetThis<Pillar>());                            //!グループに自分自身を追加
		auto ptrShadow = AddComponent<Shadowmap>();                      //!影をつける（シャドウマップを描画する）
        auto Coll = AddComponent<CollisionObb>();                        //!キューブ型の当たり判定の追加
		Coll->SetFixed(true);                                            //!ほかのオブジェクトの影響を受けない（例プレイヤーに当たったら消えるなどの処理）
		GetStage()->SetSharedGameObject(L"Pillar", GetThis<Pillar>());   //!SetSharedGameObjectへ読み込みの設定をする
        auto ptrDraw = AddComponent<PNTStaticModelDraw>();               //!描画コンポーネント

		//!影の形（メッシュ）を設定
		ptrShadow->SetMeshResource(L"PILLAR_MESH");
		ptrShadow->SetMeshToTransformMatrix(spanMat);

		//!メッシュ読み込み
		ptrDraw->SetMeshResource(L"PILLAR_MESH");
		ptrDraw->SetMeshToTransformMatrix(spanMat);

		//!RigidbodyBoxの追加
		PsBoxParam param(ptrTrans->GetWorldMatrix(), 0.0f, true, PsMotionType::MotionTypeFixed);
		auto PsPtr = AddComponent<RigidbodyBox>(param);
	}

}