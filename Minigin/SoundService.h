#pragma once
#include <string>

//interface
namespace dae
{
	using SoundID = unsigned short; //never more  then 65,535 sounds
	class SoundService
	{
	public:
		SoundService() = default; 
		virtual ~SoundService() = default;

		virtual void Play(SoundID soundID, float volume) = 0;
		virtual void Stop(SoundID sounID) = 0;
		virtual SoundID AddSound(const std::string& soundPathName) = 0;

	};

	//loactor can never be a nullptr 
	class NullSoundService final : public SoundService
	{
	public:
		virtual void Play(SoundID , float ) override {}
		virtual void Stop(SoundID ) override {}
		virtual SoundID AddSound(const std::string& ) override {return 0;}
	};

}