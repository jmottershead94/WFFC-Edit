#pragma once

#include "BaseObject.h"
#include "../include/GeometricPrimitive.h"

class PrimitiveObject : public BaseObject
{
	public:
		PrimitiveObject();
		~PrimitiveObject();

		inline void SetPrimitive(const DirectX::GeometricPrimitive primitive)	{ _primitive = std::make_shared<DirectX::GeometricPrimitive>(primitive); }
		inline void SetTexture(ID3D11ShaderResourceView* texture)				{ _texture_diffuse = texture; }
		inline void SetRender(const bool value)									{ _render = value; }
		inline void SetWireframe(const bool value)								{ _wireframe = value; }

		inline std::shared_ptr<DirectX::GeometricPrimitive> const Primitive() const	{ return _primitive; }
		inline ID3D11ShaderResourceView* const Texture() const						{ return _texture_diffuse; }
		inline bool const Visible() const											{ return _render; }
		inline bool const Wireframe() const											{ return _wireframe; }

	private:
		std::shared_ptr<DirectX::GeometricPrimitive>		_primitive;
		ID3D11ShaderResourceView *							_texture_diffuse;
		bool												_render;
		bool												_wireframe;

		/**
		 * What happens when the user left clicks on this object.
		 */
		void OnLeftMouseClick();

		/**
		 * What happens when the user has double clicked on this object.
		 */
		void OnLeftMouseDoubleClick();
};