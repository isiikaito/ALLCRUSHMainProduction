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
		
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;
		int m_HP;

		//入力ハンドラー
		InputHandler2<Wall> m_InputHandler;

		// エフェクト関連
		float m_TotalTime2;
		bool m_isPlay2;
		Effekseer::Handle m_handle2;
		Effekseer::ManagerRef m_manager2;
		EffekseerRendererDX11::RendererRef m_renderer2;
		Effekseer::EffectRef m_effect2;
		void CreateEffect();
		//HP
		//int HP;
		//void CreateEffect();

	public:
		//構築と破棄
		Wall(const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position,
			const int HP
		);
		//アクセサ
		
		
		//初期化
		virtual void OnCreate() override;
		//衝突判定
		virtual void OnCollisionEnter(shared_ptr<GameObject>& Other);
		virtual void OnDraw() override;

		//コントローラーのボタン判定X
		void OnPushX();
		void OnPushA() {}
		void OnPushUP() {}
		void OnPushDOWN() {}

		void OnPushB();

		void OnUpdate();
		public:
			
			int GetHP()const {
				return m_HP;
			}
			void SetHP(int HP) {
				m_HP = HP;
			}
	};

}
// namespace basecross
