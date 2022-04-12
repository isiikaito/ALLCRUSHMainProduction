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
		//衝突判定
		virtual void OnCollisionEnter(shared_ptr<GameObject>& Other);
		//コントローラーのボタン判定B
		//const void OnPushB(shared_ptr<GameObject>& Other);
	};
	


}
// namespace basecross
