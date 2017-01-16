#include "entity.h"

namespace sloth { namespace graphics {
	void graphics::Entity::increaseRotation(float dx, float dy, float dz)
	{
		m_RotX += dx;
		m_RotY += dy;
		m_RotZ += dz;
	}
	void graphics::Entity::increasePosition(float dx, float dy, float dz)
	{
		m_Position.x += dx;
		m_Position.y += dy;
		m_Position.z += dz;
	}

} }