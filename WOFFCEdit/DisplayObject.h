#pragma once
#include "pch.h"
#include "1300455_MottersheadJason/Utilities/Physics/Physics.h"

class DisplayObject
{
	public:
		DisplayObject();
		~DisplayObject();

		std::shared_ptr<DirectX::Model>						m_model;							//main Mesh
		ID3D11ShaderResourceView *							m_texture_diffuse;					//diffuse texture


		int m_ID;
		DirectX::SimpleMath::Vector3			m_position;
		DirectX::SimpleMath::Vector3			m_orientation;
		DirectX::SimpleMath::Vector3			m_scale;
		bool									m_render;

		void AddCollider();
		//void Update(DirectX::SimpleMath::Matrix& worldMatrix, DirectX::SimpleMath::Vector3& camPosition, DirectX::SimpleMath::Vector3& camForward);
		bool ClickedOn(DirectX::SimpleMath::Matrix& worldMatrix, DirectX::SimpleMath::Vector3& camPosition, DirectX::SimpleMath::Vector3& camForward);

		/*
		* Allows us to set this object being in focus.
		* @param value if this object is in focus or not.
		*/
		inline void const SetFocus(const bool value) { _inFocus = value; }

		/*
		* Allows us to see if this object is in focus.
		* @return const bool if the object is in focus.
		*/
		inline bool& InFocus() { return _inFocus; }

	private:
		bool _inFocus = false;
		DirectX::SimpleMath::Vector3 _position;
		Physics::AABB _aabb;

		
};

