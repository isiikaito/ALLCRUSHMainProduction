/*!
@file Player.cpp
@brief �v���C���[�Ȃǎ���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void Player::OnCreate()
	{

		//�����ʒu�Ȃǂ̐ݒ�
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(0.1f,0.1f, 0.1f);
		ptrTrans->SetRotation(0.0f, 0.0f, 0.0f);
		ptrTrans->SetPosition(40.0f, 0.25f, 0.0f);



		//CollisionSphere�Փ˔����t����
		auto ptrColl = AddComponent<CollisionSphere>();
		/*ptrColl->SetDrawActive(true);*/
		//�Փ˔����\��
		/*ptrColl->SetDrawActive(true);*/
		Mat4x4 spanMat; // ���f���ƃg�����X�t�H�[���̊Ԃ̍����s��
		spanMat.affineTransformation(
			Vec3(1.0f, 1.0f, 1.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, XM_PI * -0.5f, 0.0f),
			Vec3(0.0f, -0.5f, 0.0f)
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
		position += moveDir * speed * delta; // �f���^�^�C�����|���āu�b�ԁv�̈ړ��ʂɕϊ�����



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

		if (action != L"ActionPull") {
			ptrDraw->ChangeCurrentAnimation(L"ActionPull");			

			auto ptrXA = App::GetApp()->GetXAudio2Manager();
			ptrXA->Stop(m_BGM);//bgm(�����̒�~)

			moveStop = 0.0f;//�ړ��̒�~
		}

		SPHERE playerSp(position, 2.0f);
		auto group = GetStage()->GetSharedObjectGroup(L"Wall_Group");
		auto vec = group->GetGroupVector();
		for (auto& v : vec) {
			auto shPtr = v.lock();
			Vec3 ret;
			auto ptrWall = dynamic_pointer_cast<Wall>(shPtr);
			 
			if (ptrWall) {
				auto WallObb = ptrWall->GetComponent<CollisionObb>()->GetObb();
				if (/*�߂Â�����*/
					HitTest::SPHERE_OBB(playerSp, WallObb, ret)) { 
					//�ǂƂ̋�����2.0�ȉ��ɂȂ���
					auto ctrlVec = App::GetApp()->GetInputDevice().GetControlerVec();
					if (ctrlVec[0].wButtons & XINPUT_GAMEPAD_A) {
						//�R���g���[���̃{�^����������Ă�����AshPtr������
						GetStage()->RemoveGameObject<Wall>(shPtr);
					}
				}
			}
		}

		//auto group1 = GetStage()->GetSharedObjectGroup(L"Obstacle1_Group1");
		//auto vec1 = group1->GetGroupVector();
		//for (auto& v1 : vec1) {
		//	auto shPtr = v1.lock();
		//	Vec3 ret;
		//	auto ptrObstacle1 = dynamic_pointer_cast<Obstacle1>(shPtr);

		//	if (ptrObstacle1) {
		//		auto Obstacle1Obb = ptrObstacle1->GetComponent<CollisionObb>()->GetObb();
		//		if (/*�߂Â�����*/
		//			HitTest::SPHERE_OBB(playerSp, Obstacle1Obb, ret)) {
		//			//�ǂƂ̋�����2.0�ȉ��ɂȂ���
		//			auto ctrlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		//			if (ctrlVec[0].wButtons & XINPUT_GAMEPAD_A) {
		//				//�R���g���[���̃{�^����������Ă�����AshPtr������
		//				GetStage()->RemoveGameObject<Obstacle1>(shPtr);
		//			}
		//		}
		//	}
		//}
		//auto grav = GetComponent<Gravity>();
		//grav->StartJump(Vec3(0, 4.0f, 0));
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

		//�A�C�e���̕\��
		itemCount = 0;
		auto ptr3 = dynamic_pointer_cast<Obstacle1>(Other);
		if (ptr3) {	
			//Myitem1cpp�Őݒ�ǂݍ��݂��������������œǂݍ���
			auto Shitem = GetStage()->GetSharedGameObject<Myitem1>(L"Myitem1");
			Shitem->SetDrawActive(true);
			itemCount=1;
			/*drawPtr->SetMeshResource(L"SHIELD_TX");*/
			{
             //SetDrawActive(true);
			}
			
		}
		
	}

    //B�{�^��
    void Player::OnPushX() {
	     auto Shitem = GetStage()->GetSharedGameObject<Myitem1>(L"Myitem1");
		 if (itemCount == 1) {
			 Shitem->SetDrawActive(false);
			 itemCount = 0;
		}

	}
	void Player::OnDestroy() {
		//BGM�̃X�g�b�v
		auto PtrXA = App::GetApp()->GetXAudio2Manager();
		PtrXA->Stop(m_BGM);
	}

}
	//end basecross

