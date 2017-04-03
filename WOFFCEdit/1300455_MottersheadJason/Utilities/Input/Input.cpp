#include "Input.h"

static std::unique_ptr<Input> instance = nullptr;

Input::Input()
{
	if (instance == nullptr)
		instance = std::make_unique<Input>(*this);

	instance->SetLeftMousePressed(false);
	instance->SetRightMousePressed(false);
	instance->SetLeftMouseReleased(false);
	instance->SetRightMouseReleased(false);
	instance->SetLeftMouseDrag(false);
	instance->SetRightMouseDrag(false);
	instance->SetLeftMouseDouble(false);
	instance->SetRightMouseDouble(false);
	instance->SetMouseDragAxisX(0.0f);
	instance->SetMouseDragAxisY(0.0f);
}

Input::~Input()
{}

void Input::SetKeyDown(WPARAM key)
{
	instance->_keyboard._keys[key] = true;
}

void Input::SetKeyUp(WPARAM key)
{
	instance->_keyboard._keys[key] = false;
}

void Input::SetLeftMousePressed(const bool value)
{
	instance->_mouse._left = value;
}

void Input::SetRightMousePressed(const bool value)
{
	instance->_mouse._right = value;
}

void Input::SetLeftMouseReleased(const bool value)
{
	instance->_mouse._leftRelease = value;
}

void Input::SetRightMouseReleased(const bool value)
{
	instance->_mouse._rightRelease = value;
}

void Input::SetLeftMouseDrag(const bool value)
{
	instance->_mouse._leftDrag = value;
}

void Input::SetRightMouseDrag(const bool value)
{
	instance->_mouse._rightDrag = value;
}

void Input::SetLeftMouseDouble(const bool value)
{
	instance->_mouse._leftDoubleClick = value;
}

void Input::SetRightMouseDouble(const bool value)
{
	instance->_mouse._rightDoubleClick = value;
}

void Input::SetMouseDragAxisX(const float drag)
{
	instance->_mouse._dragX = drag;
}

void Input::SetMouseDragAxisY(const float drag)
{
	instance->_mouse._dragY = drag;
}

void Input::SetMouseX(const int x)
{
	instance->_mouse._x = x;
}

void Input::SetMouseY(const int y)
{
	instance->_mouse._y = y;
}

bool const Input::LeftMousePressed()
{
	return instance->_mouse._left;
}

bool const Input::RightMousePressed()
{
	return instance->_mouse._right;
}

bool const Input::LeftMouseReleased()
{
	return instance->_mouse._leftRelease;
}

bool const Input::RightMouseReleased()
{
	return instance->_mouse._rightRelease;
}

bool const Input::LeftMouseDrag()
{
	return instance->_mouse._leftDrag;
}

bool const Input::RightMouseDrag()
{
	return instance->_mouse._rightDrag;
}

bool const Input::LeftMouseDouble()
{
	return instance->_mouse._leftDoubleClick;
}

bool const Input::RightMouseDouble()
{
	return instance->_mouse._rightDoubleClick;
}

float const Input::MouseDragAxisX()
{
	return instance->_mouse._dragX;
}

float const Input::MouseDragAxisY()
{
	return instance->_mouse._dragY;
}

int const Input::GetMouseX()
{
	return instance->_mouse._x;
}

int const Input::GetMouseY()
{
	return instance->_mouse._y;
}

bool const Input::IsKeyDown(WPARAM key)
{
	return instance->_keyboard._keys[key];
}

bool const Input::IsKeyPressed(WPARAM key)
{
	bool keyPressed = instance->_keyboard._keys[key];
	instance->SetKeyUp(key);
	return keyPressed;
}

//void Input::GamePadSuspend()
//{
//	instance->_gamePad->Suspend();
//}
//
//void Input::GamePadResume()
//{
//	instance->_gamePad->Resume();
//}
//
//bool const Input::GamePadLeftStickUp()
//{
//	auto state = instance->_gamePad->GetState(0);
//
//	if (!state.IsConnected())
//		return false;
//
//	if (state.IsViewPressed())
//		PostQuitMessage(0);
//	else
//		return state.IsLeftThumbStickUp();
//}
//
//bool const Input::GamePadLeftStickDown()
//{
//	auto state = instance->_gamePad->GetState(0);
//
//	if (!state.IsConnected())
//		return false;
//
//	if (state.IsViewPressed())
//		PostQuitMessage(0);
//	else
//		return state.IsLeftThumbStickDown();
//}
//
//bool const Input::GamePadLeftStickRight()
//{
//	auto state = instance->_gamePad->GetState(0);
//
//	if (!state.IsConnected())
//		return false;
//
//	if (state.IsViewPressed())
//		PostQuitMessage(0);
//	else
//		return state.IsLeftThumbStickRight();
//}
//
//bool const Input::GamePadLeftStickLeft()
//{
//	auto state = instance->_gamePad->GetState(0);
//
//	if (!state.IsConnected())
//		return false;
//
//	if (state.IsViewPressed())
//		PostQuitMessage(0);
//	else
//		return state.IsLeftThumbStickLeft();
//}