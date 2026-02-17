#pragma once
#include <string>
#include <functional>
#include <filesystem>
#include <chrono>

namespace dae
{
	using clock = std::chrono::steady_clock; //steady clock ensures that the tick rate is constant, not affected by system time changes

	class Minigin final
	{
	public:
		explicit Minigin(const std::filesystem::path& dataPath);
		~Minigin();
		void Run(const std::function<void()>& load);
		void RunOneFrame();

		Minigin(const Minigin& other) = delete;
		Minigin(Minigin&& other) = delete;
		Minigin& operator=(const Minigin& other) = delete;
		Minigin& operator=(Minigin&& other) = delete;

	private:
		bool m_quit{};

		//time gameloop
		std::chrono::time_point<clock>m_PreviousTime{};
		float m_Lag{};
		static constexpr float MS_PER_UPDATE{ 16.67f }; //60 updates per second, 1000ms/60 = 16.67ms per update 


	};
}