#pragma once

#include <cmath>
#include "../Utils.h"

/*
 * Used to provide access to common mathematical functionality.
 */
class Maths
{
	friend class ToolMain;

	private:
		Maths();

	public:
		~Maths();
		static float Distance(DirectX::SimpleMath::Vector3 start, DirectX::SimpleMath::Vector3 end);
		static bool IsPointBetween(DirectX::SimpleMath::Vector3 start, DirectX::SimpleMath::Vector3 end, DirectX::SimpleMath::Vector3 currentPoint);
		static float Abs(float value);
		static std::vector<DirectX::SimpleMath::Vector3> BresenhamsLine(DirectX::SimpleMath::Vector3 start, DirectX::SimpleMath::Vector3 end);
};