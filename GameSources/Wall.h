/*!
@file Wall.h
@brief 壁の実体
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	class Wall : public GameObject {
		
		Vec3 m_Scale;     //大きさ
		Vec3 m_Rotation;  //回転
		Vec3 m_Position;  //位置
		int m_HP;         //壁のHP

		//入力ハンドラー
		InputHandler2<Wall> m_InputHandler;

	public:
		//構築と破棄
		Wall(const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position,
			const int HP
		);
		
		//初期化
		virtual void OnCreate() override;

		
		void OnPushX(){}     //コントローラーのボタン判定X
		void OnPushA() {}    //コントローラーのボタン判定A
		void OnPushUP() {}   //コントローラーのボタン判定十字キー上
		void OnPushDOWN() {} //コントローラーのボタン判定十字キー下
		void OnPushY(){}     //コントローラーのボタン判定Y
		void OnPushB(){}     //コントローラーのボタン判定B

		void OnUpdate();
		public:
			//HPの取得
			int GetHP()const {
				return m_HP;
			}
			//HPの管理
			void SetHP(int HP) {
				m_HP = HP;
			}
	};

}
// namespace basecross
