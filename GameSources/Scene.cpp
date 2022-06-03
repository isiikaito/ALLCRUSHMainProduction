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
		wstring strTexture = dataDir + L"trace.png";
		App::GetApp()->RegisterTexture(L"TRACE_TX", strTexture);
		strTexture = dataDir + L"wall.jpg";
		App::GetApp()->RegisterTexture(L"WALL_TX", strTexture);
		strTexture = dataDir + L"doukutu.png";
		App::GetApp()->RegisterTexture(L"DOUKUTU_TX", strTexture);

		strTexture = dataDir + L"TITLE.png";
		App::GetApp()->RegisterTexture(L"TITLLE_TX", strTexture);

		//strTexture = dataDir + L"GameOver.png";
		//App::GetApp()->RegisterTexture(L"GAMEOVER_TX", strTexture);

		strTexture = dataDir + L"GameOver.jpg";
		App::GetApp()->RegisterTexture(L"GAMEOVER_TX", strTexture);

		strTexture = dataDir + L"flee.png";
		App::GetApp()->RegisterTexture(L"FLEE_TX", strTexture);

		strTexture = dataDir + L"PillarBrake.png";
		App::GetApp()->RegisterTexture(L"PillarBrake_TX", strTexture);

		strTexture = dataDir + L"JustTiming.png";
		App::GetApp()->RegisterTexture(L"JustTiming_TX", strTexture);

		strTexture = dataDir + L"ClearNear.png";
		App::GetApp()->RegisterTexture(L"ClearNear_TX", strTexture);

		strTexture = dataDir + L"WallBrake.png";
		App::GetApp()->RegisterTexture(L"WallBrake_TX", strTexture);

		//���f��
		//�{�[�����f���̒ʏ탊�\�[�X
		auto multiModelMesh = MeshResource::CreateBoneModelMesh(dataDir, L"player06.bmf");
		App::GetApp()->RegisterResource(L"Object_WalkAnimation_MESH", multiModelMesh);

		//�{�[�����f���̃^���W�F���g�t�����\�[�X
		multiModelMesh = MeshResource::CreateBoneModelMeshWithTangent(dataDir, L"player06.bmf");
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
		auto staticModelMesh1 = MeshResource::CreateStaticModelMesh(dataDir, L"StageWall.bmf");
		App::GetApp()->RegisterResource(L"STAGEWALL_MESH", staticModelMesh1);

		//���̃��f���ǂݍ���
		auto staticModelMesh2 = MeshResource::CreateStaticModelMesh(dataDir, L"yuka2.bmf");
		App::GetApp()->RegisterResource(L"STAGEFLOOR_MESH", staticModelMesh2);

        //�o���̃��f���ǂݍ���
		auto staticModelMesh3 = MeshResource::CreateStaticModelMesh(dataDir, L"ExitWall.bmf");
		App::GetApp()->RegisterResource(L"EXITWALL_MESH", staticModelMesh3);

        //��Q���P�̓ǂݍ���
		auto staticModelMesh4 = MeshResource::CreateStaticModelMesh(dataDir, L"Obuject.KU2.bmf");
		App::GetApp()->RegisterResource(L"OBSTACLE1_MESH", staticModelMesh4);

		//��Q��2�̓ǂݍ���
		auto staticModelMesh5 = MeshResource::CreateStaticModelMesh(dataDir, L"Obuject05.bmf");
		App::GetApp()->RegisterResource(L"OBSTACLE2_MESH", staticModelMesh5);

		//���ǂݍ���
		auto staticModelMesh6 = MeshResource::CreateStaticModelMesh(dataDir, L"pillar.bmf");
		App::GetApp()->RegisterResource(L"PILLAR_MESH", staticModelMesh6);

		//���Γǂݍ���
		auto staticModelMesh7 = MeshResource::CreateStaticModelMesh(dataDir, L"Foring.bmf");
		App::GetApp()->RegisterResource(L"IWA_MESH", staticModelMesh7);

		//�󂷕�Maya�ǂݍ���
		auto staticModelMesh8 = MeshResource::CreateStaticModelMesh(dataDir, L"WallHPMax.bmf");
		App::GetApp()->RegisterResource(L"UNBREAKWALL_MESH", staticModelMesh8);


		//
		auto staticModelMesh9 = MeshResource::CreateStaticModelMesh(dataDir, L"BreakWall02.bmf");
		App::GetApp()->RegisterResource(L"DAMAGEWALL1_MESH", staticModelMesh9);

		//
		auto staticModelMesh10 = MeshResource::CreateStaticModelMesh(dataDir, L"BreakeWall01.bmf");
		App::GetApp()->RegisterResource(L"DAMAGEWALL2_MESH", staticModelMesh10);

		//
		auto staticModelMesh11 = MeshResource::CreateStaticModelMesh(dataDir, L"BerakWall03.bmf");
		App::GetApp()->RegisterResource(L"DAMAGEWALL3_MESH", staticModelMesh11);

		//�^�C���̃e�N�X�`��
		strTexture = dataDir + L"number.png";
		App::GetApp()->RegisterTexture(L"NUMBER_TX", strTexture);
		//�A�C�e���e�N�X�`��
		strTexture = dataDir + L"SPEED.png";
		App::GetApp()->RegisterTexture(L"SPEED_TX", strTexture);
		//X�{�^���e�N�X�`��
		strTexture = dataDir + L"XButton.png";
		App::GetApp()->RegisterTexture(L"XButton_TX", strTexture);
		//Y�{�^���e�N�X�`��
		strTexture = dataDir + L"YButton.png";
		App::GetApp()->RegisterTexture(L"YButton_TX", strTexture);
		//�n���}�[�Q�[�W
		strTexture = dataDir + L"GAGE.png";
		App::GetApp()->RegisterTexture(L"GAGE_TX", strTexture);

		//�����e�N�X�`��
		strTexture = dataDir + L"go.png";
		App::GetApp()->RegisterTexture(L"Stage1_TX", strTexture);

		//�����e�N�X�`��
		strTexture = dataDir + L"Stage2.png";
		App::GetApp()->RegisterTexture(L"Stage2_TX", strTexture);
		
		//���j���[�e�N�X�`��
		strTexture = dataDir + L"MenuSelect.png";
		App::GetApp()->RegisterTexture(L"MenuSelect_TX", strTexture);
		
		//�G�t�F�N�g�֘A
		strTexture = dataDir + L"Splash.png";
		App::GetApp()->RegisterTexture(L"SPARK_TX", strTexture);
		strTexture = dataDir + L"spark.png";
		App::GetApp()->RegisterTexture(L"SPARK_TX1", strTexture);
		strTexture = dataDir + L"SpeedUp.png";
		App::GetApp()->RegisterTexture(L"SPEEDUP_TX", strTexture);
		strTexture = dataDir + L"Impact.png";
		App::GetApp()->RegisterTexture(L"IMPACT_TX", strTexture);
		strTexture = dataDir + L"PowerUp.png";
		App::GetApp()->RegisterTexture(L"POWERUP_TX1", strTexture);

		//�T�E���h
		wstring CursorWav = dataDir + L"music.mp3";
		App::GetApp()->RegisterWav(L"BGM", CursorWav);
		//�G�̐�
		CursorWav = dataDir + L"WalkSound.wav";
		App::GetApp()->RegisterWav(L"WalkSound", CursorWav);
		//����T�E���h	
		CursorWav = dataDir + L"run.wav";
		App::GetApp()->RegisterWav(L"run", CursorWav);
		//�X�s�[�h�A�b�v�̃T�E���h
		CursorWav = dataDir + L"SpeedUp.wav";
		App::GetApp()->RegisterWav(L"SpeedUp", CursorWav);
		//�X�s�[�h�A�b�v�̃T�E���h
		CursorWav = dataDir + L"PowerUp.wav";
		App::GetApp()->RegisterWav(L"PowerUp", CursorWav);
		//�n���}�[��U��T�E���h
		CursorWav = dataDir + L"Hammer.wav";
		App::GetApp()->RegisterWav(L"Hammer", CursorWav);
		//�ǂ��U�����s�������̃T�E���h
		CursorWav = dataDir + L"AttackWall.wav";
		App::GetApp()->RegisterWav(L"AttackWall", CursorWav);
		//�ǂ���ꂽ�Ƃ��̃T�E���h
		CursorWav = dataDir + L"BrakeWall.wav";
		App::GetApp()->RegisterWav(L"BrakeWall", CursorWav);
		//�G�̐�
		CursorWav = dataDir + L"EnemyVoice.wav";
		App::GetApp()->RegisterWav(L"EnemyVoice", CursorWav);
		//�G�Ɋ₪�����鉹
		CursorWav = dataDir + L"RockAttack.wav";
		App::GetApp()->RegisterWav(L"RockAttack", CursorWav);


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

		else if (event->m_MsgStr == L"ToGameStage2") {
			//�Q�[���X�e�[�W2�̐ݒ�
			ResetActiveStage<GameStage2>();
		}
		else if (event->m_MsgStr == L"ToMenuStage") {
			//���j���[�X�e�[�W�̐ݒ�
			ResetActiveStage<MenuStage>();
		}
		else if (event->m_MsgStr == L"ToClearStage") {
			//�N���A�X�e�[�W�̐ݒ�
			ResetActiveStage<MyClearStage>();
		}

		else if (event->m_MsgStr == L"ToGameOverStage") {
			//�Q�[���I�[�o�[�X�e�[�W�̐ݒ�
			ResetActiveStage<GameOverStage>();
		}
		
		else if (event->m_MsgStr == L"ToMovieStage") {
			m_MovieActive = true;
			//�{�X�̓o��V�[���X�e�[�W�̐ݒ�
			ResetActiveStage<MyMovieStage>();
		}
	}

}
//end basecross
