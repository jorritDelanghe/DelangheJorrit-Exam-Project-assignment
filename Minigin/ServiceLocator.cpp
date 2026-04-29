#include "ServiceLocator.h"

std::unique_ptr<dae::SoundService> dae::ServiceLocator::m_soundSystem = std::make_unique<dae::NullSoundService>();