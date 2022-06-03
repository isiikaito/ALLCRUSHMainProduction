/*!
@file Player.h
@brief プレイヤーなど
*/

#pragma once
#include "stdafx.h"

namespace basecross{
	class Player : public GameObject
	{

		//文字列の表示
		void DrawStrings();

		const float MaxMoveSpeed; // 移動の最大速

		bool moveStop;//Playerの移動停止の判定

		Vec3 moveDir; // 移動方向ベクトル（単位ベクトル）
		Vec3 at1;
		float speed; // 移動の速さ

		float accel; // 加速度

		int GameOver = 0;

		//アイテムの所持数
		float itemCount;
		//
		float itemtime;
		//パワーアップアイテム
		int PowerCount;
		//プレイヤーのスピード
		float speed2;
		//落石のカウント
		float FallingCount;

		//柱カウント
		int PillarCount;
		float SoundTime;


		//出口にぶつかった
		int ExitCount;
		//プレイヤーとボスとの距離
		float PBdistance;

		//プレイヤーと柱の処理
		float PPdistance;


		//振り向きカウントタイム
		float m_TurnTime;

		//パワーアップがあるかないか
		int Power;
		
		int Gageflash;
		
		// テロップ
		void CreateTelop();
		float m_TelopTime;

		// テロップ2
		void CreateTelop2();
		float m_Telop2Time;

		// テロップ3
		void CreateTelop3();
		float m_Telop3Time;

		// テロップ4
		void CreateTelop4();
		float m_Telop4Time;

		//ゲームオーバーテロップ
		void CreateGMOTelop();
		float m_GMOTelopTime;

		Vec3 GetMoveVector() const;

		InputHandler<Player> m_InputHandler;
		//void MovePlayer();
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
		Effekseer::Handle m_handle1;
		Effekseer::ManagerRef m_manager1;
		EffekseerRendererDX11::RendererRef m_renderer1;
		Effekseer::EffectRef m_effect1;

		//void CreateEffect();
		//void CreateEffect1();
	public:
		//Player(const shared_ptr<Stage>& StagePtr);

		// ステージを渡せるコンストラクタが必須
		Player(const std::shared_ptr<Stage>& stage)
			: GameObject(stage), // ステージは親クラスに投げる
			MaxMoveSpeed(6.0f),
			moveStop(1.0f),	
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
			SoundTime(0.0f)
			//m_TotalTime(0.0f), m_isPlay(false),m_handle(0),
			//m_manager(nullptr), m_renderer(nullptr), m_effect(nullptr),
			//m_TotalTime1(0.0f), m_isPlay1(false),m_handle1(0),
			//m_manager1(nullptr), m_renderer1(nullptr), m_effect1(nullptr)
		{
		}
		//virtual void OnDraw() override;

		//Aボタン
		void OnPushA();
		//Bボタン
		void OnPushB(){}
		//Yボタン
		void OnPushY();
		//十字キー上
		void OnPushUP() {}
		//十字キー下
		void OnPushDOWN() {}
		//Xボタン
		void OnPushX();
		//敵の攻撃(/)にぶつかったとき
		virtual void OnCollisionEnter(shared_ptr<GameObject>& Other);
		void OnCreate() override; // オブジェクトの初期化用関数（UnityのStart関数）
		void OnUpdate() override; // オブジェクトのフレームごとの処理（UnityのUpdate関数）
		void OnUpdate2() override; // オブジェクトのフレームごとの処理（UnityのUpdate関数）
		void OnAttack();
		//柱カウント
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
		//パワーアップを使ったかどうか
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
		int GetGameOver()const {
			return GameOver;
		}
		void SetGameOver(int GameOver) {
			GameOver = GameOver;
		}

	};
}
//end basecross

