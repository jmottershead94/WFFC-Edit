#include "DisplayObject.h"

DisplayObject::DisplayObject()
{
	m_model = nullptr;
	_currentTexture = nullptr;
	_originalTexture = nullptr;
	_highlightedTexture = nullptr;
	m_render = true;
	m_wireframe = false;

	_transform = new TransformComponent();
	_transform->SetPosition(DirectX::SimpleMath::Vector3::Zero);
	_transform->SetRotation(DirectX::SimpleMath::Vector3::Zero);
	_transform->SetScale(DirectX::SimpleMath::Vector3::Zero);
}

DisplayObject::~DisplayObject()
{
	//if (_transform)
	//	delete _transform;
}

DisplayObject* DisplayObject::Copy()
{
	DisplayObject* newObject = new DisplayObject();

	newObject->m_model = std::make_shared<DirectX::Model>(*m_model);
	newObject->m_render = m_render;
	newObject->m_wireframe = m_wireframe;
	newObject->_currentTexture = _currentTexture;
	newObject->_originalTexture = _originalTexture;
	newObject->_highlightedTexture = _highlightedTexture;
	newObject->_transform->Translate(_transform->Position().x, _transform->Position().y + 20.0f, _transform->Position().z);
	newObject->_transform->Rotate(_transform->Rotation());
	newObject->_transform->SetScale(_transform->Scale());

	return newObject;
}

void DisplayObject::LoadTexture(const std::string filePath, ID3D11Device* device, ID3D11ShaderResourceView** texture)
{
	if (!device)
		return;

	// If there was no file path given, just provide a standard texture.
	if(filePath.empty())
		DirectX::CreateDDSTextureFromFile(device, L"database/data/Error.dds", nullptr, texture);

	// Standard texture loading.
	std::wstring texturewstr = Utils::StringToWCHART(filePath);
	HRESULT rs;
	rs = DirectX::CreateDDSTextureFromFile(device, texturewstr.c_str(), nullptr, texture);

	// If there is an error loading the texture, just provide a standard texture.
	if (rs)
		DirectX::CreateDDSTextureFromFile(device, L"database/data/Error.dds", nullptr, texture);
}

void DisplayObject::UpdateTexture()
{
	// Applying the new texture.
	m_model->UpdateEffects([&](DirectX::IEffect* effect)
	{
		auto lights = dynamic_cast<DirectX::BasicEffect*>(effect);
		if (lights)
		{
			lights->SetTexture(_currentTexture);
		}
	});
}