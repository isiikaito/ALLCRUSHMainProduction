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
		//m_manager->GetCameraCullingMaskToShowAllEffects();
		//m_manager->CreateCullingWorld(10, 10, 10, 5);

		// ���_�ʒu���m��
		//auto g_position = ::Effekseer::Vector3D(10.0f, 5.0f, 20.0f);
		auto g_position = ::Effekseer::Vector3D(0.0f, 0.0f, -5.0f);

		// ���e�s���ݒ�
		float w = (float)App::GetApp()->GetGameWidth();
		float h = (float)App::GetApp()->GetGameHeight();
		auto cameraTgt = OnGetDrawCamera();
		auto eye = cameraTgt->GetEye();
		cameraTgt->SetEye(eye);
		auto at = cameraTgt->GetAt();
		cameraTgt->SetAt(at);
		auto up = cameraTgt->GetUp();
		cameraTgt->SetUp(up);
		auto ne = cameraTgt->GetNear();
		auto fa = cameraTgt->GetFar();
		auto fovY = cameraTgt->GetFovY();

		m_renderer->SetProjectionMatrix(::Effekseer::Matrix44().PerspectiveFovRH(
			fovY, w / h, ne, fa));
		 //�J�����s���ݒ�
		//m_renderer->SetCameraMatrix(
		//	::Effekseer::Matrix44().LookAtRH(::Effekseer::Vector3D(eye.x,eye.y,eye.z), ::Effekseer::Vector3D(at.x, at.y, at.z), ::Effekseer::Vector3D(up.x, up.y, up.z)));
		m_renderer->SetCameraMatrix(
			::Effekseer::Matrix44().LookAtRH(g_position, ::Effekseer::Vector3D(at.x, at.y, at.z), ::Effekseer::Vector3D(up.x, up.y, up.z)));
		m_renderer->SetCameraParameter(::Effekseer::Vector3D(eye.x,eye.y,eye.z),::Effekseer::Vector3D(g_position));
		//m_renderer->SetCameraMatrix(
		//	::Effekseer::Matrix44().LookAtRH(g_position, ::Effekseer::Vector3D(0.0f, 0.0f, 0.0f), ::Effekseer::Vector3D(0.0f, 1.0f, 0.0f)));

		wstring dataDir;
		App::GetApp()->GetDataDirectory(dataDir);
		dataDir += L"effect\\";
		//wstring wstrEfk = dataDir + L"Laser01.efk";
		//wstring wstrEfk = dataDir + L"BrakeSmoke.efkefc";
		wstring wstrEfk = dataDir + L"ImpactDamage.efkefc";

		m_effect = ::Effekseer::Effect::Create(m_manager, (const char16_t*)wstrEfk.c_str());

	}

	void Player::CreateEffect1() {
		auto d3D11Device = App::GetApp()->GetDeviceResources()->GetD3DDevice();
		auto d3D11DeviceContext = App::GetApp()->GetDeviceResources()->GetD3DDeviceContext();;
		// �G�t�F�N�g�̃����_���[�̍쐬
		m_renderer1 = ::EffekseerRendererDX11::Renderer::Create(d3D11Device, d3D11DeviceContext, 8000);


		// �G�t�F�N�g�̃}�l�[�W���[�̍쐬
		m_manager1 = ::Effekseer::Manager::Create(8000);
		// �`�惂�W���[���̐ݒ�
		m_manager1->SetSpriteRenderer(m_renderer1->CreateSpriteRenderer());
		m_manager1->SetRibbonRenderer(m_renderer1->CreateRibbonRenderer());
		m_manager1->SetRingRenderer(m_renderer1->CreateRingRenderer());
		m_manager1->SetTrackRenderer(m_renderer1->CreateTrackRenderer());
		m_manager1->SetModelRenderer(m_renderer1->CreateModelRenderer());

		// �e�N�X�`���A���f���A�J�[�u�A�}�e���A�����[�_�[�̐ݒ肷��B
		// ���[�U�[���Ǝ��Ŋg���ł���B���݂̓t�@�C������ǂݍ���ł���B
		m_manager1->SetTextureLoader(m_renderer1->CreateTextureLoader());
		m_manager1->SetModelLoader(m_renderer1->CreateModelLoader());
		m_manager1->SetMaterialLoader(m_renderer1->CreateMaterialLoader());
		m_manager1->SetCurveLoader(Effekseer::MakeRefPtr<Effekseer::CurveLoader>());

		// ���_�ʒu���m��
		auto g_position = ::Effekseer::Vector3D(5.0f, 3.0f, 5.0f);

		// ���e�s���ݒ�
		float w = (float)App::GetApp()->GetGameWidth();
		float h = (float)App::GetApp()->GetGameHeight();
		auto cameraTgt = OnGetDrawCamera();

		auto eye = cameraTgt->GetEye();
		auto at = cameraTgt->GetAt();
		auto up = cameraTgt->GetUp();
		auto ne = cameraTgt->GetNear();
		auto fa = cameraTgt->GetFar();
		auto fovY = cameraTgt->GetFovY();

		m_renderer->SetProjectionMatrix(::Effekseer::Matrix44().PerspectiveFovRH(
			fovY, w / h, ne, fa));
		// �J�����s���ݒ�
		m_renderer->SetCameraMatrix(
			::Effekseer::Matrix44().LookAtRH(g_position, ::Effekseer::Vector3D(0.0f, 0.0f, 0.0f), ::Effekseer::Vector3D(0.0f, 1.0f, 0.0f)));

		wstring dataDir1;
		App::GetApp()->GetDataDirectory(dataDir1);
		dataDir1 += L"effect\\";

		wstring wstrEfk1 = dataDir1 + L"SpeedUp.efkefc";

		m_effect1 = ::Effekseer::Effect::Create(m_manager1, (const char16_t*)wstrEfk1.c_str());

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
		/*ptrColl->SetDrawActive(true);*/
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
		ptrDraw->AddAnimation(L"Move", 10, 30, true,50.0f);
		ptrDraw->AddAnimation(L"Action", 40, 35, false, 35.0f);
		ptrDraw->AddAnimation(L"ActionPull", 40, 20, false, 35.0f);
		ptrDraw->AddAnimation(L"ActionPush", 60, 10, false, 35.0f);
		ptrDraw->AddAnimation(L"ActionEnd", 70, 5, false, 35.0f);
		ptrDraw->AddAnimation(L"GameOver", 70, 10, false, 20.0f);
		ptrDraw->ChangeCurrentAnimation(L"Default");

		//�����������
		auto ptrString = AddComponent<StringSprite>();
		ptrString->SetText(L"");
		ptrString->SetTextRect(Rect2D<float>(16.0f, 16.0f, 640.0f, 480.0f));


		CreateEffect();
		CreateEffect1();


		
	}


	void Player::OnUpdate()

	{  
		

		//�A�j���[�V����
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
		auto Rotation = transComp->GetRotation();
		auto scale = transComp->GetScale();
		// �v���C���[�̈ړ�
		position += moveDir * speed * delta * speed2; // �f���^�^�C�����|���āu�b�ԁv�̈ړ��ʂɕϊ�����


        //�{�X�̍��W�擾
		auto ptrEnemy = GetStage()->GetSharedGameObject<EnemyObject>(L"EnemyObject");
		//�N���X�ɂ́i�j���K�v�ł������������Ƃ��Ɩ������ǂ����ł��K�v
		auto EnemyPositon = ptrEnemy->GetComponent<Transform>()->GetPosition();


		//�{�X�ƃv���C���[�����̋����ɒB������
		PBdistance = position.x - EnemyPositon.x;
		if (PBdistance>-15)
		{
			float elapsedTime = App::GetApp()->GetElapsedTime();
			if (move != L"GameOver") {
				ptrDraw->ChangeCurrentAnimation(L"GameOver");
				transComp->SetRotation(0.0f, XMConvertToRadians(180.0f), 0.0f);
				moveStop = false;
			}
		}


		//�������Ă��Ȃ��Ƃ�
		if (PillarCount == 0)
		{
			//���̍��W�擾
			auto ptrPillar = GetStage()->GetSharedGameObject<Pillar>(L"Pillar");
			//�N���X�ɂ́i�j���K�v�ł������������Ƃ��Ɩ������ǂ����ł��K�v
			auto PillarPositon = ptrPillar->GetComponent<Transform>()->GetPosition();

			//���ƃv���C���[�̋���
			PPdistance = position.x - PillarPositon.x;
			if (PPdistance < 5)
			{
				moveStop = 0.0f;//�ړ��̒�~
				position.x = -80;
				position.z = 1;
				Rotation.y = 90;
				speed = 0;


			}
		}
		



	
           
            

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
				moveStop = true;//�ړ���~����
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

		if (action != L"ActionPull") {
			ptrDraw->ChangeCurrentAnimation(L"ActionPull");

			auto ptrXA = App::GetApp()->GetXAudio2Manager();
			ptrXA->Stop(m_BGM);//bgm(�����̒�~)

			moveStop = false;//�ړ��̒�~

				}

			}

	//�v���C���[���S�[���ɂ��ǂ蒅������
	void Player::OnAttack() {
	

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
				ptrXA->Start(L"Hammer", 0, 0.0f);

				moveStop = false;//�ړ��̒�~
			}
		}
		else {
			if (now) {
				ptrDraw->ChangeCurrentAnimation(L"Default");
				auto ptrXA = App::GetApp()->GetXAudio2Manager();
				ptrXA->Stop(m_BGM);

				moveStop = true;//�ړ���~����
			}
		}
	}
	//�v���C���[��Enemy�ɓ���������
	void Player::OnCollisionEnter(shared_ptr<GameObject>& Other) {

		auto ptr = dynamic_pointer_cast<EnemyObject>(Other);
		if (ptr) {

		}
		auto ptr1 = dynamic_pointer_cast<ExitWall>(Other);
		if (ptr1) {
			ExitCount = 1;
		}

		

	}
	void Player::OnPushY() {
		//�Q�[�W�����܂�����
		if (PowerCount >= 3)
		{
			Power = 0;

		}
	}

	//X�{�^��
	void Player::OnPushX() {
		auto Shitem = GetStage()->GetSharedGameObject<Myitem1>(L"Myitem1");
		auto PlayerPos = GetComponent<Transform>()->GetPosition();
		auto SpeedUpSound = App::GetApp()->GetXAudio2Manager();
		if (itemCount == 1) {
			Shitem->SetDrawActive(false);
			//�T�E���h�̍Đ�
			SpeedUpSound->Start(L"SpeedUp", 0, 0.5f);
			speed2 = 2;
			itemCount = 0;
			if (!m_isPlay1) {
				//m_handle1 = m_manager1->Play(m_effect1,PlayerPos.x + 5, PlayerPos.y +0.5, PlayerPos.z-0.5);
				m_handle1 = m_manager1->Play(m_effect1,PlayerPos.x + 5, PlayerPos.y +0.25, PlayerPos.z - 1.0);
				//m_handle1 = m_manager1->Play(m_effect1  ,0,0,0);
				m_isPlay1 = true;
			}
		}
		
		
	}
	//�v���C���[���S�[���ɂ��ǂ蒅������
	void Player::OnUpdate2() {

		auto ptrXA = App::GetApp()->GetXAudio2Manager();
		float elapsedTime = App::GetApp()->GetElapsedTime();


		auto ptrTrans = GetComponent<Transform>();
		Vec3 pos = ptrTrans->GetPosition();
		if (pos.x < -52.0f) {
			auto ptrStage1 = GetStage()->GetSharedGameObject<Telop>(L"Telop");
			ptrStage1->SetDrawActive(true);
			// ���Ԃ̕ϐ��ɑ���
			m_TelopTime += elapsedTime;
			if (m_TelopTime >= 2.0f)
			{
				// 1�b��ɕ\�����I�t�ɂȂ�
				ptrStage1->SetDrawActive(false);

			}
		}

		// �o���e���b�v
		if (pos.x < -83.0f) {
			auto ptrStage3 = GetStage()->GetSharedGameObject<Telop3>(L"Telop3");
			ptrStage3->SetDrawActive(true);
			// ���Ԃ̕ϐ��ɑ���
			m_Telop3Time += elapsedTime;
			if (m_Telop3Time >= 2.0f)
			{
				// 1�b��ɕ\�����I�t�ɂȂ�
				ptrStage3->SetDrawActive(false);

			}
		}

		// �ǂ��󂹁I�I�e���b�v
		if (pos.x < 22.0f) {
			auto ptrStage4 = GetStage()->GetSharedGameObject<Telop4>(L"Telop4");
			ptrStage4->SetDrawActive(true);
			// ���Ԃ̕ϐ��ɑ���
			m_Telop4Time += elapsedTime;
			if (m_Telop4Time >= 2.0f)
			{
				// 1�b��ɕ\�����I�t�ɂȂ�
				ptrStage4->SetDrawActive(false);

			}
		}

		auto ptrDraw = GetComponent<BcPNTnTBoneModelDraw>();
		//float elapsedTime = App::GetApp()->GetElapsedTime();
		auto now = ptrDraw->UpdateAnimation(elapsedTime);

		auto action = ptrDraw->GetCurrentAnimation();

		if (action == L"ActionPull") {

			if (ptrDraw->IsTargetAnimeEnd()) {
				//ActionPull�̂Ƃ�����if���ɓ�������AChangeCurrentAnimation��ActionPuh�ɂ���
				ptrDraw->ChangeCurrentAnimation(L"ActionPush");
				auto transComp = GetComponent<Transform>();
				auto position = transComp->GetPosition(); // ���݂̈ʒu���W���擾����
				SPHERE playerSp(position, 2.0f);
				auto group = GetStage()->GetSharedObjectGroup(L"Wall_Group");
				auto vec = group->GetGroupVector();
				ptrXA->Start(L"Hammer", 0, 0.5f);
				moveStop = 1.0f;//�ړ���~����


				//�ǂ̔j�󏈗�
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
								//	ptrDraw->ChangeCurrentAnimation(L"ActionEnd");

								//�p���[�A�b�v���̏���
								switch (Power)
								{
								case 0:
										WallHP-=10;
									Power = 1;
									PowerCount = 0;
									Gageflash = 1;
									break;

									//�p���[�A�b�v�O�̏���
								case 1:
									WallHP -= 1;
									break;
									

								}
								
								ptrWall->SetHP(WallHP);
				//�ǂ̎c��ϋv�l�ɂ��Ă̏���
				if (WallHP >= 4)
				{
					auto ptrDraw1 = ptrWall->GetComponent<PNTStaticModelDraw>();
					ptrDraw1->SetMeshResource(L"UNBREAKWALL_MESH");
				}
				else if (WallHP >= 3)
				{
					auto ptrDraw1 = ptrWall->GetComponent<PNTStaticModelDraw>();
					ptrDraw1->SetMeshResource(L"DAMAGEWALL1_MESH");
				}
				else if(WallHP >= 2)
				{
					auto ptrDraw1 = ptrWall->GetComponent<PNTStaticModelDraw>();
					ptrDraw1->SetMeshResource(L"DAMAGEWALL2_MESH");
				}
				else if(WallHP >= 1)
				{
					auto ptrDraw1 = ptrWall->GetComponent<PNTStaticModelDraw>();
					ptrDraw1->SetMeshResource(L"DAMAGEWALL3_MESH");
				}

								if (WallHP <= 0)
								{
								ptrXA->Start(L"BrakeWall", 0, 0.5f);
								GetStage()->RemoveGameObject<Wall>(shPtr);
								PowerCount +=1;
								if (PowerCount >= 3)
								{
									PowerCount = 3;
								}
								
								}

								auto elps = App::GetApp()->GetElapsedTime();
								SoundTime += elps;
								if (WallHP >= 1)
								{
								auto AttackSound = App::GetApp()->GetXAudio2Manager();
								AttackSound->Start(L"AttackWall", 0, 0.5f);
									return;
								}


								if (WallHP <= 0)
								{
									if (!m_isPlay) {
									auto ptrWall = dynamic_pointer_cast<Wall>(shPtr);
									auto WallPos = ptrWall->GetComponent<Transform>()->GetPosition();
									//m_manager->SetTargetLocation(m_handle, ::Effekseer::Vector3D(WallPos.x, 0, 0));
									//m_handle = m_manager->Play(m_effect, WallPos.x,0,0);

									//m_handle = m_manager->Play(m_effect,0,0,0);

									//m_isPlay = true;
									}
									auto PtrSpark = GetStage()->GetSharedGameObject<ImpactSmoke>(L"MultiSpark", false);
									if (PtrSpark) {
										auto pos = GetComponent<Transform>()->GetPosition();
										PtrSpark->GetComponent<Transform>()->SetScale(5,5,5);
										PtrSpark->InsertSpark(pos);
									}

									auto BrakeSound = App::GetApp()->GetXAudio2Manager();
									GetStage()->RemoveGameObject<Wall>(shPtr);
									//�T�E���h�̍Đ�
									BrakeSound->Start(L"BrakeWall", 0, 0.5f);
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
									//�R���g���[���̃{�^����������Ă�����AshPtr������
									GetStage()->RemoveGameObject<Obstacle1>(shPtr1);
									auto Shitem = GetStage()->GetSharedGameObject<Myitem1>(L"Myitem1");
									Shitem->SetDrawActive(true);
									itemCount = 1;
							}
						}
					}
					//���j�󏈗�
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
									GetStage()->RemoveGameObject<Pillar>(shPtr2);

									
									//���΂̏���
									Falling1 = 1;
									ptrFallingRock->SetFalling(Falling1);

									
										PillarCount = 1;
										
									
						}

					}
				}
				return;
			}
		}

		//�U������

		else if (action == L"ActionPull") {

			if (ptrDraw->IsTargetAnimeEnd()) {
				//ActionPush�̂Ƃ�����if���ɓ�������AChangeCurrentAnimation��ActionPuh�ɂ���
				ptrDraw->ChangeCurrentAnimation(L"Default");

				auto ptrXA = App::GetApp()->GetXAudio2Manager();
				//�T�E���h�̍Đ�
				ptrXA->Start(L"Hammer", 0, 0.5f);
				moveStop = true;//�ړ���~����

			}
		}
		else {
			if (now) {
				ptrDraw->ChangeCurrentAnimation(L"Default");
				ptrXA->Stop(m_BGM);

				moveStop = true;//�ړ���~����
			}
		}

		if (action == L"GameOver") {
			if (now) {
				PostEvent(0.0f, GetThis<Player>(), App::GetApp()->GetScene<Scene>(), L"ToGameOverStage");
			}
		}
		//������̕\��
		DrawStrings();
	}

	void Player::OnDraw() {
		GameObject::OnDraw();
		auto elps = App::GetApp()->GetElapsedTime();
		m_manager->Update();
		if (m_isPlay) {
			m_TotalTime += elps;
			m_manager->Update();
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
				//m_manager->DrawHandle(m_handle);
				//// �G�t�F�N�g�̕`����s���B
				m_manager->DrawBack();
				//// �G�t�F�N�g�̕`����s���B
				m_manager->DrawFront();
				// �G�t�F�N�g�̕`��I���������s���B
				m_renderer->EndRendering();
			}

		}
		//�X�s�[�h�A�b�v�G�t�F�N�g
		if (m_isPlay1) {
			m_TotalTime1 += elps;
			if (m_TotalTime >= 2.0f) {
				m_manager1->StopEffect(m_handle1);
				m_TotalTime1 = 0.0f;
				m_isPlay1 = false;
				return;
			}
			else {
				// �}�l�[�W���[�̍X�V
				m_manager1->Update();
				// ���Ԃ��X�V����
				m_renderer1->SetTime(elps);
				// �G�t�F�N�g�̕`��J�n�������s���B
				m_renderer1->BeginRendering();
				// �G�t�F�N�g�̕`����s���B
				m_manager1->Draw();
				// �G�t�F�N�g�̕`����s���B
				m_manager1->DrawBack();
				// �G�t�F�N�g�̕`����s���B
				m_manager1->DrawFront();
				// �G�t�F�N�g�̕`��I���������s���B
				m_renderer1->EndRendering();
			}

		}
	}


	//������̕\��
	void Player::DrawStrings() {
		auto pos = GetComponent<Transform>()->GetPosition();

		wstring positionStr(L"Position:\t");
		positionStr += L"X=" + Util::FloatToWStr(pos.x, 6, Util::FloatModify::Fixed) + L",\t";
		positionStr += L"Y=" + Util::FloatToWStr(pos.y, 6, Util::FloatModify::Fixed) + L",\t";
		positionStr += L"Z=" + Util::FloatToWStr(pos.z, 6, Util::FloatModify::Fixed) + L"\n";

		wstring str = positionStr;

		//������R���|�[�l���g�̎擾
		auto ptrString = GetComponent<StringSprite>();
		ptrString->SetText(str);

	}
	
	void Player::OnDestroy() {
		//BGM�̃X�g�b�v
		auto PtrXA = App::GetApp()->GetXAudio2Manager();
		PtrXA->Stop(m_BGM);
	}
}
	//end basecross

