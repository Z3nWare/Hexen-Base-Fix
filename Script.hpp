#pragma once
#include <chrono>
#include <optional> 
#include <Windows.h>

class Script {
public:
	using Helper = void(*)();
public:
	explicit Script(Helper func, std::optional<std::size_t> StackSize = std::nullopt) : m_Function(func), m_ScriptFiber(nullptr), m_MainFiber(nullptr)
	{
		m_ScriptFiber = CreateFiber(StackSize.has_value() ? StackSize.value() : 0, [](void* param) {
			auto CurrentScript = static_cast<Script*>(param);
			CurrentScript->FiberFunc();
			}, this);
	}
	~Script()
	{
		if (m_ScriptFiber) DeleteFiber(m_ScriptFiber);
	}

	void Tick()
	{
		m_MainFiber = GetCurrentFiber();
		if (!m_WakeTime.has_value() || m_WakeTime.value() <= std::chrono::high_resolution_clock::now()) {
			SwitchToFiber(m_ScriptFiber);
		}
	}

	void ScriptYield(std::optional<std::chrono::high_resolution_clock::duration> Time = std::nullopt)
	{
		if (Time.has_value()) {
			m_WakeTime = std::chrono::high_resolution_clock::now() + Time.value();
		}
		else {
			m_WakeTime = std::nullopt;
		}
		SwitchToFiber(m_MainFiber);
	}

	static Script* GetCurrent()
	{
		return static_cast<Script*>(GetFiberData());
	}
private:
	void FiberFunc()
	{
		try {
			m_Function();
		}
		catch (...) {}
		[]() {
		}();
		while (true) {
			ScriptYield();
		}
	}
private:
	void* m_ScriptFiber;
	void* m_MainFiber;
	Helper m_Function;
	std::optional<std::chrono::high_resolution_clock::time_point> m_WakeTime;
};