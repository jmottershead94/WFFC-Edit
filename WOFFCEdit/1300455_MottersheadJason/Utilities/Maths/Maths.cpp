#include "Maths.h"

std::unique_ptr<Maths> instance = nullptr;

/*
 * Constructs this instance.
 */
Maths::Maths()
{
	if (instance == nullptr)
		instance = std::make_unique<Maths>(*this);
}

/*
 * Destructs this instance.
 */
Maths::~Maths()
{}

/*
 * Calculates the distance between two points.
 * @param start the first point we are calculating from.
 * @param end the second point we are calculating to.
 * @return float the distance between the two given points.
 */
float Maths::Distance(DirectX::SimpleMath::Vector3 start, DirectX::SimpleMath::Vector3 end)
{
	float result = 0.0f;
	float x = (end.x - start.x) * (end.x - start.x);
	float y = (end.y - start.y) * (end.y - start.y);
	float z = (end.z - start.z) * (end.z - start.z);

	// Calculate the square root of x^2 + y^2 + z^2 for the distance.
	result = std::sqrt(x + y + z);

	return result;
}

/*
 * Checks to see if a given point is on a line between two given points.
 * @param start the first point we are calculating from.
 * @param end the second point we are calculating to.
 * @param currentPoint the point we want to check and see if it is on the line.
 * @return bool if the current point is on the line.
 */
bool Maths::IsPointBetween(DirectX::SimpleMath::Vector3 start, DirectX::SimpleMath::Vector3 end, DirectX::SimpleMath::Vector3 currentPoint)
{
	if (Distance(start, currentPoint) + Distance(end, currentPoint) == Distance(start, end))
		return true;

	return false;
}

/*
 * Get the absolute value of a number.
 * @param the value to return an absolute value of.
 * @return float the absolute value itself.
 */
float Maths::Abs(float value)
{
	float absolute = value;

	if (absolute < 0.0f)
		absolute *= -1.0f;

	return absolute;
}

/*
 * Determines the points on a line given a start and end point.
 * @param start the point to go from.
 * @param end the point to go to.
 * @return std::vector<DirectX::SimpleMath::Vector3> the data structure of points on the line.
 */
std::vector<DirectX::SimpleMath::Vector3> Maths::BresenhamsLine(DirectX::SimpleMath::Vector3 start, DirectX::SimpleMath::Vector3 end)
{
	std::vector<DirectX::SimpleMath::Vector3> result;

	// The current position values to use.
	float x = start.x;
	float y = start.y;
	float z = start.z;

	// Calculating the difference in x, y and z.
	float dx = Abs(end.x - start.x);
	float dy = Abs(end.y - start.y);
	float dz = Abs(end.z - start.z);

	float xStep = 1.0f, yStep = 1.0f, zStep = 1.0f;
	float errorX = 1.0f, errorY = 1.0f, errorZ = 1.0f;

	// If any of the start points are greater than the end points, reverse their respective steps.
	if (start.x > end.x)
		xStep = -1.0f;

	if (start.y > end.y)
		yStep = -1.0f;

	if (start.z > end.z)
		zStep = -1.0f;

	if (dz > dx && dz > dy)
	{
		errorX = dz * 0.5f;
		errorY = dz * 0.5f;

		// Stepping the z coordinate along.
		while (z != end.z)
		{
			DirectX::SimpleMath::Vector3 point(x, y, z);
			result.push_back(point);

			// Stepping the x coordinate along.
			errorX -= dx;
			if (errorX < 0.0f)
			{
				x += xStep;
				errorX += dz;
			}

			// Stepping the y coordinate along.
			errorY -= dy;
			if (errorY < 0.0f)
			{
				y += yStep;
				errorY += dz;
			}
			z += zStep;
		}
	}
	else if (dx > dy)
	{
		errorZ = dx * 0.5f;
		errorY = dx * 0.5f;

		// Stepping the x coordinate along.
		while (x != end.x)
		{
			DirectX::SimpleMath::Vector3 point(x, y, z);
			result.push_back(point);

			// Stepping the y coordinate along.
			errorY -= dy;
			if (errorY < 0.0f)
			{
				y += yStep;
				errorY += dx;
			}

			// Stepping the z coordinate along.
			errorZ -= dz;
			if (errorZ < 0.0f)
			{
				z += zStep;
				errorZ += dx;
			}
			x += xStep;
		}
	}
	else
	{
		errorX = dy * 0.5f;
		errorZ = dy * 0.5f;

		// Stepping the y coordinate along.
		while (y != end.y)
		{
			DirectX::SimpleMath::Vector3 point(x, y, z);
			result.push_back(point);

			// Stepping the x coordinate along.
			errorX -= dx;
			if (errorX < 0.0f)
			{
				x += xStep;
				errorX += dy;
			}

			// Stepping the z coordinate along.
			errorZ -= dz;
			if (errorZ < 0.0f)
			{
				z += zStep;
				errorZ += dy;
			}
			y += yStep;
		}
	}

	result.push_back(end);

	return result;
}