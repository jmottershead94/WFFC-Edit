#include "Maths.h"

static std::unique_ptr<Maths> instance = nullptr;

Maths::Maths() :
	PI(3.1415f)
{
	if (instance == nullptr)
		instance = std::make_unique<Maths>(*this);
}

Maths::~Maths()
{}

float Maths::Distance(const DirectX::SimpleMath::Vector3& start, const DirectX::SimpleMath::Vector3& end)
{
	float result = 0.0f;
	float x = (end.x - start.x) * (end.x - start.x);
	float y = (end.y - start.y) * (end.y - start.y);
	float z = (end.z - start.z) * (end.z - start.z);

	// Calculate the square root of x^2 + y^2 + z^2 for the distance.
	result = std::sqrt(x + y + z);

	return result;
}

bool Maths::IsPointBetween(const DirectX::SimpleMath::Vector3& start, const DirectX::SimpleMath::Vector3& end, const DirectX::SimpleMath::Vector3& currentPoint)
{
	return (Distance(start, currentPoint) + Distance(end, currentPoint) == Distance(start, end));
}

float Maths::RadiansToDegrees(const float radians)
{
	float degrees = 0.0f;
	degrees = radians * (180.0f / instance->PI);
	return degrees;
}

float Maths::DegreesToRadians(const float degrees)
{
	float radians = 0.0f;
	radians = degrees * (instance->PI / 180.0f);
	return radians;
}

float Maths::Abs(const float value)
{
	float absolute = value;

	if (absolute < 0.0f)
		absolute *= -1.0f;

	return absolute;
}

float Maths::RoundFloat(const float value)
{
	float rounded = static_cast<int>(value);
	return rounded;
}

DirectX::SimpleMath::Vector3 Maths::RoundVector3(const DirectX::SimpleMath::Vector3& point)
{
	DirectX::SimpleMath::Vector3 roundedFloatValues(RoundFloat(point.x), RoundFloat(point.y), RoundFloat(point.z));
	return roundedFloatValues;
}

std::vector<DirectX::SimpleMath::Vector3> Maths::BresenhamsLine(const DirectX::SimpleMath::Vector3& start, const DirectX::SimpleMath::Vector3& end)
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
	float marginOfError = 0.003f;

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
		while(z != end.z)
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