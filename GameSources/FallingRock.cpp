/**
*@file FallingRock.cpp
*@brief落石実体が実装されているソースファイル
*@author Kaito Isii
*@details 落石実体の実装
*/

#include "stdafx.h"
#include "Project.h"

/** basecross共通のネームスペース */
namespace basecross {
	//!パラメータの初期化
	FallingRock::FallingRock(const shared_ptr<Stage>& StagePtr, const Vec3& Scale, const Vec3& Rotation, const Vec3& Position) :
		GameObject(StagePtr),
		m_Scale(Scale),
		m_Rotation(Rotation),
		m_Position(Position),
		m_Falling(0)
	{}


	
	void FallingRock::OnCreate() {
		//!初期位置などの設定
		
		//!衝突判定の設定
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_Scale);      //!大きさ
		ptrTrans->SetRotation(m_Rotation);//!回転
		ptrTrans->SetPosition(m_Position);//!位置

		//!モデルとトランスフォームの間の差分行列
		Mat4x4 spanMat; 
		spanMat.affineTransformation(
			Vec3(0.2f, 0.2f, 0.2f),//!大きさ
			Vec3(0.0f, 5.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),//!回転
			Vec3(0.0f, -0.5f, 0.5f)//!位置
		);

		
		auto group3 = GetStage()->GetSharedObjectGroup(L"FallingRock_Group1");  //!オブジェクトのグループを得る
        group3->IntoGroup(GetThis < FallingRock > ());                          //!グループに自分自身を追加
		auto ptrShadow = AddComponent<Shadowmap>();                             //!影をつける（シャドウマップを描画する）
		auto Coll = AddComponent<CollisionObb>();                               //!キューブ型の当たり判定
		Coll->SetFixed(true);                                                   //!ほかのオブジェクトの影響を受けない
		GetStage()->SetSharedGameObject(L"FallingRock", GetThis<FallingRock>());//!読み込みの設定をする
        auto ptrDraw = AddComponent<PNTStaticModelDraw>();                      //!描画コンポーネント
		
		//!影の形（メッシュ）を設定
		ptrShadow->SetMeshResource(L"IWA_MESH");
		ptrShadow->SetMeshToTransformMatrix(spanMat);

		//!メッシュの設定
		ptrDraw->SetMeshResource(L"IWA_MESH");
		ptrDraw->SetMeshToTransformMatrix(spanMat);
		
	}

	void FallingRock::OnUpdate()
	{
		//!柱が壊れたら
		if (m_Falling==1)
		{
			auto ptrGra = AddComponent<Gravity>();//!重力をつける
		}
	}
}