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
		 * Calculates the correct vectors (right, forward, up) for this transform.
		 */
		void CalculateVectors();

		/**
		 * Updates the look at point based on the position and forward vectors.
		 */
		void CalculateLookAt();

		/**
		 * Sets the position of this transform.
		 * @param position the vector3 position to set this transform to.
		 */
		inline void SetPosition(const DirectX::SimpleMath::Vector3& position)		{ _position = position; }

		/**
		 * Sets the position of this transform.
		 * @param x the x position of this transform.
		 * @param y the y position of this transform.
		 * @param z the z position of this transform.
		 */
		inline void SetPosition(const float& x, const float& y, const float& z)		{ _position = DirectX::SimpleMath::Vector3(x, y, z); }

		/**
		 * Moves this transform to a new position.
		 * @param translation how far to move this transform.
		 */
		inline void Translate(const DirectX::SimpleMath::Vector3& translation)		{ _position += translation; }

		/**
		 * Moves this transform to a new position.
		 * @param x how far to translate this transform on the x axis.
		 * @param y how far to translate this transform on the y axis.
		 * @param z how far to translate this transform on the z axis.
		 */
		inline void Translate(const float x, const float y, const float z)			{ _position += DirectX::SimpleMath::Vector3(x, y, z); }
		
		/**
		 * Sets the rotation of this transform.
		 * @param rotation how much this transform has rotated.
		 */
		inline void SetRotation(const DirectX::SimpleMath::Vector3& rotation)		{ _rotation = rotation; }

		/**
		 * Sets the rotation of this transform.
		 * @param x the x rotation of this transform.
		 * @param y the y rotation of this transform.
		 * @param z the z rotation of this transform.
		 */
		inline void SetRotation(const float& x, const float& y, const float& z)		{ _rotation = DirectX::SimpleMath::Vector3(x, y, z); }

		/**
		 * Sets the x rotation of this transform.
		 * @param x the x axis rotation value.
		 */
		inline void SetRotationX(const float& x)									{ _rotation.x = x; }

		/**
		 * Rotate this transform to a new orientation.
		 * @param rotation how far to rotate this transform.
		 */
		inline void Rotate(const DirectX::SimpleMath::Vector3& rotation)			{ _rotation += rotation; }

		/**
		 * Rotate this transform to a new orientation.
		 * @param x how far to rotate this transform on the x axis.
		 * @param y how far to rotate this transform on the y axis.
		 * @param z how far to rotate this transform on the z axis.
		 */
		inline void Rotate(const float x, const float y, const float z)				{ _rotation += DirectX::SimpleMath::Vector3(x, y, z); }
		
		/**
		 * Sets the scale of this transform.
		 * @param scale how much this transform has scaled.
		 */
		inline void SetScale(const DirectX::SimpleMath::Vector3& scale)				{ _scale = scale; }

		/**
		 * Sets the scale of this transform.
		 * @param x the x scale factor of this transform.
		 * @param y the y scale factor of this transform.
		 * @param z the z scale factor of this transform.
		 */
		inline void SetScale(const float& x, const float& y, const float& z)		{ _scale = DirectX::SimpleMath::Vector3(x, y, z); }

		/**
		 * Sets the look at point for this transform.
		 * @param lookAt the point that this transform should be looking at.
		 */
		inline void SetLookAt(const DirectX::SimpleMath::Vector3& lookAt)			{ _lookAt = lookAt; }
	
		/**
		 * Gets the position of this transform.
		 * @return const DirectX::SimpleMath::Vector3 the position.
		 */
		inline DirectX::SimpleMath::Vector3 const Position() const	{ return _position; }

		/**
		 * Gets the rotation of this transform.
		 * @return const DirectX::SimpleMath::Vector3 the rotation.
		 */
		inline DirectX::SimpleMath::Vector3 const Rotation() const	{ return _rotation; }

		/**
		 * Gets the scale of this transform.
		 * @return const DirectX::SimpleMath::Vector3 the scale.
		 */
		inline DirectX::SimpleMath::Vector3 const Scale() const		{ return _scale; }

		/**
		 * Gets the look at point for this transform.
		 * @return const DirectX::SimpleMath::Vector3 the look at position.
		 */
		inline DirectX::SimpleMath::Vector3 const LookAt() const	{ return _lookAt; }

		/**
		 * Gets the forward vector of this transform.
		 * @return const DirectX::SimpleMath::Vector3 the forward vector.
		 */
		inline DirectX::SimpleMath::Vector3 const Forward() const { return _forward; }

		/**
		 * Gets the right vector of this transform.
		 * @return const DirectX::SimpleMath::Vector3 the right vector.
		 */
		inline DirectX::SimpleMath::Vector3 const Right() const		{ return _right; }

		/**
		 * Gets the up vector of this transform.
		 * @return const DirectX::SimpleMath::Vector3 the up vector.
		 */
		inline DirectX::SimpleMath::Vector3 const Up() const		{ return _up; }

		/*
		 * Obtains the ID of this component.
		 * @return const int the ID of this component.
		 */
		int const GetID() const override							{ return IDNumber; }

	private:
		DirectX::SimpleMath::Vector3 _position, _rotation, _scale;
		DirectX::SimpleMath::Vector3 _lookAt;
		DirectX::SimpleMath::Vector3 _right, _up, _forward;
};