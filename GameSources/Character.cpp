/*!
@file Character.cpp
@brief �L�����N�^�[�Ȃǎ���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//�@���̂̃J�����}��
	//--------------------------------------------------------------------------------------
	//�\�z�Ɣj��
	Cameraman::Cameraman(const shared_ptr<Stage>& StagePtr,
		float ToPlayerLen
	) :
		GameObject(StagePtr),
		m_ToPlayerLen(ToPlayerLen)
	{}
	Cameraman::~Cameraman() {}

	//������
	void Cameraman::OnCreate() {
		//�����ʒu�Ȃǂ̐ݒ�
		auto ptr = GetComponent<Transform>();
		ptr->SetScale(0.25f, 0.25f, 0.25f);	//���a25�Z���`�̋���
		ptr->SetRotation(0.0f, 0.0f, 0.0f);
		ptr->SetPosition(0, +m_ToPlayerLen, 1.0f);
	}
	//����
	void Cameraman::OnUpdate() {
		//�v���C���[�̎擾
		auto ptrPlayer = GetStage()->GetSharedGameObject<Player>(L"Player");
		//�v���C���[�̃|�W�V�����擾
		auto playerPos = ptrPlayer->GetComponent<Transform>()->GetPosition();
		//�{�X�̎擾
		auto ptrEnemy = GetStage()->GetSharedGameObject<EnemyObject>(L"EnemyObject");
		//�{�X�̕\���̎擾
		auto EnemySetDrawActiveCount = ptrEnemy->GetEnemySetDrawActiveCount();
		ptrEnemy->SetEnemySetDrawActiveCount(EnemySetDrawActiveCount);

		//�J�����̃|�W�V�����擾
		auto ptrTrans = GetComponent<Transform>();
		auto pos = ptrTrans->GetPosition();
		//�J�����ƃv���C���[�̊Ԃ̋���
		Vec3 span = pos - playerPos;
		float nowLen = length(span);
		span.normalize();
		span *= m_ToPlayerLen;
		Vec3 target = playerPos + span;
		Easing<Vec3> easig;
		Vec3 v;
		target.y = playerPos.y + 2.0f;
		target.x = playerPos.x + 5.0f;

		m_PillarCount = ptrPlayer->GetPillarCount();
		ptrPlayer->SetPillarCount(m_PillarCount);
		if (m_Turn == 0)
		{
			if (m_PillarCount == 0)
			{
				//���̎擾
				auto ptrPillar = GetStage()->GetSharedGameObject<Pillar>(L"Pillar");
				auto PillarPos = ptrPillar->GetComponent<Transform>()->GetPosition();
				m_PPdistance = playerPos.x - PillarPos.x;
			}
				if (m_PPdistance < 2)
				{
					EnemySetDrawActiveCount = 0;
					target.y = playerPos.y + 2.0f;
					target.x = playerPos.x - 5.0f;
				}
			
		}

		if (m_PillarCount == 1)
		{
			//elapsedTime���擾���邱�Ƃɂ�莞�Ԃ��g����
			float elapsedTime = App::GetApp()->GetElapsedTime();
			//���Ԃ�ϐ��ɑ���
			m_TurnTime += elapsedTime;
			if (m_TurnTime > 2 && m_TurnTime < 2.1)
			{
				target.y = playerPos.y + 2.0f;
				target.x = playerPos.x + 5.0f;
				m_Turn = 1;
			}
		}

		//auto ptrEnemy = GetStage()->GetSharedGameObject<EnemyObject>(L"EnemyObject");
		auto enemyPos = ptrEnemy->GetComponent<Transform>()->GetPosition();

		float distance = playerPos.x - enemyPos.x;

		if (distance > -5.0f) {
			target.x = playerPos.x - 5.0f;
		}

		v = easig.EaseIn(EasingType::Cubic, pos, target, 1.0f, 1.0f);
		//if (playerPos.z > -7.0f) {
		//	target.y = playerPos.y + 2.0f;
		//	target.z = playerPos.z - 5.0f;
		//	target.x = playerPos.x;
		//}
		//else {
		//}
		//if (playerPos.x <= -6.5f || playerPos.x >= -7.5f) {
		//	v = easig.EaseIn(EasingType::Cubic, pos, target, 0.4f, 1.0f);
		//}
		//if (nowLen < 2.5f) {
		//	v = easig.EaseIn(EasingType::Cubic, pos, target, 0.7f, 1.0f);
		//}
		//else {
		//	v = easig.EaseIn(EasingType::Cubic, pos, target, 0.7f, 1.0f);
		//}
		ptrTrans->SetPosition(v);

	}
	//--------------------------------------------------------------------------------------
	//�@�I�[�v�j���O�J�����}��
	//--------------------------------------------------------------------------------------
	//�\�z�Ɣj��
	OpeningCameraman::OpeningCameraman(const shared_ptr<Stage>& StagePtr) :
		GameObject(StagePtr),
		m_StartPos(-20.0f, 5.0f, -20.0f),
		m_EndPos(18.0f, 2.0f, 10.0f),
		m_AtStartPos(0.0f, 0.0f, 0.0f),
		m_AtEndPos(18.0f, 0.0f, 18.0f),
		m_AtPos(m_AtStartPos),
		m_TotalTime(0.0f)
	{}
	OpeningCameraman::~OpeningCameraman() {}
	//������
	void OpeningCameraman::OnCreate() {
		//�����ʒu�Ȃǂ̐ݒ�
		auto ptr = GetComponent<Transform>();
		ptr->SetScale(0.25f, 0.25f, 0.25f);	//���a25�Z���`�̋���
		ptr->SetRotation(0.0f, 0.0f, 0.0f);
		ptr->SetPosition(m_StartPos);
		//�X�e�[�g�}�V���̍\�z
		m_StateMachine.reset(new StateMachine<OpeningCameraman>(GetThis<OpeningCameraman>()));
		//�ŏ��̃X�e�[�g��OpeningCameramanToGoalState�ɐݒ�
		m_StateMachine->ChangeState(OpeningCameramanToGoalState::Instance());
	}
	//����
	void OpeningCameraman::OnUpdate() {
		//�X�e�[�g�}�V����Update���s��
		//���̒��ŃX�e�[�g�̐؂�ւ����s����
		m_StateMachine->Update();
	}

	void OpeningCameraman::ToGoalEnterBehavior() {
		m_StartPos = Vec3(45.0f, 2.0f, 0.0f);
		m_EndPos = Vec3(50.0f, 2.0f, 0.0f);
		m_AtStartPos = Vec3(40.0f, 0.0f, 0.0f);
		m_AtEndPos = Vec3(60.0f, 2.0f, 0.0f);
		m_AtPos = m_AtStartPos;
		m_TotalTime = 0.0f;
	}

	void OpeningCameraman::ToStartEnterBehavior() {
		m_StartPos = Vec3(50.0f, 2.0f, -2.0f);
		m_EndPos = Vec3(47.0f, 2.0f, -2.0f);
		m_AtStartPos = Vec3(60.0f, 2.0f, 0.0f);
		m_AtEndPos = Vec3(60.0f, 2.0f, 0.0f);
		m_AtPos = m_AtStartPos;
		m_TotalTime = 0.0f;
	}

	bool OpeningCameraman::ExcuteBehavior(float totaltime) {
		float ElapsedTime = App::GetApp()->GetElapsedTime();
		m_TotalTime += ElapsedTime * 3.0f;
		if (m_TotalTime > totaltime) {
			return true;
		}
		Easing<Vec3> easing;
		auto TgtPos = easing.EaseInOut(EasingType::Cubic, m_StartPos, m_EndPos, m_TotalTime, totaltime);
		m_AtPos = easing.EaseInOut(EasingType::Cubic, m_AtStartPos, m_AtEndPos, m_TotalTime, totaltime);
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetPosition(TgtPos);
		return false;
	}

	void OpeningCameraman::EndStateEnterBehavior() {
		auto ptrGameGtage = GetTypeStage<GameStage>();
		ptrGameGtage->ToObjCamera();
	}




	//--------------------------------------------------------------------------------------
	//	class OpeningCameramanToGoalState : public ObjState<OpeningCameraman>;
	//--------------------------------------------------------------------------------------
	shared_ptr<OpeningCameramanToGoalState> OpeningCameramanToGoalState::Instance() {
		static shared_ptr<OpeningCameramanToGoalState> instance(new OpeningCameramanToGoalState);
		return instance;
	}
	void OpeningCameramanToGoalState::Enter(const shared_ptr<OpeningCameraman>& Obj) {
		Obj->ToGoalEnterBehavior();
	}
	void OpeningCameramanToGoalState::Execute(const shared_ptr<OpeningCameraman>& Obj) {
		if (Obj->ExcuteBehavior(5.0f)) {
			Obj->GetStateMachine()->ChangeState(OpeningCameramanToStartState::Instance());
		}
	}
	void OpeningCameramanToGoalState::Exit(const shared_ptr<OpeningCameraman>& Obj) {
	}
	//--------------------------------------------------------------------------------------
	//	class OpeningCameramanToStartState : public ObjState<OpeningCameraman>;
	//--------------------------------------------------------------------------------------
	shared_ptr<OpeningCameramanToStartState> OpeningCameramanToStartState::Instance() {
		static shared_ptr<OpeningCameramanToStartState> instance(new OpeningCameramanToStartState);
		return instance;
	}
	void OpeningCameramanToStartState::Enter(const shared_ptr<OpeningCameraman>& Obj) {
		Obj->ToStartEnterBehavior();
	}
	void OpeningCameramanToStartState::Execute(const shared_ptr<OpeningCameraman>& Obj) {
		if (Obj->ExcuteBehavior(3.0f)) {
			Obj->GetStateMachine()->ChangeState(OpeningCameramanEndState::Instance());
		}
	}
	void OpeningCameramanToStartState::Exit(const shared_ptr<OpeningCameraman>& Obj) {
	}

	//--------------------------------------------------------------------------------------
	//	class OpeningCameramanEndState : public ObjState<OpeningCameraman>;
	//--------------------------------------------------------------------------------------
	shared_ptr<OpeningCameramanEndState> OpeningCameramanEndState::Instance() {
		static shared_ptr<OpeningCameramanEndState> instance(new OpeningCameramanEndState);
		return instance;
	}
	void OpeningCameramanEndState::Enter(const shared_ptr<OpeningCameraman>& Obj) {
		Obj->EndStateEnterBehavior();
	}
	void OpeningCameramanEndState::Execute(const shared_ptr<OpeningCameraman>& Obj) {
	}
	void OpeningCameramanEndState::Exit(const shared_ptr<OpeningCameraman>& Obj) {
	}
	//--------------------------------------------------------------------------------------
	//�@�G���f�B���O�J�����}��
	//--------------------------------------------------------------------------------------
	//�\�z�Ɣj��
	//EndingCameraman::EndingCameraman(const shared_ptr<Stage>& StagePtr) :
	//	GameObject(StagePtr),
	//	m_StartPos(-20.0f, 5.0f, -20.0f),
	//	m_EndPos(18.0f, 2.0f, 10.0f),
	//	m_AtStartPos(0.0f, 0.0f, 0.0f),
	//	m_AtEndPos(18.0f, 0.0f, 18.0f),
	//	m_AtPos(m_AtStartPos),
	//	m_TotalTime(0.0f)
	//{}
	//EndingCameraman::~EndingCameraman() {}
	////������
	//void EndingCameraman::OnCreate() {
	//	//�����ʒu�Ȃǂ̐ݒ�
	//	auto ptr = GetComponent<Transform>();
	//	ptr->SetScale(0.25f, 0.25f, 0.25f);	//���a25�Z���`�̋���
	//	ptr->SetRotation(0.0f, 0.0f, 0.0f);
	//	ptr->SetPosition(m_StartPos);
	//	//�X�e�[�g�}�V���̍\�z
	//	m_StateMachine.reset(new StateMachine<EndingCameraman>(GetThis<EndingCameraman>()));
	//	//�ŏ��̃X�e�[�g��EndingCameramanToGoalState�ɐݒ�
	//	m_StateMachine->ChangeState(EndingCameramanToGoalState::Instance());
	//}
	////����
	//void EndingCameraman::OnUpdate() {
	//	//�X�e�[�g�}�V����Update���s��
	//	//���̒��ŃX�e�[�g�̐؂�ւ����s����
	//	m_StateMachine->Update();
	//}

	//void EndingCameraman::ToGoalEnterBehavior() {
	//	m_StartPos = Vec3(0.0f, 2.0f, 0.0f);
	//	m_EndPos = Vec3(0.0f, 2.0f, 0.0f);
	//	m_AtStartPos = Vec3(40.0f, 0.0f, 0.0f);
	//	m_AtEndPos = Vec3(60.0f, 2.0f, 0.0f);
	//	m_AtPos = m_AtStartPos;
	//	m_TotalTime = 0.0f;
	//}

	//void EndingCameraman::ToStartEnterBehavior() {
	//	m_StartPos = Vec3(50.0f, 2.0f, -2.0f);
	//	m_EndPos = Vec3(47.0f, 2.0f, -2.0f);
	//	m_AtStartPos = Vec3(60.0f, 2.0f, 0.0f);
	//	m_AtEndPos = Vec3(60.0f, 2.0f, 0.0f);
	//	m_AtPos = m_AtStartPos;
	//	m_TotalTime = 0.0f;
	//}

	//bool EndingCameraman::ExcuteBehavior(float totaltime) {
	//	float ElapsedTime = App::GetApp()->GetElapsedTime();
	//	m_TotalTime += ElapsedTime * 3.0f;
	//	if (m_TotalTime > totaltime) {
	//		return true;
	//	}
	//	Easing<Vec3> easing;
	//	auto TgtPos = easing.EaseInOut(EasingType::Cubic, m_StartPos, m_EndPos, m_TotalTime, totaltime);
	//	m_AtPos = easing.EaseInOut(EasingType::Cubic, m_AtStartPos, m_AtEndPos, m_TotalTime, totaltime);
	//	auto ptrTrans = GetComponent<Transform>();
	//	ptrTrans->SetPosition(TgtPos);
	//	return false;
	//}

	//void EndingCameraman::EndStateEnterBehavior() {
	//	auto ptrGameGtage = GetTypeStage<GameStage>();
	//	ptrGameGtage->ToMyCamera();
	//}




	////--------------------------------------------------------------------------------------
	////	class EndingCameramanToGoalState : public ObjState<EndingCameraman>;
	////--------------------------------------------------------------------------------------
	//shared_ptr<EndingCameramanToGoalState> EndingCameramanToGoalState::Instance() {
	//	static shared_ptr<EndingCameramanToGoalState> instance(new EndingCameramanToGoalState);
	//	return instance;
	//}
	//void EndingCameramanToGoalState::Enter(const shared_ptr<EndingCameraman>& Obj) {
	//	Obj->ToGoalEnterBehavior();
	//}
	//void EndingCameramanToGoalState::Execute(const shared_ptr<EndingCameraman>& Obj) {
	//	if (Obj->ExcuteBehavior(5.0f)) {
	//		Obj->GetStateMachine()->ChangeState(EndingCameramanToStartState::Instance());
	//	}
	//}
	//void EndingCameramanToGoalState::Exit(const shared_ptr<EndingCameraman>& Obj) {
	//}
	////--------------------------------------------------------------------------------------
	////	class EndingCameramanToStartState : public ObjState<EndingCameraman>;
	////--------------------------------------------------------------------------------------
	//shared_ptr<EndingCameramanToStartState> EndingCameramanToStartState::Instance() {
	//	static shared_ptr<EndingCameramanToStartState> instance(new EndingCameramanToStartState);
	//	return instance;
	//}
	//void EndingCameramanToStartState::Enter(const shared_ptr<EndingCameraman>& Obj) {
	//	Obj->ToStartEnterBehavior();
	//}
	//void EndingCameramanToStartState::Execute(const shared_ptr<EndingCameraman>& Obj) {
	//	if (Obj->ExcuteBehavior(3.0f)) {
	//		Obj->GetStateMachine()->ChangeState(EndingCameramanEndState::Instance());
	//	}
	//}
	//void EndingCameramanToStartState::Exit(const shared_ptr<EndingCameraman>& Obj) {
	//}

	////--------------------------------------------------------------------------------------
	////	class EndingCameramanEndState : public ObjState<EndingCameraman>;
	////--------------------------------------------------------------------------------------
	//shared_ptr<EndingCameramanEndState> EndingCameramanEndState::Instance() {
	//	static shared_ptr<EndingCameramanEndState> instance(new EndingCameramanEndState);
	//	return instance;
	//}
	//void EndingCameramanEndState::Enter(const shared_ptr<EndingCameraman>& Obj) {
	//	Obj->EndStateEnterBehavior();
	//}
	//void EndingCameramanEndState::Execute(const shared_ptr<EndingCameraman>& Obj) {
	//}
	//void EndingCameramanEndState::Exit(const shared_ptr<EndingCameraman>& Obj) {
	//}

}
//end basecross
