/*!
@file Character.cpp
@brief �L�����N�^�[�Ȃǎ���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{
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
		auto ptrPlayer = GetStage()->GetSharedGameObject<Player>(L"Player");
		auto playerPos = ptrPlayer->GetComponent<Transform>()->GetPosition();
		auto ptrTrans = GetComponent<Transform>();
		auto pos = ptrTrans->GetPosition();
		Vec3 span = pos - playerPos;
		float nowLen = length(span);
		span.normalize();
		span *= m_ToPlayerLen;
		Vec3 target = playerPos + span;
		Easing<Vec3> easig;
		Vec3 v;
		auto ptrPillar = GetStage()->GetSharedGameObject<Pillar>(L"Pillar");
		auto pillarPos = ptrPillar->GetComponent<Transform>()->GetPosition();
		float PillarDis = playerPos.x - pillarPos.x;

		int EnemySetDrawActiveCount(0);
		int PillarCount(0);

		PillarCount = ptrPlayer->GetPillarCount();
		ptrPlayer->SetPillarCount(PillarCount);


		if (m_Turn == 0)
		{
			if (PillarDis < 10)
			{
				EnemySetDrawActiveCount = 0;
				target.x = playerPos.x - 5.0f;
			}
		}

		//������ꂽ��
		if (PillarCount == 1)
		{

			//elapsedTime���擾���邱�Ƃɂ�莞�Ԃ��g����
			float elapsedTime = App::GetApp()->GetElapsedTime();
			//���Ԃ�ϐ��ɑ���
			m_TurnTime += elapsedTime;
			//�������Ă����b���
			if (m_TurnTime > 2 && m_TurnTime < 2.1)
			{
				EnemySetDrawActiveCount = 1;
				//�J���������ʂ�����
				target.x = playerPos.x + 5.0f;

				m_Turn = 1;
			}

		}

		target.y = playerPos.y + 2.0f;
		target.x = playerPos.x + 5.0f;

		//�{�X�̍��W�擾
		auto ptrEnemy = GetStage()->GetSharedGameObject<EnemyObject>(L"EnemyObject");
		auto enemyPos = ptrEnemy->GetComponent<Transform>()->GetPosition();
		float distance = playerPos.x - enemyPos.x;

		if (distance > -5.0f) {//�G�ɓ���������
			target.y = playerPos.y + 2.0f;
			target.x = playerPos.x - 5.0f;
		}


		v = easig.EaseIn(EasingType::Cubic, pos, target, 1.0f, 1.0f);

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
}
//end basecross
