/*!
@file Enemy.h
@brief �G�Ȃ�
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	�ǂ�������G�I�u�W�F�N�g
	//--------------------------------------------------------------------------------------

	class EnemyObject : public GameObject {
		//�X�e�[�g�}�V�[��
		unique_ptr< StateMachine<EnemyObject> >  m_StateMachine;
		Vec3 m_StartPos;              //�ʒu
		float m_StateChangeSize;
	    Vec3 m_Force;	              //�t�H�[�X
		Vec3 m_Velocity;              //���x
		int m_Speed=30;               //�X�s�[�h
		float EnemyTime;              //����
		float StopTime;               //�{�X�̎~�߂Ă��鎞��
		int StopCount;                //�{�X���������~�߂Ă��邩�ǂ���
		int PillarCount;              //���������Ă��邩�ǂ���
		int m_EnemySetDrawActiveCount;//�{�X�̕\���J�E���g
		float m_Telop2Time;           // �e���b�v2
		bool m_Event;
	
		
		

		
		

	public:
		//�\�z�Ɣj��
		EnemyObject(const shared_ptr<Stage>& StagePtr); // , const Vec3& StartPos);
		virtual ~EnemyObject();
		//������
		virtual void OnCreate() override;
		//�A�N�Z�T
		const unique_ptr<StateMachine<EnemyObject>>& GetStateMachine() {
			return m_StateMachine;
		}
		float GetStateChangeSize() const {
			return m_StateChangeSize;
		}
		const Vec3& GetForce()const {
			return m_Force;
		}
		void SetForce(const Vec3& f) {
			m_Force = f;
		}
		void AddForce(const Vec3& f) {
			m_Force += f;
		}
		const Vec3& GetVelocity()const {
			return m_Velocity;
		}
		void SetVelocity(const Vec3& v) {
			m_Velocity = v;
		}
		void ApplyForce();
		/*void OnPushB();*/
		/*void OnPushX() {}*/
		Vec3 GetTargetPos()const;
		//����
		virtual void OnUpdate() override;
		virtual void OnCollisionEnter(shared_ptr<GameObject>& Other);
		int GetEnemySetDrawActiveCount()const {
			return m_EnemySetDrawActiveCount;
		}
		void SetEnemySetDrawActiveCount(int m_EnemySetDrawActiveCount) {
			m_EnemySetDrawActiveCount = m_EnemySetDrawActiveCount;
		}
		
	};

	//--------------------------------------------------------------------------------------
	//	�p�r: �v���C���[���牓���Ƃ��̈ړ�
	//--------------------------------------------------------------------------------------
	class SeekFarState : public ObjState<EnemyObject>
	{
		SeekFarState() {}
	public:
		static shared_ptr<SeekFarState> Instance();
		virtual void Enter(const shared_ptr<EnemyObject>& Obj)override;
		virtual void Execute(const shared_ptr<EnemyObject>& Obj)override;
		virtual void Exit(const shared_ptr<EnemyObject>& Obj)override;
	};

	//--------------------------------------------------------------------------------------
	//	�p�r: �v���C���[����߂��Ƃ��̈ړ�
	//--------------------------------------------------------------------------------------
	class SeekNearState : public ObjState<EnemyObject>
	{
		SeekNearState() {}
	public:
		static shared_ptr<SeekNearState> Instance();
		virtual void Enter(const shared_ptr<EnemyObject>& Obj)override;
		virtual void Execute(const shared_ptr<EnemyObject>& Obj)override;
		virtual void Exit(const shared_ptr<EnemyObject>& Obj)override;
	};
	
}

