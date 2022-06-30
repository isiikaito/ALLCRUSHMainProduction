/*!
@file Player.h
@brief プレイヤーなど
*/

#pragma once
#include "stdafx.h"

namespace basecross{
	enum class  GameState {
		Game,
		Down,
		FadeStart,
		FadeOut,
		ChangeStage,
		GameExit
	};

	class Player : public GameObject
	{
		const float MaxMoveSpeed; // 移動の最大速
		bool moveStop;            //Playerの移動停止の判定
		Vec3 moveDir;             // 移動方向ベクトル（単位ベクトル）
		Vec3 at1;
		float EndPos;			  // ゲームオーバー時のプレイヤー座標
		float EndAngle;			  // ゲームオーバー時のプレイヤーの向き
		float speed;              // 移動の速さ
		float accel;              // 加速度
		int GameOver = 0;
		float itemCount;          //アイテムの所持数
		float itemtime;           //アイテムの持続時間
		int PowerCount;           //パワーアップアイテム
		float speed2;             //プレイヤーのスピード
		int FallingCount;	      //落石のカウント
		int PillarCount;	      //柱が壊れているかどうか
		float SoundTime;
		int ExitCount;            //出口にぶつかった
	    float PBdistance;         //プレイヤーとボスとの距離
		float PPdistance;         //プレイヤーと柱の処理
		float m_TurnTime;         //振り向きから直るまでの時間
		int Power;                //パワーアップがあるかないか
		int Gageflash;            //パワーアップを使ったかどうか
		GameState m_State;		  //ゲームオーバー用のステート
		bool m_Event;             //柱のイベントを行うかどうか
		float m_TelopTime;	      // テロップ
		float m_Telop2Time;       // テロップ2	
		float m_Telop3Time;       // テロップ3
		float m_Telop4Time;       // テロップ4


		/*Vec3 GetMoveVector() const;*/

		InputHandler<Player> m_InputHandler;
		
		InputHandler2<Player> m_InputHandler2;
		shared_ptr<SoundItem> m_BGM;
		void OnDestroy();

		// エフェクト関連
		//float m_TotalTime;
		//bool m_isPlay;
		//Effekseer::Handle m_handle;
		//Effekseer::ManagerRef m_manager;
		//EffekseerRendererDX11::RendererRef m_renderer;
		//Effekseer::EffectRef m_effect;

		// エフェクト関連1
		//float m_TotalTime1;
		//bool m_isPlay1;
		//Effekseer::Handle m_handle1;
		//Effekseer::ManagerRef m_manager1;
		//EffekseerRendererDX11::RendererRef m_renderer1;
		//Effekseer::EffectRef m_effect1;

		//void CreateEffect();
		//void CreateEffect1();

		//オープニング
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

		// ステージを渡せるコンストラクタが必須
		Player(const std::shared_ptr<Stage>& stage)
			: GameObject(stage), // ステージは親クラスに投げる
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

		void OnPushX();           //コントローラーのボタン判定X
		void OnPushA();           //コントローラーのボタン判定A
		void OnPushUP() {}        //コントローラーのボタン判定十字キー上
		void OnPushDOWN(){}       //コントローラーのボタン判定十字キー下
		void OnPushY();           //コントローラーのボタン判定Y
		void OnPushB() {}         //コントローラーのボタン判定B
		void TelopManager();      //テロップを出す
		void BreakWall();         //壁を壊す処理
		void BreakPillar();       //柱を壊す処理
		void BreakObstacle();     //障害物を壊す処理
		void Enemydistance();     //プレイヤーとボスとの距離
		void Pillardistance();    //柱との距離
		void OnCreate() override; // オブジェクトの初期化用関数（UnityのStart関数）
		void OnUpdate() override; // オブジェクトのフレームごとの処理（UnityのUpdate関数）

		virtual void OnCollisionEnter(shared_ptr<GameObject>& Other);//敵の攻撃にぶつかったとき
		
		
		//柱が壊れているか判定する
		int GetPillarCount()const {
			return PillarCount;
		}
		void SetPillarCount(int PillarCount) {
			PillarCount = PillarCount;
		}
		//壁を殴った回数
		int GetPowerCount()const {
			return PowerCount;
		}
		void SetPowerCount(int PowerCount)
		{
			PowerCount = PowerCount;
		}

		//パワーアップ
		int GetPower()const {
			return Power;
		}
		void SetPower(int Power)
		{
			Power = Power;
		}
		//パワーアップを使ったかどうか判定する
		int GetGageflash()const {
			return Gageflash;
		}
		void SetGageflash(int Gageflash)
		{
			Gageflash = Gageflash;
		}

		//出口に当たったかどうか
		int GetExitCount()const {
			return ExitCount;
		}
		void SetExitCount(int ExitCount)
		{
			ExitCount = ExitCount;
		}
		//柱イベントが発生したかどうか
		bool GetPEvent()const {
			return m_Event;
		}
		void SetPEvent(bool m_Event)
		{
			m_Event = m_Event;
		}
		//ゲームオーバー判定
		int GetGameOver()const {
			return GameOver;
		}
		void SetGameOver(int GameOver) {
			GameOver = GameOver;
		}
		//ステージを切り替え
		GameState GetGameState() {
			return m_State;
		}
		void SetGameState(GameState s) {
			m_State = s;
		}

	};
}
//end basecross

