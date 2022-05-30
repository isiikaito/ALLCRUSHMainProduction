#include "stdafx.h"
#include "Project.h"

namespace basecross {

	shared_ptr<GameObject> MyCamera::GetTargetObject() const {
		if (!m_TargetObject.expired()) {
			return m_TargetObject.lock();
		}
		return nullptr;
	}

	void MyCamera::SetTargetObject(const shared_ptr<GameObject>& Obj) {
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
		Vec3 pillarPos(0.0f);
		int EnemySetDrawActiveCount(0);
		int PillarCount(0);
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
				PillarCount = player->GetPillarCount();
				player->SetPillarCount(PillarCount);
				break;
			}

			// ���ւ̃L���X�g�����݂�
			auto pillar = dynamic_pointer_cast<Pillar>(obj);
			if (pillar)
			{
				// �L���X�g�ɐ������Ă�������W���擾����
				auto pillarTrans = pillar->GetComponent<Transform>();
				pillarPos = pillarTrans->GetPosition();
				break;
			}
			//�{�X�ւ̃L���X�g�����݂�
			auto Enemy = dynamic_pointer_cast<EnemyObject>(obj);
			if (Enemy)
			{
            EnemySetDrawActiveCount = Enemy->GetEnemySetDrawActiveCount();
			Enemy->SetEnemySetDrawActiveCount(EnemySetDrawActiveCount);
			break;
			}
			
		}

		auto CameraAngleY = XM_PI;

		auto eye = playerPos + Vec3(cosf(CameraAngleY), 0.0f, sinf(0.0f)) * distance;
		eye.y = 2.0f;
		playerPos.y = 0.5f;

		SetEye(eye);
		SetAt(playerPos); // �v���C���[�𒆎~����悤�ɂ���

		//�v���C���[�ƒ��̋���
		PPdistance = playerPos.x - pillarPos.x;
		//�v���C���[�ƒ��̈ʒu�����̋����ɂȂ�����U��Ԃ�
		
		if (m_Turn==0)
		{
			if (PPdistance < -75)
			{
				EnemySetDrawActiveCount = 0;
				auto CameraAngleY = XM_PI;

				auto eye = playerPos + Vec3(cosf(CameraAngleY), 0.0f, sinf(0.0f)) * distance;
				eye.y = 2.0f;
				SetEye(eye);


			}
		}
				
		//������ꂽ��
		if (PillarCount == 1)
		{

			//elapsedTime���擾���邱�Ƃɂ�莞�Ԃ��g����
			float elapsedTime = App::GetApp()->GetElapsedTime();
			//���Ԃ�ϐ��ɑ���
			m_TurnTime += elapsedTime;
			//�������Ă����b���
			if (m_TurnTime >2&&m_TurnTime<2.1)
			{
				EnemySetDrawActiveCount = 1;
				//�J���������ʂ�����
				auto eye = playerPos + Vec3(cosf(angleY), 0.0f, sinf(angleY)) * distance; // �v���C���[�̍��W�𒆐S�ɁAangleY����荞�ށi�v���C���[����̋�����distance�j
				eye.y = 2.0f;
				playerPos.y = 0.5f;

				m_Turn = 1;
				SetEye(eye);
				SetAt(playerPos); // �v���C���[�𒆎~����悤�ɂ���
				
			}
			
		}






	}

	//--------------------------------------------------------------------------------------
	//	�I�[�v�j���O�J�����i�R���|�[�l���g�ł͂Ȃ��j
	//--------------------------------------------------------------------------------------
	OpeningCamera::OpeningCamera() :
		Camera()
	{}
	OpeningCamera::~OpeningCamera() {}

	void OpeningCamera::OnUpdate() {
		auto ptrOpeningCameraman = dynamic_pointer_cast<OpeningCameraman>(GetCameraObject());
		if (ptrOpeningCameraman) {
			auto pos = ptrOpeningCameraman->GetAtPos();
			SetAt(pos);
		}
		Camera::OnUpdate();
	}

	//--------------------------------------------------------------------------------------
	//	�G���f�B���O�J�����i�R���|�[�l���g�ł͂Ȃ��j
	//--------------------------------------------------------------------------------------
	//EndingCamera::EndingCamera() :
	//	Camera()
	//{}
	//EndingCamera::~EndingCamera() {}

	//void EndingCamera::OnUpdate() {
	//	auto ptrEndingCameraman = dynamic_pointer_cast<EndingCameraman>(GetCameraObject());
	//	if (ptrEndingCameraman) {
	//		auto pos = ptrEndingCameraman->GetAtPos();
	//		SetAt(pos);
	//	}
	//	Camera::OnUpdate();
	//}

	//--------------------------------------------------------------------------------------
	//	�I�u�W�F�N�g�J�����i�R���|�[�l���g�ł͂Ȃ��j
	//--------------------------------------------------------------------------------------
	//�\�z�Ɣj��
	ObjCamera::ObjCamera() :
		Camera()
	{}
	ObjCamera::~ObjCamera() {}

	void ObjCamera::SetTargetObject(const shared_ptr<GameObject>& Obj) {
		m_TargetObject = Obj;
	}

	void ObjCamera::OnUpdate() {
		auto ptrTarget = m_TargetObject.lock();
		if (ptrTarget) {
			auto pos = ptrTarget->GetComponent<Transform>()->GetPosition();
			pos.y += 1.0f;
			SetAt(pos);
		}
		Camera::OnUpdate();

	}
}

//end basecross