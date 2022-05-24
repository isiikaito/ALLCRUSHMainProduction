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
		m_HP(HP),
		//エフェクト
		m_TotalTime2(0.0f), m_isPlay2(false), m_handle2(0),
		m_manager2(nullptr), m_renderer2(nullptr), m_effect2(nullptr)

	{}

	void Wall::CreateEffect() {
		auto d3D11Device = App::GetApp()->GetDeviceResources()->GetD3DDevice();
		auto d3D11DeviceContext = App::GetApp()->GetDeviceResources()->GetD3DDeviceContext();;
		// エフェクトのレンダラーの作成
		m_renderer2 = ::EffekseerRendererDX11::Renderer::Create(d3D11Device, d3D11DeviceContext, 8000);


		// エフェクトのマネージャーの作成
		m_manager2 = ::Effekseer::Manager::Create(8000);
		// 描画モジュールの設定
		m_manager2->SetSpriteRenderer(m_renderer2->CreateSpriteRenderer());
		m_manager2->SetRibbonRenderer(m_renderer2->CreateRibbonRenderer());
		m_manager2->SetRingRenderer(m_renderer2->CreateRingRenderer());
		m_manager2->SetTrackRenderer(m_renderer2->CreateTrackRenderer());
		m_manager2->SetModelRenderer(m_renderer2->CreateModelRenderer());

		// テクスチャ、モデル、カーブ、マテリアルローダーの設定する。
		// ユーザーが独自で拡張できる。現在はファイルから読み込んでいる。
		m_manager2->SetTextureLoader(m_renderer2->CreateTextureLoader());
		m_manager2->SetModelLoader(m_renderer2->CreateModelLoader());
		m_manager2->SetMaterialLoader(m_renderer2->CreateMaterialLoader());
		m_manager2->SetCurveLoader(Effekseer::MakeRefPtr<Effekseer::CurveLoader>());

		// 視点位置を確定
		auto g_position = ::Effekseer::Vector3D(10.0f, 5.0f,0.0f);

		// 投影行列を設定
		float w = (float)App::GetApp()->GetGameWidth();
		float h = (float)App::GetApp()->GetGameHeight();
		m_renderer2->SetProjectionMatrix(::Effekseer::Matrix44().PerspectiveFovRH(
			90.0f / 180.0f * 3.14f, w / h, 1.0f, 500.0f));
		// カメラ行列を設定
		m_renderer2->SetCameraMatrix(
			::Effekseer::Matrix44().LookAtRH(g_position, ::Effekseer::Vector3D(0.0f, 0.0f, 0.0f), ::Effekseer::Vector3D(0.0f, 1.0f, 0.0f)));

		wstring dataDir;
		App::GetApp()->GetDataDirectory(dataDir);
		dataDir += L"effect\\";
		//wstring wstrEfk = dataDir + L"Laser01.efk";
		wstring wstrEfk = dataDir + L"BrakeSmoke.efkefc";


		m_effect2 = ::Effekseer::Effect::Create(m_manager2, (const char16_t*)wstrEfk.c_str());

	}

	void Wall::OnCreate() {

		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_Scale);
		ptrTrans->SetRotation(m_Rotation);
		ptrTrans->SetPosition(m_Position);
		//オブジェクトのグループを得る
		auto group = GetStage()->GetSharedObjectGroup(L"Wall_Group");
		//グループに自分自身を追加
		group->IntoGroup(GetThis<Wall>());

		//影をつける
		auto ptrShadow = AddComponent<Shadowmap>();
		ptrShadow->SetMeshResource(L"DEFAULT_CUBE");

		auto ptrDraw = AddComponent<BcPNTStaticDraw>();
		ptrDraw->SetFogEnabled(false);
		ptrDraw->SetMeshResource(L"DEFAULT_CUBE");
		ptrDraw->SetOwnShadowActive(true);
		ptrDraw->SetTextureResource(L"WALL_TX");

		PsBoxParam param(ptrTrans->GetWorldMatrix(), 0.0f, true, PsMotionType::MotionTypeFixed);
		auto PsPtr = AddComponent<RigidbodyBox>(param);
		PsPtr->SetDrawActive(false);

		//Obbの衝突判定をつける
		auto ptrColl = AddComponent<CollisionObb>();
		//auto obb = ptrColl->GetObb();
		CreateEffect();
		//GetStage()->SetSharedGameObject(L"Wall_Group",GetThis<Wall>());

	}
	void Wall::OnUpdate()
	{
		m_InputHandler.PushHandle(GetThis<Wall>());

		//コントローラの取得
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();

		//Bボタンが押されているとき
		if (cntlVec[0].wButtons & XINPUT_GAMEPAD_B) {
			//表示
			SetDrawActive(false);
		}
		//Bボタンが押されていないとき
		else {
			SetDrawActive(true);
		}
	}


	void  Wall::OnPushB() {
	}

	//Xボタンをおしたら
	void Wall::OnPushX()
	{
		//auto ptrWall = GetStage()->GetSharedGameObject<Wall>(L"Wall_Group");
		auto WallPos = GetComponent<Transform>()->GetWorldPosition();
		if (!m_isPlay2) {
			m_handle2 = m_manager2->Play(m_effect2,WallPos.x,0,0);
			m_isPlay2 = true;
		}
	}

	void Wall::OnDraw() {
		GameObject::OnDraw();
		auto elps = App::GetApp()->GetElapsedTime();
		if (m_isPlay2) {
			m_TotalTime2 += elps;
			if (m_TotalTime2 >= 2.0f) {
				m_manager2->StopEffect(m_handle2);
				m_TotalTime2 = 0.0f;
				m_isPlay2 = false;
				return;
			}
			else {
				// マネージャーの更新
				m_manager2->Update();
				// 時間を更新する
				m_renderer2->SetTime(elps);
				// エフェクトの描画開始処理を行う。
				m_renderer2->BeginRendering();
				// エフェクトの描画を行う。
				m_manager2->Draw();
				// エフェクトの描画を行う。
				//m_manager->DrawHandleBack(m_handle);
				// エフェクトの描画を行う。
				//m_manager->DrawHandleFront(m_handle);
				// エフェクトの描画終了処理を行う。
				m_renderer2->EndRendering();
			}

		}
	}
	//壁に当たったら
	void Wall::OnCollisionEnter(shared_ptr<GameObject>& Other) {
				}
			
}
//end basecross
