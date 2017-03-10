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
void Utils::Initialize(HWND hwnd)
{
	_hwnd = hwnd;
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
 * @param hwnd the current handle to the window.
 * @return Vector3 the position of the cursor on screen.
 */
DirectX::SimpleMath::Vector3 Utils::GetCursorPositionInWindow()
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