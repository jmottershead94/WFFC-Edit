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
void Utils::Initialize(HWND hwnd, const float mapSize)
{
	instance->_hwnd = hwnd;
	instance->_mapSize = mapSize;
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
	DirectX::SimpleMath::Vector3 cursorPosition(GetCursorPositionInWindow());
	DirectX::SimpleMath::Matrix cursorMatrix;
	cursorMatrix.CreateTranslation(cursorPosition);

	DirectX::SimpleMath::Matrix camMatrix;
	camMatrix.Translation(camPosition);

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

	//1024, 768
	
	DirectX::SimpleMath::Matrix mat;
	mat = worldMatrix * projectionMatrix.Invert();

	DirectX::SimpleMath::Matrix dir;
	DirectX::SimpleMath::Matrix screenCoordinates;
	DirectX::SimpleMath::Vector3 screenPosition(cursorPosition.x, cursorPosition.y, 1.0f);
	screenCoordinates = screenCoordinates.CreateTranslation(screenPosition);
	//DirectX::SimpleMath::Vector3 cameraPosition(camPosition.x, camPosition.y, 1.0f);
	//screenCoordinates = screenCoordinates.CreateTranslation(cameraPosition);

	dir = mat.Transpose() * screenCoordinates;
	dir /= mat.m[3][0] + mat.m[3][1] + mat.m[3][2] + mat.m[3][3];
	dir -= (camMatrix - cursorMatrix);

	return dir.Translation();
}