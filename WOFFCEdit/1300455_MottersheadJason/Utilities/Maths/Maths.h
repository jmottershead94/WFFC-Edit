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
		/*
		 * Constructs this instance.
		 */
		explicit Maths();

	public:
		const float PI;

		/*
		 * Destructs this instance.
		 */
		~Maths();

		/*
		 * Calculates the distance between two points.
		 * @param start the first point we are calculating from.
		 * @param end the second point we are calculating to.
		 * @return float the distance between the two given points.
		 */
		static float Distance(DirectX::SimpleMath::Vector3 start, DirectX::SimpleMath::Vector3 end);

		/*
		 * Checks to see if a given point is on a line between two given points.
		 * @param start the first point we are calculating from.
		 * @param end the second point we are calculating to.
		 * @param currentPoint the point we want to check and see if it is on the line.
		 * @return bool if the current point is on the line.
		 */
		static bool IsPointBetween(DirectX::SimpleMath::Vector3 start, DirectX::SimpleMath::Vector3 end, DirectX::SimpleMath::Vector3 currentPoint);

		/*
		 * Converts radian value to degrees.
		 * @param radians the radian value to convert to degrees.
		 * @return float the radian value in degrees.
		 */
		static float RadiansToDegrees(const float radians);

		/*
		 * Converts degrees value to radians.
		 * @param degrees the degree value to convert to radians.
		 * @return float the degree value in radians.
		 */
		static float DegreesToRadians(const float degrees);

		/*
		 * Get the absolute value of a number.
		 * @param value the value to return an absolute value of.
		 * @return float the absolute value itself.
		 */
		static float Abs(const float value);

		/*
		 * Provides access to rounded floating point values.
		 * @param value the value to return as rounded.
		 * @return float the rounded float value.
		 */
		static float RoundFloat(const float value);

		/*
		 * Provides quick access to a rounded off Vector3.
		 * @param point the Vector3 to round off.
		 * @return DirectX::SimpleMath::Vector3 the rounded Vector3.
		 */
		static DirectX::SimpleMath::Vector3 RoundVector3(DirectX::SimpleMath::Vector3& point);

		/*
		 * Determines the points on a line given a start and end point.
		 * @param start the point to go from.
		 * @param end the point to go to.
		 * @return std::vector<DirectX::SimpleMath::Vector3> the data structure of points on the line.
		 */
		static std::vector<DirectX::SimpleMath::Vector3> BresenhamsLine(DirectX::SimpleMath::Vector3 start, DirectX::SimpleMath::Vector3 end);
};