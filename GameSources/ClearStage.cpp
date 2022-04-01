/*!
@file GameStage.cpp
@briefクリアステージ実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	クリアステージクラス実体
	//--------------------------------------------------------------------------------------
	void ClearStage::CreateViewLight() {
		const Vec3 eye(0.0f, 20.0f, -10.0f);
		const Vec3 at(0.0f);
		auto PtrView = CreateView<SingleView>();
		//ビューのカメラの設定
		auto PtrCamera = ObjectFactory::Create<Camera>();
		PtrView->SetCamera(PtrCamera);
		PtrCamera->SetEye(eye);
		PtrCamera->SetAt(at);
		//マルチライトの作成
		auto PtrMultiLight = CreateLight<MultiLight>();
		//デフォルトのライティングを指定
		PtrMultiLight->SetDefaultLighting();
	}



	void ClearStage::OnCreate() {
		try {

			//ビューとライトの作成
			CreateViewLight();
			AddGameObject<ClearObject>();

		}
		catch (...) {
			throw;
		}
	}


}
//end basecross
