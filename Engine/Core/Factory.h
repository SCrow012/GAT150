#pragma once
#include <map>
#include <functional>

namespace nc
{
	template<typename TBase, typename TKey>
	class Factory
	{
	public:
		using function_t = std::function<TBase* ()>;

	public:
		template<typename T = TBase>
		T* Create(TKey key);
		void Register(TKey key, function_t function);

	protected:
		std::map<TKey, function_t> m_regristry;
	};

	template<typename TBase, typename TKey>
	template<typename T>
	inline T* Factory<TBase, TKey>::Create(TKey key)
	{
		T* object{ nullptr };

		auto iter = m_regristry.find(key);
		if (iter != m_regristry.end())
		{
			object = dynamic_cast<T*>(iter->second());
		}

		return object;
	}

	template<typename TBase, typename TKey>
	inline void Factory<TBase, TKey>::Register(TKey key, function_t function)
	{
		m_regristry[key] = function;
	}
}
