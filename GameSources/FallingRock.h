/*!
@file FallingRock.h
@brief　落石
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	class FallingRock : public GameObject {
		Vec3 m_Scale;    //大きさ
		Vec3 m_Rotation; //回転
		Vec3 m_Position; //位置
		int m_Falling;   //柱が破壊されたかどうか
	public:
		//構築と破棄
		FallingRock(const shared_ptr<Stage>& StagePtr, const Vec3& Scale, const Vec3& Rotation, const Vec3& Position);
		virtual ~FallingRock() {}

		
		//初期化
		virtual void OnCreate() override;
		virtual void OnUpdate() override;

		//柱が破壊されたかどうかの取得
		int GetFalling()const {
			return m_Falling;
		}

		//柱が破壊されているかどうかの管理
		void SetFalling(int Falling) {
			m_Falling = Falling;
		}
	};
}
