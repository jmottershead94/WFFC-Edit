#pragma once

#include "../Utilities/Maths/Maths.h"

/*
 * An abstract class that stores collider information.
 */
class Collider
{
	// Provides the raycast class with access to protected and private attributes and methods.
	friend class Raycast;

	public:
		/*
		 * Constructs this instance.
		 */
		explicit Collider() :
			kinematic(true),
			position(DirectX::SimpleMath::Vector3::Zero),
			rotation(DirectX::SimpleMath::Vector3::Zero),
			scale(1.0f, 1.0f, 1.0f),
			offset(DirectX::SimpleMath::Vector3::Zero)
		{};

		/*
		 * Constructs this instance.
		 * @param isKinematic if this collider is static or dynamic.
		 * @param newPosition the position of this collider.
		 * @param newRotation the rotation of this collider.
		 * @param newScale the scale of this collider.
		 * @param newOffset the offset of this collider from it's position.
		 */
		explicit Collider(const bool isKinematic, const DirectX::SimpleMath::Vector3& newPosition, const DirectX::SimpleMath::Vector3& newRotation, const DirectX::SimpleMath::Vector3& newScale, const DirectX::SimpleMath::Vector3& newOffset = DirectX::SimpleMath::Vector3::Zero) :
			kinematic(isKinematic),
			position(newPosition),
			rotation(newRotation),
			scale(newScale),
			offset(newOffset)
		{};

		/*
		 * Destructs this instance.
		 */
		virtual ~Collider() {};

		/*
		 * Updates the position and bounds of the collider.
		 * @param newPosition the new position of the collider.
		 * @param newRotation the new rotation of the collider.
		 * @param newScale the new scale of the collider.
		 */
		virtual void Update(const DirectX::SimpleMath::Vector3& newPosition, const DirectX::SimpleMath::Vector3& newRotation, const DirectX::SimpleMath::Vector3& newScale) = 0;

	protected:
		bool kinematic;
		DirectX::SimpleMath::Vector3 position;
		DirectX::SimpleMath::Vector3 rotation;
		DirectX::SimpleMath::Vector3 scale;
		DirectX::SimpleMath::Vector3 offset;

		/*
		 * Constructs this instance.
		 * @param collider the collider to copy.
		 */
		explicit Collider(const Collider& collider) :
			kinematic(collider.kinematic),
			position(collider.position),
			rotation(collider.rotation),
			scale(collider.scale),
			offset(collider.offset)
		{}

		/*
		 * Tests for point collisions in this collider.
		 * @param point the point to test against this collider.
		 * @return bool if the point lies inside of the collider.
		 */
		virtual bool const PointCollision(const DirectX::SimpleMath::Vector3& point) = 0;

		/*
		 * Tests for AABB collisions in this collider.
		 * @param collider the AABB collider to test against this collider.
		 * @return bool if the AABB lies inside of the collider.
		 */
		virtual bool const AABBCollision(const Collider& collider) = 0;
};