#pragma once
#include "script.hpp"
#include <mutex>

class ScriptManager {
public:
	explicit ScriptManager() = default;
	~ScriptManager() = default;
public:
	void AddScript(std::unique_ptr<Script> script)
	{
		std::lock_guard Lock(m_Mutex);
		m_Scripts.push_back(std::move(script));
	}

	void RemoveAllScripts()
	{
		std::lock_guard Lock(m_Mutex);
		m_Scripts.clear();
	}

	void Tick()
	{
		static bool EnsureMainFiber = (ConvertThreadToFiber(nullptr), true);
		std::lock_guard Lock(m_Mutex);
		for (auto const& Scr : m_Scripts) {
			Scr->Tick();
		}
	}
private:
	std::recursive_mutex m_Mutex;
	std::vector<std::unique_ptr<Script>> m_Scripts;
};