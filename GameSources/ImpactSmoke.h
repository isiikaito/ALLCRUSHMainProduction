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
	class ImpactSmoke : public MultiParticle {
	public:
		//�\�z�Ɣj��
		ImpactSmoke(shared_ptr<Stage>& StagePtr);
		virtual ~ImpactSmoke();
		//������
		virtual void OnCreate() override;
		void InsertSpark(const Vec3& Pos);
		void InsertSpark1(const Vec3& Pos);
		void InsertSpark2(const Vec3& Pos);
		void InsertSpark3(const Vec3& Pos);
		void InsertSpark4(const Vec3& Pos);

		virtual void OnUpdate() override;

	};


}
// end namespace basecross
