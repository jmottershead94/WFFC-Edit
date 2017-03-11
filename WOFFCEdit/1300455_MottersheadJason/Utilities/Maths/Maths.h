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
		const float PI;
		static float Distance(DirectX::SimpleMath::Vector3 start, DirectX::SimpleMath::Vector3 end);
		static bool IsPointBetween(DirectX::SimpleMath::Vector3 start, DirectX::SimpleMath::Vector3 end, DirectX::SimpleMath::Vector3 currentPoint);
		static float RadiansToDegrees(const float radians);
		static float DegreesToRadians(const float degrees);
		static float Abs(const float value);
		static float RoundFloat(const float value);
		static DirectX::SimpleMath::Vector3 RoundVector3(DirectX::SimpleMath::Vector3& point);
		static std::vector<DirectX::SimpleMath::Vector3> BresenhamsLine(DirectX::SimpleMath::Vector3 start, DirectX::SimpleMath::Vector3 end);
};