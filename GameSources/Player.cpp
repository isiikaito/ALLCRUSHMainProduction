/*!
@file Player.cpp
@brief �v���C���[�Ȃǎ���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{
	void Player::OnCreate()
	{
		// �I�u�W�F�N�g�̌����ڂ����肷��h���[�R���|�[�l���g���u�ǉ��v����
		auto drawComp = AddComponent<PNTStaticDraw>(); // �V�K�ŃR���|�[�l���g��ǉ�����
		drawComp->SetMeshResource(L"DEFAULT_CUBE"); // �`���ݒ�

				// �g�����X�t�H�[���R���|�[�l���g���u�擾�v����i�g�����X�t�H�[�������͏��߂���ǉ�����Ă���j
		auto transComp = GetComponent<Transform>(); // ���łɒǉ�����Ă���R���|�[�l���g���擾����
		transComp->SetPosition(-2.0f, 0.5f, 0.0f);


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

		auto ptrTarget = m_TargetObject.lock();
		if (pad.wPressedButtons & XINPUT_GAMEPAD_LEFT_SHOULDER)
		{
			auto pos = ptrTarget->GetComponent<Transform>()->GetPosition();
			SetAt(pos);
		}
	}

}
//end basecross

