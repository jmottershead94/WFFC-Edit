#pragma once

#include <memory>
#include <Windows.h>

/**
 * Provides access to input anywhere in the application, input 
 * here will be platform specific and not consider cross platform.
 */
class Input
{
	friend class ToolMain;

	private:
		/**
		 * Holds information about PC specific input.
		 */
		typedef struct PC
		{
			/**
			 * Holds information about mouse input.
			 */
			typedef struct Mouse
			{
				int _x, _y;
				bool _left, _right;
				bool _leftRelease, _rightRelease;
				bool _leftDrag, _rightDrag;
				bool _leftDoubleClick, _rightDoubleClick;
				float _leftDragAxis, _rightDragAxis;
			};

			/**
			 * Holds information about keyboard input.
			 */
			typedef struct Keyboard
			{
				bool _keys[256];
			};

			Mouse _mouse;
			Keyboard _keyboard;
		};

		PC _pc;

		/**
		 * Constructs this instance.
		 */
		explicit Input();

	public:
		/**
		 * Destructs this instance.
		 */
		~Input();

		static void SetKeyDown(const int key);
		static void SetKeyUp(const int key);
		static void SetLeftMousePressed(const bool value);
		static void SetRightMousePressed(const bool value);
		static void SetLeftMouseReleased(const bool value);
		static void SetRightMouseReleased(const bool value);
		static void SetLeftMouseDrag(const bool value);
		static void SetRightMouseDrag(const bool value);
		static void SetLeftMouseDouble(const bool value);
		static void SetRightMouseDouble(const bool value);
		static void SetLeftDragAxis(const float drag);
		static void SetRightDragAxis(const float drag);
		static void SetMouseX(const int x);
		static void SetMouseY(const int y);

		static bool LeftMousePressed();
		static bool RightMousePressed();
		static bool LeftMouseReleased();
		static bool RightMouseReleased();
		static bool LeftMouseDrag();
		static bool RightMouseDrag();
		static bool LeftMouseDouble();
		static bool RightMouseDouble();
		static float LeftMouseDragAxis();
		static float RightMouseDragAxis();
		static int GetMouseX();
		static int GetMouseY();

		/**
		 * Checks if a key has been pressed.
		 * @param key the current key we are checking.
		 */
		static bool IsKeyDown(WPARAM key);
};