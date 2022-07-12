/**
* @file Player.cpp
* @brief �v���C���[�N���X�̎������L�q����Ă���\�[�X�t�@�C���t�@�C��
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
//#pragma comment(lib, "Effekseer.lib")
//#pragma comment(lib, "EffekseerRendererDX11.lib")

	/** �v���C���[�̏����ʒu�Ȃǂ̐ݒ肷��֐�
	*
	*/
	void Player::OnCreate()
	{

		//�����ʒu�Ȃǂ̐ݒ�
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(0.4f, 0.4f, 0.4f);
		ptrTrans->SetRotation(0.0f, 0.0f, 0.0f);
		ptrTrans->SetPosition(40.0f, 0.25f, 0.0f);
		itemCount = 0;

		//CollisionSphere�Փ˔����t����
		AddComponent<CollisionCapsule>();
		
		Mat4x4 spanMat; // ���f���ƃg�����X�t�H�[���̊Ԃ̍����s��
		spanMat.affineTransformation(
			Vec3(0.2f, 0.2f, 0.2f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, XM_PI * -0.5f, 0.0f),
			Vec3(0.0f, -1.0f, 0.0f)
		);

		//�d�͂�����
		AddComponent<Gravity>();

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
		ptrDraw->AddAnimation(L"Move", 10, 30, true, 40.0f);
		ptrDraw->AddAnimation(L"Action", 40, 30, false, 35.0f);
		ptrDraw->AddAnimation(L"ActionPull", 40, 20, false, 35.0f);
		ptrDraw->AddAnimation(L"ActionPush", 60, 10, false, 35.0f);
		ptrDraw->AddAnimation(L"GameOver", 70, 20, false, 17.0f);
		ptrDraw->ChangeCurrentAnimation(L"Default");

		//CreateEffect();
		//CreateEffect1();

	}
	//�ǂ�j�󂷂�
	void Player::BreakWall()
	{
		auto transComp = GetComponent<Transform>();
		auto position = transComp->GetPosition(); // ���݂̈ʒu���W���擾����
		SPHERE playerSp(position, 2.0f);

		//����ǂ̃O���[�v�̎擾
		auto group = GetStage()->GetSharedObjectGroup(L"Wall_Group");
		auto vec = group->GetGroupVector();

		//�ǂ̔j�󏈗�
		for (auto& v : vec) {
			//�O���[�v�̂P�����o��
			auto shPtr = v.lock();
			Vec3 ret;
			//����ǂ̎擾
			auto ptrWall = dynamic_pointer_cast<Wall>(shPtr);
			if (ptrWall) {
				auto WallObb = ptrWall->GetComponent<CollisionObb>()->GetObb();//����ǂ̏Փ˔���擾
				auto WallHP = ptrWall->GetHP();                                //����ǂ�HP�擾
                 /*�߂Â�����*/
				if (HitTest::SPHERE_OBB(playerSp, WallObb, ret)) {
					//�ǂƂ̋�����2.0�ȉ��ɂȂ���
					auto ctrlVec = App::GetApp()->GetInputDevice().GetControlerVec();
					//�p���[�A�b�v���̏���
					switch (Power)
					{
					case 0:
						WallHP -= 10;
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
					if (WallHP <= 0)
					{
						auto ptrXA = App::GetApp()->GetXAudio2Manager();
						ptrXA->Start(L"BrakeWall", 0, 0.5f);
						GetStage()->RemoveGameObject<Wall>(shPtr);
						PowerCount += 1;
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
						auto PtrSpark = GetStage()->GetSharedGameObject<InsertEffect>(L"MultiEffect", false);
						if (PtrSpark) {
							auto pos = GetComponent<Transform>()->GetPosition();
							PtrSpark->InsertSplash(pos);
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

	}

	//����j�󂷂鏈��
	void Player::BreakPillar()
	{
		//���j�󏈗�
		auto transComp = GetComponent<Transform>();
		auto position = transComp->GetPosition(); // ���݂̈ʒu���W���擾����
		SPHERE playerSp(position, 2.0f);
		auto group2 = GetStage()->GetSharedObjectGroup(L"Pillar_Group1");
		auto vec2 = group2->GetGroupVector();
		for (auto& v2 : vec2) {
			auto shPtr2 = v2.lock();
			Vec3 ret2;
			auto ptrPillar = dynamic_pointer_cast<Pillar>(shPtr2);

			if (ptrPillar) {
				auto PillarObb = ptrPillar->GetComponent<CollisionObb>()->GetObb();
				auto ptrFallingRock = GetStage()->GetSharedGameObject<FallingRock>(L"FallingRock");
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
	}

	void Player::BreakObstacle()
	{
		auto transComp = GetComponent<Transform>();
		auto position = transComp->GetPosition(); // ���݂̈ʒu���W���擾����
		SPHERE playerSp(position, 2.0f);

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
					auto XSprite1 = GetStage()->GetSharedGameObject<XSprite>(L"XSprite");
					XSprite1->SetDrawActive(true);
					itemCount = 1;
				}
			}
		}

	}

	void Player::Enemydistance()
	{
		//�A�j���[�V����
		auto ptrDraw = GetComponent<BcPNTnTBoneModelDraw>();
		auto AnimationName = ptrDraw->GetCurrentAnimation();//���݂̃A�j���[�V���������擾����
		auto transComp = GetComponent<Transform>();
		auto position = transComp->GetPosition(); // ���݂̈ʒu���W���擾����
		auto rotation = transComp->GetRotation();
		//�{�X�̍��W�擾
		auto ptrEnemy = GetStage()->GetSharedGameObject<EnemyObject>(L"EnemyObject");
		//�N���X�ɂ́i�j���K�v�ł������������Ƃ��Ɩ������ǂ����ł��K�v
		auto EnemyPositon = ptrEnemy->GetComponent<Transform>()->GetPosition();

		//�{�X�ƃv���C���[�����̋����ɒB������
		PBdistance = position.x - EnemyPositon.x;
		if (PBdistance >= -3)
		{
			position.z = EndPos;
			transComp->SetRotation(EndAngle, 0.0f, EndAngle);

			if (AnimationName != L"GameOver") {
				ptrDraw->ChangeCurrentAnimation(L"GameOver");
				GameOver = 1;
				moveStop = false;
				if (moveStop == false)
				{
					if (m_State == GameState::Game)
					{
						m_State = GameState::Down;
					}
				}
			}
		}
	}

	//�v���C���[�ƒ��̋��������ɂȂ�����s������
	void Player::Pillardistance()
	{

	}
	void Player::OnUpdate()
	{
		auto ptrGameStage = dynamic_pointer_cast<GameStage>(GetStage());
		float elapsedTime = App::GetApp()->GetElapsedTime();
		if (elapsedTime)
		{
			m_opningStop += elapsedTime;
			if (m_opningStop >= XM_PI) {
				m_opningStop = 0;
			}
			if (ptrGameStage->GetCameraSelect() == CameraSelect::openingCamera) {
				return;
			}
			if (m_opningStop == 1)
			{
				moveStop = true;
			}
		}
		//�A�j���[�V����
		auto ptrDraw = GetComponent<BcPNTnTBoneModelDraw>();
		auto AnimationName = ptrDraw->GetCurrentAnimation();

		// �A�v���P�[�V�����I�u�W�F�N�g���擾����
		auto& app = App::GetApp();
		// �f���^�^�C�����擾����
		float delta = app->GetElapsedTime(); // �O�t���[������́u�o�ߎ��ԁv
		// �J�������擾����
		auto stage = GetStage(); // ���̃I�u�W�F�N�g���ǉ�����Ă���X�e�[�W
		auto camera = stage->GetView()->GetTargetCamera(); // �J�������擾����
		// �J�����̉�荞��
		float rad = XM_PI * 0.5f;

		// �Q�[���R���g���[���[�I�u�W�F�N�g���擾����
		auto& device = app->GetInputDevice();
		const auto& pad = device.GetControlerVec()[0]; // �[���Ԗڂ̃R���g���[���[���擾����
		moveDir = Vec3(pad.fThumbLX, 0.0f, pad.fThumbLY); // �傫���� 0.0f �` 1.0f;
		auto m = Mat3x3( // Y�����S�ŉ�]������s��
			Vec3( cosf(rad), 0.0f, sinf(rad)),   // X���̌���
			Vec3(      0.0f, 0.0f,      0.0f),   // Y���̌���
			Vec3(-sinf(rad), 0.0f,  cosf(rad))); // Z���̌���
		moveDir = moveDir * m; // �X�e�B�b�N�̓��͂�angleY���W�A����]������
		speed = MaxMoveSpeed * moveDir.length() * moveStop; // �ő呬�~�X�e�B�b�N�x�N�g���̑傫���~��~�����邩�ǂ����̔���
		moveDir.normalize(); // �ړ������𐳋K������
		auto transComp = GetComponent<Transform>();
		auto position = transComp->GetPosition(); // ���݂̈ʒu���W���擾����
		auto rotation = transComp->GetRotation();
		auto scale = transComp->GetScale();

		// �v���C���[�̈ړ�
		position += moveDir * speed * delta * speed2; // �f���^�^�C�����|���āu�b�ԁv�̈ړ��ʂɕϊ�����

		//�{�X�Ƃ̋��������ɂȂ�����s������
		Enemydistance();
		//�������Ă��Ȃ��Ƃ�
		if (PillarCount == 0)
		{
			//���̍��W�擾
			auto ptrPillar = GetStage()->GetSharedGameObject<Pillar>(L"Pillar");
			//�N���X�ɂ́i�j���K�v�ł������������Ƃ��Ɩ������ǂ����ł��K�v
			auto PillarPositon = ptrPillar->GetComponent<Transform>()->GetPosition();
			//���ƃv���C���[�̋���
			PPdistance = position.x - PillarPositon.x;
			if (PPdistance <= 5)
			{
				position.x = PillarPositon.x;
				position.z = 1;
				moveStop = false;//�ړ��̒�~
				transComp->SetRotation(XM_PI, 0.0f, XM_PI);//�v���C���[�̌�����O���ɌŒ�
				speed = 0;
				m_Event = true;
			}

		}
		if (itemCount == 2)
		{
			float elapsedTime1 = App::GetApp()->GetElapsedTime();
			itemtime += elapsedTime1;
			if (itemtime >= 4)
			{
				speed2 = 1;
			}
		}
		
		transComp->SetPosition(position); // �X�V�����l�ōĐݒ肷��
		if (speed > 0.0f) // �X�e�B�b�N���|��Ă�����E�E
		{
			float rotY = atan2f(-moveDir.z, moveDir.x); // �A�[�N�^���W�F���g���g���ƃx�N�g�����p�x�ɕϊ��ł���
			transComp->SetRotation(0.0f, rotY, 0.0f); // ���W�A���p�Őݒ�
			//�����A�j���[�V����
			if (AnimationName == L"Default") {
				ptrDraw->ChangeCurrentAnimation(L"Move");
				//�T�E���h�̍Đ�
				auto ptrXA = App::GetApp()->GetXAudio2Manager();
				m_BGM = ptrXA->Start(L"run", 0, 0.5f);
			}
		}
		else {
			//�����~�܂�A�j���[�V����
			if (AnimationName == L"Move") {
				ptrDraw->ChangeCurrentAnimation(L"Default");
				auto ptrXA = App::GetApp()->GetXAudio2Manager();
				ptrXA->Stop(m_BGM);
				//moveStop = true;//�ړ���~����
			}
		}
		//�R���g���[���`�F�b�N���ē��͂�����΃R�}���h�Ăяo��
		m_InputHandler.PushHandle(GetThis<Player>());
		//MovePlayer();
		m_InputHandler2.PushHandle(GetThis<Player>());
		if (ptrGameStage->GetCameraSelect() == CameraSelect::openingCamera) {
			return;
		}
		//�R���g���[���`�F�b�N���ē��͂�����΃R�}���h�Ăяo��
		m_InputHandler.PushHandle(GetThis<Player>());
		
		auto ptrXA = App::GetApp()->GetXAudio2Manager();
		auto AnimationNow = ptrDraw->UpdateAnimation(elapsedTime);	//���݂̃A�j���[�V�������I��������Atrue
		auto ActionName = ptrDraw->GetCurrentAnimation();

		if (ActionName == L"ActionPull") {
			if (ptrDraw->IsTargetAnimeEnd()) {
				//ActionPull�̂Ƃ�����if���ɓ�������AChangeCurrentAnimation��ActionPuh�ɂ���
				ptrDraw->ChangeCurrentAnimation(L"ActionPush");
			    ptrXA->Start(L"Hammer", 0, 0.5f);
				//�v���C���[���ǂ��󂷏���
				BreakWall();
				//�v���C���[����Q�����󂷏���
				BreakObstacle();
				//�v���C���[�������󂷏���
				BreakPillar();
				return;
			}
		}
		//�U������
		else if (ActionName == L"ActionPull") {
			if (ptrDraw->IsTargetAnimeEnd()) {
				//ActionPush�̂Ƃ�����if���ɓ�������AChangeCurrentAnimation��ActionPuh�ɂ���
				ptrDraw->ChangeCurrentAnimation(L"Default");
				auto ptrXA = App::GetApp()->GetXAudio2Manager();
				//�T�E���h�̍Đ�
				ptrXA->Start(L"Hammer", 0, 0.5f);
			}
		}
		else {
			if (AnimationNow) {
				ptrDraw->ChangeCurrentAnimation(L"Default");
				ptrXA->Stop(m_BGM);

				moveStop = true;//�ړ���~����
			}
		}
		TelopManager();
	}
	//�v���C���[��Enemy�ɓ���������
	void Player::OnCollisionEnter(shared_ptr<GameObject>& Other) {
		auto ptr = dynamic_pointer_cast<EnemyObject>(Other);
		if (ptr) {
		}
		auto ptr1 = dynamic_pointer_cast<ExitWall>(Other);
		if (ptr1) {
			SetGameState(GameState::GameExit);
		}
	}
	

	//A�{�^��
	void Player::OnPushA() 
	{
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


	
	void Player::OnPushY() {
		auto PtrSpark = GetStage()->GetSharedGameObject<InsertEffect>(L"MultiEffect", false);
		auto PowerUpSound = App::GetApp()->GetXAudio2Manager();
		//�Q�[�W�����܂�����
		if (PowerCount >= 3)
		{
			auto pos = GetComponent<Transform>()->GetPosition();
			PowerUpSound->Start(L"PowerUp", 0, 0.5f);
			Power = 0;
			PtrSpark->InsertPowerUp(pos);
		}
	}

	//X�{�^��
	void Player::OnPushX() {
		auto Shitem = GetStage()->GetSharedGameObject<Myitem1>(L"Myitem1");
		auto PlayerPos = GetComponent<Transform>()->GetPosition();
		auto SpeedUpSound = App::GetApp()->GetXAudio2Manager();

		if (itemCount == 1) {
			speed2 = 2;
			itemCount = 2;

			auto XSprite1 = GetStage()->GetSharedGameObject<XSprite>(L"XSprite");
			XSprite1->SetDrawActive(false);

			Shitem->SetDrawActive(false);
			//�T�E���h�̍Đ�
			SpeedUpSound->Start(L"SpeedUp", 0, 0.5f);

			auto PtrSpark = GetStage()->GetSharedGameObject<InsertEffect>(L"MultiEffect", false);
			if (PtrSpark) {
				auto pos = GetComponent<Transform>()->GetPosition();
				PtrSpark->InsertSpeedUp(pos);
			}
		}
		if (GetGameState() == GameState::ChangeStage) {
			PostEvent(0.0f, GetThis<Player>(), App::GetApp()->GetScene<Scene>(), L"ToTitleStage");
		}
	}
	void Player::TelopManager() {
		auto ptrTrans = GetComponent<Transform>();
		Vec3 pos = ptrTrans->GetPosition();
		float elapsedTime = App::GetApp()->GetElapsedTime();
		//�R���g���[���`�F�b�N���ē��͂�����΃R�}���h�Ăяo��
		m_InputHandler.PushHandle(GetThis<Player>());

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

	}
	void Player::OnDestroy() {
		//BGM�̃X�g�b�v
		auto PtrXA = App::GetApp()->GetXAudio2Manager();
		PtrXA->Stop(m_BGM);
	}
}
	//end basecross