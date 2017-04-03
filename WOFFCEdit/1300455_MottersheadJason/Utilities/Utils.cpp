#include "Utils.h"

static std::unique_ptr<Utils> instance = nullptr;

Utils::Utils() :
	_wireframeMode(false),
	_invertedCameraControls(false)
{
	if (instance == nullptr)
		instance = std::make_unique<Utils>(*this);
}

Utils::~Utils()
{}

void Utils::Initialize(HWND hwnd, int width, int height)
{
	instance->_hwnd = hwnd;
	instance->_width = width;
	instance->_height = height;
}

HWND const Utils::GetWindow()
{
	return instance->_hwnd;
}

DirectX::SimpleMath::Vector3 const Utils::GetCursorPositionInWindow()
{
	DirectX::SimpleMath::Vector3 cursorPosition;
	POINT p;

	if (GetCursorPos(&p))
	{
		cursorPosition.x = static_cast<float>(p.x);
		cursorPosition.y = static_cast<float>(p.y);
		cursorPosition.z = 0.0f;
	}

	if (ScreenToClient(instance->_hwnd, &p))
	{
		cursorPosition.x = static_cast<float>(p.x);
		cursorPosition.y = static_cast<float>(p.y);
		cursorPosition.z = 0.0f;
	}

	return cursorPosition;
}

DirectX::SimpleMath::Vector3 const Utils::GetCursorPositionInWorld(const DirectX::SimpleMath::Matrix& worldMatrix, const DirectX::SimpleMath::Matrix& projectionMatrix, const DirectX::SimpleMath::Matrix& viewMatrix, const D3D11_VIEWPORT& viewPort)
{
	// Accessing the cursor position in terms of the client window.
	// Calculating offsets for cursor position based on screen width/height.
	DirectX::SimpleMath::Vector3 cursorPosition(GetCursorPositionInWindow());
	cursorPosition.x -= ((instance->_width / 2) / instance->_width);
	cursorPosition.y -= ((instance->_height / 2) / instance->_height);

	// worldCursorPosition provides the mouse position in 3D space.
	// pointOne and pointTwo provide a way to cast a ray for this cursor point - we can calculate direction with these.
	DirectX::SimpleMath::Vector3 worldCursorPosition;
	DirectX::SimpleMath::Vector3 pointOne, pointTwo;

	// Cursor at the minimum depth distance.
	// Unprojecting from screen space to world space.
	pointOne = DirectX::XMVector3Unproject(cursorPosition, viewPort.TopLeftX, viewPort.TopLeftY, viewPort.Width, viewPort.Height, viewPort.MinDepth, viewPort.MaxDepth, projectionMatrix, viewMatrix, worldMatrix);

	// Cursor at the maximum depth distance.
	// Unprojecting from screen space to world space.
	cursorPosition.z = 1.0f;
	pointTwo = DirectX::XMVector3Unproject(cursorPosition, viewPort.TopLeftX, viewPort.TopLeftY, viewPort.Width, viewPort.Height, viewPort.MinDepth, viewPort.MaxDepth, projectionMatrix, viewMatrix, worldMatrix);
	
	// Starting point from the cursor on screen, in the direction of the cursor "ray" based on viewport depth.
	worldCursorPosition = pointOne;
	instance->_cursorWorldDirection = pointTwo - pointOne;
	instance->_cursorWorldDirection.Normalize();

	return worldCursorPosition;
}

DirectX::SimpleMath::Vector3 const Utils::GetCursorDirectionInWorld()
{
	return instance->_cursorWorldDirection;
}

void Utils::SetWireframe(const bool wireframeState)
{
	instance->_wireframeMode = wireframeState;
}

bool const Utils::WireframeMode()
{
	return instance->_wireframeMode;
}

void Utils::SetInvertedCamera(const bool invertedState)
{
	instance->_invertedCameraControls = invertedState;
}

bool const Utils::InvertCamera()
{
	return instance->_invertedCameraControls;
}

std::wstring const Utils::StringToWCHART(std::string s)
{
	int len;
	int slength = (int)s.length() + 1;
	len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
	wchar_t* buf = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
	std::wstring r(buf);
	delete[] buf;
	return r;
}

std::string const Utils::HighlightedTexturePath()
{
	return "database/data/highlighted.dds";
}