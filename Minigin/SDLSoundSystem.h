#pragma once
#include "SoundService.h"
#include <memory>

namespace dae
{
	class SDLSoundSystem final : public SoundService
	{
	public:
		explicit SDLSoundSystem();
		virtual ~SDLSoundSystem()  override;

		SDLSoundSystem(const SDLSoundSystem& other) = delete;
		SDLSoundSystem(SDLSoundSystem&& other) = delete;
		SDLSoundSystem& operator=(const SDLSoundSystem& other) = delete;
		SDLSoundSystem& operator=(SDLSoundSystem&& other) = delete;

		virtual void Play(SoundID soundID, float volume) override;
		virtual void Stop(SoundID soundID) override;
		virtual SoundID AddSound(const std::string& soundName) override;
	
		virtual void MuteSounds(bool isSoundMuted) override;
		virtual bool GetMuteStatusSound() const override;
	private:
		class SDLSoundSystemImpl;
		std::unique_ptr<SDLSoundSystemImpl> m_pSDLSoundSystemImpl;
		bool m_isSoundMuted{ false };
	};
}