#include "Utils.h"

std::unique_ptr<Utils> instance = nullptr;

/*
 * Constructs this instance.
 */
Utils::Utils()
{
	if (instance == nullptr)
		instance = std::make_unique<Utils>(*this);
}

/*
 * Destructs this instance.
 */
Utils::~Utils()
{}

/*
 * Initializes this instance.
 * @param hwnd the handle to the current window.
 */
void Utils::Initialize(HWND hwnd, int width, int height)
{
	instance->_hwnd = hwnd;
	instance->_width = width;
	instance->_height = height;
}

/*
 * Provides access to the window handle instance.
 * @return const HWND the current window.
 */
HWND const Utils::GetWindow()
{
	return instance->_hwnd;
}

/*
 * Provides access to the cursor position in the current window instance.
 * @return const Vector3 the position of the cursor on screen.
 */
DirectX::SimpleMath::Vector3 const Utils::GetCursorPositionInWindow()
{
	DirectX::SimpleMath::Vector3 cursorPosition;
	POINT p;

	if (GetCursorPos(&p))
	{
		cursorPosition.x = static_cast<float>(p.x);
		cursorPosition.y = static_cast<float>(p.y);
		cursorPosition.z = 1.0f;
	}

	if (ScreenToClient(instance->_hwnd, &p))
	{
		cursorPosition.x = static_cast<float>(p.x);
		cursorPosition.y = static_cast<float>(p.y);
		cursorPosition.z = 1.0f;
	}

	return cursorPosition;
}

/*
 * Provides access to the cursor position in the game world.
 * @param worldMatrix the world matrix from the game.
 * @param camPosition the position of the game camera.
 * @return const Vector3 the position of the cursor in the game.
 */
DirectX::SimpleMath::Vector3 const Utils::GetCursorPositionInWorld(DirectX::SimpleMath::Matrix worldMatrix, DirectX::SimpleMath::Vector3 camPosition)
{
	// Converting cursor coordinates into a matrix for operations later on.
	DirectX::SimpleMath::Vector3 cursorPosition(GetCursorPositionInWindow());
	DirectX::SimpleMath::Matrix dir;
	float halfWidth = instance->_width * 0.5f;
	float halfHeight = instance->_height * 0.5f;

	// Calculate the current cursor position based on the screen width and height.
	cursorPosition.x = (cursorPosition.x / halfWidth) - 1.0f;
	cursorPosition.y = (cursorPosition.y / halfHeight) - 1.0f;

	// Calculate the position of the cursor in the 3D world and return it.
	DirectX::SimpleMath::Matrix position3D;
	position3D = position3D.CreateTranslation(camPosition.x - (cursorPosition.x * (1.0f / halfWidth)), camPosition.y - (cursorPosition.y * (1.0f / halfHeight)), camPosition.z);
	dir = worldMatrix * position3D;
	return dir.Translation();
}