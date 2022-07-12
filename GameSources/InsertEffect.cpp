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
		auto ptrParticle = InsertParticle(25);
		ptrParticle->SetEmitterPos(Pos);
		ptrParticle->SetTextureResource(L"SPARK_TX");
		ptrParticle->SetMaxTime(1.0f);
		for (auto& rParticleSprite : ptrParticle->GetParticleSpriteVec()) {			
			rParticleSprite.m_LocalPos.x = Util::RandZeroToOne() * 0.3f - 0.1f;
			rParticleSprite.m_LocalPos.y = Util::RandZeroToOne() * 0.3f;
			rParticleSprite.m_LocalPos.z = Util::RandZeroToOne() * 0.3f - 0.1f;

			rParticleSprite.m_LocalScale.x = 5.0f;
			rParticleSprite.m_LocalScale.y = 5.0f;
			//�e�p�[�e�B�N���̈ړ����x���w��
			rParticleSprite.m_Color = Col4(0.8f, 0.8f, 0.0f, 0.4f);

			rParticleSprite.m_Velocity = Vec3(
				rParticleSprite.m_LocalPos.x * 18.0f,
				rParticleSprite.m_LocalPos.y * 18.0f,
				rParticleSprite.m_LocalPos.z * 18.0f
			);
			//�F�̎w��
		}
	}

	void ImpactSmoke::InsertSpark1(const Vec3& Pos) {
		auto ptrParticle = InsertParticle(18);
		ptrParticle->SetEmitterPos(Pos);
		ptrParticle->SetTextureResource(L"SPARK_TX1");
		ptrParticle->SetMaxTime(1.0f);
		for (auto& rParticleSprite : ptrParticle->GetParticleSpriteVec()) {
			rParticleSprite.m_LocalPos.x = Util::RandZeroToOne() * 0.3f - 0.1f;
			rParticleSprite.m_LocalPos.y = Util::RandZeroToOne() * 0.3f;
			rParticleSprite.m_LocalPos.z = Util::RandZeroToOne() * 0.3f - 0.1f;

			rParticleSprite.m_LocalScale.x = 5.0f;
			rParticleSprite.m_LocalScale.y = 5.0f;
			//�e�p�[�e�B�N���̈ړ����x���w��
			rParticleSprite.m_Velocity = Vec3(
				rParticleSprite.m_LocalPos.x * 28.0f,
				rParticleSprite.m_LocalPos.y * 28.0f,
				rParticleSprite.m_LocalPos.z * 28.0f
			);
			//�F�̎w��
			rParticleSprite.m_Color = Col4(0.4f,0.4f,0.4f,0.8f);
		}
	}

	void ImpactSmoke::InsertSpark2(const Vec3& Pos) {
		auto ptrParticle = InsertParticle(16);
		ptrParticle->SetEmitterPos(Pos);
		ptrParticle->SetTextureResource(L"SPEEDUP_TX");
		ptrParticle->SetMaxTime(1.0f);
		for (auto& rParticleSprite : ptrParticle->GetParticleSpriteVec()) {
			rParticleSprite.m_LocalPos.x = Util::RandZeroToOne() * 0.2f - 0.1f;
			rParticleSprite.m_LocalPos.y = Util::RandZeroToOne() * 0.2f;
			rParticleSprite.m_LocalPos.z = Util::RandZeroToOne() * 0.2f - 0.1f;

			rParticleSprite.m_LocalScale.x = 5.0f;
			rParticleSprite.m_LocalScale.y = 5.0f;
			//�e�p�[�e�B�N���̈ړ����x���w��
			rParticleSprite.m_Velocity = Vec3(
				rParticleSprite.m_LocalPos.x * 25.0f,
				rParticleSprite.m_LocalPos.y * 25.0f,
				rParticleSprite.m_LocalPos.z * 25.0f
			);
			//�F�̎w��
			rParticleSprite.m_Color = Col4(0.4f, 0.4f, 0.4f, 0.8f);
		}
	}

	void ImpactSmoke::InsertSpark3(const Vec3& Pos) {
		auto ptrParticle = InsertParticle(10);
		ptrParticle->SetEmitterPos(Pos);
		ptrParticle->SetTextureResource(L"IMPACT_TX");
		ptrParticle->SetMaxTime(1.0f);
		for (auto& rParticleSprite : ptrParticle->GetParticleSpriteVec()) {
			rParticleSprite.m_LocalPos.x = Util::RandZeroToOne() * 0.2f - 0.1f;
			rParticleSprite.m_LocalPos.y = Util::RandZeroToOne() * 0.2f;
			rParticleSprite.m_LocalPos.z = Util::RandZeroToOne() * 0.2f - 0.1f;

			rParticleSprite.m_LocalScale.x = 5.0f;
			rParticleSprite.m_LocalScale.y = 5.0f;
			//�e�p�[�e�B�N���̈ړ����x���w��
			rParticleSprite.m_Velocity = Vec3(
				rParticleSprite.m_LocalPos.x * 20.0f,
				rParticleSprite.m_LocalPos.y * 20.0f,
				rParticleSprite.m_LocalPos.z * 20.0f
			);
			//�F�̎w��
			rParticleSprite.m_Color = Col4(0.4f, 0.4f, 0.4f, 0.8f);
		}
	}

	void ImpactSmoke::InsertSpark4(const Vec3& Pos) {
		auto ptrParticle = InsertParticle(14);
		ptrParticle->SetEmitterPos(Pos);
		ptrParticle->SetTextureResource(L"POWERUP_TX1");
		ptrParticle->SetMaxTime(1.0f);
		for (auto& rParticleSprite : ptrParticle->GetParticleSpriteVec()) {
			rParticleSprite.m_LocalPos.x = Util::RandZeroToOne() * 0.2f - 0.1f;
			rParticleSprite.m_LocalPos.y = Util::RandZeroToOne() * 0.2f;
			rParticleSprite.m_LocalPos.z = Util::RandZeroToOne() * 0.2f - 0.1f;

			rParticleSprite.m_LocalScale.x = 5.0f;
			rParticleSprite.m_LocalScale.y = 5.0f;
			//�e�p�[�e�B�N���̈ړ����x���w��
			rParticleSprite.m_Velocity = Vec3(
				rParticleSprite.m_LocalPos.x * 18.0f,
				rParticleSprite.m_LocalPos.y * 18.0f,
				rParticleSprite.m_LocalPos.z * 18.0f
			);
			//�F�̎w��
			rParticleSprite.m_Color = Col4(0.4f, 0.4f, 0.4f, 0.8f);
		}
	}
}
// end namespace basecross
