/*!
@file Player.cpp
@brief �v���C���[�Ȃǎ���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{
	void Player::OnCreate()
	{
		//�����ʒu�Ȃǂ̐ݒ�
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(0.5f, 0.5f, 0.5f);
		ptrTrans->SetRotation(0.0f, 0.0f, 0.0f);
		ptrTrans->SetPosition(0.0f, 0.25f, 0.0f);

		//CollisionSphere�Փ˔����t����
		auto ptrColl = AddComponent<CollisionSphere>();

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
		ptrShadow->SetMultiMeshResource(L"Object_WalkAnimation_MESH");
		ptrShadow->SetMeshToTransformMatrix(spanMat);

		//�`��R���|�[�l���g�̐ݒ�
		auto ptrDraw = AddComponent<BcPNTnTBoneModelDraw>();
		ptrDraw->SetFogEnabled(true);
		//�`�悷�郁�b�V����ݒ�
		ptrDraw->SetMultiMeshResource(L"Object_WalkAnimation_MESH_WITH_TAN");
		ptrDraw->SetNormalMapTextureResource(L"OBJECT_NORMAL_TX");
		ptrDraw->SetMeshToTransformMatrix(spanMat);
		ptrDraw->AddAnimation(L"Default", 0, 30, true, 30.0f);
		ptrDraw->ChangeCurrentAnimation(L"Default");
	}

	void Player::OnUpdate()
	{
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
		auto mainCamera = dynamic_pointer_cast<MainCamera>(camera);
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

		speed = MaxMoveSpeed * moveDir.length(); // �ő呬�~�X�e�B�b�N�x�N�g���̑傫��
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
		}

		//�A�j���V����
		auto ptrDraw = GetComponent<BcPNTnTBoneModelDraw>();
		float elapsedTime = App::GetApp()->GetElapsedTime();
		ptrDraw->UpdateAnimation(elapsedTime);

	}

}
//end basecross

