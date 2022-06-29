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
		//初期位置の設定
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_Scale);      
		ptrTrans->SetRotation(m_Rotation);
		ptrTrans->SetPosition(m_Position);

        // モデルとトランスフォームの間の差分行列
		Mat4x4 spanMat;                 
		spanMat.affineTransformation(
			Vec3(0.3f, 0.095f, 0.09f),    //大きさ
			Vec3(0.0f, 5.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),       //回転
			Vec3(-0.4f, -0.7f, 0.0f)      //位置
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

		//描画コンポーネント
		auto ptrDraw = AddComponent<PNTStaticModelDraw>();

		//メッシュの設定
		ptrDraw->SetMeshResource(L"UNBREAKWALL_MESH");
		ptrDraw->SetMeshToTransformMatrix(spanMat);

		//Obbの衝突判定をつける
		auto ptrColl = AddComponent<CollisionObb>();

		//ほかのオブジェクトの影響を受けない
		ptrColl->SetFixed(true);
	}

	void Wall::OnUpdate()
	{
		m_InputHandler.PushHandle(GetThis<Wall>());

		//コントローラの取得
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();

		//Bボタンが押されているとき
		if (cntlVec[0].wButtons & XINPUT_GAMEPAD_B) {
			//壁の描画の表示をしない
			SetDrawActive(false);
		}

		//Bボタンが押されていないとき
		else {
			//壁の描画の処理をする
			SetDrawActive(true);
		}
		
		auto WallHP = GetHP();                            //壁のHP取得
		auto ptrDraw = GetComponent<PNTStaticModelDraw>();//壁の描画コンポーネント
		
		//壁の残り耐久値についての処理
		
		//HPが4だった時
		if (WallHP >= 4)
		{
			ptrDraw->SetMeshResource(L"UNBREAKWALL_MESH");

		}

		//HPが3だった時
		else if (WallHP >= 3)
		{
			Mat4x4 spanMat; // モデルとトランスフォームの間の差分行列
			spanMat.affineTransformation(
				Vec3(0.3f, 0.095f, 0.09f),//大きさ
				Vec3(0.0f, 5.0f, 0.0f),
				Vec3(0.0f, 0.0f, 0.0f),   //回転
				Vec3(-0.4f, -0.7f, 0.0f)  //位置
			);
			ptrDraw->SetMeshResource(L"DAMAGEWALL1_MESH");
			ptrDraw->SetMeshToTransformMatrix(spanMat);
			
		}

		//HPが2だった時
		else if (WallHP >=2)
		{
		
			Mat4x4 spanMat; // モデルとトランスフォームの間の差分行列
			spanMat.affineTransformation(
				Vec3(0.3f, 0.095f, 0.09f),//大きさ
				Vec3(0.0f, 5.0f, 0.0f),
				Vec3(0.0f, 0.0f, 0.0f),   //回転
				Vec3(-0.4f, -0.7f, 0.0f)  //位置
			);
			ptrDraw->SetMeshResource(L"DAMAGEWALL2_MESH");
			ptrDraw->SetMeshToTransformMatrix(spanMat);
		}

		//HPが1だった時
		else if (WallHP >= 1)
		{
			Mat4x4 spanMat; // モデルとトランスフォームの間の差分行列
			spanMat.affineTransformation(
				Vec3(0.3f, 0.095f, 0.09f),//大きさ
				Vec3(0.0f, 5.0f, 0.0f),
				Vec3(0.0f, 0.0f, 0.0f),   //回転
				Vec3(-0.4f, -0.7f, 0.0f)  //位置
			);
			ptrDraw->SetMeshResource(L"DAMAGEWALL3_MESH");
		
			ptrDraw->SetMeshToTransformMatrix(spanMat);
			
		}

	}

}
//end basecross
