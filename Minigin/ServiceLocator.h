#pragma once
#include "SoundService.h"
#include <memory>

namespace dae
{
    class ServiceLocator final
    {
    public:
        static SoundService& GetSoundSystem() { return *m_soundSystem; }

        static void RegisterSounSystem(std::unique_ptr<SoundService> soundSystem)
        {
            if (soundSystem)
                m_soundSystem = std::move(soundSystem);
            else
                m_soundSystem = std::make_unique<NullSoundService>();
        }

    private:
        static std::unique_ptr<SoundService> m_soundSystem;
    };
}