#pragma once

#include <memory>
#include <vector>
#include "../include/DirectXHelpers.h"
#include "../include/SimpleMath.h"

using namespace std;

/*
 * Provides quick an easy access to common header files,
 * and will provide access to common functionality.
 */
class Utils
{
	friend class ToolMain;

	private:
		Utils();
		HWND _hwnd;

	public:
		~Utils();
		void Initialize(HWND hwnd);
		static HWND const GetWindow();
		static DirectX::SimpleMath::Vector3 GetCursorPositionInWindow();
};