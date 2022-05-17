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

	//初期化
	void EnemyObject::OnCreate() {
		auto ptrTransform = GetComponent<Transform>();
		//ptrTransform->SetPosition(m_StartPos);
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

		//Obbの衝突判定をつける
		auto ptrColl = AddComponent<CollisionObb>();

		//重力をつける
		auto ptrGra = AddComponent<Gravity>();

		//影をつける（シャドウマップを描画する）
		auto ptrShadow = AddComponent<Shadowmap>();
		//影をつける
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
		
		
		//透明処理をする
		//pngのテクスチャを透明化させる処理(jpgは透明化できないので無理)
		/*SetAlphaActive(false);*/
		//ボスの表示自体をなくす処理(jpgでもpngでも関係ない)
		/*SetDrawActive(false);*/
	/*	ptrColl->SetDrawActive(true);*/
		//ステートマシンの構築
		m_StateMachine.reset(new StateMachine<EnemyObject>(GetThis<EnemyObject>()));
		//最初のステートをSeekFarStateに設定
		m_StateMachine->ChangeState(SeekFarState::Instance());
	}

void EnemyObject::OnCollisionEnter(shared_ptr<GameObject>& Other) {
		//落石に当たったら
		auto ptr = dynamic_pointer_cast<FallingRock>(Other);
		
		  
		if (ptr) {
			//落石オブジェクトを消す
			GetStage()->RemoveGameObject<FallingRock>(Other);
			StopCount = 1;
			//ボスのスピードを0にする
			m_Speed = 0;
		
		}
		
	}
	//操作
	void EnemyObject::OnUpdate() {
		
       //ボスのHPが0だった場合
		if (StopCount==1)
		{  
			float elapsedTime = App::GetApp()->GetElapsedTime();
			
			
           //時間を変数に足す
		   StopTime += elapsedTime;
		   if (StopTime >=2.0f)
		   {
			   //ボスのスピードを１にする
			   m_Speed=20;
		   }
		}

		m_Force = Vec3(0);
		//ステートマシンのUpdateを行う
		//この中でステートの切り替えが行われる
		m_StateMachine->Update();
		auto ptrUtil = GetBehavior<UtilBehavior>();
		ptrUtil->RotToHead(1.0f);

		//アニメーション
		auto ptrDraw = GetComponent<BcPNTnTBoneModelDraw>();
		float elapsedTime = App::GetApp()->GetElapsedTime();
		ptrDraw->UpdateAnimation(elapsedTime);

         auto& app = App::GetApp();

		float delta = app->GetElapsedTime();

		auto& device = app->GetInputDevice();
		const auto& pad = device.GetControlerVec()[0];

		//コントローラの取得
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();

		//Bボタンが押されているとき
		if (cntlVec[0].wButtons & XINPUT_GAMEPAD_B) {
			//表示
			SetDrawActive(true);
		}
		//Bボタンが押されていないとき
		else {
			/*SetAlphaActive(true);*/
			SetDrawActive(false);
		}
		
		////コントローラチェックして入力があればコマンド呼び出し
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
			//サウンドの再生
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

	
	/*void EnemyObject::OnPushB() {
		


	}*/

}