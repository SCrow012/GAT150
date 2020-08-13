#include "pch.h"
#include "PlayerComponents.h"
#include "Objects/GameObject.h"
#include "Components/PhysicsComponent.h"

namespace nc
{
	void PlayerComponent::Create(void* data)
	{
	}

	void PlayerComponent::Destroy()
	{
	}

	void PlayerComponent::Update()
	{
		if (m_owner->m_engine->GetSystem<nc::InputSystem>()->GetButtonState(SDL_SCANCODE_LEFT) == nc::InputSystem::eButtonState::HELD)
		{
			m_owner->m_transform.angle = m_owner->m_transform.angle - 200.0f * m_owner->m_engine->GetTimer().DeltaTime();
		}
		if (m_owner->m_engine->GetSystem<nc::InputSystem>()->GetButtonState(SDL_SCANCODE_RIGHT) == nc::InputSystem::eButtonState::HELD)
		{
			m_owner->m_transform.angle = m_owner->m_transform.angle + 200.0f * m_owner->m_engine->GetTimer().DeltaTime();
		}

		nc::Vector2 force{ 0,0 };
		if (m_owner->m_engine->GetSystem<nc::InputSystem>()->GetButtonState(SDL_SCANCODE_UP) == nc::InputSystem::eButtonState::HELD)
		{
			force = nc::Vector2::forward * 1000.0f;
		}
		force = nc::Vector2::Rotate(force, nc::DegreesToRadians(m_owner->m_transform.angle));

		PhysicComponent* component = m_owner->GetComponent<PhysicComponent>();
		if (component)
		{
			component->SetForce(force);
		}
	}

}
