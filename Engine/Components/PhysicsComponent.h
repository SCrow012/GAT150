#pragma once
#include "Component.h"
#include "Math/Vector2.h"

namespace nc
{
	class PhysicComponent : public Component
	{
	public:
		virtual void Create(void* data = nullptr) override;
		virtual void Destroy() override;

		virtual void Update() override;

	protected:
		Vector2 m_velocity;
		Vector2 m_force;
		float m_drag{ 1.0f };
	};
}