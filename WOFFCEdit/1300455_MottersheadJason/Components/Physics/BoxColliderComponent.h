#pragma once

#include "ColliderComponent.h"

/**
 * Stores information about box (AABB) colliders.
 */
class BoxColliderComponent : public ColliderComponent
{
	public:
		static const int IDNumber = 'BCCP';		// Provides a unique ID for this component.

		/**
		 * Constructs this instance.
		 */
		explicit BoxColliderComponent();

		/**
		 * Constructs this instance.
		 * @param isKinematic if this collider is static or dynamic.
		 * @param newPosition the position of this collider.
		 * @param newRotation the rotation of this collider.
		 * @param newScale the scale of this collider.
		 * @param newOffset the offset of this collider from it's position.
		 */
		explicit BoxColliderComponent(const bool isKinematic, const DirectX::SimpleMath::Vector3& newPosition, const DirectX::SimpleMath::Vector3& newRotation, const DirectX::SimpleMath::Vector3& newScale, const DirectX::SimpleMath::Vector3& newOffset);
		
		/**
		 * Destructs this instance.
		 */
		~BoxColliderComponent();

		/**
		 * Updates the position and bounds of the collider.
		 * @param dt the time passed since the last frame update.
		 * @param newPosition the new position of the collider.
		 * @param newRotation the new rotation of the collider.
		 * @param newScale the new scale of the collider.
		 */
		void Update(const double& dt, const DirectX::SimpleMath::Vector3& newPosition, const DirectX::SimpleMath::Vector3& newRotation, const DirectX::SimpleMath::Vector3& newScale) override;

		/**
		 * Obtains the ID of this component.
		 * @return const int the ID of this component.
		 */
		int const GetID() const override { return IDNumber; }

	protected:
		/**
		 * Tests for point collisions in this collider.
		 * @param point the point to test against this collider.
		 * @return const bool if the point lies inside of the collider.
		 */
		bool const PointCollision(const DirectX::SimpleMath::Vector3& point) override;

		/**
		 * Tests for AABB collisions in this collider.
		 * @param collider the AABB collider to test against this collider.
		 * @return const bool if the AABB lies inside of the collider.
		 */
		bool const AABBCollision(const ColliderComponent& collider) override;

		/**
		 * Used to update the bounds of the collider.
		 */
		void SetBounds() override;

	private:
		DirectX::SimpleMath::Vector3 _vecMax, _vecMin;
};