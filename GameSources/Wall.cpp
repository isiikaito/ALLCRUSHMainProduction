/*!
@file Wall.cpp
@brief カベの実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
#pragma comment(lib, "Effekseer.lib")
#pragma comment(lib, "EffekseerRendererDX11.lib")

	Wall::Wall(const shared_ptr<Stage>& StagePtr,
		const Vec3& Scale,
		const Quat& Qt,
		const Vec3& Position,
		const int& HP

	) :
		GameObject(StagePtr),
		m_Scale(Scale),
		m_Qt(Qt),
		m_Position(Position),
		m_HP(HP),
		//エフェクト
		m_TotalTime(0.0f), m_isPlay(false), m_handle(0),
		m_manager(nullptr), m_renderer(nullptr), m_effect(nullptr)

	{}

	void Wall::CreateEffect() {
		auto d3D11Device = App::GetApp()->GetDeviceResources()->GetD3DDevice();
		auto d3D11DeviceContext = App::GetApp()->GetDeviceResources()->GetD3DDeviceContext();;
		// エフェクトのレンダラーの作成
		m_renderer = ::EffekseerRendererDX11::Renderer::Create(d3D11Device, d3D11DeviceContext, 8000);


		// エフェクトのマネージャーの作成
		m_manager = ::Effekseer::Manager::Create(8000);
		// 描画モジュールの設定
		m_manager->SetSpriteRenderer(m_renderer->CreateSpriteRenderer());
		m_manager->SetRibbonRenderer(m_renderer->CreateRibbonRenderer());
		m_manager->SetRingRenderer(m_renderer->CreateRingRenderer());
		m_manager->SetTrackRenderer(m_renderer->CreateTrackRenderer());
		m_manager->SetModelRenderer(m_renderer->CreateModelRenderer());

		// テクスチャ、モデル、カーブ、マテリアルローダーの設定する。
		// ユーザーが独自で拡張できる。現在はファイルから読み込んでいる。
		m_manager->SetTextureLoader(m_renderer->CreateTextureLoader());
		m_manager->SetModelLoader(m_renderer->CreateModelLoader());
		m_manager->SetMaterialLoader(m_renderer->CreateMaterialLoader());
		m_manager->SetCurveLoader(Effekseer::MakeRefPtr<Effekseer::CurveLoader>());

		// 視点位置を確定
		auto g_position = ::Effekseer::Vector3D(10.0f, 5.0f,20.0f);

		// 投影行列を設定
		float w = (float)App::GetApp()->GetGameWidth();
		float h = (float)App::GetApp()->GetGameHeight();
		m_renderer->SetProjectionMatrix(::Effekseer::Matrix44().PerspectiveFovRH(
			90.0f / 180.0f * 3.14f, w / h, 1.0f, 500.0f));
		// カメラ行列を設定
		m_renderer->SetCameraMatrix(
			::Effekseer::Matrix44().LookAtRH(g_position, ::Effekseer::Vector3D(0.0f, 0.0f, 0.0f), ::Effekseer::Vector3D(0.0f, 1.0f, 0.0f)));

		wstring dataDir;
		App::GetApp()->GetDataDirectory(dataDir);
		dataDir += L"effect\\";
		//wstring wstrEfk = dataDir + L"Laser01.efk";
		wstring wstrEfk = dataDir + L"BrakeSmoke.efkefc";


		m_effect = ::Effekseer::Effect::Create(m_manager, (const char16_t*)wstrEfk.c_str());

	}

	void Wall::OnCreate() {

		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_Scale);
		ptrTrans->SetQuaternion(m_Qt);
		ptrTrans->SetPosition(m_Position);

		//オブジェクトのグループを得る
		auto group = GetStage()->GetSharedObjectGroup(L"Wall_Group");
		//グループに自分自身を追加
		group->IntoGroup(GetThis<Wall>());

		//影をつける
		auto ptrShadow = AddComponent<Shadowmap>();
		ptrShadow->SetMeshResource(L"DEFAULT_CUBE");

		auto ptrDraw = AddComponent<BcPNTStaticDraw>();
		ptrDraw->SetFogEnabled(true);
		ptrDraw->SetMeshResource(L"DEFAULT_CUBE");
		ptrDraw->SetOwnShadowActive(true);
		ptrDraw->SetTextureResource(L"WALL_TX");

		PsBoxParam param(ptrTrans->GetWorldMatrix(), 0.0f, true, PsMotionType::MotionTypeFixed);
		auto PsPtr = AddComponent<RigidbodyBox>(param);
		PsPtr->SetDrawActive(true);

		//Obbの衝突判定をつける
		auto ptrColl = AddComponent<CollisionObb>();
		//auto obb = ptrColl->GetObb();
		CreateEffect();
		//GetStage()->SetSharedGameObject(L"Wall_Group",GetThis<Wall>());

	}
	void Wall::OnUpdate()
	{
		m_InputHandler.PushHandle(GetThis<Wall>());

	}


	void  Wall::OnPushB() {
		//if (!m_isPlayTest) {
		//	//auto pos = ptr->GetComponent<Transform>()->GetPosition();
		//	m_handle = m_manager->Play(m_effect, 0,0,0);
		//	m_isPlayTest = true;
		//}
	}

	//Xボタンをおしたら
	void Wall::OnPushX()
	{
		//auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		//RemoveComponent<Wall>();
			//SetUpdateActive(false);
			//SetDrawActive(false);
			/*SetUpdateActive(false);
			SetDrawActive(false);*/
	}

	//壁に当たったら
	void Wall::OnCollisionEnter(shared_ptr<GameObject>& Other) {
		auto ptr = dynamic_pointer_cast<Player>(Other);
			if (ptr) {
				if (!m_isPlay) {
					auto pos = ptr->GetComponent<Transform>()->GetWorldPosition();
					m_handle = m_manager->Play(m_effect, pos.x, pos.y, pos.z);

					m_isPlay = true;
				}
		}
	}
	void Wall::OnDraw() {
		GameObject::OnDraw();
		if (m_isPlay) {
			auto elps = App::GetApp()->GetElapsedTime();
			m_TotalTime += elps;
			if (m_TotalTime >= 2.0f) {
				m_manager->StopEffect(m_handle);
				m_TotalTime = 0.0f;
				m_isPlay = false;
				return;
			}
			else {
				// マネージャーの更新
				m_manager->Update();
				// 時間を更新する
				m_renderer->SetTime(elps);
				// エフェクトの描画開始処理を行う。
				m_renderer->BeginRendering();
				// エフェクトの描画を行う。
				m_manager->Draw();
				// エフェクトの描画終了処理を行う。
				m_renderer->EndRendering();
			}

		}
	}

}
	
//end basecross
