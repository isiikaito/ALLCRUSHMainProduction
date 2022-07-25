/**
*@file FallingRock.h
*@brief 落石オブジェクトの実装が定義されているヘッダーファイル
*@author Kaito Isii
*@details 落石オブジェクトの実装
*/
#pragma once
#include "stdafx.h"

/** basecross共通のネームスペース */
namespace basecross {

	class FallingRock : public GameObject {
		Vec3 m_Scale;    //!大きさ
		Vec3 m_Rotation; //!回転
		Vec3 m_Position; //!位置
		int m_Falling;   //!柱が破壊されたかどうか
	public:

		/**
		* コンストラクタ
		*/
		FallingRock(const shared_ptr<Stage>& StagePtr, const Vec3& Scale, const Vec3& Rotation, const Vec3& Position);

        /**
　　　　* デストラクタ
　　　　*/
		virtual ~FallingRock() {}

		
		/**
		* 落石オブジェクトの初期パラメータを初期化する関数
		*/
		virtual void OnCreate() override;

		/**
		* 柱オブジェクトが破壊されたときに落石が落ちる関数
		*/
		virtual void OnUpdate() override;
		
		/**
         * 柱オブジェクトが破壊されたかどうか
         * @return int 柱オブジェクトがステージ上に存在するかどうかが返ってくる
         */
		int GetFalling()const {
			return m_Falling;
		}

		/**
		 * 柱オブジェクトが破壊されたかどうか
		 * @param[in] int  Falling ステージ上で破壊されtかどうか
		 */
		void SetFalling(int Falling) {
			m_Falling = Falling;
		}
	};
}
