#pragma once

#include "../Component.h"
#include "../../Utilities/Maths/Maths.h"

/**
 * Stores information for colliders in general, actual colliders
 * should inherit from this class.
 */
class ColliderComponent : public Component
{
	friend class Raycast;

	public:
		/**
		 * Destructs this instance.
		 */
		~ColliderComponent()
		{}

		/**
		 * Updates the position and bounds of the collider.
		 * @param dt the time passed since the last frame update.
		 * @param newPosition the new position of the collider.
		 * @param newRotation the new rotation of the collider.
		 * @param newScale the new scale of the collider.
		 */
		virtual void Update(const double& dt, const DirectX::SimpleMath::Vector3& newPosition, const DirectX::SimpleMath::Vector3& newRotation, const DirectX::SimpleMath::Vector3& newScale) = 0;

		/**
		 * Sets if this collider is dynamic or static.
		 * @param value if the collider will be dynamic or static.
		 */
		inline void SetKinematic(const bool value)									{ kinematic = value; }

		/**
		 * Provides access to the dynamic state of this collider.
		 * @return const bool if this object is static or dynamic.
		 */
		inline bool const Kinematic() const								{ return kinematic; }

	protected:
		bool kinematic;
		DirectX::SimpleMath::Vector3 position;
		DirectX::SimpleMath::Vector3 rotation;
		DirectX::SimpleMath::Vector3 scale;
		DirectX::SimpleMath::Vector3 halfScale;
		DirectX::SimpleMath::Vector3 offset;

		/**
		 * Tests for point collisions in this collider.
		 * @param point the point to test against this collider.
		 * @return const bool if the point lies inside of the collider.
		 */
		virtual bool const PointCollision(const DirectX::SimpleMath::Vector3& point) = 0;

		/**
		 * Tests for AABB collisions in this collider.
		 * @param collider the AABB collider to test against this collider.
		 * @return const bool if the AABB lies inside of the collider.
		 */
		virtual bool const AABBCollision(const ColliderComponent& collider) = 0;

		/**
		 * Used to update the bounds of the collider.
		 */
		virtual void SetBounds() = 0;

		/**
		 * Sets the position of this collider.
		 * @param newPosition the new position of this collider.
		 */
		inline void SetPosition(const DirectX::SimpleMath::Vector3& newPosition) { position = newPosition; }

		/**
		 * Sets the rotation of this collider.
		 * @param newRotation the new rotation value of this collider.
		 */
		inline void SetRotation(const DirectX::SimpleMath::Vector3& newRotation) { rotation = newRotation; }

		/**
		 * Sets the scale of this collider.
		 * @param newScale the new scale value of this collider.
		 */
		inline void SetScale(const DirectX::SimpleMath::Vector3& newScale) { scale = newScale; }

		/**
		 * Sets the half scale value of this collider.
		 */
		inline void SetHalfScale() { halfScale = scale * 0.5f; }

		/**
		 * Sets the offset position of this collider.
		 * @param newOffset the new offset position of this collider.
		 */
		inline void SetOffset(const DirectX::SimpleMath::Vector3& newOffset) { offset = newOffset; }

		/**
		 * Provides access to the position of this collider.
		 * @return const DirectX::SimpleMath::Vector3 the collider position.
		 */
		inline DirectX::SimpleMath::Vector3 const Position() const { return position; }

		/**
		 * Provides access to the rotation of this collider.
		 * @return const DirectX::SimpleMath::Vector3 the collider rotation.
		 */
		inline DirectX::SimpleMath::Vector3 const Rotation() const { return rotation; }

		/**
		 * Provides access to the scale of this collider.
		 * @return const DirectX::SimpleMath::Vector3 the collider scale.
		 */
		inline DirectX::SimpleMath::Vector3 const Scale() const { return scale; }

		/**
		 * Provides access to the offset of this collider.
		 * @return const DirectX::SimpleMath::Vector3 the collider offset value.
		 */
		inline DirectX::SimpleMath::Vector3 const Offset() const { return offset; }

};