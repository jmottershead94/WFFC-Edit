#include "DisplayObject.h"

DisplayObject::DisplayObject(ID3D11Device* device) : BaseObject(),
	_device(device)
{
	m_model = nullptr;
	//m_texture_diffuse = nullptr;
	_currentTexture = nullptr;
	_originalTexture = nullptr;
	_highlightedTexture = nullptr;
	m_render = true;
	m_wireframe = false;
}

DisplayObject::~DisplayObject()
{}

void DisplayObject::LoadTexture(const std::string filePath, ID3D11ShaderResourceView** texture)
{
	if (!_device)
		return;

	// If there was no file path given, just provide a standard texture.
	if(filePath.empty())
		DirectX::CreateDDSTextureFromFile(_device, L"database/data/Error.dds", nullptr, texture);

	// Standard texture loading.
	std::wstring texturewstr = Utils::StringToWCHART(filePath);
	HRESULT rs;
	rs = DirectX::CreateDDSTextureFromFile(_device, texturewstr.c_str(), nullptr, texture);

	// If there is an error loading the texture, just provide a standard texture.
	if (rs)
		DirectX::CreateDDSTextureFromFile(_device, L"database/data/Error.dds", nullptr, texture);
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