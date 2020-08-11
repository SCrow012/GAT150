#include "pch.h"
#include "PhysicsComponent.h"
#include "Objects/GameObject.h"

namespace nc
{
	void PhysicComponent::Create(void* data)
	{

	}

	void PhysicComponent::Destroy()
	{

	}

	void PhysicComponent::Update()
	{
		m_velocity = m_velocity + m_force; // *timer.DeltaTime();
		m_velocity = m_velocity * m_drag;
		m_owner->m_transform.position = m_owner->m_transform.position + m_velocity; //* timer.DeltaTime();
	}
}
