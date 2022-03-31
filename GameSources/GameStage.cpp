/*!
@file GameStage.cpp
@brief �Q�[���X�e�[�W����
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	�Q�[���X�e�[�W�N���X����
	//--------------------------------------------------------------------------------------
	void GameStage::CreateViewLight() {
		const Vec3 eye(0.0f, 5.0f, -5.0f);
		const Vec3 at(0.0f);
		auto PtrView = CreateView<SingleView>();

		//�r���[�̃J�����̐ݒ�
		auto PtrCamera = ObjectFactory::Create<MyCamera>();
		PtrView->SetCamera(PtrCamera);
		PtrCamera->SetEye(eye);
		PtrCamera->SetAt(at);

		//�}���`���C�g�̍쐬
		auto PtrMultiLight = CreateLight<MultiLight>();

		//�f�t�H���g�̃��C�e�B���O���w��
		PtrMultiLight->SetDefaultLighting();
	}

	void GameStage::CreatestageObject() {
		//CSV�̍s�P�ʂ̔z��
		vector<wstring>LineVec;
		//0�Ԗڂ̃J������L"stageObject"�ł���s�𔲂��o��
		m_CsvC.GetSelect(LineVec, 0, L"stageObject");
		for (auto& v : LineVec) {
			//�g�[�N���i�J�����j�̔z�u
			vector<wstring>Tokens;
			//�g�[�N���i�J�����j�P�ʂŕ�����𒊏o�iL','�j
			Util::WStrToTokenVector(Tokens, v, L',');
			//�g�[�N���i�J�����j���X�P�[���A��]�A�ʒu�ɓǂݍ���
			Vec3 Scale(
				(float)_wtof(Tokens[1].c_str()),
				(float)_wtof(Tokens[2].c_str()),
				(float)_wtof(Tokens[3].c_str())

			);
			Vec3 Rot;
			//��]�́uXM_PLDIV2�v�̕�����ɂȂ��Ă���ꍇ������
			Rot.x = (Tokens[4] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[4].c_str());
			Rot.y = (Tokens[5] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[5].c_str());
			Rot.z = (Tokens[6] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[6].c_str());

			Vec3 Pos(
				(float)_wtof(Tokens[7].c_str()),
				(float)_wtof(Tokens[8].c_str()),
				(float)_wtof(Tokens[9].c_str())
			);
			//�e�l���������̂ŃI�u�W�F�N�g�̍쐬
			AddGameObject<stageObject>(Scale, Rot, Pos, 1.0f, 1.0f, Tokens[10]);
		}
	}

	void GameStage::CreateWall() {
		AddGameObject<Wall>(Vec3(10.0f, 10.0f, 1.0f), Quat(), Vec3(0.0f, 1.0f, 3.0f));
	}
	//�v���C���[�̍쐬
	void GameStage::CreatePlayer() {
		//�v���[���[�̍쐬
		auto PlayerPtr = AddGameObject<Player>();
		//�V�F�A�z��Ƀv���C���[��ǉ�
		SetSharedGameObject(L"Player", PlayerPtr);
	}
	void GameStage::OnCreate() {
		try {

			//�����v�Z�L��
			SetPhysicsActive(true);

			// �u�A�v���v�I�u�W�F�N�g�̃C���X�^���X���擾����i�C���X�^���X�F�N���X�̎��ԁA�I�u�W�F�N�g�w���̃I�u�W�F�N�g�̂��Ɓj
			auto& app = App::GetApp();
			wstring DataDir;
			App::GetApp()->GetDataDirectory(DataDir);
			//CSV�t�@�C�����̓ǂݍ���C
			m_CsvC.SetFileName(DataDir + L"stageObject.csv");
			m_CsvC.ReadCsv();

			//�r���[�ƃ��C�g�̍쐬
			CreateViewLight();

			// �v���C���[�I�u�W�F�N�g���X�e�[�W�ɒǉ�����
			//AddGameObject<Player>(); // �w��̃Q�[���I�u�W�F�N�g�𐶐����ăX�e�[�W�ɒǉ����A���̃|�C���^��Ԃ�

			//�v���[���[�̍쐬
			CreatePlayer();

			AddGameObject<EnemyObject>();
			//�I�u�W�F�N�g�̒ǉ�
			CreatestageObject();
			//
			CreateWall();
		}
		catch (...) {
			throw;
		}
	}
	void GameStage::OnUpdate() {
		//�R���g���[���`�F�b�N���ē��͂�����΃R�}���h�Ăяo��
		m_InputHandler.PushHandle(GetThis<GameStage>());
	}

	void GameStage::ToObjCamera() {
		auto ptrBoss = GetSharedGameObject<Boss>(L"Boss");
		//ObjCamera�ɕύX
		auto ptrCameraman = GetSharedGameObject<Cameraman>(L"Cameraman");
		auto ptrObjCamera = dynamic_pointer_cast<ObjCamera>(m_ObjCameraView->GetCamera());
		if (ptrObjCamera) {
			ptrObjCamera->SetCameraObject(ptrCameraman);
			ptrObjCamera->SetTargetObject(ptrBoss);
			//m_ObjCameraView���g��
			SetView(m_ObjCameraView);
			m_CameraSelect = CameraSelect::objCamera;
		}
	}
	void GameStage::ToMyCamera() {
		auto ptrPlayer = GetSharedGameObject<Player>(L"Player");
		//MyCamera�ɕύX
		auto ptrMyCamera = dynamic_pointer_cast<MyCamera>(m_MyCameraView->GetCamera());
		if (ptrMyCamera) {
			ptrMyCamera->SetTargetObject(ptrPlayer);
			//m_MyCameraView���g��
			SetView(m_MyCameraView);
			m_CameraSelect = CameraSelect::myCamera;
		}
	}


	//B�{�^���J�����̕ύX
	void GameStage::OnPushB() {
		switch (m_CameraSelect) {
		case CameraSelect::myCamera:
		{
			ToObjCamera();
		}
		break;
		case CameraSelect::objCamera:
		{
			ToMyCamera();
		}
		break;
		}
	}

}
//end basecross
