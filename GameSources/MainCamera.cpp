#include "stdafx.h"
#include "Project.h"

namespace basecross {

	void MainCamera::OnUpdate()
	{
		auto& app = App::GetApp();

		float delta = app->GetElapsedTime();

		auto& device = app->GetInputDevice();
		const auto& pad = device.GetControlerVec()[0];

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

		angleY += XMConvertToRadians(90.0f) * -pad.fThumbRX * delta;

		auto eye = playerPos + Vec3(cosf(angleY), 0.0f, sinf(angleY)) * distance; // �v���C���[�̍��W�𒆐S�ɁAangleY����荞�ށi�v���C���[����̋�����distance�j
		eye.y = 2.0f;

		SetEye(eye);
		SetAt(playerPos); // �v���C���[�𒆎~����悤�ɂ���
	}
}
