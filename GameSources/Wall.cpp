/*!
@file Wall.cpp
@brief �J�x�̎���
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
		//�G�t�F�N�g
		m_TotalTime2(0.0f), m_isPlay2(false), m_handle2(0),
		m_manager2(nullptr), m_renderer2(nullptr), m_effect2(nullptr)

	{}

	void Wall::CreateEffect() {
		auto d3D11Device = App::GetApp()->GetDeviceResources()->GetD3DDevice();
		auto d3D11DeviceContext = App::GetApp()->GetDeviceResources()->GetD3DDeviceContext();;
		// �G�t�F�N�g�̃����_���[�̍쐬
		m_renderer2 = ::EffekseerRendererDX11::Renderer::Create(d3D11Device, d3D11DeviceContext, 8000);


		// �G�t�F�N�g�̃}�l�[�W���[�̍쐬
		m_manager2 = ::Effekseer::Manager::Create(8000);
		// �`�惂�W���[���̐ݒ�
		m_manager2->SetSpriteRenderer(m_renderer2->CreateSpriteRenderer());
		m_manager2->SetRibbonRenderer(m_renderer2->CreateRibbonRenderer());
		m_manager2->SetRingRenderer(m_renderer2->CreateRingRenderer());
		m_manager2->SetTrackRenderer(m_renderer2->CreateTrackRenderer());
		m_manager2->SetModelRenderer(m_renderer2->CreateModelRenderer());

		// �e�N�X�`���A���f���A�J�[�u�A�}�e���A�����[�_�[�̐ݒ肷��B
		// ���[�U�[���Ǝ��Ŋg���ł���B���݂̓t�@�C������ǂݍ���ł���B
		m_manager2->SetTextureLoader(m_renderer2->CreateTextureLoader());
		m_manager2->SetModelLoader(m_renderer2->CreateModelLoader());
		m_manager2->SetMaterialLoader(m_renderer2->CreateMaterialLoader());
		m_manager2->SetCurveLoader(Effekseer::MakeRefPtr<Effekseer::CurveLoader>());

		// ���_�ʒu���m��
		auto g_position = ::Effekseer::Vector3D(10.0f, 5.0f,0.0f);

		// ���e�s���ݒ�
		float w = (float)App::GetApp()->GetGameWidth();
		float h = (float)App::GetApp()->GetGameHeight();
		m_renderer2->SetProjectionMatrix(::Effekseer::Matrix44().PerspectiveFovRH(
			90.0f / 180.0f * 3.14f, w / h, 1.0f, 500.0f));
		// �J�����s���ݒ�
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
		//�I�u�W�F�N�g�̃O���[�v�𓾂�
		auto group = GetStage()->GetSharedObjectGroup(L"Wall_Group");
		//�O���[�v�Ɏ������g��ǉ�
		group->IntoGroup(GetThis<Wall>());

		//�e������
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

		//Obb�̏Փ˔��������
		auto ptrColl = AddComponent<CollisionObb>();
		//auto obb = ptrColl->GetObb();
		CreateEffect();
		//GetStage()->SetSharedGameObject(L"Wall_Group",GetThis<Wall>());

	}
	void Wall::OnUpdate()
	{
		m_InputHandler.PushHandle(GetThis<Wall>());

		//�R���g���[���̎擾
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();

		//B�{�^����������Ă���Ƃ�
		if (cntlVec[0].wButtons & XINPUT_GAMEPAD_B) {
			//�\��
			SetDrawActive(false);
		}
		//B�{�^����������Ă��Ȃ��Ƃ�
		else {
			SetDrawActive(true);
		}
	}


	void  Wall::OnPushB() {
	}

	//X�{�^������������
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
				// �}�l�[�W���[�̍X�V
				m_manager2->Update();
				// ���Ԃ��X�V����
				m_renderer2->SetTime(elps);
				// �G�t�F�N�g�̕`��J�n�������s���B
				m_renderer2->BeginRendering();
				// �G�t�F�N�g�̕`����s���B
				m_manager2->Draw();
				// �G�t�F�N�g�̕`����s���B
				//m_manager->DrawHandleBack(m_handle);
				// �G�t�F�N�g�̕`����s���B
				//m_manager->DrawHandleFront(m_handle);
				// �G�t�F�N�g�̕`��I���������s���B
				m_renderer2->EndRendering();
			}

		}
	}
	//�ǂɓ���������
	void Wall::OnCollisionEnter(shared_ptr<GameObject>& Other) {
				}
			
}
//end basecross
