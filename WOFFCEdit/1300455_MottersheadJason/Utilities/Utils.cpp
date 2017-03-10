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
 * @return Vector3 the position of the cursor on screen.
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
 * @return Vector3 the position of the cursor in the game.
 */
DirectX::SimpleMath::Vector3 const Utils::GetCursorPositionInWorld(DirectX::SimpleMath::Matrix worldMatrix, DirectX::SimpleMath::Matrix projectionMatrix, DirectX::SimpleMath::Vector3 camPosition)
{
	//mousePosition.x /= (TERRAINRESOLUTION * TERRAINRESOLUTION);
	//mousePosition.y /= (TERRAINRESOLUTION * TERRAINRESOLUTION);
	//mousePosition.x *= 512.0f;
	//mousePosition.y *= 512.0f;
	//mousePosition.x += m_camPosition.x;
	//mousePosition.y += m_camPosition.y;
	//mousePosition.z += m_camPosition.z;

	/*cursorPosition.x /= instance->_mapSize;
	cursorPosition.y /= instance->_mapSize;
	cursorPosition.x *= 512.0f;
	cursorPosition.y *= 512.0f;
	cursorPosition.x = cameraPosition.x;
	cursorPosition.x += cameraPosition.x;
	cursorPosition.y += cameraPosition.y;
	cursorPosition.z += cameraPosition.z;*/

	// Converting cursor coordinates into a matrix for operations later on.

	DirectX::SimpleMath::Vector3 cursorPosition(GetCursorPositionInWindow());
	cursorPosition.x -= (instance->_width * 0.5f);
	cursorPosition.y -= (instance->_height * 0.5f);
	DirectX::SimpleMath::Matrix cursorMatrix;
	cursorMatrix.CreateTranslation(cursorPosition);

	// Convering camera coordiantes into a matrix for operations later on.
	DirectX::SimpleMath::Matrix camMatrix;
	camMatrix.Translation(camPosition);
	
	// Attempting to unproject screen coordinates.
	DirectX::SimpleMath::Matrix mat;
	mat = worldMatrix * projectionMatrix.Invert();

	// Using the cursor position.
	DirectX::SimpleMath::Matrix screenCoordinates;
	DirectX::SimpleMath::Vector3 screenPosition(cursorPosition.x, cursorPosition.y, 1.0f);
	screenCoordinates = screenCoordinates.CreateTranslation(screenPosition);
	
	// Using the camera position.
	DirectX::SimpleMath::Matrix cameraScreenCoordinates;
	DirectX::SimpleMath::Vector3 cameraPosition(camPosition.x, camPosition.y, 1.0f);
	cameraScreenCoordinates = cameraScreenCoordinates.CreateTranslation(cameraPosition);
	
	DirectX::SimpleMath::Matrix resultingMatrix = screenCoordinates * cameraScreenCoordinates;
	DirectX::SimpleMath::Matrix dir;
	dir = mat.Transpose() * resultingMatrix;
	dir /= mat.m[3][0] + mat.m[3][1] + mat.m[3][2] + mat.m[3][3];
	//dir -= (camMatrix - cursorMatrix);
	//dir -= (cursorMatrix - camMatrix);
	dir -= (cursorMatrix - camMatrix);

	return dir.Translation();
}