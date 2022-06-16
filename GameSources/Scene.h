/*!
@file Scene.h
@brief �V�[��
*/
#pragma once

#include "stdafx.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	///	�Q�[���V�[��
	//--------------------------------------------------------------------------------------
	class Scene : public SceneBase {
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief �R���X�g���N�^
		*/
		//--------------------------------------------------------------------------------------
		void CreateResourses();
		bool m_MovieActive;
		int m_StageSelect;
		Scene() :SceneBase() , m_MovieActive(false),m_StageSelect(1){}
		//--------------------------------------------------------------------------------------
		/*!
		@brief �f�X�g���N�^
		*/
		//--------------------------------------------------------------------------------------
		virtual ~Scene();
		//--------------------------------------------------------------------------------------
		/*!
		@brief ������
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnCreate() override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief �C�x���g�擾
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnEvent(const shared_ptr<Event>& event) override;
		bool IsMovieActive() const {
			return m_MovieActive;
		}
		//�X�e�[�W�̑I���̎擾
		int GetStageSelect()const {
			return m_StageSelect;
		}
		void SetStageSelect(int StageSelect) {
			m_StageSelect = StageSelect;
		}
	};

}

//end basecross

