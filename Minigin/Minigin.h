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
		std::chrono::time_point<clock>m_previousTime{};
		float m_lag{}; //how far game is behind on real world time
		static constexpr float FIXED_TIME_STEP{ 1.f/60.f}; //60 updates per second


	};
}