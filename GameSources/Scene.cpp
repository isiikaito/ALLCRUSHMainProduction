/*!
@file Scene.cpp
@brief �V�[������
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	///	�Q�[���V�[��
	//--------------------------------------------------------------------------------------
	void Scene::CreateResourses() {
		wstring dataDir;
		//�T���v���̂��߃A�Z�b�g�f�B���N�g�����擾
		App::GetApp()->GetAssetsDirectory(dataDir);
		//�e�Q�[���͈ȉ��̂悤�Ƀf�[�^�f�B���N�g�����擾���ׂ�
		//App::GetApp()->GetDataDirectory(DataDir);
		wstring strTexture = dataDir + L"sky.jpg";
		App::GetApp()->RegisterTexture(L"SKY_TX", strTexture);
		strTexture = dataDir + L"trace.png";
		App::GetApp()->RegisterTexture(L"TRACE_TX", strTexture);
		strTexture = dataDir + L"wall.jpg";
		App::GetApp()->RegisterTexture(L"WALL_TX", strTexture);
		strTexture = dataDir + L"doukutu.png";
		App::GetApp()->RegisterTexture(L"DOUKUTU_TX", strTexture);
		strTexture = dataDir + L"Titlle.jpg";
		App::GetApp()->RegisterTexture(L"TITLLE_TX", strTexture);

		strTexture = dataDir + L"�Q�[���I�[�o�[.jpg";
		App::GetApp()->RegisterTexture(L"GAMEOVER_TX", strTexture);

		//���f��
		//�{�[�����f���̒ʏ탊�\�[�X
		auto multiModelMesh = MeshResource::CreateBoneModelMesh(dataDir, L"Walkman.bmf");
		App::GetApp()->RegisterResource(L"Object_WalkAnimation_MESH", multiModelMesh);

		//�{�[�����f���̃^���W�F���g�t�����\�[�X
		multiModelMesh = MeshResource::CreateBoneModelMeshWithTangent(dataDir, L"Walkman.bmf");
		App::GetApp()->RegisterResource(L"Object_WalkAnimation_MESH_WITH_TAN", multiModelMesh);

		//�{�[�����f��(�}���`���b�V��)�̒ʏ탊�\�[�X
		auto EnemyModelMesh = MeshResource::CreateBoneModelMesh(dataDir, L"EnemyRun.bmf");
		App::GetApp()->RegisterResource(L"EnemyRun_MESH", EnemyModelMesh);

		//�{�[�����f��(�}���`���b�V��)�̃^���W�F���g�t�����\�[�X
		EnemyModelMesh = MeshResource::CreateBoneModelMeshWithTangent(dataDir, L"EnemyRun.bmf");
		App::GetApp()->RegisterResource(L"EnemyRun_MESH_WITH_TAN", EnemyModelMesh);

		//�@���}�b�v
		strTexture = dataDir + L"Tx_Checker_Normal.png";
		App::GetApp()->RegisterTexture(L"OBJECT_NORMAL_TX", strTexture);

		//�T�E���h
		wstring CursorWav = dataDir + L"music.mp3";
		App::GetApp()->RegisterWav(L"BGM", CursorWav);

	}
	void Scene::OnCreate() {
		try {
			//���\�[�X�쐬
			CreateResourses();
			//�N���A����F��ݒ�
			Col4 Col;
			Col.set(31.0f / 255.0f, 30.0f / 255.0f, 71.0f / 255.0f, 255.0f / 255.0f);
			SetClearColor(Col);
			//�������g�ɃC�x���g�𑗂�
			//�ŏ��̃V�[���ɐݒ�ł���
			PostEvent(0.0f, GetThis<ObjectInterface>(), GetThis<Scene>(), L"ToTitleStage");

		}

		catch (...) {
			throw;
		}
	}

	Scene::~Scene() {
	}

	void Scene::OnEvent(const shared_ptr<Event>& event) {
		if (event->m_MsgStr == L"ToTitleStage") {
			//�^�C�g���X�e�[�W�̐ݒ�
			ResetActiveStage<TitleStage>();
		}

		else if (event->m_MsgStr == L"ToGameStage") {
			//�ŏ��̃A�N�e�B�u�X�e�[�W�̐ݒ�
			ResetActiveStage<GameStage>();
		}

		else if (event->m_MsgStr == L"ToClearStage") {
			//�ŏ��̃A�N�e�B�u�X�e�[�W�̐ݒ�
			ResetActiveStage<ClearStage>();
		}

		else if (event->m_MsgStr == L"ToGameOverStage") {
			//�ŏ��̃A�N�e�B�u�X�e�[�W�̐ݒ�
			ResetActiveStage<GameOverStage>();
		}
		


	}

}
//end basecross
