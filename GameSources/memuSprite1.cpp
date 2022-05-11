/*!
@file memuSprite.cpp
@brief �����e�N�X�`��
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	memuSprite1::memuSprite1(const shared_ptr<Stage>& StagePtr,
		const wstring& TextureKey, bool Trace,
		const Vec2& StartScale, const Vec3& StartPos) :
		GameObject(StagePtr),
		m_TextureKey(TextureKey),
		m_Trace(Trace),
		m_StartScale(StartScale),
		m_StartPos(StartPos),
		m_idleTime(0)
	
		
	{}

	memuSprite1::~memuSprite1() {}
	void memuSprite1::OnCreate() {


		float helfSize = 0.5f;
		//���_�z��(�c��5���\��)
		vector<VertexPositionColorTexture> vertices = {
			{ VertexPositionColorTexture(Vec3(-helfSize, helfSize, 0),Col4(1.0f,1.0f,1.0f,1.0f), Vec2(0.0f, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(helfSize, helfSize, 0), Col4(0.0f, 1.0f, 1.0f, 1.0f), Vec2(1.0f, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(-helfSize, -helfSize, 0), Col4(1.0f, 0.0f, 1.0f, 1.0f), Vec2(0.0f, 1.0f)) },
			{ VertexPositionColorTexture(Vec3(helfSize, -helfSize, 0), Col4(0.0f, 0.0f, 0, 1.0f), Vec2(1.0f, 1.0f)) },
		};
		//�C���f�b�N�X�z��
		vector<uint16_t> indices = { 0, 1, 2, 1, 3, 2 };
		SetAlphaActive(m_Trace);
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_StartScale.x, m_StartScale.y, 1.0f);
		ptrTrans->SetRotation(0, 0, 0);
		ptrTrans->SetPosition(m_StartPos);
		//���_�ƃC���f�b�N�X���w�肵�ăX�v���C�g�쐬
		auto ptrDraw = AddComponent<PCTSpriteDraw>(vertices, indices);
		ptrDraw->SetSamplerState(SamplerState::LinearWrap);
		ptrDraw->SetTextureResource(m_TextureKey);

		//�ǂݍ��݂̐ݒ������
		GetStage()->SetSharedGameObject(L"memuSprite1", GetThis<memuSprite1>());
	}
	////�\���L�[��
	//void memuSprite1::OnPushUP() {
	//	num--;
	//	if (num < 0)
	//	{
	//		num = 0;
	//	}
	//}
	////�\���L�[��
	//void memuSprite1::OnPushDOUN() {
	//	num++;
	//	if (num > 2)
	//	{
	//		num = 2;
	//	}
	//}

	//void memuSprite1::OnPushB()
	//{
	//	num++;
	//}
	void  memuSprite1::OnUpdate()
	{

		/*float elapsedTime = App::GetApp()->GetElapsedTime();
		m_idleTime += elapsedTime;
		if (num == 0)
		{
			if (m_idleTime >= 1.0f)
			{
				SetDrawActive(false);

				if (m_idleTime >= 1.5f)
				{
					SetDrawActive(true);
					m_idleTime = 0;
				}

				return;
			}
		}*/



	}

	
}