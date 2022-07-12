/*!
@file ImpactSmoke.h
@brief�@�G�t�F�N�g
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	/// �����̃X�p�[�N�N���X
	//--------------------------------------------------------------------------------------
	class InsertEffect : public MultiParticle {
	public:
		//�\�z�Ɣj��
		InsertEffect(shared_ptr<Stage>& StagePtr);
		virtual ~InsertEffect();
		//������
		virtual void OnCreate() override;
		void InsertSplash(const Vec3& Pos);
		void InsertSpark(const Vec3& Pos);
		void InsertSpeedUp(const Vec3& Pos);
		void InsertImpact(const Vec3& Pos);
		void InsertPowerUp(const Vec3& Pos);

		virtual void OnUpdate() override;

	};


}
// end namespace basecross
