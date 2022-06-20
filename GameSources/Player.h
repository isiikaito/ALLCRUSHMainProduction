/*!
@file Player.h
@brief �v���C���[�Ȃ�
*/

#pragma once
#include "stdafx.h"

namespace basecross{
	enum class  GameState {
		Game,
		Down,
		FadeStart,
		FadeOut,
		ChangeStage
	};

	class Player : public GameObject
	{
		const float MaxMoveSpeed; // �ړ��̍ő呬
		bool moveStop;            //Player�̈ړ���~�̔���
		Vec3 moveDir;             // �ړ������x�N�g���i�P�ʃx�N�g���j
		Vec3 at1;
		float EndPos;			  // �Q�[���I�[�o�[���̃v���C���[���W
		float EndAngle;			  // �Q�[���I�[�o�[���̃v���C���[�̌���
		float speed;              // �ړ��̑���
		float accel;              // �����x
		int GameOver = 0;
		float itemCount;          //�A�C�e���̏�����
		float itemtime;           //�A�C�e���̎�������
		int PowerCount;           //�p���[�A�b�v�A�C�e��
		float speed2;             //�v���C���[�̃X�s�[�h
		int FallingCount;	      //���΂̃J�E���g
		int PillarCount;	      //�������Ă��邩�ǂ���
		float SoundTime;
		int ExitCount;            //�o���ɂԂ�����
	    float PBdistance;         //�v���C���[�ƃ{�X�Ƃ̋���
		float PPdistance;         //�v���C���[�ƒ��̏���
		float m_TurnTime;         //�U��������璼��܂ł̎���
		int Power;                //�p���[�A�b�v�����邩�Ȃ���
		int Gageflash;            //�p���[�A�b�v���g�������ǂ���
		GameState m_State;		  //�Q�[���I�[�o�[�p�̃X�e�[�g
		float m_TelopTime;	// �e���b�v
		bool m_Event;

		// �e���b�v2
		
		float m_Telop2Time;

		// �e���b�v3
		/*void CreateTelop3();*/
		float m_Telop3Time;

		// �e���b�v4
		/*void CreateTelop4();*/
		float m_Telop4Time;

		//�Q�[���I�[�o�[�e���b�v
		//void CreateGMOTelop();
		//float m_GMOTelopTime;

		/*Vec3 GetMoveVector() const;*/

		InputHandler<Player> m_InputHandler;
		//void MovePlayer();
		InputHandler2<Player> m_InputHandler2;
		shared_ptr<SoundItem> m_BGM;
		void OnDestroy();

		// �G�t�F�N�g�֘A
		//float m_TotalTime;
		//bool m_isPlay;
		//Effekseer::Handle m_handle;
		//Effekseer::ManagerRef m_manager;
		//EffekseerRendererDX11::RendererRef m_renderer;
		//Effekseer::EffectRef m_effect;

		// �G�t�F�N�g�֘A1
		//float m_TotalTime1;
		//bool m_isPlay1;
		//Effekseer::Handle m_handle1;
		//Effekseer::ManagerRef m_manager1;
		//EffekseerRendererDX11::RendererRef m_renderer1;
		//Effekseer::EffectRef m_effect1;

		//void CreateEffect();
		//void CreateEffect1();

		//�I�[�v�j���O
		float m_opningStop;
		float m_TotalTime1;
		bool m_isPlay1;
		/*Effekseer::Handle m_handle1;
		Effekseer::ManagerRef m_manager1;
		EffekseerRendererDX11::RendererRef m_renderer1;
		Effekseer::EffectRef m_effect1;*/

		//void CreateEffect();
		//void CreateEffect1();
	public:
		//Player(const shared_ptr<Stage>& StagePtr);

		// �X�e�[�W��n����R���X�g���N�^���K�{
		Player(const std::shared_ptr<Stage>& stage)
			: GameObject(stage), // �X�e�[�W�͐e�N���X�ɓ�����
			MaxMoveSpeed(6.0f),
			moveStop(1.0f),	
			EndPos(1.0f),
			EndAngle(180.0f * XM_PI / 180.0f),
			moveDir(0.0f, 0.0f, 0.0f),
			at1(0.0f,0.0f,0.0f),
			speed(0.0f),
			speed2(1.0f),
			accel(0.0f),
			itemCount(0),
			PowerCount(0),
			Power(1),
			ExitCount(0),
			Gageflash(0),
			SoundTime(0.0f),
			FallingCount(0),
			PillarCount(0),
			PBdistance(0),
			PPdistance(0),
			itemtime(0.0f),
			m_TelopTime(0.0f),
			m_Telop2Time(0.0f),
			m_Telop3Time(0.0f),
			m_Telop4Time(0.0f),
			m_TotalTime1(0.0f),
			m_isPlay1(0),
			m_opningStop(0.0f),
			m_TurnTime(0.0f),
			m_Event(false),
			m_State(GameState::Game)
			
			//m_TotalTime(0.0f), m_isPlay(false),m_handle(0),
			//m_manager(nullptr), m_renderer(nullptr), m_effect(nullptr),
			//m_TotalTime1(0.0f), m_isPlay1(false),m_handle1(0),
			//m_manager1(nullptr), m_renderer1(nullptr), m_effect1(nullptr)
		{
		}
		//virtual void OnDraw() override;

		//A�{�^��
		void OnPushA();
		//B�{�^��
		void OnPushB(){}
		//Y�{�^��
		void OnPushY();
		//�\���L�[��
		void OnPushUP() {}
		//�\���L�[��
		void OnPushDOWN() {}
		//X�{�^��
		void OnPushX();
		//�G�̍U��(/)�ɂԂ������Ƃ�
		virtual void OnCollisionEnter(shared_ptr<GameObject>& Other);
		void OnCreate() override; // �I�u�W�F�N�g�̏������p�֐��iUnity��Start�֐��j
		void OnUpdate() override; // �I�u�W�F�N�g�̃t���[�����Ƃ̏����iUnity��Update�֐��j
		void OnUpdate2() override; // �I�u�W�F�N�g�̃t���[�����Ƃ̏����iUnity��Update�֐��j
		//���J�E���g
		int GetPillarCount()const {
			return PillarCount;
		}
		void SetPillarCount(int PillarCount) {
			PillarCount = PillarCount;
		}
		//�ǂ���������
		int GetPowerCount()const {
			return PowerCount;
		}
		void SetPowerCount(int PowerCount)
		{
			PowerCount = PowerCount;
		}

		//�p���[�A�b�v
		int GetPower()const {
			return Power;
		}
		void SetPower(int Power)
		{
			Power = Power;
		}
		//�p���[�A�b�v���g�������ǂ���
		int GetGageflash()const {
			return Gageflash;
		}
		void SetGageflash(int Gageflash)
		{
			Gageflash = Gageflash;
		}

		//�o���ɓ����������ǂ���
		int GetExitCount()const {
			return ExitCount;
		}
		void SetExitCount(int ExitCount)
		{
			ExitCount = ExitCount;
		}
		//���C�x���g�������������ǂ���
		bool GetPEvent()const {
			return m_Event;
		}
		void SetPEvent(bool m_Event)
		{
			m_Event = m_Event;
		}

		int GetGameOver()const {
			return GameOver;
		}
		void SetGameOver(int GameOver) {
			GameOver = GameOver;
		}
		GameState GetGameState() {
			return m_State;
		}
		void SetGameState(GameState s) {
			m_State = s;
		}

	};
}
//end basecross

