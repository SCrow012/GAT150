#include "pch.h"
#include "ObjectFactory.h"
#include "Components/PhysicsComponent.h"
#include "Components/SpriteComponent.h"
#include "Components/SpriteAnimationComponent.h"

namespace nc
{
	void ObjectFactoryImpl::Initialize()
	{
		nc::ObjectFactory::Instance().Register("GameObject", new Creator<GameObject, Object> );
		nc::ObjectFactory::Instance().Register("PhysicsComponent", new Creator<PhysicComponent, Object>);
		nc::ObjectFactory::Instance().Register("SpriteComponent", new Creator<SpriteComponent, Object>);
		nc::ObjectFactory::Instance().Register("SpriteAnimationComponent", new Creator<SpriteAnimationComponent, Object>);
	}
}

