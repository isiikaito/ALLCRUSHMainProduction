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
		//初期位置の設定
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_Scale);
		ptrTrans->SetRotation(m_Rotation);
		ptrTrans->SetPosition(m_Position);



		//モデルの見た目を決める
		Mat4x4 spanMat; // モデルとトランスフォームの間の差分行列
		spanMat.affineTransformation(
			Vec3(0.2f, 0.2f, 0.2f),//大きさ
			Vec3(0.0f, 5.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),//回転
			Vec3(0.0f, -0.5f, 0.5f)//位置
		);

		//オブジェクトのグループを得る
		auto group3 = GetStage()->GetSharedObjectGroup(L"FallingRock_Group1");

		//グループに自分自身を追加
		group3->IntoGroup(GetThis < FallingRock > ());

		//影をつける（シャドウマップを描画する）
		auto ptrShadow = AddComponent<Shadowmap>();

		//影の形（メッシュ）を設定
		ptrShadow->SetMeshResource(L"IWA_MESH");
		ptrShadow->SetMeshToTransformMatrix(spanMat);

		//描画コンポーネント
		auto ptrDraw = AddComponent<PNTStaticModelDraw>();

		//メッシュの設定
		ptrDraw->SetMeshResource(L"IWA_MESH");
		ptrDraw->SetMeshToTransformMatrix(spanMat);
		
		//キューブ型の当たり判定
		auto Coll = AddComponent<CollisionObb>();
		
		//ほかのオブジェクトの影響を受けない
		Coll->SetFixed(true);
        
		//読み込みの設定をする
		GetStage()->SetSharedGameObject(L"FallingRock", GetThis<FallingRock>());
	}

	void FallingRock::OnUpdate()
	{
		//柱が壊れたら
		if (m_Falling==1)
		{
			//重力をつける
			auto ptrGra = AddComponent<Gravity>();
		}
	}
}