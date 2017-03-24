#pragma once
#include "pch.h"
#include "1300455_MottersheadJason/Objects/BaseObject.h"

class DisplayObject : public BaseObject
{
	public:
		DisplayObject();
		~DisplayObject();

		std::shared_ptr<DirectX::Model>						m_model;							//main Mesh
		ID3D11ShaderResourceView *							m_texture_diffuse;					//diffuse texture
		bool									m_render;
		bool									m_wireframe;

	private:
		/**
		 * What happens when the user left clicks on this object.
		 */
		void OnLeftMouseClick();

		/**
		 * What happens when the user has double clicked on this object.
		 */
		void OnLeftMouseDoubleClick();
};