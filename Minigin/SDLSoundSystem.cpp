#include "SDLSoundSystem.h"
#include <SDL3_mixer/SDL_mixer.h>
#include <thread>
#include <map>
#include <mutex>
#include <queue>
#include <string>

dae::SDLSoundSystem::~SDLSoundSystem()
{
}

void dae::SDLSoundSystem::Play(SoundID soundID, float volume)
{
}

void dae::SDLSoundSystem::Stop(SoundID soundID)
{
}

//SDLSoundSystemImpl
namespace dae
{
	struct soundRequest
	{
		SoundID soundId;
		float volume;
	};

	class SDLSoundSystem::SDLSoundSystemImpl
	{
	public:
		SDLSoundSystemImpl()
		{
			MIX_Init();
			m_mixer = MIX_CreateMixerDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK,nullptr);
			m_thread = std::jthread(&SDLSoundSystemImpl::ProcessQueue, this);

		}
		~SDLSoundSystemImpl()
		{
			//free all loaded sounds

			MIX_DestroyMixer(m_mixer);
			MIX_Quit();
		}
		void Play(SoundID soundID, float volume)
		{
			{
				std::lock_guard lock (m_mutex); //grab the key
				m_soundQueue.push({ soundID,volume });
			}//mutex here released, release the key
			m_conditionVar.notify_one();
		}
		SoundID AddSound(const std::string& soundName)
		{
			SoundID id = m_currentNumId;
			++m_currentNumId;

			m_nameSoundsMap[id] = soundName;
			return id;
		}
	private:
		
		void ProcessQueue()
		{
			while (m_isRunning)
			{
				std::unique_lock lock(m_mutex); // can lock and unlock

				//release key and let thread sleep unitl notify_one
				m_conditionVar.wait(lock, [this]()
					{
						return !m_soundQueue.empty()
							|| !m_isRunning;
					});

				while (!m_soundQueue.empty())
				{
					soundRequest soundReq{ m_soundQueue.front() };
					m_soundQueue.pop();
					lock.unlock(); //so loading is not blocking main trhead

					//load
					if (m_audiosMap.find(soundReq.soundId) == m_audiosMap.end()) //check audio already loaded
					{
						//precode: false= audio is decoded on the fly while playing, uses less memory
						//true= audio is fully decoded into raw PCM upfront when loading, uses more memory but has lower latency during playback
						m_audiosMap[soundReq.soundId] = MIX_LoadAudio(m_mixer,m_nameSoundsMap[soundReq.soundId].c_str(),false);

						//play the sound
						MIX_Audio* audio = m_audiosMap[soundReq.soundId];

						if (audio)
						{
							MIX_Track* track = MIX_CreateTrack(m_mixer);
							MIX_SetTrackAudio(track, audio);
							MIX_SetTrackGain(track, soundReq.soundId); //set volume
							MIX_PlayTrack(track,0);
						}
						lock.lock(); //lock so the queue can safely be accessed 
					}
				}
			}
		}

		std::jthread m_thread{};
		MIX_Mixer* m_mixer{nullptr};
		SoundID m_currentNumId; //gets higher every time new sound
		std::map<SoundID, std::string> m_nameSoundsMap;
		std::map<SoundID, MIX_Audio*>m_audiosMap;

		bool m_isRunning{ true };
		std::mutex m_mutex{};
		std::queue<soundRequest> m_soundQueue{};
		std::condition_variable m_conditionVar{};

	};
}
