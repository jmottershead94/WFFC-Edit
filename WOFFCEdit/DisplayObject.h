#pragma once
#include "pch.h"
#include "1300455_MottersheadJason/Physics/AABBCollider.h"
#include "1300455_MottersheadJason/Physics/Raycast.h"

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
		bool									m_wireframe;

		/*
		 * Adds a collider to this object.
		 */
		void AddCollider();

		/*
		 * Provides a way to check if this object has been clicked on.
		 * @param worldMatrix used to help calculate the cursor position in the world.
		 * @param camPosition used to help determine the cursor position in the world.
		 * @param camForward the direction the camera is looking.
		 * @return bool if this object has been clicked on.
		 */
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
		Collider* _collider;
		Raycast _ray;
};

