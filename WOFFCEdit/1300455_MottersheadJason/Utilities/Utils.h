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
		DirectX::XMFLOAT4 floaty;
		Utils();
		HWND _hwnd;
		float _mapSize;
		DirectX::SimpleMath::Matrix _projectionMatrix;

	public:
		~Utils();
		static void Initialize(HWND hwnd, const float mapSize);
		static HWND const GetWindow();
		static DirectX::SimpleMath::Vector3 const GetCursorPositionInWindow();
		static DirectX::SimpleMath::Vector3 const GetCursorPositionInWorld(DirectX::SimpleMath::Matrix worldMatrix, DirectX::SimpleMath::Matrix projectionMatrix, DirectX::SimpleMath::Vector3 camPosition);
};