#pragma once

#include "Input.h"

/**
 * Provides access to input anywhere in the application, 
 * input here should be considered cross platform.
 */
class CrossPlatformInput
{
	friend class Editor;

	private:
		/**
		 * Constructs this instance.
		 */
		explicit CrossPlatformInput();

	public:
		/**
		 * Destructs this instance.
		 */
		~CrossPlatformInput();

		/**
		 * Checks if input for moving forward has been activated.
		 * @return const bool if the input is saying to move forward.
		 */
		static bool const MoveForward();

		/**
		 * Checks if input for moving back has been activated.
		 * @return const bool if the input is saying to move back.
		 */
		static bool const MoveBack();

		/**
		 * Checks if input for moving right has been activated.
		 * @return const bool if the input is saying to move right.
		 */
		static bool const MoveRight();

		/**
		 * Checks if input for moving left has been activated.
		 * @return const bool if the input is saying to move left.
		 */
		static bool const MoveLeft();

		/**
		 * Checks if input for moving up has been activated.
		 * @return const bool if the input is saying to move up.
		 */
		static bool const MoveUp();

		/**
		 * Checks if input for moving down has been activated.
		 * @return const bool if the input is saying to move down.
		 */
		static bool const MoveDown();

		/**
		 * Checks if input for rotating to the right has been activated.
		 * @return const bool if the input is saying to rotate right.
		 */
		static bool const RotateRight();

		/**
		 * Checks if input for rotating to the left has been activated.
		 * @return const bool if the input is saying to rotate left.
		 */
		static bool const RotateLeft();

		/**
		 * Checks if input for rotating upwards has been activated.
		 * @return const bool if the input is saying to rotate up.
		 */
		static bool const RotateUp();

		/**
		 * Checks if input for rotating down has been activated.
		 * @return const bool if the input is saying to rotate right.
		 */
		static bool const RotateDown();

		/**
		 * Checks if input for selecting something has been activated.
		 * @return const bool if the input is selecting something.
		 */
		static bool const SelectPressed();

		/**
		 * Checks if input for selecting something has been released.
		 * @return const bool if the input for selecting something has released.
		 */
		static bool const SelectReleased();

		/**
		 * Checks if input for selecting something has been activated twice in one go.
		 * @return const bool if the input for selecting has been activated twice in one go.
		 */
		static bool const SelectDoublePressed();

// Below resides cross platform input commands specific to the editor.
#if TOOL_EDITOR
		/**
		 * Checks if input for activating the editor's translate mode has been activated.
		 * @return const bool if the input for switching to translate mode has been activated.
		 */
		static bool const TranslateHotKeyPressed();

		/**
		 * Checks if input for activating the editor's rotate mode has been activated.
		 * @return const bool if the input for switching to rotate mode has been activated.
		 */
		static bool const RotateHotKeyPressed();

		/**
		 * Checks if input for activating the editor's scale mode has been activated.
		 * @return const bool if the input for switching to scale mode has been activated.
		 */
		static bool const ScaleHotKeyPressed();

		/**
		 * Checks if input for activating camera movement has been activated.
		 * @return const bool if the input for activating camera input has been activated.
		 */
		static bool const CameraActivationPressed();

		/**
		 * Checks if input for generating random terrain has been activated.
		 * @return const bool if the random terrain generation input has been activated.
		 */
		static bool const GenerateTerrainPressed();

		/**
		 * Checks if input for setting wireframe mode has been activated.
		 * @return const bool if the input for wireframe mode is activated.
		 */
		static bool const WireframeModePressed();

		/**
		 * Checks if input for saving has been activated.
		 * @return const bool if the input is selecting something.
		 */
		static bool const SavePressed();

		/**
		 * Checks if input for spawning trees has been activated.
		 * @return const bool if the input for spawning trees has been pressed.
		 */
		static bool const SpawnTreePressed();
#endif
};