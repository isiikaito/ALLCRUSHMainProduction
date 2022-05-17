/*!
@file Player.cpp
@brief �v���C���[�Ȃǎ���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
#pragma comment(lib, "Effekseer.lib")
#pragma comment(lib, "EffekseerRendererDX11.lib")

	//Player::Player(const shared_ptr<Stage>& StagePtr) :
	//	GameObject(StagePtr),
	//	MaxMoveSpeed(6.0f),
	//	moveStop(1.0f),	
	//	moveDir(0.0f, 0.0f, 0.0f),
	//	speed(0.0f),
	//	accel(0.0f),
	//	itemCount(0.0f),
	//	m_TotalTime(0.0f), m_isPlay(false), m_handle(0),
	//	m_manager(nullptr), m_renderer(nullptr), m_effect(nullptr)
	//{}

	void Player::CreateEffect() {
		auto d3D11Device = App::GetApp()->GetDeviceResources()->GetD3DDevice();
		auto d3D11DeviceContext = App::GetApp()->GetDeviceResources()->GetD3DDeviceContext();;
		// �G�t�F�N�g�̃����_���[�̍쐬
		m_renderer = ::EffekseerRendererDX11::Renderer::Create(d3D11Device, d3D11DeviceContext, 8000);


		// �G�t�F�N�g�̃}�l�[�W���[�̍쐬
		m_manager = ::Effekseer::Manager::Create(8000);
		// �`�惂�W���[���̐ݒ�
		m_manager->SetSpriteRenderer(m_renderer->CreateSpriteRenderer());
		m_manager->SetRibbonRenderer(m_renderer->CreateRibbonRenderer());
		m_manager->SetRingRenderer(m_renderer->CreateRingRenderer());
		m_manager->SetTrackRenderer(m_renderer->CreateTrackRenderer());
		m_manager->SetModelRenderer(m_renderer->CreateModelRenderer());

		// �e�N�X�`���A���f���A�J�[�u�A�}�e���A�����[�_�[�̐ݒ肷��B
		// ���[�U�[���Ǝ��Ŋg���ł���B���݂̓t�@�C������ǂݍ���ł���B
		m_manager->SetTextureLoader(m_renderer->CreateTextureLoader());
		m_manager->SetModelLoader(m_renderer->CreateModelLoader());
		m_manager->SetMaterialLoader(m_renderer->CreateMaterialLoader());
		m_manager->SetCurveLoader(Effekseer::MakeRefPtr<Effekseer::CurveLoader>());

		// ���_�ʒu���m��
		auto g_position = ::Effekseer::Vector3D(10.0f, 5.0f, 20.0f);

		// ���e�s���ݒ�
		float w = (float)App::GetApp()->GetGameWidth();
		float h = (float)App::GetApp()->GetGameHeight();
		m_renderer->SetProjectionMatrix(::Effekseer::Matrix44().PerspectiveFovRH(
			90.0f / 180.0f * 3.14f, w / h, 1.0f, 500.0f));
		// �J�����s���ݒ�
		m_renderer->SetCameraMatrix(
			::Effekseer::Matrix44().LookAtRH(g_position, ::Effekseer::Vector3D(0.0f, 0.0f, 0.0f), ::Effekseer::Vector3D(0.0f, 1.0f, 0.0f)));

		wstring dataDir;
		App::GetApp()->GetDataDirectory(dataDir);
		dataDir += L"effect\\";
		//wstring wstrEfk = dataDir + L"Laser01.efk";
		wstring wstrEfk = dataDir + L"BrakeSmoke.efkefc";

		m_effect = ::Effekseer::Effect::Create(m_manager, (const char16_t*)wstrEfk.c_str());

	}

	void Player::OnCreate()
	{

		//�����ʒu�Ȃǂ̐ݒ�
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(0.5f, 0.5f, 0.5f);
		ptrTrans->SetRotation(0.0f, 0.0f, 0.0f);
		ptrTrans->SetPosition(40.0f, 0.25f, 0.0f);
		itemCount = 0;


		//CollisionSphere�Փ˔����t����
		auto ptrColl = AddComponent<CollisionCapsule>();
		/*ptrColl->SetDrawActive(true);*/
		//�Փ˔����\��
		ptrColl->SetDrawActive(true);
		Mat4x4 spanMat; // ���f���ƃg�����X�t�H�[���̊Ԃ̍����s��
		spanMat.affineTransformation(
			Vec3(0.2f, 0.2f, 0.2f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, XM_PI * -0.5f, 0.0f),
			Vec3(0.0f, -1.0f, 0.0f)
		);

		//�d�͂�����
		auto ptrGra = AddComponent<Gravity>();
		//�e������i�V���h�E�}�b�v��`�悷��j
		auto ptrShadow = AddComponent<Shadowmap>();

		//�e�̌`�i���b�V���j��ݒ�
		ptrShadow->SetMeshResource(L"Object_WalkAnimation_MESH");
		ptrShadow->SetMeshToTransformMatrix(spanMat);

		//�`��R���|�[�l���g�̐ݒ�
		auto ptrDraw = AddComponent<BcPNTnTBoneModelDraw>();
		ptrDraw->SetFogEnabled(true);
		//�`�悷�郁�b�V����ݒ�
		ptrDraw->SetMeshResource(L"Object_WalkAnimation_MESH_WITH_TAN");
		ptrDraw->SetNormalMapTextureResource(L"OBJECT_NORMAL_TX");
		ptrDraw->SetMeshToTransformMatrix(spanMat);
		ptrDraw->AddAnimation(L"Default", 0, 10, true, 15.0f);
		ptrDraw->AddAnimation(L"Move", 10, 30, true, 50.0f);
		ptrDraw->AddAnimation(L"Action", 40, 35, false, 35.0f);
		ptrDraw->AddAnimation(L"ActionPull", 40, 20, false, 35.0f);
		ptrDraw->AddAnimation(L"ActionPush", 60, 15, false, 35.0f);
		ptrDraw->ChangeCurrentAnimation(L"Default");

		CreateEffect();

	}

	void Player::OnUpdate()
	{
		//�A�j���V����
		auto ptrDraw = GetComponent<BcPNTnTBoneModelDraw>();
		auto move = ptrDraw->GetCurrentAnimation();

		// �A�v���P�[�V�����I�u�W�F�N�g���擾����
		auto& app = App::GetApp();

		// �f���^�^�C�����擾����
		float delta = app->GetElapsedTime(); // �O�t���[������́u�o�ߎ��ԁv

		// �J�������擾����
		auto stage = GetStage(); // ���̃I�u�W�F�N�g���ǉ�����Ă���X�e�[�W
		auto camera = stage->GetView()->GetTargetCamera(); // �J�������擾����

		// �J�����̉�荞��
		float rad = 0.0f;

		// Camera�I�u�W�F�N�g��MainCamera�I�u�W�F�N�g�Ɂu�_�E���L���X�g�v����
		auto mainCamera = dynamic_pointer_cast<MyCamera>(camera);
		if (mainCamera) // nullptr�o�Ȃ�������A�L���X�g����
		{
			rad = mainCamera->GetAngleY() + XMConvertToRadians(90.0f);
		}

		// �Q�[���R���g���[���[�I�u�W�F�N�g���擾����
		auto& device = app->GetInputDevice();
		const auto& pad = device.GetControlerVec()[0]; // �[���Ԗڂ̃R���g���[���[���擾����
		moveDir = Vec3(pad.fThumbLX, 0.0f, pad.fThumbLY); // �傫���� 0.0f �` 1.0f;
		auto m = Mat3x3( // Y�����S�ŉ�]������s��
			Vec3(cosf(rad), 0.0f, sinf(rad)),  // X���̌���
			Vec3(0.0f, 1.0f, 0.0f),  // Y���̌���
			Vec3(-sinf(rad), 0.0f, cosf(rad))); // Z���̌���
		moveDir = moveDir * m; // �X�e�B�b�N�̓��͂�angleY���W�A����]������

		speed = MaxMoveSpeed * moveDir.length() * moveStop; // �ő呬�~�X�e�B�b�N�x�N�g���̑傫���~��~�����邩�ǂ����̔���
		moveDir.normalize(); // �ړ������𐳋K������

		auto transComp = GetComponent<Transform>();
		auto position = transComp->GetPosition(); // ���݂̈ʒu���W���擾����
		auto scale = transComp->GetScale();
		// �v���C���[�̈ړ�
		position += moveDir * speed * delta * speed2; // �f���^�^�C�����|���āu�b�ԁv�̈ړ��ʂɕϊ�����



		transComp->SetPosition(position); // �X�V�����l�ōĐݒ肷��
		if (speed > 0.0f) // �X�e�B�b�N���|��Ă�����E�E
		{
			float rotY = atan2f(-moveDir.z, moveDir.x); // �A�[�N�^���W�F���g���g���ƃx�N�g�����p�x�ɕϊ��ł���
			transComp->SetRotation(0.0f, rotY, 0.0f); // ���W�A���p�Őݒ�
			//�����A�j���[�V����
			//if (move != L"Move") {
			if (move == L"Default") {
				ptrDraw->ChangeCurrentAnimation(L"Move");
				//�T�E���h�̍Đ�
				auto ptrXA = App::GetApp()->GetXAudio2Manager();
				m_BGM = ptrXA->Start(L"run", 0, 0.5f);
			}
		}
		else {
			//�����~�܂�A�j���[�V����
			if (move == L"Move") {
				ptrDraw->ChangeCurrentAnimation(L"Default");
				auto ptrXA = App::GetApp()->GetXAudio2Manager();
				ptrXA->Stop(m_BGM);
				moveStop = 1.0f;//�ړ���~����
			}
		}

		//�R���g���[���`�F�b�N���ē��͂�����΃R�}���h�Ăяo��
		m_InputHandler.PushHandle(GetThis<Player>());
		//MovePlayer();
		m_InputHandler2.PushHandle(GetThis<Player>());

	}

	//A�{�^��
	void Player::OnPushA() {
		//�n���}�[��U��A�j���[�V����
		auto ptrDraw = GetComponent<BcPNTnTBoneModelDraw>();
		auto action = ptrDraw->GetCurrentAnimation();
		//if (action == L"Default") {
		auto transComp = GetComponent<Transform>();
		auto position = transComp->GetPosition(); // ���݂̈ʒu���W���擾����
		SPHERE playerSp(position, 2.0f);
		auto group = GetStage()->GetSharedObjectGroup(L"Wall_Group");
		auto vec = group->GetGroupVector();
		if (action != L"ActionPull") {
			ptrDraw->ChangeCurrentAnimation(L"ActionPull");

			auto ptrXA = App::GetApp()->GetXAudio2Manager();
			ptrXA->Stop(m_BGM);//bgm(�����̒�~)

			moveStop = 0.0f;//�ړ��̒�~

			for (auto& v : vec) {
				auto shPtr = v.lock();
				Vec3 ret;
				auto ptrWall = dynamic_pointer_cast<Wall>(shPtr);
				if (ptrWall) {
					auto WallObb = ptrWall->GetComponent<CollisionObb>()->GetObb();
					auto WallHP = ptrWall->GetHP();

					if (/*�߂Â�����*/
						HitTest::SPHERE_OBB(playerSp, WallObb, ret)) {
						//�ǂƂ̋�����2.0�ȉ��ɂȂ���
						auto ctrlVec = App::GetApp()->GetInputDevice().GetControlerVec();
						if (ctrlVec[0].wButtons & XINPUT_GAMEPAD_A) {
							//while (WallHP >= 1) {
								//�R���g���[���[�̃{�^����������Ă�����A�ϋv�l���P���炷
							if (WallHP > 1) {
								int a = 1;
							}
						}

						//GetStage()->RemoveGameObject<Wall>(shPtr);
						if (!m_isPlay) {
							//auto pos = ptr->GetComponent<Transform>()->GetWorldPosition();
							m_handle = m_manager->Play(m_effect, 0, 0, 0);
							m_isPlay = true;
						}
						WallHP--;
						////�T�E���h�̍Đ�
						//ptrXA->Start(L"AttackWall", 0, 0.5f);
						ptrWall->SetHP(WallHP);
					}
					if (WallHP <= 0)
					{
						auto ptrXA = App::GetApp()->GetXAudio2Manager();
						GetStage()->RemoveGameObject<Wall>(shPtr);
						//�T�E���h�̍Đ�
						ptrXA->Start(L"BrakeWall", 0, 0.5f);
					}
				}

			}
		}

		//��Q���P�̔j��

		auto group1 = GetStage()->GetSharedObjectGroup(L"Obstacle1_Group1");
		auto vec1 = group1->GetGroupVector();
		for (auto& v1 : vec1) {
			auto shPtr1 = v1.lock();
			Vec3 ret1;
			auto ptrObstacle1 = dynamic_pointer_cast<Obstacle1>(shPtr1);

			if (ptrObstacle1) {
				auto Obstacle1Obb = ptrObstacle1->GetComponent<CollisionObb>()->GetObb();
				if (/*�߂Â�����*/
					HitTest::SPHERE_OBB(playerSp, Obstacle1Obb, ret1)) {
					//�ǂƂ̋�����2.0�ȉ��ɂȂ���
					auto ctrlVec1 = App::GetApp()->GetInputDevice().GetControlerVec();
					if (ctrlVec1[0].wButtons & XINPUT_GAMEPAD_A) {
						//�R���g���[���̃{�^����������Ă�����AshPtr������
						GetStage()->RemoveGameObject<Obstacle1>(shPtr1);
						auto Shitem = GetStage()->GetSharedGameObject<Myitem1>(L"Myitem1");
						Shitem->SetDrawActive(true);
						itemCount = 1;
					}

				}
			}
		}
		//��
		auto group2 = GetStage()->GetSharedObjectGroup(L"Pillar_Group1");
		auto vec2 = group2->GetGroupVector();
		for (auto& v2 : vec2) {
			auto shPtr2 = v2.lock();
			Vec3 ret2;
			auto ptrPillar = dynamic_pointer_cast<Pillar>(shPtr2);

			auto ptrFallingRock = GetStage()->GetSharedGameObject<FallingRock>(L"FallingRock");
			if (ptrPillar) {
				auto PillarObb = ptrPillar->GetComponent<CollisionObb>()->GetObb();
				auto Falling1 = ptrFallingRock->GetFalling();
				if (/*�߂Â�����*/
					HitTest::SPHERE_OBB(playerSp, PillarObb, ret2)) {
					//�ǂƂ̋�����2.0�ȉ��ɂȂ���
					auto ctrlVec1 = App::GetApp()->GetInputDevice().GetControlerVec();
					if (ctrlVec1[0].wButtons & XINPUT_GAMEPAD_A) {
						//�R���g���[���̃{�^����������Ă�����AshPtr������
						GetStage()->RemoveGameObject<Pillar>(shPtr2);
						//���΂̏���
						Falling1 = 1;
						ptrFallingRock->SetFalling(Falling1);

					}

				}
			}
		}
	}
	void Player::OnDraw() {
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
				// �}�l�[�W���[�̍X�V
				m_manager->Update();
				// ���Ԃ��X�V����
				m_renderer->SetTime(elps);
				// �G�t�F�N�g�̕`��J�n�������s���B
				m_renderer->BeginRendering();
				// �G�t�F�N�g�̕`����s���B
				m_manager->Draw();
				// �G�t�F�N�g�̕`��I���������s���B
				m_renderer->EndRendering();
			}

		}
	}


	//�v���C���[���S�[���ɂ��ǂ蒅������
	void Player::OnAttack() {
		//auto ptrTrans = GetComponent<Transform>();
		//Vec3 pos = ptrTrans->GetPosition();
		//if (pos.x < -45.0f) {
		//	PostEvent(0.0f, GetThis<Player>(), App::GetApp()->GetScene<Scene>(), L"ToClearStage");
		//}

		auto ptrDraw = GetComponent<BcPNTnTBoneModelDraw>();
		float elapsedTime = App::GetApp()->GetElapsedTime();
		auto now = ptrDraw->UpdateAnimation(elapsedTime);

		auto action = ptrDraw->GetCurrentAnimation();

		if (action == L"ActionPull") {

			if (ptrDraw->IsTargetAnimeEnd()) {
				//ActionPull�̂Ƃ�����if���ɓ�������AChangeCurrentAnimation��ActionPuh�ɂ���
				ptrDraw->ChangeCurrentAnimation(L"ActionPush");

				auto ptrXA = App::GetApp()->GetXAudio2Manager();
				//�T�E���h�̍Đ�
				ptrXA->Start(L"Hammer", 0, 0.f);
			}
		}
		else {
			if (now) {
				ptrDraw->ChangeCurrentAnimation(L"Default");
				auto ptrXA = App::GetApp()->GetXAudio2Manager();
				ptrXA->Stop(m_BGM);

				moveStop = 1.0f;//�ړ���~����
			}
		}
	}
	//�v���C���[��Enemy�ɓ���������
	void Player::OnCollisionEnter(shared_ptr<GameObject>& Other) {

		auto ptr = dynamic_pointer_cast<EnemyObject>(Other);
		if (ptr) {
			PostEvent(0.0f, GetThis<Player>(), App::GetApp()->GetScene<Scene>(), L"ToGameOverStage");
		}
		auto ptr1 = dynamic_pointer_cast<ExitWall>(Other);
		if (ptr1) {
			PostEvent(0.0f, GetThis<Player>(), App::GetApp()->GetScene<Scene>(), L"ToClearStage");
		}

		

	}

	//B�{�^��
	void Player::OnPushX() {
		auto Shitem = GetStage()->GetSharedGameObject<Myitem1>(L"Myitem1");
		if (itemCount == 1) {
			Shitem->SetDrawActive(false);
			speed2 = 2;
			itemCount = 0;

		}
	}
	//�v���C���[���S�[���ɂ��ǂ蒅������
	void Player::OnUpdate2() {
		//auto ptrTrans = GetComponent<Transform>();
		//Vec3 pos = ptrTrans->GetPosition();
		//if (pos.x < -45.0f) {
		//	PostEvent(0.0f, GetThis<Player>(), App::GetApp()->GetScene<Scene>(), L"ToClearStage");
		//}

		auto ptrDraw = GetComponent<BcPNTnTBoneModelDraw>();
		float elapsedTime = App::GetApp()->GetElapsedTime();
		auto now = ptrDraw->UpdateAnimation(elapsedTime);

		auto action = ptrDraw->GetCurrentAnimation();

		if (action == L"ActionPull") {

			if (ptrDraw->IsTargetAnimeEnd()) {
				//ActionPull�̂Ƃ�����if���ɓ�������AChangeCurrentAnimation��ActionPuh�ɂ���
				ptrDraw->ChangeCurrentAnimation(L"ActionPush");

				auto ptrXA = App::GetApp()->GetXAudio2Manager();
				//�T�E���h�̍Đ�
				ptrXA->Start(L"Hammer", 0, 0.5f);
			}
		}
		else {
			if (now) {
				ptrDraw->ChangeCurrentAnimation(L"Default");
				auto ptrXA = App::GetApp()->GetXAudio2Manager();
				ptrXA->Stop(m_BGM);

				moveStop = 1.0f;//�ړ���~����
			}
		}
	}
	
	void Player::OnDestroy() {
		//BGM�̃X�g�b�v
		auto PtrXA = App::GetApp()->GetXAudio2Manager();
		PtrXA->Stop(m_BGM);
	}
}
	//end basecross

