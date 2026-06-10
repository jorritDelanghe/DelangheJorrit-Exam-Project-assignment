#pragma once

#include "Command.h"

namespace dae
{
	class MuteSoundCommand final : public Command
	{
	public:
		MuteSoundCommand() =default;
		virtual ~MuteSoundCommand() noexcept override = default;

		MuteSoundCommand(const MuteSoundCommand& other) = delete;
		MuteSoundCommand(MuteSoundCommand&& other) = delete;
		MuteSoundCommand& operator= (const MuteSoundCommand& other) = delete;
		MuteSoundCommand& operator= (MuteSoundCommand&& other) = delete;

		virtual void Execute() override;
	};

}