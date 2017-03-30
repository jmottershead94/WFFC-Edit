#pragma once
#include "pch.h"
#include "1300455_MottersheadJason/Objects/BaseObject.h"
#include "DDSTextureLoader.h"
#include "Effects.h"

class DisplayObject : public BaseObject
{
	public:
		DisplayObject(ID3D11Device* device);
		~DisplayObject();

		std::shared_ptr<DirectX::Model>		m_model;	//main Mesh
		bool								m_render;
		bool								m_wireframe;
		
		/**
		 * Loads a texture.
		 * @param filePath the file path to this texture.
		 * @param texture the texture to load this file into.
		 */
		void LoadTexture(const std::string filePath, ID3D11ShaderResourceView** texture);

		/**
		 * Sets a new texture, and then immediately updates it.
		 * @param the new texture to set.
		 */
		inline void SetTexture(ID3D11ShaderResourceView* texture)	{ _currentTexture = texture; UpdateTexture(); }
		
		/**
		 * Provides access to the current texture.
		 * @return ID3D11ShaderResourceView** the current texture.
		 */
		inline ID3D11ShaderResourceView** Texture()					{ return &_currentTexture; }

		/**
		 * Provides access to the original texture.
		 * @return ID3D11ShaderResourceView** the original texture.
		 */
		inline ID3D11ShaderResourceView** OriginalTexture()			{ return &_originalTexture; }

		/**
		 * Provides access to the highlighted texture.
		 * @return ID3D11ShaderResourceView** the highlighted texture.
		 */
		inline ID3D11ShaderResourceView** HighlightedTexture()		{ return &_highlightedTexture; }

	private:
		ID3D11Device* _device;
		ID3D11ShaderResourceView* _currentTexture;
		ID3D11ShaderResourceView* _originalTexture;
		ID3D11ShaderResourceView* _highlightedTexture;
		
		/**
		 * Updates the texture to the current texture pointer.
		 */
		void UpdateTexture();

		/**
		 * What happens when the user left clicks on this object.
		 */
		void OnLeftMouseClick();

		/**
		 * What happens when the user has double clicked on this object.
		 */
		void OnLeftMouseDoubleClick();
};