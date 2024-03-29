/**
* @file MyCamera.h
* @brief カメラクラスの定義が記述されているヘッダーファイル
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	class MyCamera : public Camera
	{
		float angleY; // Y軸中心の回り込み（ラジアン角）
		float distance; // 注視対象からの距離

		weak_ptr<GameObject> m_TargetObject;	//目標となるオブジェクト
		bsm::Vec3 m_TargetToAt;	//目標から視点を調整する位置ベクトル
		//float m_ToTargetLerp;	//目標を追いかける際の補間値
		float PPdistance;
		float m_TurnTime;
		bool m_Turn;
	public:
		void SetTargetObject(const shared_ptr<GameObject>& Obj);

		shared_ptr<GameObject> GetTargetObject() const;
		/*float GetToTargetLerp() const;
		void SetToTargetLerp(float f);*/
		//Bボタンカメラの変更
		//void OnPushB();


		MyCamera()
			: angleY(0.0f), 
			distance(5.0f),
			PPdistance(0.0f),
			m_Turn(true),
			m_TurnTime(0.0f)
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
	//--------------------------------------------------------------------------------------
	//	オープニングカメラ（コンポーネントではない）
	//--------------------------------------------------------------------------------------
	class OpeningCamera : public Camera {
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief	コンストラクタ
		*/
		//--------------------------------------------------------------------------------------
		OpeningCamera();
		//--------------------------------------------------------------------------------------
		/*!
		@brief	デストラクタ
		*/
		//--------------------------------------------------------------------------------------
		virtual ~OpeningCamera();
		//--------------------------------------------------------------------------------------
		/*!
		@brief 更新処理
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnUpdate()override;
	};
	//--------------------------------------------------------------------------------------
	//	メインカメラ（コンポーネントではない）
	//--------------------------------------------------------------------------------------
	class ObjCamera : public Camera {
		weak_ptr<GameObject> m_TargetObject;	//目標となるオブジェクト
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief	コンストラクタ
		*/
		//--------------------------------------------------------------------------------------
		ObjCamera();
		//--------------------------------------------------------------------------------------
		/*!
		@brief	デストラクタ
		*/
		//--------------------------------------------------------------------------------------
		virtual ~ObjCamera();
		//--------------------------------------------------------------------------------------
		/*!
		@brief	カメラの目標オブジェクトを設定する
		@param[in]	Obj	カメラの目標オブジェクト
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void SetTargetObject(const shared_ptr<GameObject>& Obj);
		//--------------------------------------------------------------------------------------
		/*!
		@brief 更新処理
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnUpdate()override;
	};
}