#pragma once

#include <Windows.h>
#include "GamePad.h"
#include "../Utils.h"

/**
 * Provides access to input anywhere in the application, input 
 * here will be platform specific and not consider cross platform.
 */
class Input
{
	friend class ToolMain;

	private:
		/**
		 * Holds information about mouse input.
		 */
		struct Mouse
		{
			int _x, _y;
			bool _left, _right;
			bool _leftRelease, _rightRelease;
			bool _leftDrag, _rightDrag;
			bool _leftDoubleClick, _rightDoubleClick;
			float _dragX, _dragY;
		};

		/**
		 * Holds information about keyboard input.
		 */
		struct Keyboard
		{
			bool _keys[256];
		};

		Mouse _mouse;
		Keyboard _keyboard;
		//std::unique_ptr<DirectX::GamePad> _gamePad;

		/**
		 * Constructs this instance.
		 */
		explicit Input();

		/**
		 * Provides a way to set how far the mouse has dragged along the x axis.
		 * @param drag how far the mouse has dragged along the x axis (clamped between -1.0f and 1.0f).
		 */
		static void SetMouseDragAxisX(const float drag);

		/**
		 * Provides a way to set how far the mouse has dragged along the y axis.
		 * @param drag how far the mouse has dragged along the y axis (clamped between -1.0f and 1.0f).
		 */
		static void SetMouseDragAxisY(const float drag);

		/**
		 * Provides a way to set the x position of the mouse.
		 * @param x the x position of the cursor.
		 */
		static void SetMouseX(const int x);

		/**
		 * Provides a way to set the x position of the mouse.
		 * @param x the x position of the cursor.
		 */
		static void SetMouseY(const int y);

	public:
		/**
		 * Destructs this instance.
		 */
		~Input();

		/**
		 * Provides a way to set a key down.
		 * @param key the key that is being pressed down.
		 */
		static void SetKeyDown(WPARAM key);

		/**
		 * Provides a way to set a key up.
		 * @param key the key that has been released.
		 */
		static void SetKeyUp(WPARAM key);

		/**
		 * Provides a way to toggle left mouse presses.
		 * @param value if the left mouse button is currently being pressed.
		 */
		static void SetLeftMousePressed(const bool value);

		/**
		 * Provides a way to toggle right mouse presses.
		 * @param value if the right mouse button is currently being pressed.
		 */
		static void SetRightMousePressed(const bool value);

		/**
		 * Provides a way to toggle left mouse releases.
		 * @param value if the left mouse button has been released.
		 */
		static void SetLeftMouseReleased(const bool value);

		/**
		 * Provides a way to toggle right mouse releases.
		 * @param value if the right mouse button has been released.
		 */
		static void SetRightMouseReleased(const bool value);

		/**
		 * Provides a way to toggle left mouse drag.
		 * @param value if the left mouse button is held and the mouse is being dragged.
		 */
		static void SetLeftMouseDrag(const bool value);

		/**
		 * Provides a way to toggle right mouse drag.
		 * @param value if the right mouse button is held and the mouse is being dragged.
		 */
		static void SetRightMouseDrag(const bool value);

		/**
		 * Provides a way to toggle double left mouse presses.
		 * @param value if the left mouse button has been clicked twice in one go.
		 */
		static void SetLeftMouseDouble(const bool value);

		/**
		 * Provides a way to toggle double right mouse presses.
		 * @param value if the right mouse button has been clicked twice in one go.
		 */
		static void SetRightMouseDouble(const bool value);

		/**
		 * Checks if the left mouse button has been pressed.
		 * @return const bool if the left mouse button is being pressed.
		 */
		static bool const LeftMousePressed();

		/**
		 * Checks if the right mouse button has been pressed.
		 * @return const bool if the right mouse button is being pressed.
		 */
		static bool const RightMousePressed();

		/**
		 * Checks if the left mouse button has been released.
		 * @return const bool if the left mouse button has been released.
		 */
		static bool const LeftMouseReleased();

		/**
		 * Checks if the right mouse button has been released.
		 * @return const bool if the right mouse button has been released.
		 */
		static bool const RightMouseReleased();

		/**
		 * Checks if the left mouse button is being held and if the mouse is also being dragged.
		 * @return const bool if the left mouse button is held along with the mouse being dragged.
		 */
		static bool const LeftMouseDrag();

		/**
		 * Checks if the right mouse button is being held and if the mouse is also being dragged.
		 * @return const bool if the right mouse button is held along with the mouse being dragged.
		 */
		static bool const RightMouseDrag();

		/**
		 * Checks if the left mouse button has been clicked twice.
		 * @return const bool if the left mouse button has been clicked twice.
		 */
		static bool const LeftMouseDouble();

		/**
		 * Checks if the right mouse button has been clicked twice.
		 * @return const bool if the right mouse button has been clicked twice.
		 */
		static bool const RightMouseDouble();

		/**
		 * Provides a way to check the current mouse drag value for the x axis.
		 * @return const float the mouse x drag value (-1.0f for left, 1.0f for right).
		 */
		static float const MouseDragAxisX();

		/**
		 * Provides a way to check the current mouse drag value for the y axis.
		 * @return const float the mouse y drag value (-1.0f for down, 1.0f for up).
		 */
		static float const MouseDragAxisY();

		/**
		 * Provides a way to check the x position of the mouse.
		 * @return const int the x position of the mouse.
		 */
		static int const GetMouseX();

		/**
		 * Provides a way to check the y position of the mouse.
		 * @return const int the y position of the mouse.
		 */
		static int const GetMouseY();

		/**
		 * Checks if a key has been pressed.
		 * @param key the current key we are checking.
		 */
		static bool const IsKeyDown(WPARAM key);

		/**
		 * Checks to see if a key has been pressed once.
		 * @param key the current key we are checking.
		 */
		static bool const IsKeyPressed(WPARAM key);

		//==========================================================================================================
		//
		// Unique pointer implementation was not working in this class.
		// Tried controls in the game class, still didn't work with Dualshock 4, need to get my 360 controller back.
		//

		/*static void GamePadSuspend();
		static void GamePadResume();
		static bool const GamePadLeftStickUp();
		static bool const GamePadLeftStickDown();
		static bool const GamePadLeftStickRight();
		static bool const GamePadLeftStickLeft();
		static bool const GamePadLeftTriggerPressed();
		static bool const GamePadRightTriggerPressed();
		static bool const GamePadRightStickUp();
		static bool const GamePadRightStickDown();
		static bool const GamePadRightStickRight();
		static bool const GamePadRightStickLeft();*/

};