#include "Utils.h"

std::unique_ptr<Utils> instance = nullptr;

/*
 * Constructs this instance.
 */
Utils::Utils()
{
	if (instance == nullptr)
	{
		instance = std::make_unique<Utils>(*this);
	}
}

/*
 * Destructs this instance.
 */
Utils::~Utils()
{}

/*
 * Provides access to the cursor position in the current window instance.
 * @param hwnd the current handle to the window.
 * @return Vector3 the position of the cursor on screen.
 */
DirectX::SimpleMath::Vector3 Utils::GetCursorPositionInWindow(HWND hwnd)
{
	DirectX::SimpleMath::Vector3 cursorPosition;
	
	POINT p;
	if (GetCursorPos(&p))
	{
		cursorPosition.x = static_cast<float>(p.x);
		cursorPosition.y = static_cast<float>(p.y);
		cursorPosition.z = 1.0f;
	}

	if (ScreenToClient(hwnd, &p))
	{
		cursorPosition.x = static_cast<float>(p.x);
		cursorPosition.y = static_cast<float>(p.y);
		cursorPosition.z = 1.0f;
	}

	return cursorPosition;
}