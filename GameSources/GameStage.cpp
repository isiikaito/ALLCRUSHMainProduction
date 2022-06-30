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

		//OpeningCameraView�p�̃r���[
		m_OpeningCameraView = ObjectFactory::Create<SingleView>(GetThis<Stage>());
		auto ptrOpeningCamera = ObjectFactory::Create<OpeningCamera>();
		m_OpeningCameraView->SetCamera(ptrOpeningCamera);
		//MyCamera�p�̃r���[
		m_MyCameraView = ObjectFactory::Create<SingleView>(GetThis<Stage>());
		auto ptrMyCamera = ObjectFactory::Create<MyCamera>();
		ptrMyCamera->SetEye(Vec3(0.0f, 5.0f, -5.0f));
		ptrMyCamera->SetAt(Vec3(0.0f, 0.0f, 0.0f));
		m_MyCameraView->SetCamera(ptrMyCamera);
		//������Ԃł�m_OpeningCameraView���g��
		SetView(m_OpeningCameraView);
		m_CameraSelect = CameraSelect::openingCamera;
		//�}���`���C�g�̍쐬
		auto PtrMultiLight = CreateLight<MultiLight>();

		//�f�t�H���g�̃��C�e�B���O���w��
		PtrMultiLight->SetDefaultLighting();
	}

	void GameStage::CreateMultiSpark() {
		auto MultiSparkPtr = AddGameObject<ImpactSmoke>();
		//���L�I�u�W�F�N�g�ɃX�p�[�N��o�^
		SetSharedGameObject(L"MultiSpark", MultiSparkPtr);
	}

	void GameStage::CreateMultiSpark1() {
		auto MultiSparkPtr = AddGameObject<ImpactSmoke>();
		//���L�I�u�W�F�N�g�ɃX�p�[�N��o�^
		SetSharedGameObject(L"MultiSpark1", MultiSparkPtr);
	}

	
	//����ǂ̍쐬
	void GameStage::CreateWall() {
		//�O���[�v�̎擾
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
			//HP�̎擾
			int HP(
				(int)_wtof(Tokens[10].c_str())
				);
			//�e�l���������̂ŃI�u�W�F�N�g�̍쐬
			AddGameObject<Wall>(Scale, Rot, Pos,HP);
		}
	}
	//�X�e�[�W�̕ǂ̍쐬
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
			Vec2(180.0f, 180.0f), Vec3(-530.0f, -280.0f, 0.0f));
	}
	//X�{�^���X�v���C�g
	void GameStage::CreateXSprite() {
		AddGameObject<XSprite>(L"XButton_TX", true,
			//�e�N�X�`���̑傫���@�@�@�@�ʒu
			Vec2(80.0f, 80.0f), Vec3(-520.0f, -190.0f, 0.0f));
	}
	//Y�{�^���X�v���C�g
	void GameStage::CreateYSprite() {
		AddGameObject<YSprite>(L"YButton_TX", true,
			//�e�N�X�`���̑傫���@�@�@�@�ʒu
			Vec2(80.0f, 80.0f), Vec3(550.0f, -90.0f, 0.0f));
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
			Vec2(40.0f,40.0f), Vec3(550.0f, -320.0f, 0.1f));
	}
	void GameStage::CreateGageSprite2()
	{
		AddGameObject<GageSprite2>(true,
			Vec2(40.0f, 40.0f), Vec3(550.0f, -280.0f, 0.1f));
	}
	void GameStage::CreateGageSprite3()
	{
		AddGameObject<GageSprite3>(true,
			Vec2(40.0f, 50.0f), Vec3(550.0f, -235.0f, 0.1f));
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

	// ������e���b�v
	void GameStage::CreateTickerSprite()
	{
		AddGameObject<TickerSprite>(L"FLEE_TX", true,
			Vec2(500.0f, 700.0f), Vec2(0.0f, 0.0f));
	}

	// �����󂷃e���b�v
	void GameStage::CreateTelop()
	{
		AddGameObject<Telop>(L"PillarBrake_TX", true,
			Vec2(500.0f, 700.0f), Vec2(0.0f, 0.0f));
	}

	// �����󂷃^�C�~���O�e���b�v
	void GameStage::CreateTelop2()
	{
		AddGameObject<Telop2>(L"JustTiming_TX", true,
			Vec2(500.0f, 700.0f), Vec2(0.0f, 0.0f));
	}

	// �o���O�e���b�v
	void GameStage::CreateTelop3()
	{
		AddGameObject<Telop3>(L"ClearNear_TX", true,
			Vec2(500.0f, 700.0f), Vec2(0.0f, 0.0f));
	}

	// �ǂ��󂹁I�I�e���b�v
	void GameStage::CreateTelop4()
	{
		AddGameObject<Telop4>(L"WallBrake_TX", true,
			Vec2(500.0f, 700.0f), Vec2(0.0f, 0.0f));
	}

	

	void GameStage::BGM() {
		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		m_BGM = XAPtr->Start(L"BGM", XAUDIO2_LOOP_INFINITE, 0.4f);
	}

	//�J�����}���̍쐬
	void GameStage::CreateCameraman() {
		auto ptrPlayer = GetSharedGameObject<Player>(L"Player");
		auto ptrCameraman = AddGameObject<Cameraman>(2.0f);
		//�V�F�A�z���Cameraman��ǉ�
		SetSharedGameObject(L"Cameraman", ptrCameraman);
		//�V�F�A�z���OpeningCameraman��ǉ�
		auto ptrOpeningCameraman = AddGameObject<OpeningCameraman>();
		SetSharedGameObject(L"OpeningCameraman", ptrOpeningCameraman);

		auto ptrOpeningCamera = dynamic_pointer_cast<OpeningCamera>(m_OpeningCameraView->GetCamera());
		if (ptrOpeningCamera) {
			ptrOpeningCamera->SetCameraObject(ptrOpeningCameraman);
			SetView(m_OpeningCameraView);
			m_CameraSelect = CameraSelect::openingCamera;
		}

	}

	void GameStage::OnCreate() {
		try {
			
			auto  Select = App::GetApp()->GetScene<Scene>()->GetStageSelect();

			SetPhysicsActive(true);//�����v�Z�L��
			
			// �u�A�v���v�I�u�W�F�N�g�̃C���X�^���X���擾����i�C���X�^���X�F�N���X�̎��ԁA�I�u�W�F�N�g�w���̃I�u�W�F�N�g�̂��Ɓj
			auto& app = App::GetApp();
			wstring DataDir;
			App::GetApp()->GetDataDirectory(DataDir);
			//CSV�t�@�C�����̓ǂݍ���C
			m_CsvC.SetFileName(DataDir + L"stage"+ Util::IntToWStr(Select)+L".csv");
			m_CsvC.ReadCsv();

			
			CreateViewLight();           //�r���[�ƃ��C�g�̍쐬
			CreateMultiSpark();          //�G�t�F�N�g0�̍쐬
			CreateMultiSpark1();         //�G�t�F�N�g1�̍쐬
			CreatePlayer();              //�v���[���[�̍쐬
			BGM();                       //BGM�̍Đ�
			CreatePillar();              //���̍쐬
			AddGameObject<EnemyObject>();//�G�̍쐬
			CreateStageWall();           //�X�e�[�W�̕ǂ̒ǉ�	
			CreateStageFloor();          //���̒ǉ�
			CreateObstacle1();           //��Q���P�̒ǉ�
			CreateFallingRock();         //����
			CreateExitWall();            //�}���ł������o��
			CreateTime();                //�^�C���X�v���C�g�쐬
			CreateWall();                //����ǂ̍쐬
			CreateMyitem1();             //�A�C�e���X�v���C�g
			CreateXSprite();             //X�{�^���̃X�v���C�g�̍쐬
			CreateYSprite();             //Y�{�^���̃X�v���C�g�̍쐬
			CreateMygage();              //�Q�[�W�̘g�̍쐬
			CreateGageSprite();          //�Q�[�W�̃X�v���C�g1�̍쐬
			CreateGageSprite2();         //�Q�[�W�̃X�v���C�g2�̍쐬
			CreateGageSprite3();         //�Q�[�W�̃X�v���C�g3�̍쐬
			CreateGageWhite();           //�Q�[�W�̔w�i�̍쐬
			CreateTickerSprite();        //�e���b�v0�̍쐬
			CreateTelop();               //�e���b�v1�̍쐬
			CreateTelop2();              //�e���b�v2�̍쐬
			CreateTelop3();              //�e���b�v3�̍쐬
			CreateTelop4();              //�e���b�v4�̍쐬
			CreateCameraman();           //�J�����}���̍쐬

		}
		catch (...) {
			throw;
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

		auto ptrPlayer = GetSharedGameObject<Player>(L"Player");
		auto Exit = ptrPlayer->GetExitCount();
		auto GameOver = ptrPlayer->GetGameOver();
		auto state = ptrPlayer->GetGameState();
		static shared_ptr<FadeOut> fadeOut = nullptr;
		static float FadeTime = 0.0f;
		switch (state)
		{
		case GameState::Game:
			break;
		case GameState::Down:
			ptrPlayer->SetGameState(GameState::FadeStart);
			break;
		case GameState::FadeStart:
			fadeOut = AddGameObject<FadeOut>(true,
				Vec2(1290.0f, 960.0f), Vec3(0.0f, 0.0f, 0.0f));
			ptrPlayer->SetGameState(GameState::FadeOut);
		case GameState::FadeOut:
			FadeTime += elapsedTime;
			if (FadeTime >= 1.0f)
			{
				AddGameObject<GameOverSprite>(L"GAMEOVERTELOP_TX", true,
					Vec2(500.0f, 500.0f), Vec3(0.0f, 0.0f, 0.0f));
				AddGameObject<PushButtonXTelop>(L"PushButtonX_TX", true,
					Vec2(500.0f, 500.0f), Vec3(0.0f, -250.0f, 0.0f));
				ptrPlayer->SetGameState(GameState::ChangeStage);
			}
			break;
		case GameState::ChangeStage:
			break;

			//�t�F�[�h�A�E�g�̍쐬
			AddGameObject<GameOverSprite>(L"GAMEOVERTELOP_TX", true,
				Vec2(1290.0f, 960.0f), Vec3(0.0f, 0.0f, 0.0f));

			m_createGameOverObjectFlg = true;
		case GameState::GameExit:
			//�t�F�[�h�A�E�g�̍쐬
			AddGameObject<FadeOut>(true,
				Vec2(1290.0f, 960.0f), Vec3(0.0f, 0.0f, 0.0f));
			float elapsedTime1 = App::GetApp()->GetElapsedTime();
			m_ExitTime += elapsedTime1;
			if (m_ExitTime >= 1.0f)
			{
				PostEvent(0.0, GetThis<GameStage>(), App::GetApp()->GetScene<Scene>(), L"ToClearStage");
			}
	}
		ptrPlayer->SetExitCount(Exit);
        ptrPlayer->SetGameOver(GameOver);
		// �e���b�v�̎���
		auto ptrStage = GetSharedGameObject<TickerSprite>(L"TickerSprite");
		// ���Ԃ̕ϐ��ɑ���
		m_idleTime += elapsedTime;
		if (m_idleTime >= 2.0f)
		{
			// 1�b��ɕ\�����I�t�ɂȂ�
			ptrStage->SetDrawActive(false);
		}
	}

	void GameStage::OnDestroy() {
		//BGM�̃X�g�b�v
		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		XAPtr->Stop(m_BGM);
	}

}
//end basecross
