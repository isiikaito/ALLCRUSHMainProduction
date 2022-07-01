/*!
@file GageSprite3.h
@brief �Q�[�W
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	//�Q�[�W
	class GageSprite3 : public GameObject
	{
		bool m_Trace;       //����
		Vec2 m_StartScale;  //�傫��
		Vec3 m_StartPos;    //�ʒu
		float m_TotalTime;  //���Ԃ̎擾
		int m_BreakCount;   //�ǂ��󂵂���
		int m_PowerON;      //�p���[�A�b�v��
		int m_PowerOFF;     //�p���[�A�b�v���ĂȂ�
		vector<VertexPositionColor>m_BackupVertices;//�o�b�N�A�b�v���_�f�[�^


	public:
		GageSprite3(const shared_ptr<Stage>& StagePtr, bool Trace,
			const Vec2& StartScale, const Vec3& StartPos);

		virtual ~GageSprite3();

		virtual void OnCreate() override;//������
		virtual void OnUpdate()override; //�X�V

		
	};
}
