/*!
@file FadeOut.cpp
@brief �Q�[�W�̎���a
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//�Q�[�W

	FadeOutBlack::FadeOutBlack(const shared_ptr<Stage>& StagePtr, bool Trace,
		const Vec2& StartScale, const Vec3& StartPos) :
		GameObject(StagePtr),
		m_Trace(Trace),
		m_StartScale(StartScale),
		m_StartPos(StartPos),
		m_TotalTime(0)
		
		
	{}

	FadeOutBlack::~FadeOutBlack() {}
	void FadeOutBlack::OnCreate() {


		float helfSize = 0.5f;
		//���_�z��
		m_BackupVertices = {
			//�J���[�@�����x
{ VertexPositionColor(Vec3(-helfSize, helfSize, 0),Col4(0.0f,0.0f,0.0f,0.0f)) },
{ VertexPositionColor(Vec3(helfSize, helfSize, 0), Col4(0.0f,0.0f,0.0f,0.0f)) },
{ VertexPositionColor(Vec3(-helfSize, -helfSize, 0), Col4(0.0f,0.0f,0.0f,0.0f)) },
{ VertexPositionColor(Vec3(helfSize, -helfSize, 0), Col4(0.0f,0.0f,0.0f,0.0f)) },
		};
		//�C���f�b�N�X�z��
		vector<uint16_t> indices = { 0, 1, 2, 1, 3, 2 };
		SetAlphaActive(m_Trace);
		//���_�ƃC���f�b�N�X���w�肵�ăX�v���C�g�쐬

		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_StartScale.x, m_StartScale.y, 1.0f);
		ptrTrans->SetRotation(0, 0, 0);
		ptrTrans->SetPosition(m_StartPos);
		auto ptrDraw = AddComponent<PCSpriteDraw>(m_BackupVertices, indices);

		//���_�ƃC���f�b�N�X���w�肵�ăX�v���C�g�쐬
		AddComponent<PCSpriteDraw>(m_BackupVertices, indices);

		////�ǂݍ��݂̐ݒ������
		//GetStage()->SetSharedGameObject(L"FadeOutBlack", GetThis<FadeOutBlack>());

		
	}
	
	//�_�ŏ����iElapsedtime�𗘗p���Ă���j
	void FadeOutBlack::OnUpdate() {

	
		
			float elapsedTime = App::GetApp()->GetElapsedTime();
			m_TotalTime += elapsedTime;

			if (m_TotalTime >= XM_PI) {
				m_TotalTime = 0;
			}

			vector<VertexPositionColor> newVertices;
			for (size_t i = 0; i < m_BackupVertices.size(); i++) {
				Col4 col = m_BackupVertices[i].color;
				//sin��0�`�P�܂łɂ���0�̎��͓����P�̎��͕\���Ƃ��Ă���
				col.w = sin(m_TotalTime);
				auto v = VertexPositionColor(
					m_BackupVertices[i].position,
					col
				);
				newVertices.push_back(v);
			}
			auto ptrDraw = GetComponent<PCSpriteDraw>();
			ptrDraw->UpdateVertices(newVertices);
			if (m_TotalTime >= 1)
			{
	              PostEvent(0.0f, GetThis<FadeOutBlack>(), App::GetApp()->GetScene<Scene>(), L"ToMenuStage");
				
			
			}
	
		
			

	}


}