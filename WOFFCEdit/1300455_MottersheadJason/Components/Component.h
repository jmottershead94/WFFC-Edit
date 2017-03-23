#pragma once

/**
 * A base component class to allow for any type of 
 * components to be added to the base object class.
 */
class Component
{
	public:
		/**
		 * Destructs this instance.
		 */
		virtual ~Component()
		{}

		/**
		 * Provides a way to retreive the ID of this component.
		 * @return const int the ID of this component.
		 */
		virtual int const GetID() const = 0;
};