/*!
@file Enemy.cpp
@brief 敵の実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	追いかける配置オブジェクト
	//--------------------------------------------------------------------------------------
	//構築と破棄
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

	void EnemyObject::OnCreate() {	//初期化
		auto ptrTransform = GetComponent<Transform>();
		ptrTransform->SetPosition(60.0f, 0.0f, 0.0f);
		ptrTransform->SetScale(3.0f, 3.0f, 2.0f);
		ptrTransform->SetRotation(0.0f, 0.0f, 0.0f);

		Mat4x4 spanMat; // モデルとトランスフォームの間の差分行列
		spanMat.affineTransformation(
			Vec3(0.2f, 0.1f, 0.06f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, XM_PI * -0.5f, 0.0f),
			Vec3(0.0f, -0.5f, -1.0f)
		);

		auto ptrColl = AddComponent<CollisionObb>(); //Obbの衝突判定をつける
		auto ptrGra = AddComponent<Gravity>();		 //重力をつける
		auto ptrShadow = AddComponent<Shadowmap>();	 //影をつける（シャドウマップを描画する）
		ptrShadow->SetMeshResource(L"EnemyRun_MESH");//影をつける
		ptrShadow->SetMeshToTransformMatrix(spanMat);

		auto ptrDraw = AddComponent<BcPNTnTBoneModelDraw>();
		ptrDraw->SetFogEnabled(false);         
		ptrDraw->SetDiffuse(Col4(1.0, 1.0, 1.0, 0.1)); //R    G    B    A
		ptrDraw->SetMeshResource(L"EnemyRun_MESH_WITH_TAN");
		ptrDraw->SetMeshToTransformMatrix(spanMat);
		ptrDraw->AddAnimation(L"Default", 0, 30, true, 30.0f);
		ptrDraw->ChangeCurrentAnimation(L"Default");
			
		m_StateMachine.reset(new StateMachine<EnemyObject>(GetThis<EnemyObject>())); //ステートマシンの構築	
		m_StateMachine->ChangeState(SeekFarState::Instance()); //最初のステートをSeekFarStateに設定
		GetStage()->SetSharedGameObject(L"EnemyObject", GetThis<EnemyObject>());//読み込みの設定をする
	}

	void EnemyObject::OnCollisionEnter(shared_ptr<GameObject>& Other) {
		auto ptr = dynamic_pointer_cast<FallingRock>(Other); //落石に当たったら
		
		if (ptr) {
			GetStage()->RemoveGameObject<FallingRock>(Other); //落石オブジェクトを消す
			StopCount = 1;	
			m_Speed = 0; //ボスのスピードを0にする
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
		auto ptrPlayer = GetStage()->GetSharedGameObject<Player>(L"Player"); //プレイヤーの取得
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
       
		if (StopCount==1) //ボスのStopCountが１だった場合
		{  
		   StopTime += elapsedTime; //時間を変数に足す
		   if (StopTime >=2.0f)
		   {
			   m_Speed=20;
			   StopCount = 0;
			   StopTime = 0.0f;
		   }
		   return;
		}

		m_Force = Vec3(0);
		m_StateMachine->Update();//ステートマシンのUpdateを行う。この中でステートの切り替えが行われる
		auto ptrUtil = GetBehavior<UtilBehavior>();
		ptrUtil->RotToHead(1.0f);
		auto ptrDraw = GetComponent<BcPNTnTBoneModelDraw>();//アニメーション
		ptrDraw->UpdateAnimation(elapsedTime);

        auto& app = App::GetApp();
		float delta = app->GetElapsedTime();
		auto& device = app->GetInputDevice();
		const auto& pad = device.GetControlerVec()[0];

		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec(); //コントローラの取得
		//Bボタンが押されているとき
		if (cntlVec[0].wButtons & XINPUT_GAMEPAD_B) {
			SetDrawActive(true);//表示
		}
		//Bボタンが押されていないとき
		else {
			SetDrawActive(false);//非表示
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
				auto ptrStage2 = GetStage()->GetSharedGameObject<Telop2>(L"Telop2"); // 今だ！！テロップ
				ptrStage2->SetDrawActive(true);
				m_Telop2Time += elapsedTime; // 時間の変数に足す
				if (m_Telop2Time >= 2.0f)
				{
					// 2秒後に表示がオフになる
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
			//サウンドの再生
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
	//	プレイヤーから遠いときの移動
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
	//	プレイヤーから近いときの移動
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