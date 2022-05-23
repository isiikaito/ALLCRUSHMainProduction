#pragma once
#include "stdafx.h"

namespace basecross {

	class MyCamera : public Camera
	{
		float angleY; // Y軸中心の回り込み（ラジアン角）
		float distance; // 注視対象からの距離

		weak_ptr<GameObject> m_TargetObject;	//目標となるオブジェクト
		bsm::Vec3 m_TargetToAt;	//目標から視点を調整する位置ベクトル
		float m_ToTargetLerp;	//目標を追いかける際の補間値
		float PPdistance;
		float m_TurnTime;
		float m_Turn;
	public:
		void SetTargetObject(const shared_ptr<GameObject>& Obj);

		shared_ptr<GameObject> GetTargetObject() const;
		float GetToTargetLerp() const;
		void SetToTargetLerp(float f);
		//Bボタンカメラの変更
		void OnPushB();


		MyCamera()
			: angleY(0.0f), distance(5.0f)
		{
			//void SetTargetObject(const shared_ptr<GameObject>&Obj);
			//weak_ptr<GameObject> m_TargetObject;	//目標となるオブジェクト
			//float m_ToTargetLerp;	//目標を追いかける際の補間値
			//void SetToTargetLerp(float f);

		}

		void OnUpdate() override;

		float GetAngleY() const
		{
			return angleY;
		}

	};
}