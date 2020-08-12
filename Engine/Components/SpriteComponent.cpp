#include "pch.h"
#include "SpriteComponent.h"
#include "Graphics/Texture.h"

void nc::SpriteComponent::Create(void* data)
{
	m_texture = m_owner->m_engine->GetSystem<nc::ResourceManager>()->Get<nc::Texture>("cars.png", m_owner->m_engine->GetSystem<nc::Renderer>());
}

void nc::SpriteComponent::Destroy()
{
}

void nc::SpriteComponent::Update()
{
}

void nc::SpriteComponent::Draw()
{
	m_texture->Draw({ 0, 16, 64, 144 }, m_owner->m_transform.position, { 1, 1 }, m_owner->m_transform.angle);
}
