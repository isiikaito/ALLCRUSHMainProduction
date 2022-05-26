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

		//MyCamera�p�̃r���[
		m_MyCameraView = ObjectFactory::Create<SingleView>(GetThis<Stage>());
		auto ptrMyCamera = ObjectFactory::Create<MyCamera>();
		ptrMyCamera->SetEye(Vec3(0.0f, 5.0f, -5.0f));
		ptrMyCamera->SetAt(Vec3(0.0f, 0.0f, 0.0f));
		m_MyCameraView->SetCamera(ptrMyCamera);
		//������ԂŎg��View
		SetView(m_MyCameraView);
		//m_CameraSelect = CameraSelect::myCamera;
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
		auto group = CreateSharedObjectGroup(L"Wall_Group");
		//CSV�̍s�P�ʂ̔z��
		vector<wstring>LineVec;
		//0�Ԗڂ̃J������L"BreakWall"�ł���s�𔲂��o��
		m_CsvC.GetSelect(LineVec, 0, L"Wall");
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
			int HP(
				(int)_wtof(Tokens[10].c_str())
				);
			//�e�l���������̂ŃI�u�W�F�N�g�̍쐬
			AddGameObject<Wall>(Scale, Rot, Pos,HP);
		}
		//HP
		//AddGameObject<Wall>(Vec3(1.0f, 10.0f, 10.0f), Vec3(), Vec3(-5.0f, 1.0f, 0.0f),1);
		//AddGameObject<Wall>(Vec3(1.0f, 10.0f, 10.0f), Vec3(), Vec3(-13.0f, 1.0f, 0.0f),3);
		//AddGameObject<Wall>(Vec3(1.0f, 10.0f, 10.0f), Vec3(), Vec3(-21.0f, 1.0f, 0.0f),1);
		//AddGameObject<Wall>(Vec3(1.0f, 10.0f, 10.0f), Vec3(), Vec3(-29.0f, 1.0f, 0.0f),2);
		//AddGameObject<Wall>(Vec3(1.0f, 10.0f, 10.0f), Vec3(), Vec3(-37.0f, 1.0f, 0.0f),4);

	}
	//�}���̕ǂ̍쐬
	void GameStage::CreateStageWall() {
		//CSV�̍s�P�ʂ̔z��
		vector<wstring>LineVec;
		//0�Ԗڂ̃J������L"stageObject"�ł���s�𔲂��o��
		m_CsvC.GetSelect(LineVec, 0, L"StageWall");
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
			AddGameObject<StageWall>(Scale, Rot, Pos);
			

		}

	}

	//�}���̕ǂ̍쐬
	void GameStage::CreateExitWall() {
		//CSV�̍s�P�ʂ̔z��
		vector<wstring>LineVec;
		//0�Ԗڂ̃J������L"stageObject"�ł���s�𔲂��o��
		m_CsvC.GetSelect(LineVec, 0, L"ExitWall");
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
			AddGameObject<ExitWall>(Scale, Rot, Pos);


		}

	}

	//�}���̏��̍쐬
	void GameStage::CreateStageFloor() {
		//CSV�̍s�P�ʂ̔z��
		vector<wstring>LineVec;
		//0�Ԗڂ̃J������L"stageObject"�ł���s�𔲂��o��
		m_CsvC.GetSelect(LineVec, 0, L"StageFloor");
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
			AddGameObject<StageFloor>(Scale, Rot, Pos);
		}
		


	}
	//��Q���P�쐬
	void GameStage::CreateObstacle1() {
		auto group1 = CreateSharedObjectGroup(L"Obstacle1_Group1");
		//CSV�̍s�P�ʂ̔z��
		vector<wstring>LineVec;
		//0�Ԗڂ̃J������L"stageObject"�ł���s�𔲂��o��
		m_CsvC.GetSelect(LineVec, 0, L"Obstacle1");
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
			AddGameObject<Obstacle1>(Scale, Rot, Pos);
		}
	}

	//��Q��2�쐬
	void GameStage::CreateObstacle2() {
		//CSV�̍s�P�ʂ̔z��
		vector<wstring>LineVec;
		//0�Ԗڂ̃J������L"stageObject"�ł���s�𔲂��o��
		m_CsvC.GetSelect(LineVec, 0, L"Obstacle2");
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
			AddGameObject<Obstacle2>(Scale, Rot, Pos);
		}
	}

	//���̍쐬
	void GameStage::CreatePillar() {
		auto group2 = CreateSharedObjectGroup(L"Pillar_Group1");
		//CSV�̍s�P�ʂ̔z��
		vector<wstring>LineVec;
		//0�Ԗڂ̃J������L"stageObject"�ł���s�𔲂��o��
		m_CsvC.GetSelect(LineVec, 0, L"Pillar");
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
			AddGameObject<Pillar>(Scale, Rot, Pos);
		}
	}

	//���΂̍쐬
	void GameStage::CreateFallingRock() {
		
		//CSV�̍s�P�ʂ̔z��
		vector<wstring>LineVec;
		auto group3 = CreateSharedObjectGroup(L"FallingRock_Group1");
		//0�Ԗڂ̃J������L"stageObject"�ł���s�𔲂��o��
		m_CsvC.GetSelect(LineVec, 0, L"FallingRock");
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
			AddGameObject<FallingRock>(Scale, Rot, Pos);
		}
	}

	//�^�C���X�v���C�g�쐬
	void GameStage::CreateTime() {
		AddGameObject<MyTime>(4,
			L"NUMBER_TX",
			true,
			Vec2(80.0f, 80.0f),
			Vec3(600.0f, 340.0f, 0.0f));
	}

	//�A�C�e���X�v���C�g�쐬
	void GameStage::CreateMyitem1() {
		AddGameObject<Myitem1>(L"SPEED_TX", true,
			//�e�N�X�`���̑傫���@�@�@�@�ʒu
			Vec2(180.0f, 180.0f), Vec3(-530.0f, -310.0f, 0.0f));
	}

	//�Q�[�W�̘g�쐬
	void GameStage::CreateMygage() {
		AddGameObject<Mygage>(L"GAGE_TX", true,
			Vec2(240.0f, 240.0f), Vec3(550.0f, -220.0f, 0.0f));
	}
	//�Q�[�W�̃o�[�̍쐬
	void GameStage::CreateGageSprite()
	{
		AddGameObject<GageSprite>(true,
			Vec2(40.0f,50.0f), Vec3(550.0f, -310.0f, 0.1f));
	}
	void GameStage::CreateGageSprite2()
	{
		AddGameObject<GageSprite2>(true,
			Vec2(40.0f, 40.0f), Vec3(550.0f, -270.0f, 0.1f));
	}
	void GameStage::CreateGageSprite3()
	{
		AddGameObject<GageSprite3>(true,
			Vec2(40.0f, 40.0f), Vec3(550.0f, -230.0f, 0.1f));
	}

	void GameStage::CreateGageWhite()
	{
		AddGameObject<GageSpriteWhite>(true,
			Vec2(40.0f, 130.0f), Vec3(550.0f, -274.0f, 0.2f));
	}

	

	//�v���C���[�̍쐬
	void GameStage::CreatePlayer() {
		//�v���[���[�̍쐬
		auto PlayerPtr = AddGameObject<Player>();
		//�V�F�A�z��Ƀv���C���[��ǉ�
		SetSharedGameObject(L"Player", PlayerPtr);
	}
	//�G�̍쐬
	void GameStage::CreateEnemy() {
		////�v���[���[�̍쐬
		//auto EnemyPtr = AddGameObject<EnemyObject>();
		////�V�F�A�z��Ƀv���C���[��ǉ�
		//SetSharedGameObject(L"Enemy", EnemyPtr);
	}

	// ������e���b�v
	void GameStage::CreateTickerSprite()
	{
		AddGameObject<TickerSprite>(L"FLEE_TX", true,
			Vec2(500.0f, 700.0f), Vec2(0.0f, 0.0f));
	}

	// �����󂷃e���b�v
	void GameStage::CreateTelop()
	{
		AddGameObject<Telop>(L"������_TX", true,
			Vec2(500.0f, 700.0f), Vec2(0.0f, 0.0f));
	}

	// �����󂷃^�C�~���O�e���b�v
	void GameStage::CreateTelop2()
	{
		AddGameObject<Telop2>(L"���󂷃^�C�~���O_TX", true,
			Vec2(500.0f, 700.0f), Vec2(0.0f, 0.0f));
	}

	// �o���O�e���b�v
	void GameStage::CreateTelop3()
	{
		AddGameObject<Telop3>(L"�o���O_TX", true,
			Vec2(500.0f, 700.0f), Vec2(0.0f, 0.0f));
	}

	// �ǂ��󂹁I�I�e���b�v
	void GameStage::CreateTelop4()
	{
		AddGameObject<Telop4>(L"�ǂ��󂹁I�I_TX", true,
			Vec2(500.0f, 700.0f), Vec2(0.0f, 0.0f));
	}

	void GameStage::BGM() {
		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		m_BGM = XAPtr->Start(L"BGM", XAUDIO2_LOOP_INFINITE, 0.1f);
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
			m_CsvC.SetFileName(DataDir + L"stage1.csv");
			m_CsvC.ReadCsv();

			//�r���[�ƃ��C�g�̍쐬
			CreateViewLight();

			// �v���C���[�I�u�W�F�N�g���X�e�[�W�ɒǉ�����
			//AddGameObject<Player>(); // �w��̃Q�[���I�u�W�F�N�g�𐶐����ăX�e�[�W�ɒǉ����A���̃|�C���^��Ԃ�

			//�v���[���[�̍쐬
			CreatePlayer();
			//�G�̍쐬
			CreateEnemy();
			//BGM�̍Đ�
			BGM();

			CreatePillar();
			AddGameObject<EnemyObject>();
			//�I�u�W�F�N�g�̒ǉ�
			CreatestageObject();
			//�}���ł������X�e�[�W�̕ǂ̒ǉ�
			CreateStageWall(); 
			//�}���ō�������̒ǉ�
			CreateStageFloor();
			//��Q���P�̒ǉ�
			CreateObstacle1();
			//����
			CreateFallingRock();
			//�}���ł������o��
			CreateExitWall();
			//�^�C���X�v���C�g�쐬
			CreateTime();
			//����ǂ̍쐬
			CreateWall();
			//�A�C�e���X�v���C�g
			CreateMyitem1();
			//�Q�[�W�X�v���C�g
			CreateMygage();
			CreateGageSprite();
			CreateGageSprite2();
			CreateGageSprite3();
			CreateGageWhite();
			// ������e���b�v
			CreateTickerSprite();

			CreateTelop();
			CreateTelop2();
			CreateTelop3();
			CreateTelop4();
		}
		catch (...) {
			throw;
		}
	}
	void GameStage::OnUpdate() {
		//�R���g���[���`�F�b�N���ē��͂�����΃R�}���h�Ăяo��
		m_InputHandler.PushHandle(GetThis<GameStage>());
		float elapsedTime = App::GetApp()->GetElapsedTime();
		m_TotalTime += elapsedTime;
		if (m_TotalTime >= 10000.0f) {
			m_TotalTime = 0.0f;
		}
		//�^�C�����X�V����
		auto ptrScor = GetSharedGameObject<MyTime>(L"Time");
		ptrScor->SetScore(m_TotalTime);


		// �e���b�v�̎���
		auto ptrStage = GetSharedGameObject<TickerSprite>(L"TickerSprite");
		// ���Ԃ̕ϐ��ɑ���
		m_idleTime += elapsedTime;
		if (m_idleTime >= 2.0f)
		{
			// 1�b��ɕ\�����I�t�ɂȂ�
			ptrStage->SetDrawActive(false);
		}

		// �e���b�v�̎���
		auto ptrStage1 = GetSharedGameObject<Telop>(L"Telop");
		// ���Ԃ̕ϐ��ɑ���
		m_TelopTime += elapsedTime;
		if (m_TelopTime >= 1.6f)
		{
			// 1�b��ɕ\�����I�t�ɂȂ�
			ptrStage1->SetDrawActive(false);

		}

		// �e���b�v�̎���
		auto ptrStage2 = GetSharedGameObject<Telop2>(L"Telop2");
		// ���Ԃ̕ϐ��ɑ���
		m_Telop2Time += elapsedTime;
		if (m_Telop2Time >= 2.0f)
		{
			// 1�b��ɕ\�����I�t�ɂȂ�
			ptrStage2->SetDrawActive(false);

		}

		// �e���b�v�̎���
		auto ptrStage3 = GetSharedGameObject<Telop3>(L"Telop3");
		// ���Ԃ̕ϐ��ɑ���
		m_Telop3Time += elapsedTime;
		if (m_Telop3Time >= 2.0f)
		{
			// 1�b��ɕ\�����I�t�ɂȂ�
			ptrStage3->SetDrawActive(false);

		}

		// �e���b�v�̎���
		auto ptrStage4 = GetSharedGameObject<Telop4>(L"Telop4");
		// ���Ԃ̕ϐ��ɑ���
		m_Telop4Time += elapsedTime;
		if (m_Telop4Time >= 2.0f)
		{
			// 1�b��ɕ\�����I�t�ɂȂ�
			ptrStage4->SetDrawActive(false);

		}
		return;
	}

	void GameStage::OnDestroy() {
		//BGM�̃X�g�b�v
		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		XAPtr->Stop(m_BGM);
	}

}
//end basecross
