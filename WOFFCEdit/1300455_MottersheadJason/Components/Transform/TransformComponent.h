#pragma once

#include "../Component.h"
#include "../../Utilities/Maths/Maths.h"

/**
 * Stores information about the position, rotation and scale of an object.
 */
class TransformComponent : public Component
{
	public:
		static const int IDNumber = 'TRCP';		// Provides a unique ID for this component.

		/**
		 * Constructs this instance.
		 */
		explicit TransformComponent();

		/**
		 * Destructs this instance.
		 */
		~TransformComponent();

		/**
		 * Sets the position of this transform.
		 * @param position the vector3 position to set this transform to.
		 */
		inline void SetPosition(const DirectX::SimpleMath::Vector3& position)	{ _position = position; }

		/**
		 * Sets the position of this transform.
		 * @param x the x position of this transform.
		 * @param y the y position of this transform.
		 * @param z the z position of this transform.
		 */
		inline void SetPosition(const float& x, const float& y, const float& z)	{ _position = DirectX::SimpleMath::Vector3(x, y, z); }

		/**
		 * Sets the rotation of this transform.
		 * @param rotation how much this transform has rotated.
		 */
		inline void SetRotation(const DirectX::SimpleMath::Vector3& rotation)	{ _rotation = rotation; }

		/**
		 * Sets the rotation of this transform.
		 * @param x the x rotation of this transform.
		 * @param y the y rotation of this transform.
		 * @param z the z rotation of this transform.
		 */
		inline void SetRotation(const float& x, const float& y, const float& z)	{ _rotation = DirectX::SimpleMath::Vector3(x, y, z); }

		/**
		 * Sets the scale of this transform.
		 * @param scale how much this transform has scaled.
		 */
		inline void SetScale(const DirectX::SimpleMath::Vector3& scale)			{ _scale = scale; }

		/**
		 * Sets the scale of this transform.
		 * @param x the x scale factor of this transform.
		 * @param y the y scale factor of this transform.
		 * @param z the z scale factor of this transform.
		 */
		inline void SetScale(const float& x, const float& y, const float& z)		{ _scale = DirectX::SimpleMath::Vector3(x, y, z); }

		/**
		 * Gets the position of this transform.
		 * @return const DirectX::SimpleMath::Vector3 the position.
		 */
		inline DirectX::SimpleMath::Vector3 const GetPosition() const	{ return _position; }

		/**
		 * Gets the rotation of this transform.
		 * @return const DirectX::SimpleMath::Vector3 the rotation.
		 */
		inline DirectX::SimpleMath::Vector3 const GetRotation() const	{ return _rotation; }

		/**
		 * Gets the scale of this transform.
		 * @return const DirectX::SimpleMath::Vector3 the scale.
		 */
		inline DirectX::SimpleMath::Vector3 const GetScale() const		{ return _scale; }

		/*
		 * Obtains the ID of this component.
		 * @return const int the ID of this component.
		 */
		int const GetID() const override { return IDNumber; }

	private:
		DirectX::SimpleMath::Vector3 _position, _rotation, _scale;
};