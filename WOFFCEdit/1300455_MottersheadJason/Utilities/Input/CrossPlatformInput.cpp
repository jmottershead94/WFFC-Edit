#include "CrossPlatformInput.h"

static std::unique_ptr<CrossPlatformInput> instance = nullptr;

CrossPlatformInput::CrossPlatformInput()
{
	if (instance == nullptr)
		instance = std::make_unique<CrossPlatformInput>(*this);
}

CrossPlatformInput::~CrossPlatformInput()
{}

bool const CrossPlatformInput::MoveForward()
{
#if _WIN32
	return (Input::IsKeyDown('W') /*|| Input::GamePadLeftStickUp()*/);
#elif
	return false;
#endif
}

bool const CrossPlatformInput::MoveBack()
{
#if _WIN32
	return (Input::IsKeyDown('S') /*|| Input::GamePadLeftStickDown()*/);
#elif
	return false;
#endif
}

bool const CrossPlatformInput::MoveRight()
{
#if _WIN32
	return (Input::IsKeyDown('D') /*|| Input::GamePadLeftStickRight()*/);
#elif
	return false;
#endif
}

bool const CrossPlatformInput::MoveLeft()
{
#if _WIN32
	return (Input::IsKeyDown('A') /*|| Input::GamePadLeftStickLeft()*/);
#elif
	return false;
#endif
}

bool const CrossPlatformInput::MoveUp()
{
#if _WIN32
	return Input::IsKeyDown('E');
#elif
	return false;
#endif
}

bool const CrossPlatformInput::MoveDown()
{
#if _WIN32
	return Input::IsKeyDown('Q');
#elif
	return false;
#endif
}

bool const CrossPlatformInput::RotateRight()
{
#if _WIN32
	return (Input::MouseDragAxisX() > 0.0f || Input::IsKeyDown('L'));
#elif
	return false;
#endif
}

bool const CrossPlatformInput::RotateLeft()
{
#if _WIN32
	return (Input::MouseDragAxisX() < 0.0f || Input::IsKeyDown('J'));
#elif
	return false;
#endif
}

bool const CrossPlatformInput::RotateUp()
{
#if _WIN32
	return (Input::MouseDragAxisY() > 0.0f || Input::IsKeyDown('I'));
#elif
	return false;
#endif
}

bool const CrossPlatformInput::RotateDown()
{
#if _WIN32
	return (Input::MouseDragAxisY() < 0.0f || Input::IsKeyDown('K'));
#elif
	return false;
#endif
}

bool const CrossPlatformInput::SelectPressed()
{
#if _WIN32
	return Input::LeftMousePressed();
#elif
	return false;
#endif
}

bool const CrossPlatformInput::SelectReleased()
{
#if _WIN32
	return Input::LeftMouseReleased();
#elif
	return false;
#endif
}

bool const CrossPlatformInput::SelectDoublePressed()
{
#if _WIN32
	return Input::LeftMouseDouble();
#elif
	return false;
#endif
}

#if TOOL_EDITOR
	bool const CrossPlatformInput::TranslateHotKeyPressed()
	{
	#if _WIN32
		return Input::IsKeyPressed('1');
	#elif
		return false;
	#endif
	}

	bool const CrossPlatformInput::RotateHotKeyPressed()
	{
	#if _WIN32
		return Input::IsKeyPressed('2');
	#elif
		return false;
	#endif
	}

	bool const CrossPlatformInput::ScaleHotKeyPressed()
	{
	#if _WIN32
		return Input::IsKeyPressed('3');
	#elif
		return false;
	#endif
	}

	bool const CrossPlatformInput::CameraActivationPressed()
	{
	#if _WIN32
		return Input::RightMousePressed();
	#elif
		return false;
	#endif
	}

	bool const CrossPlatformInput::GenerateTerrainPressed()
	{
	#if _WIN32
		return Input::IsKeyPressed('G');
	#elif
		return false;
	#endif
	}

	bool const CrossPlatformInput::WireframeModePressed()
	{
	#if _WIN32
		bool keyPressed = (Input::IsKeyDown('W') && GetAsyncKeyState(VK_CONTROL));

		if(keyPressed)
			Input::SetKeyUp('W');

		return keyPressed;
	#elif
		return false;
	#endif
	}

	bool const CrossPlatformInput::SavePressed()
	{
	#if _WIN32
		bool keyPressed = (Input::IsKeyDown('S') && GetAsyncKeyState(VK_CONTROL));

		if(keyPressed)
			Input::SetKeyUp('S');

		return keyPressed;
	#elif
		return false;
	#endif
	}

	bool const CrossPlatformInput::SpawnTreePressed()
	{
	#if _WIN32
		return Input::IsKeyPressed('P');
	#elif
		return false;
	#endif
	}
#endif