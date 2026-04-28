#pragma once


//interface
namespace dae
{
	class SoundService
	{
	public:
		SoundService();
		virtual ~SoundService();

		SoundService(const SoundService& other) =delete;
		SoundService( SoundService&& other) =delete;
		SoundService& operator=(const SoundService& other) =delete;
		SoundService& operator=(SoundService&& other) =delete;

		virtual void Play();
		virtual void Stop();
		virtual void Pause();

	};

}