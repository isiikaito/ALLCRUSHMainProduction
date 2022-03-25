/*!
@file GameStage.cpp
@brief ゲームステージ実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	stageObject::stageObject(const shared_ptr<Stage>& stagePtr,
		const Vec3& Scale,
		const Vec3& Rotation,
		const Vec3& Position,
		float UPic,
		float VPic,
		const wstring& Texname) :
		GameObject(stagePtr),
		m_scale(Scale),
		m_rotation(Rotation),
		m_position(Position),
		m_UPic(UPic),
		m_VPic(VPic),
		m_textureName(Texname) {}
	void stageObject::OnCreate() {
		auto ptrTransform = GetComponent<Transform>();
		ptrTransform->SetScale(m_scale);
		ptrTransform->SetRotation(m_rotation);
		ptrTransform->SetPosition(m_position);

		//OBB衝突判定を付ける
		auto Coll = AddComponent<CollisionObb>();
		Coll->SetFixed(true);

		vector<VertexPositionNormalTexture> vertices;
		vector<uint16_t> indices;
		MeshUtill::CreateCube(1.0f, vertices, indices);
		float UCount = m_scale.x / m_UPic;
		float VCount = m_scale.z / m_VPic;
		for (size_t i = 0; i < vertices.size(); i++)
		{
			if (vertices[i].textureCoordinate.x >= 1.0f)
			{
				vertices[i].textureCoordinate.x = UCount;
			}
			if (vertices[i].textureCoordinate.y >= 1.0f)
			{
				float FrontBetween = bsm::angleBetweenNormals(vertices[i].normal, Vec3(0, 1, 0));
				float BackBetween = bsm::angleBetweenNormals(vertices[i].normal, Vec3(0, 1, 0));
				if (FrontBetween < 0.01f || BackBetween < 0.01f)
				{
					vertices[i].textureCoordinate.y = VCount;
				}
			}
		}
		//描画コンポーネントの追加
		/*auto ptrDraw = AddComponent<BcPNTStaticDraw>();*/
		//描画コンポーネントに形状（メッシュ）を設定
		//描画コンポーネントの追加
		auto ptrDraw = AddComponent<BcPNTStaticDraw>();
		ptrDraw->CreateOriginalMesh(vertices, indices);
		ptrDraw->SetOriginalMeshUse(true);
		ptrDraw->SetFogEnabled(true);

		//タイリング処理の設定
		ptrDraw->SetSamplerState(SamplerState::LinearWrap);



		//重力を付ける
		/*auto ptrGra = AddComponent<Gravity>();*/

		auto shadowPtr = AddComponent<Shadowmap>();
		//影メッシュを設定
		shadowPtr->SetMeshResource(L"DEFAULT_CUBE");


		ptrDraw->SetMeshResource(L"DEFAULT_CUBE");
		ptrDraw->SetTextureResource(m_textureName);



		SetAlphaActive(true);
	}

}

