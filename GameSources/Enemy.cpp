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
	EnemyObject::EnemyObject(const shared_ptr<Stage>& StagePtr) : //, const Vec3& StartPos) :
		GameObject(StagePtr),
		//m_StartPos(StartPos),
		m_StateChangeSize(5.0f),
		m_Force(0),
		m_Velocity(0),
		StopCount(0)
	{
	}
	EnemyObject::~EnemyObject() {}

	//������
	void EnemyObject::OnCreate() {
		auto ptrTransform = GetComponent<Transform>();
		//ptrTransform->SetPosition(m_StartPos);
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

		//Obb�̏Փ˔��������
		auto ptrColl = AddComponent<CollisionObb>();

		//�d�͂�����
		auto ptrGra = AddComponent<Gravity>();

		//�e������i�V���h�E�}�b�v��`�悷��j
		auto ptrShadow = AddComponent<Shadowmap>();
		//�e������
		ptrShadow->SetMeshResource(L"EnemyRun_MESH");
		ptrShadow->SetMeshToTransformMatrix(spanMat);

		auto ptrDraw = AddComponent<BcPNTnTBoneModelDraw>();

		ptrDraw->SetFogEnabled(false);
		                       //R    G    B    A
		ptrDraw->SetDiffuse(Col4(1.0, 1.0, 1.0, 0.1));
		ptrDraw->SetMeshResource(L"EnemyRun_MESH_WITH_TAN"); //EnemyRun_MESH
		//ptrDraw->SetNormalMapTextureResource(L"OBJECT_NORMAL_TX");
		ptrDraw->SetMeshToTransformMatrix(spanMat);
		ptrDraw->AddAnimation(L"Default", 0, 30, true, 30.0f);
		ptrDraw->ChangeCurrentAnimation(L"Default");
		
		
		//��������������
		//png�̃e�N�X�`���𓧖��������鏈��(jpg�͓������ł��Ȃ��̂Ŗ���)
		/*SetAlphaActive(false);*/
		//�{�X�̕\�����̂��Ȃ�������(jpg�ł�png�ł��֌W�Ȃ�)
		/*SetDrawActive(false);*/
	/*	ptrColl->SetDrawActive(true);*/
		//�X�e�[�g�}�V���̍\�z
		m_StateMachine.reset(new StateMachine<EnemyObject>(GetThis<EnemyObject>()));
		//�ŏ��̃X�e�[�g��SeekFarState�ɐݒ�
		m_StateMachine->ChangeState(SeekFarState::Instance());
	}

void EnemyObject::OnCollisionEnter(shared_ptr<GameObject>& Other) {
		//���΂ɓ���������
		auto ptr = dynamic_pointer_cast<FallingRock>(Other);
		
		  
		if (ptr) {
			//���΃I�u�W�F�N�g������
			GetStage()->RemoveGameObject<FallingRock>(Other);
			StopCount = 1;
			//�{�X�̃X�s�[�h��0�ɂ���
			m_Speed = 0;
		
		}
		
	}
	//����
	void EnemyObject::OnUpdate() {
		
       //�{�X��HP��0�������ꍇ
		if (StopCount==1)
		{  
			float elapsedTime = App::GetApp()->GetElapsedTime();
			
			
           //���Ԃ�ϐ��ɑ���
		   StopTime += elapsedTime;
		   if (StopTime >=2.0f)
		   {
			   //�{�X�̃X�s�[�h���P�ɂ���
			   m_Speed=20;
		   }
		}

		m_Force = Vec3(0);
		//�X�e�[�g�}�V����Update���s��
		//���̒��ŃX�e�[�g�̐؂�ւ����s����
		m_StateMachine->Update();
		auto ptrUtil = GetBehavior<UtilBehavior>();
		ptrUtil->RotToHead(1.0f);

		//�A�j���[�V����
		auto ptrDraw = GetComponent<BcPNTnTBoneModelDraw>();
		float elapsedTime = App::GetApp()->GetElapsedTime();
		ptrDraw->UpdateAnimation(elapsedTime);

         auto& app = App::GetApp();

		float delta = app->GetElapsedTime();

		auto& device = app->GetInputDevice();
		const auto& pad = device.GetControlerVec()[0];

		//�R���g���[���̎擾
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();

		//B�{�^����������Ă���Ƃ�
		if (cntlVec[0].wButtons & XINPUT_GAMEPAD_B) {
			//�\��
			SetDrawActive(true);
		}
		//B�{�^����������Ă��Ȃ��Ƃ�
		else {
			/*SetAlphaActive(true);*/
			SetDrawActive(false);
		}
		
		////�R���g���[���`�F�b�N���ē��͂�����΃R�}���h�Ăяo��
		//m_InputHandler.PushHandle(GetThis<EnemyObject>());

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

		m_Velocity += m_Force/m_Speed * elapsedTime;
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

	
	/*void EnemyObject::OnPushB() {
		


	}*/

}