#pragma once
#include "GameObject.h"
namespace dae
{
	class Command
	{
	public:
		explicit Command() = default;
		virtual~Command() noexcept = default;
		virtual void Execute() = 0;

		Command(const Command& other) = delete;
		Command(Command&& other) = delete;
		Command& operator=(const Command& other) = delete;
		Command& operator=(Command&& other) = delete;
	};
}