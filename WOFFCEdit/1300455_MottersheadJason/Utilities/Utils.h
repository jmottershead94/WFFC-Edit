#pragma once

#include <iostream>
#include <memory>
#include <vector>
#include "../include/DirectXHelpers.h"
#include "../include/SimpleMath.h"

using namespace std;

#define UNUSED(x) (void)(x)

/**
 * Provides quick an easy access to common header files,
 * and will provide access to common functionality.
 */
class Utils
{
	friend class ToolMain;

	private:
		HWND _hwnd;
		int _width, _height;
		bool _wireframeMode;

		/**
		 * Constructs this instance.
		 */
		explicit Utils();
		
	public:
		/**
		 * Destructs this instance.
		 */
		~Utils();

		/**
		 * Initializes this instance.
		 * @param hwnd the handle to the current window.
		 * @param width the width of the window used.
		 * @param height the height of the window used.
		 */
		static void Initialize(HWND hwnd, int width, int height);

		/**
		 * Provides access to the window handle instance.
		 * @return const HWND the current window.
		 */
		static HWND const GetWindow();

		/**
		 * Provides access to the cursor position in the current window instance.
		 * @return const DirectX::SimpleMath::Vector3 the position of the cursor on screen.
		 */
		static DirectX::SimpleMath::Vector3 const GetCursorPositionInWindow();

		/**
		 * Provides access to the cursor position in the game world.
		 * @param worldMatrix the world matrix from the game.
		 * @param camPosition the position of the game camera.
		 * @return const DirectX::SimpleMath::Vector3 the position of the cursor in the game.
		 */
		static DirectX::SimpleMath::Vector3 const GetCursorPositionInWorld(DirectX::SimpleMath::Matrix worldMatrix, DirectX::SimpleMath::Vector3 camPosition);

		/**
		 * Provides a way to set wireframe mode for the application as a whole.
		 * @param wireframeState if we are using wireframe mode or not.
		 */
		static void SetWireframe(const bool wireframeState);

		/**
		 * Provides access to the current status of wireframe for the application.
		 * @return const bool if the application is using wireframe mode or not.
		 */
		static bool const WireframeMode();

		/**
		 * Provides a way to convert a string to a wstring.
		 * @param s the string to convert.
		 */
		static std::wstring const StringToWCHART(std::string s);

		/**
		 * Provides access to the file path and location of the highlighted texture.
		 * @return const std::string the file path and location of the highlighted texture.
		 */
		static std::string const HighlightedTexturePath();
};