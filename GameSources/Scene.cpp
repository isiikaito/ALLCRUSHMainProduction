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
		wstring strTexture = dataDir + L"������.jpg";
		App::GetApp()->RegisterTexture(L"DAMAGEWALL_TX", strTexture);
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

		strTexture = dataDir + L"�Q�[���N���A.jpg";
		App::GetApp()->RegisterTexture(L"GAMECREA_TX", strTexture);

		//strTexture = dataDir + L"kari.mp4";
		//App::GetApp()->RegisterTexture(L"KARI_TX", strTexture);

		//���f��
		//�{�[�����f���̒ʏ탊�\�[�X
		auto multiModelMesh = MeshResource::CreateBoneModelMesh(dataDir, L"player1.bmf");
		App::GetApp()->RegisterResource(L"Object_WalkAnimation_MESH", multiModelMesh);

		//�{�[�����f���̃^���W�F���g�t�����\�[�X
		multiModelMesh = MeshResource::CreateBoneModelMeshWithTangent(dataDir, L"player1.bmf");
		App::GetApp()->RegisterResource(L"Object_WalkAnimation_MESH_WITH_TAN", multiModelMesh);

		//�{�[�����f��(�}���`���b�V��)�̒ʏ탊�\�[�X
		auto EnemyModelMesh = MeshResource::CreateBoneModelMesh(dataDir, L"EnemyBoss1.bmf");
		App::GetApp()->RegisterResource(L"EnemyRun_MESH", EnemyModelMesh);

		//�{�[�����f��(�}���`���b�V��)�̃^���W�F���g�t�����\�[�X
		EnemyModelMesh = MeshResource::CreateBoneModelMeshWithTangent(dataDir, L"EnemyBoss1.bmf");
		App::GetApp()->RegisterResource(L"EnemyRun_MESH_WITH_TAN", EnemyModelMesh);

		//�@���}�b�v
		strTexture = dataDir + L"Tx_Checker_Normal.png";
		App::GetApp()->RegisterTexture(L"OBJECT_NORMAL_TX", strTexture);

		//�ǂ̃��f���ǂݍ���
		auto staticModelMesh1 = MeshResource::CreateStaticModelMesh(dataDir, L"Stage2.bmf");
		App::GetApp()->RegisterResource(L"STAGEWALL_MESH", staticModelMesh1);

		//���̃��f���ǂݍ���
		auto staticModelMesh2 = MeshResource::CreateStaticModelMesh(dataDir, L"yuka2.bmf");
		App::GetApp()->RegisterResource(L"STAGEFLOOR_MESH", staticModelMesh2);

        //�o���̃��f���ǂݍ���
		auto staticModelMesh3 = MeshResource::CreateStaticModelMesh(dataDir, L"ExitWall.bmf");
		App::GetApp()->RegisterResource(L"EXITWALL_MESH", staticModelMesh3);

		//�^�C���̃e�N�X�`��
		strTexture = dataDir + L"number.png";
		App::GetApp()->RegisterTexture(L"NUMBER_TX", strTexture);
		strTexture = dataDir + L"��.png";
		App::GetApp()->RegisterTexture(L"SHIELD_TX", strTexture);
		

		//�T�E���h
		wstring CursorWav = dataDir + L"music.mp3";
		App::GetApp()->RegisterWav(L"BGM", CursorWav);
		//����T�E���h
		CursorWav = dataDir + L"run.wav";
		App::GetApp()->RegisterWav(L"run", CursorWav);
		//�n���}�[��U��T�E���h
		CursorWav = dataDir + L"Hammer.wav";
		App::GetApp()->RegisterWav(L"Hammer", CursorWav);

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
			//�Q�[���X�e�[�W�̐ݒ�
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
		
		else if (event->m_MsgStr == L"ToMovieStage") {
			m_MovieActive = true;
			//�ŏ��̃A�N�e�B�u�X�e�[�W�̐ݒ�
			ResetActiveStage<MyMovieStage>();
		}
	}

}
//end basecross
