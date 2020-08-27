#pragma once
#include "Engine.h"
#include "Object.h"
#include "Math/Transform.h"
#include <bitset>

namespace nc
{
	class Component;

	class GameObject :public Object
	{
	public:
		enum eFlags
		{
			ACTIVE,
			VISIBLE,
			DESTROY,
			TRANSIENT
		};

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
		std::vector<GameObject*> GetContactsWithTag(const std::string& tag);

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
		std::string m_tag;
		std::bitset<32> m_flags;

	protected:
		std::vector<Component*> m_components;
		std::list<GameObject*> m_contacts;
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
