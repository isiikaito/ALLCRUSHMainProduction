/*!
@file Enemy.cpp
@brief �G�̎���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	�ǂ�������z�u�I�u�W�F�N�g
	//--------------------------------------------------------------------------------------
	//�\�z�Ɣj��
	EnemyObject::EnemyObject(const shared_ptr<Stage>& StagePtr) : 
		GameObject(StagePtr),
		m_StateChangeSize(5.0f),
		m_Force(0),
		m_Velocity(0),
		EnemyTime(0.0f),
		StopCount(0),
		PillarCount(0),
		StopTime(0.0f),
		m_EnemySetDrawActiveCount(0),
		m_Telop2Time(0.0f),
		m_Event(false)
	{
	}
	EnemyObject::~EnemyObject() {}

	void EnemyObject::OnCreate() {	//������
		auto ptrTransform = GetComponent<Transform>();
		ptrTransform->SetPosition(60.0f, 0.0f, 0.0f);
		ptrTransform->SetScale(3.0f, 3.0f, 2.0f);
		ptrTransform->SetRotation(0.0f, 0.0f, 0.0f);

		Mat4x4 spanMat; // ���f���ƃg�����X�t�H�[���̊Ԃ̍����s��
		spanMat.affineTransformation(
			Vec3(0.2f, 0.1f, 0.06f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, XM_PI * -0.5f, 0.0f),
			Vec3(0.0f, -0.5f, -1.0f)
		);

		auto ptrColl = AddComponent<CollisionObb>(); //Obb�̏Փ˔��������
		auto ptrGra = AddComponent<Gravity>();		 //�d�͂�����
		auto ptrShadow = AddComponent<Shadowmap>();	 //�e������i�V���h�E�}�b�v��`�悷��j
		ptrShadow->SetMeshResource(L"EnemyRun_MESH");//�e������
		ptrShadow->SetMeshToTransformMatrix(spanMat);

		auto ptrDraw = AddComponent<BcPNTnTBoneModelDraw>();
		ptrDraw->SetFogEnabled(false);         
		ptrDraw->SetDiffuse(Col4(1.0, 1.0, 1.0, 0.1)); //R    G    B    A
		ptrDraw->SetMeshResource(L"EnemyRun_MESH_WITH_TAN");
		ptrDraw->SetMeshToTransformMatrix(spanMat);
		ptrDraw->AddAnimation(L"Default", 0, 30, true, 30.0f);
		ptrDraw->ChangeCurrentAnimation(L"Default");
			
		m_StateMachine.reset(new StateMachine<EnemyObject>(GetThis<EnemyObject>())); //�X�e�[�g�}�V���̍\�z	
		m_StateMachine->ChangeState(SeekFarState::Instance()); //�ŏ��̃X�e�[�g��SeekFarState�ɐݒ�
		GetStage()->SetSharedGameObject(L"EnemyObject", GetThis<EnemyObject>());//�ǂݍ��݂̐ݒ������
	}

	void EnemyObject::OnCollisionEnter(shared_ptr<GameObject>& Other) {
		auto ptr = dynamic_pointer_cast<FallingRock>(Other); //���΂ɓ���������
		
		if (ptr) {
			GetStage()->RemoveGameObject<FallingRock>(Other); //���΃I�u�W�F�N�g������
			StopCount = 1;	
			m_Speed = 0; //�{�X�̃X�s�[�h��0�ɂ���
			auto PtrSpark = GetStage()->GetSharedGameObject<InsertEffect>(L"MultiEffect", false);
			auto RockSound = App::GetApp()->GetXAudio2Manager();
			RockSound->Start(L"RockAttack", 0, 0.5f);
			if (PtrSpark) {
				auto pos = GetComponent<Transform>()->GetPosition();
				PtrSpark->InsertImpact(pos);
			}
		}
	}
	
	void EnemyObject::OnUpdate() {
		auto ptrPlayer = GetStage()->GetSharedGameObject<Player>(L"Player"); //�v���C���[�̎擾
		auto Exit = ptrPlayer->GetExitCount();
		ptrPlayer->SetExitCount(Exit);
		m_Event = ptrPlayer->GetPEvent();
		ptrPlayer->SetPEvent(m_Event);

		auto ptrXA = App::GetApp()->GetXAudio2Manager();
		float elapsedTime = App::GetApp()->GetElapsedTime();
		auto ptrTrans = GetComponent<Transform>();
		Vec3 pos = ptrTrans->GetPosition();

		if (Exit == 1)
		{
			m_Speed = 0;
		}
       
		if (StopCount==1) //�{�X��StopCount���P�������ꍇ
		{  
		   StopTime += elapsedTime; //���Ԃ�ϐ��ɑ���
		   if (StopTime >=2.0f)
		   {
			   m_Speed=20;
			   StopCount = 0;
			   StopTime = 0.0f;
		   }
		   return;
		}

		m_Force = Vec3(0);
		m_StateMachine->Update();//�X�e�[�g�}�V����Update���s���B���̒��ŃX�e�[�g�̐؂�ւ����s����
		auto ptrUtil = GetBehavior<UtilBehavior>();
		ptrUtil->RotToHead(1.0f);
		auto ptrDraw = GetComponent<BcPNTnTBoneModelDraw>();//�A�j���[�V����
		ptrDraw->UpdateAnimation(elapsedTime);

        auto& app = App::GetApp();
		float delta = app->GetElapsedTime();
		auto& device = app->GetInputDevice();
		const auto& pad = device.GetControlerVec()[0];

		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec(); //�R���g���[���̎擾
		//B�{�^����������Ă���Ƃ�
		if (cntlVec[0].wButtons & XINPUT_GAMEPAD_B) {
			SetDrawActive(true);//�\��
		}
		//B�{�^����������Ă��Ȃ��Ƃ�
		else {
			SetDrawActive(false);//��\��
		}
		
		if (m_EnemySetDrawActiveCount == 0)
		{
			SetDrawActive(true);
		}
		if (m_EnemySetDrawActiveCount == 1)
		{
			SetDrawActive(false);
		}
		if (m_Event == true)
		{
			if (pos.x < -25) {
				auto ptrStage2 = GetStage()->GetSharedGameObject<Telop2>(L"Telop2"); // �����I�I�e���b�v
				ptrStage2->SetDrawActive(true);
				m_Telop2Time += elapsedTime; // ���Ԃ̕ϐ��ɑ���
				if (m_Telop2Time >= 2.0f)
				{
					// 2�b��ɕ\�����I�t�ɂȂ�
					ptrStage2->SetDrawActive(false);
				}m_Event = false;
			}
		}
	}

	Vec3 EnemyObject::GetTargetPos()const {
		auto ptrTarget = GetStage()->GetSharedObject(L"Player");
		return ptrTarget->GetComponent<Transform>()->GetWorldPosition();
	}

	void EnemyObject::ApplyForce() {
		float elapsedTime = App::GetApp()->GetElapsedTime();
		auto elps = App::GetApp()->GetElapsedTime();
		EnemyTime += elps;
		if (EnemyTime >= 6.0f) {
			EnemyTime = 0.0f;
			auto ptrXA = App::GetApp()->GetXAudio2Manager();
			//�T�E���h�̍Đ�
			ptrXA->Start(L"EnemyVoice", 0, 0.2f);
			return;
		}
		m_Velocity += m_Force / (float)m_Speed * elapsedTime;
		auto ptrTrans = GetComponent<Transform>();
		auto pos = ptrTrans->GetPosition();
		pos += m_Velocity * elapsedTime;
		ptrTrans->SetPosition(pos);
	}

	//--------------------------------------------------------------------------------------
	//	�v���C���[���牓���Ƃ��̈ړ�
	//--------------------------------------------------------------------------------------
	shared_ptr<SeekFarState> SeekFarState::Instance() {
		static shared_ptr<SeekFarState> instance(new SeekFarState);
		return instance;
	}
	void SeekFarState::Enter(const shared_ptr<EnemyObject>& Obj) {
	}
	void SeekFarState::Execute(const shared_ptr<EnemyObject>& Obj) {
		auto ptrSeek = Obj->GetBehavior<SeekSteering>();
		//auto ptrSep = Obj->GetBehavior<SeparationSteering>();
		auto force = Obj->GetForce();
		force = ptrSeek->Execute(force, Obj->GetVelocity(), Obj->GetTargetPos());
		//force += ptrSep->Execute(force);
		Obj->SetForce(force);
		Obj->ApplyForce();
		float f = bsm::length(Obj->GetComponent<Transform>()->GetPosition() - Obj->GetTargetPos());
		if (f < Obj->GetStateChangeSize()) {
			Obj->GetStateMachine()->ChangeState(SeekNearState::Instance());
		}
	}

	void SeekFarState::Exit(const shared_ptr<EnemyObject>& Obj) {
	}

	//--------------------------------------------------------------------------------------
	//	�v���C���[����߂��Ƃ��̈ړ�
	//--------------------------------------------------------------------------------------
	shared_ptr<SeekNearState> SeekNearState::Instance() {
		static shared_ptr<SeekNearState> instance(new SeekNearState);
		return instance;
	}
	void SeekNearState::Enter(const shared_ptr<EnemyObject>& Obj) {
	}
	void SeekNearState::Execute(const shared_ptr<EnemyObject>& Obj) {
		auto ptrArrive = Obj->GetBehavior<ArriveSteering>();
		//auto ptrSep = Obj->GetBehavior<SeparationSteering>();
		auto force = Obj->GetForce();
		force = ptrArrive->Execute(force, Obj->GetVelocity(), Obj->GetTargetPos());
		//force += ptrSep->Execute(force);
		Obj->SetForce(force);
		Obj->ApplyForce();
		float f = bsm::length(Obj->GetComponent<Transform>()->GetPosition() - Obj->GetTargetPos());
		if (f >= Obj->GetStateChangeSize()) {
			Obj->GetStateMachine()->ChangeState(SeekFarState::Instance());
		}
	}

	void SeekNearState::Exit(const shared_ptr<EnemyObject>& Obj) {
	}
}