/*!
@file Wall.h
@brief 壁の実体
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	///	物理計算する固定のボックス
	//--------------------------------------------------------------------------------------
	class Wall : public GameObject {
		unique_ptr< StateMachine<Wall> > m_StateMachine;
		Vec3 m_Scale;
		Quat m_Qt;
		Vec3 m_Position;
		Vec3 m_ActionVelocity;
		Vec3 m_ActiveMax;

		//入力ハンドラー
		InputHandler2<Wall> m_InputHandler;

		//エラー

		// エフェクト関連
		float m_TotalTime;
		bool m_isPlay;
		Effekseer::Handle m_handle;
		Effekseer::ManagerRef m_manager;
		EffekseerRendererDX11::RendererRef m_renderer;
		Effekseer::EffectRef m_effect;

		void CreateEffect();
		//HP
		//int HP;
	public:
		//構築と破棄
		Wall(const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Quat& Qt,
			const Vec3& Position
		);
		//アクセサ
		
		Vec3 GetActionVelocity()const {
			return m_ActionVelocity;
		}
		
		//初期化
		virtual void OnCreate() override;
		//描画
		virtual void OnDraw() override;
		//衝突判定
		virtual void OnCollisionEnter(shared_ptr<GameObject>& Other);
		//コントローラーのボタン判定X
		void OnPushX();
		void OnPushA() {}

		void OnPushB();

		void OnUpdate();
			float m_StateChangeSize;

			Vec3 m_Force;

			Vec3 m_Velocity;
		public:
			Wall(const shared_ptr<Stage>& StagePtr, const Vec3& StartPos);
			const unique_ptr<StateMachine<Wall>>& GetStateMachine() {
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
			Vec3 GetTargetPos()const;


		//bool IsHitSegmentTriangles(const Vec3& StartPos,const Vec3& EndPos,TRIANGLE& tri,Vec3& HitPoint);
		//bool IsHitSphereTriangles(const SPHERE& StartSp, const SPHERE& EndSp, TRIANGLE& tri, Vec3 HitPoint);
	};

}
// namespace basecross
