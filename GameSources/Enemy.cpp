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
	EnemyObject::EnemyObject(const shared_ptr<Stage>& StagePtr, const Vec3& StartPos) :
		GameObject(StagePtr),
		m_StartPos(StartPos),
		m_StateChangeSize(5.0f),
		m_Force(0),
		m_Velocity(0)
	{
	}
	EnemyObject::~EnemyObject() {}

	//������
	void EnemyObject::OnCreate() {
		auto ptrTransform = GetComponent<Transform>();
		ptrTransform->SetPosition(m_StartPos);
		ptrTransform->SetScale(0.125f, 0.25f, 0.25f);
		ptrTransform->SetRotation(0.0f, 0.0f, 0.0f);

		//�I�u�W�F�N�g�̃O���[�v�𓾂�
		auto group = GetStage()->GetSharedObjectGroup(L"SeekGroup");
		//�O���[�v�Ɏ������g��ǉ�
		group->IntoGroup(GetThis<EnemyObject>());
		//Obb�̏Փ˔��������
		auto ptrColl = AddComponent<CollisionObb>();
		//�d�͂�����
		auto ptrGra = AddComponent<Gravity>();
		//�����s��������
		auto PtrSep = GetBehavior<SeparationSteering>();
		PtrSep->SetGameObjectGroup(group);
		//�e������
		auto ptrShadow = AddComponent<Shadowmap>();
		ptrShadow->SetMeshResource(L"DEFAULT_CUBE");

		auto ptrDraw = AddComponent<BcPNTStaticDraw>();
		ptrDraw->SetFogEnabled(true);
		ptrDraw->SetMeshResource(L"DEFAULT_CUBE");
		ptrDraw->SetTextureResource(L"TRACE_TX");
		//��������������
		SetAlphaActive(true);

		//�X�e�[�g�}�V���̍\�z
		m_StateMachine.reset(new StateMachine<EnemyObject>(GetThis<EnemyObject>()));
		//�ŏ��̃X�e�[�g��SeekFarState�ɐݒ�
		m_StateMachine->ChangeState(SeekFarState::Instance());
	}


	//����
	void EnemyObject::OnUpdate() {
		m_Force = Vec3(0);
		//�X�e�[�g�}�V����Update���s��
		//���̒��ŃX�e�[�g�̐؂�ւ����s����
		m_StateMachine->Update();
		auto ptrUtil = GetBehavior<UtilBehavior>();
		ptrUtil->RotToHead(1.0f);
	}


	Vec3 EnemyObject::GetTargetPos()const {
		auto ptrTarget = GetStage()->GetSharedObject(L"Player");
		return ptrTarget->GetComponent<Transform>()->GetWorldPosition();
	}


	void EnemyObject::ApplyForce() {
		float elapsedTime = App::GetApp()->GetElapsedTime();
		m_Velocity += m_Force * elapsedTime;
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
		auto ptrSep = Obj->GetBehavior<SeparationSteering>();
		auto force = Obj->GetForce();
		force = ptrSeek->Execute(force, Obj->GetVelocity(), Obj->GetTargetPos());
		force += ptrSep->Execute(force);
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
		auto ptrSep = Obj->GetBehavior<SeparationSteering>();
		auto force = Obj->GetForce();
		force = ptrArrive->Execute(force, Obj->GetVelocity(), Obj->GetTargetPos());
		force += ptrSep->Execute(force);
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