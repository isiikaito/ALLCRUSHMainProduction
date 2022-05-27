/*!
@file ImpactSmoke.cpp
@brief�@�G�t�F�N�g
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	// �����̃X�p�[�N�N���X
	//--------------------------------------------------------------------------------------
	//�\�z�Ɣj��
	ImpactSmoke::ImpactSmoke(shared_ptr<Stage>& StagePtr) :
		MultiParticle(StagePtr)
	{}
	ImpactSmoke::~ImpactSmoke() {}

	//������
	void ImpactSmoke::OnCreate() {
		SetAddType(true);
	}

	void ImpactSmoke::OnUpdate() {
		for (auto ptrParticle : GetParticleVec()) {
			for (auto& rParticleSprite : ptrParticle->GetParticleSpriteVec()) {
				if (rParticleSprite.m_Active) {
					rParticleSprite.m_Color.z += 0.05f;
					if (rParticleSprite.m_Color.z >= 1.0f) {
						rParticleSprite.m_Color.z = 1.0f;
					}
				}
			}
		}
		//�e�N���X��OnUpdate()���Ă�
		MultiParticle::OnUpdate();
	}



	void ImpactSmoke::InsertSpark(const Vec3& Pos) {
		auto ptrParticle = InsertParticle(60);
		ptrParticle->SetEmitterPos(Pos);
		ptrParticle->SetTextureResource(L"SPARK_TX");
		ptrParticle->SetMaxTime(1.0f);
		for (auto& rParticleSprite : ptrParticle->GetParticleSpriteVec()) {
			rParticleSprite.m_LocalPos.x = Util::RandZeroToOne() * 0.2f - 0.1f;
			rParticleSprite.m_LocalPos.y = Util::RandZeroToOne() * 0.2f;
			rParticleSprite.m_LocalPos.z = Util::RandZeroToOne() * 0.2f - 0.1f;
			//�e�p�[�e�B�N���̈ړ����x���w��
			rParticleSprite.m_Velocity = Vec3(
				rParticleSprite.m_LocalPos.x * 25.0f,
				rParticleSprite.m_LocalPos.y * 25.0f,
				rParticleSprite.m_LocalPos.z * 25.0f
			);
			//�F�̎w��
			rParticleSprite.m_Color = Col4(0.0f, 1.0f, 0.0f, 1.0f);
		}
	}


}
// end namespace basecross
