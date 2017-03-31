#include "DisplayObject.h"

DisplayObject::DisplayObject() : BaseObject()
{
	m_model = nullptr;
	_currentTexture = nullptr;
	_originalTexture = nullptr;
	_highlightedTexture = nullptr;
	m_render = true;
	m_wireframe = false;
}

DisplayObject::~DisplayObject()
{}

DisplayObject* DisplayObject::Copy()
{
	DisplayObject* newObject = new DisplayObject();

	newObject->m_model = std::make_shared<DirectX::Model>(*m_model);
	newObject->m_render = m_render;
	newObject->m_wireframe = m_wireframe;
	newObject->_currentTexture = _currentTexture;
	newObject->_originalTexture = _originalTexture;
	newObject->_highlightedTexture = _highlightedTexture;
	newObject->transform->Translate(transform->Position().x, transform->Position().y + 20.0f, transform->Position().z);
	newObject->transform->Rotate(transform->Rotation());
	newObject->transform->SetScale(transform->Scale());

	newObject->collider->Update(0.00, newObject->transform->Position(), newObject->transform->Rotation(), newObject->transform->Scale());
	newObject->editorCollider->Update(0.00, newObject->transform->Position(), newObject->transform->Rotation(), newObject->transform->Scale());

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

void DisplayObject::OnLeftMouseClick()
{
	// Reverse the focus of this object.
	inFocus = !inFocus;

	// Set the correct texture.
	if (inFocus)
		SetTexture(_highlightedTexture);
	else
		SetTexture(_originalTexture);
}

void DisplayObject::OnLeftMouseDoubleClick()
{
	// Move the camera over to this object.
	camera->Transform().SetPosition(Maths::Lerp(camera->Transform().Position(), transform->Position(), 0.2f));
}