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

		/**
		 * Provides a way to enable/disable this component.
		 * @param value if this component is enabled/disabled.
		 */
		inline void SetEnabled(const bool value)	{ _enabled = value; }

		/**
		 * Provides access to the active state of this component.
		 * @return const bool if this component is enabled.
		 */
		inline bool const Enabled() const			{ return _enabled; }

	private:
		bool _enabled = true;
};