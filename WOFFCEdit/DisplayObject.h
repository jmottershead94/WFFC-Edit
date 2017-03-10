#pragma once
#include "pch.h"
#include "1300455_MottersheadJason/Utilities/Maths/Maths.h"

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

		void Update(DirectX::SimpleMath::Vector3& camForward);

		/*
		* Allows us to set this object being in focus.
		* @param value if this object is in focus or not.
		*/
		inline void const SetFocus(const bool value) { _inFocus = value; }

		/*
		* Allows us to see if this object is in focus.
		* @return const bool if the object is in focus.
		*/
		inline bool const InFocus() const { return _inFocus; }

	private:
		bool _inFocus = false;
		DirectX::SimpleMath::Vector3 _position;

		bool ClickedOn(DirectX::SimpleMath::Vector3& camForward);
};

