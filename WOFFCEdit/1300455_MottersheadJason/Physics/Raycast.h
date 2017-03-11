#pragma once

#include "Collider.h"

/*
 * A class to perform raycasting with.
 */
class Raycast
{
	public:
		/*
		 * Constructs this instance.
		 */
		explicit Raycast();

		/*
		 * Destructs this instance.
		 */
		~Raycast();

		/*
		 * Casts a ray from a start point to an end point and checks for collisions along the ray.
		 * @param start where to draw the ray FROM.
		 * @param end where the ray should END.
		 * @param collider the collider to test this ray against.
		 * @param returnFirstHit if this function should return after the first collision has been detected.
		 * @return bool if this ray has hit something.
		 */
		bool Hit(const DirectX::SimpleMath::Vector3& start, const DirectX::SimpleMath::Vector3& end, Collider& collider, const bool& returnFirstHit = true);

		/*
		 * Provides access to the origin of the ray.
		 * @return const DirectX::SimpleMath::Vector3 the starting point of the ray.
		 */
		inline DirectX::SimpleMath::Vector3 const GetOrigin() const			{ return _start; }

		/*
		 * Provides access to the end of the ray.
		 * @return const DirectX::SimpleMath::Vector3 the end of the ray.
		 */
		inline DirectX::SimpleMath::Vector3 const GetEnd() const			{ return _end; }

		/*
		 * Provides access to the direction of the ray.
		 * @return const DirectX::SimpleMath::Vector3 the direction of the ray.
		 */
		inline DirectX::SimpleMath::Vector3 const GetDirection() const		{ return _direction; }

	private:
		DirectX::SimpleMath::Vector3 _start;
		DirectX::SimpleMath::Vector3 _end;
		DirectX::SimpleMath::Vector3 _direction;
};