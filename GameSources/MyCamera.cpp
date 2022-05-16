#include "stdafx.h"
#include "Project.h"

namespace basecross {

	shared_ptr<GameObject> MyCamera::GetTargetObject() const {
		if (!m_TargetObject.expired()) {
			return m_TargetObject.lock();
		}
		return nullptr;
	}

	void MyCamera::SetTargetObject(const shared_ptr<GameObject>&Obj) {
			m_TargetObject = Obj;
		}

	// �J����
	void MyCamera::OnUpdate()
	{
		auto& app = App::GetApp();

		float delta = app->GetElapsedTime();

		auto& device = app->GetInputDevice();
		const auto& pad = device.GetControlerVec()[0];

		//auto rotate = GetCameraObject()->GetComponent<Transform>()->GetRotation();


		// �v���C���[�̍��W���擾����
		Vec3 playerPos(0.0f); // �v���C���[�̍��W�i���j
		auto stage = app->GetScene<Scene>()->GetActiveStage(); // �X�e�[�W�I�u�W�F�N�g���擾����
		auto objs = stage->GetGameObjectVec(); // �X�e�[�W�ɒǉ�����Ă��邷�ׂẴI�u�W�F�N�g
		for (auto& obj : objs)
		{
			// �v���C���[�ւ̃L���X�g�����݂�
			auto player = dynamic_pointer_cast<Player>(obj);
			if (player)
			{
				// �L���X�g�ɐ������Ă�������W���擾����
				auto playerTrans = player->GetComponent<Transform>();
				playerPos = playerTrans->GetPosition();
				break;
			}
		}

		//auto group = GetStage()->GetSharedGameObject();


		//�J�����̃X�e�B�b�N����
		angleY += XMConvertToRadians(90.0f) * -pad.fThumbRX * delta;
		if (angleY < -XM_PIDIV4 * 3) {
			angleY = -XM_PIDIV4 * 3;//�J�����̉E��]�̌��E��]�x
		}
		if (angleY > +XM_PIDIV4 * 3) {
			angleY = +XM_PIDIV4 * 3;//�J�����̍���]�̌��E��]�x
		}

		auto eye = playerPos + Vec3(cosf(angleY), 0.0f, sinf(angleY)) * distance; // �v���C���[�̍��W�𒆐S�ɁAangleY����荞�ށi�v���C���[����̋�����distance�j
		eye.y = 2.0f;
		playerPos.y = 0.5f;

		SetEye(eye);
		SetAt(playerPos); // �v���C���[�𒆎~����悤�ɂ���
		//�R���g���[���̎擾
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();

		//auto rot = GetRot;

		//B�{�^��
		if (cntlVec[0].wButtons & XINPUT_GAMEPAD_B) {

			auto CameraAngleY = XM_PI;

			auto eye = playerPos + Vec3(cosf(CameraAngleY), 0.0f, sinf(0.0f)) * distance;
			eye.y = 2.0f;
			SetEye(eye);
		}
	}
}
//end basecross