#pragma once
#include "Engine.h"
#include "Object.h"
#include "Math/Transform.h"

namespace nc
{
	class Component;

	class GameObject :public Object
	{
	public:
		GameObject() = default;
		GameObject(const GameObject& other);

		virtual void Create(void* data = nullptr) override;
		virtual void Destroy() override;
		virtual Object* Clone() const override { return new GameObject{ *this }; };

		void Read(const rapidjson::Value& value) override;

		void Update();
		void Draw();

		void BeginContact(GameObject* other);
		void EndContact(GameObject* other);

		template<typename T>
		T* GetComponent();

		void AddComponent(Component* component);
		void RemoveComponent(Component* component);
		void RemoveAllComponents();

		void ReadComponents(const rapidjson::Value& value);

	public:
		Transform m_transform;
		Engine* m_engine{ nullptr };
		std::string m_name;

	protected:
		std::vector<Component*> m_components;
	};

	template<typename T>
	T* GameObject::GetComponent()
	{
		T* result{ nullptr };

		for (auto component : m_components)
		{
			result = dynamic_cast<T*>(component);
			if (result) break;
		}

		return result;
	}
}
