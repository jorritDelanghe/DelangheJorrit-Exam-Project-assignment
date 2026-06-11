#include "MuteSoundCommand.h"
#include "ServiceLocator.h"

void dae::MuteSoundCommand::Execute()
{
	auto& soundSystem = ServiceLocator::GetSoundSystem();
	soundSystem.MuteSounds(!soundSystem.GetMuteStatusSound());
}
