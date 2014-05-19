#pragma once

namespace FormatInformation
{
	class EntityFormat
	{
	public:
		EntityFormat(bool animated) : m_animated(animated) {}
		virtual ~EntityFormat(void) {}

		bool isAnimated(void) { return m_animated; }

	protected:

		// Format information
		bool m_animated;
	};
	
	static const EntityFormat FRMT_ANIMATED = EntityFormat(true);
	static const EntityFormat FRMT_STATIC = EntityFormat(true);
}