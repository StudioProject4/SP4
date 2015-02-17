#include "MusicSystem.h"

#include <assert.h>
//#define NDEBUG 

CMusicSystem* CMusicSystem::instance = 0;

CMusicSystem::CMusicSystem(void)
	:engine(0)
	,allSoundPaused(false)
	,allSoundMuted(false)
{
	Init();
}

CMusicSystem::~CMusicSystem(void)
{
}

CMusicSystem* CMusicSystem::GetInstance()
{
	if(instance == 0)
	{
		instance = new CMusicSystem();
	}

	return instance;
}

CAudio* CMusicSystem::FindSound(std::string name)
{

	CAudio* result = (*soundList.find(name)).second;

	assert(result && "Sound Object not Found");

	return result;
}

CAudio* CMusicSystem::FindBgm(std::string name)
{
	CAudio* result = (*bgmList.find(name)).second;
	assert(result && "BGM Object not Found");
	return result;
}

bool CMusicSystem::RegisterBgm(CAudio * a_audio, std::string nametoberegister)
{
	if(a_audio)
	{
		if(engine)
		{
			
			if(nametoberegister != "nil")
			{
				
				bgmList.insert (std::make_pair(nametoberegister,a_audio));
			}else
			{
				bgmList.insert (std::make_pair(a_audio->GetAudioName(),a_audio));
			}
			bgmTrackList.push_back(a_audio->GetAudioName());
		
			return true;
		}
	}
	return false;
}

bool CMusicSystem::RegisterSound(CAudio * a_audio, std::string nametoberegister)
{
	if(a_audio)
	{
		if(engine)
		{
			if(nametoberegister != "nil")
			{
				soundList.insert (std::make_pair(nametoberegister,a_audio));
			}else
			{
				soundList.insert (std::make_pair(a_audio->GetAudioName(),a_audio));
			}

			soundTrackList.push_back(a_audio->GetAudioName());
			return true;
		}
	}
	return false;
}

bool CMusicSystem::RegisterBgm2D(std::string filename,std::string nametoberegister , bool withLoop,bool withSoundEffectControl )
{
	if(engine)
	{
		CAudio* newAudio = new CAudio();
		newAudio->Init(this->CreateSampleAudio2D(filename.c_str(),withLoop,withSoundEffectControl),filename.c_str(),nametoberegister);	
		newAudio->SetIsPaused();
		if(newAudio->CheckValidAudioPtr())
		{
			RegisterBgm(newAudio,newAudio->GetAudioName());
			return true;
		}
		
	}
	return false;
}

bool CMusicSystem::RegisterSound2D(std::string filename, std::string nametoberegister, bool withLoop,bool withSoundEffectControl)
{
	if(engine)
	{
		CAudio* newAudio = new CAudio();

		newAudio->Init(this->CreateSampleAudio2D(filename.c_str(),withLoop,withSoundEffectControl),filename.c_str(),nametoberegister);	
		newAudio->SetIsPaused();
		if(newAudio->CheckValidAudioPtr())
		{
			RegisterSound(newAudio,newAudio->GetAudioName());
			return true;
		}
		
	}
	return false;
}

bool CMusicSystem::RegisterBgm3D(std::string filename,std::string nametoberegister,irrklang::vec3df pos, bool withLoop,bool withSoundEffectControl )
{
	if(engine)
	{
		CAudio* newAudio = new CAudio();
		newAudio->Init(this->CreateSampleAudio3D(filename.c_str(),pos,withLoop,withSoundEffectControl),filename.c_str(),nametoberegister);	

		newAudio->SetIsPaused();
		if(newAudio->CheckValidAudioPtr())
		{
			RegisterBgm(newAudio,newAudio->GetAudioName());
			return true;
		}
		
	}
	return false;
}

bool CMusicSystem::RegisterSound3D(std::string filename, std::string nametoberegister,irrklang::vec3df pos, bool withLoop,bool withSoundEffectControl )
{
	if(engine)
	{
		CAudio* newAudio = new CAudio();
		newAudio->Init(this->CreateSampleAudio3D(filename.c_str(),pos,withLoop,withSoundEffectControl),filename.c_str(),nametoberegister);	
		newAudio->SetIsPaused();
		if(newAudio->CheckValidAudioPtr())
		{
			RegisterSound(newAudio,newAudio->GetAudioName());
			return true;
		}
		
	}
	return false;
}


bool CMusicSystem::PlayBgmTrack(std::string trackname)
{
	if(engine)
	{
		CAudio* a_audio = FindBgm(trackname);
		if(a_audio)
		{
			a_audio->active = true;
			return a_audio->SetIsPaused(false);
		}
		
	}
	return false;
}
bool CMusicSystem::PauseBgmTrack(std::string trackname,bool pause)
{
	if(engine)
	{
		CAudio* a_audio = FindBgm(trackname);
		if(a_audio)
		{
			return a_audio->SetIsPaused(pause);	
		}
	}
	return false;
}

bool CMusicSystem::PlayBgmTrack(unsigned short trackindex)
{
	if(trackindex <bgmTrackList.size())
	{
		if(engine)
		{		
			if(PlayBgmTrack(bgmTrackList[trackindex]))	
			{
				this->currentBgmTrack = trackindex;
			}
		}
	}
	return false;
}
bool CMusicSystem::PauseBgmTrack(unsigned short trackindex,bool pause)
{
	if(trackindex <bgmTrackList.size())
	{
		if(engine)
		{
			return PauseBgmTrack(bgmTrackList[trackindex],pause);		
		}
	}
	return false;
}



bool CMusicSystem::PlaySoundTrack(unsigned short trackindex)
{
	if(trackindex <soundTrackList.size())
	{
		if(engine)
		{
			if(PlaySoundTrack(bgmTrackList[trackindex]))
			{
				this->currentSoundTrack = trackindex;
			}
		}
	}
	return false;
}

bool CMusicSystem::PlaySoundTrack(std::string trackname)
{
	if(engine)
	{
		CAudio* a_audio = FindSound(trackname);
		if(a_audio)
		{
			a_audio->active = true;
			return a_audio->SetIsPaused(false);	
		}
		return true;
	}
	return false;
}
bool CMusicSystem::PauseSoundTrack(std::string trackname,bool pause)
{
	if(engine)
	{
		CAudio* a_audio = FindSound(trackname);
		if(a_audio)
		{
			return a_audio->SetIsPaused(pause);
		}
	}
	return false;
}
bool CMusicSystem::PauseSoundTrack(unsigned short trackindex,bool pause)
{
	if(trackindex <soundTrackList.size())
	{
		if(engine)
		{
			return PauseSoundTrack(soundTrackList[trackindex],pause);	
		}
	}
	return false;
}

bool CMusicSystem::SetAllAudioVolume(float volume)
{
	if(engine)
	{
		if(volume <0)
		{
			volume = 0.f;
		}else
		{
			while(volume >1)
			{
				volume *= 0.1f;
			}
		}
		engine->setSoundVolume(volume);
		return true;
	}
	return false;
}
bool CMusicSystem::UnMute()
{
	if(allSoundMuted)//if there are sound to unmute then bother to go in.
	{
		if(engine)
		{
			engine->setSoundVolume(1.f);
			allSoundMuted = false;
			return true;
		}
	}
	return false;
}
bool CMusicSystem::Mute()
{
	if(!allSoundMuted)//if there are sound to mute then bother to go in.
	{
		if(engine)
		{
			engine->setSoundVolume(0.f);
			allSoundMuted = true;
			return true;
		}
	}
	return false;
}

bool CMusicSystem::ToggleMute()
{
	if(engine)
	{
		allSoundMuted = !allSoundMuted;
		if(allSoundMuted)
		{
			engine->setSoundVolume(0.f);
		}else
		{
			engine->setSoundVolume(1.f);
		}
		return true;
	}
	return false;
}

bool CMusicSystem::TogglePause()
{
	if(engine)
	{
		//allSoundPaused = !allSoundPaused;
		TAudioList::iterator it;

		for(it = bgmList.begin();it!= bgmList.end();++it)
		{
			if((*it).second->active)
			{
				PauseBgmTrack((*it).second->GetAudioName(),!(*it).second->CheckIsPaused());
			}
		}
		for(it = soundList.begin();it!= soundList.end();++it)
		{
			if((*it).second->active)
			{
				PauseSoundTrack((*it).second->GetAudioName(),!(*it).second->CheckIsPaused());
			}
		}
		//engine->setAllSoundsPaused(allSoundPaused);
		return true;
	}
	return false;
}

bool CMusicSystem::Resume()
{
	if(engine)
	{
		//allSoundPaused = false;
		//engine->setAllSoundsPaused(false);
		TAudioList::iterator it;

		for(it = bgmList.begin();it!= bgmList.end();++it)
		{
			if((*it).second->active &&(*it).second->CheckIsPaused())
			{
				PauseBgmTrack((*it).second->GetAudioName(),false);
			}
		}
		for(it = soundList.begin();it!= soundList.end();++it)
		{
			if((*it).second->active &&(*it).second->CheckIsPaused())
			{
				PauseSoundTrack((*it).second->GetAudioName(),false);
			}
		}
		return true;
	}
	return false;
}

bool CMusicSystem::Pause()
{
	if(engine)
	{
		//allSoundPaused = true;

		TAudioList::iterator it;

		for(it = bgmList.begin();it!= bgmList.end();++it)
		{
			if((*it).second->active && !(*it).second->CheckIsPaused())
			{
				PauseBgmTrack((*it).second->GetAudioName(),true);
			}
		}
		for(it = soundList.begin();it!= soundList.end();++it)
		{
			if((*it).second->active && !(*it).second->CheckIsPaused())
			{
				PauseSoundTrack((*it).second->GetAudioName(),true);
			}
		}
		//engine->setAllSoundsPaused(true);

		return true;
	}
	return false;
}

bool CMusicSystem::StopAllSounds()
{
	if(engine)
	{
		engine->stopAllSounds();
		return true;
	}
	return false;
}

bool CMusicSystem::TranverseBGMTrack(bool forward,bool warp)
{
	if(engine)
	{
		if(forward)
		{
			PauseBgmTrack(currentBgmTrack);
			++currentBgmTrack;

			if(warp)
			{
				if(currentBgmTrack>bgmTrackList.size())
				{
					currentBgmTrack = 0;
				}
			}
			
			PlayBgmTrack(currentBgmTrack);
		}else
		{
			PauseBgmTrack(currentBgmTrack);
			--currentBgmTrack;
			if(warp)
			{
				if(currentBgmTrack<0)
				{
					currentBgmTrack = bgmTrackList.size();
				}
			}
			PlayBgmTrack(currentBgmTrack);
		}
		return true;
	}
	return false;
}

bool CMusicSystem::TranverseSoundTrack(bool forward,bool warp)
{
	if(engine)
	{
		if(forward)
		{
			PauseSoundTrack(currentSoundTrack);
			++currentSoundTrack;

			if(warp)
			{
				if(currentSoundTrack>soundTrackList.size())
				{
					currentSoundTrack = 0;
				}
			}
			
			PlaySoundTrack(currentSoundTrack);
		}else
		{
			PauseSoundTrack(currentSoundTrack);
			--currentSoundTrack;
			if(warp)
			{
				if(currentSoundTrack<0)
				{
					currentSoundTrack = soundTrackList.size();
				}
			}
			PlaySoundTrack(currentSoundTrack);
		}
		return true;
	}
	return false;
}

bool CMusicSystem::CheckAudioIsPlaying(std::string audioname)
{
	if(engine)
	{
		return engine->isCurrentlyPlaying(audioname.c_str());
	}
	return false;
}

bool CMusicSystem::CheckAudioIsPlaying(const char* audioname)
{
	if(engine)
	{
		return engine->isCurrentlyPlaying(audioname);
	}
	return false;
}

bool CMusicSystem::Init()
{
	engine = createIrrKlangDevice();

	if(engine)
	{
		return true;
	}

	return false;
}

bool CMusicSystem::CleanUp()
{
	if(engine)
	{
		engine->stopAllSounds();

		TAudioList::iterator it;

		for(it = bgmList.begin(); it!= bgmList.end();++it)
		{
			(*it).second->CleanUp();
			(*it).second = 0;
		
			//bgmList.erase(it);
		}

		for(it = soundList.begin(); it!= soundList.end();++it)
		{
			(*it).second->CleanUp();
			(*it).second = 0;
		
			//soundList.erase(it);
		}

		bgmList.clear();
		soundList.clear();

		//engine->drop();
		//engine = 0;
		return true;
	}
	return false;
}

bool CMusicSystem::Reset()
{
	if(engine)
	{
		if(CleanUp() && Init())
		{
			return true;
		}
	}else
	{
		return Init();
	}
	return false;
}

bool CMusicSystem::Release()
{
	if(engine)
	{
		engine->drop();
		engine = 0;
		delete this;

		return true;
	}
	return false;
}

bool CMusicSystem::Exit()
{
	if(engine)
	{
		if(CleanUp() && Release())
		{
			return true;
		}
	}
	return false;
}

irrklang::ISound* CMusicSystem::CreateSampleAudio2D(const char* filename,bool withLoop,bool withAudioEffect)
{
	if(engine)
	{
		return engine->play2D(filename,withLoop,true,true,ESM_AUTO_DETECT,withAudioEffect);
	}
	return 0;
}

irrklang::ISound* CMusicSystem::CreateSampleAudio3D(const char* filename,irrklang::vec3df pos,bool withLoop,bool withAudioEffect)
{
	if(engine)
	{
		return engine->play3D(filename,pos,withLoop,true,true,ESM_AUTO_DETECT,withAudioEffect);
	}
	return 0;
}

irrklang::ISound* CMusicSystem::CreateIrrklangISound2D(const char* filename,bool playLooped,bool startPauseed,bool track,irrklang::E_STREAM_MODE mode,bool enableSoundEffect)
{
	if(engine)
	{
		return engine->play2D(filename,playLooped,startPauseed,track,mode,enableSoundEffect);	
	}
	return 0;
}
irrklang::ISound* CMusicSystem::CreateIrrklangISound3D(const char* filename,irrklang::vec3df pos,bool playLooped,bool startPauseed ,bool track,irrklang::E_STREAM_MODE mode,bool enableSoundEffect)
{
	if(engine)
	{
		return engine->play3D(filename,pos,playLooped,startPauseed,track,mode,enableSoundEffect);
	}
	return 0;
}
void CMusicSystem::PrintDebugInformation()
{
}

void CMusicSystem::PrintBgmTrackList()
{
	//TAudioTrackList::iterator it;

	//for(it = bgmTrackList.begin();it!=bgmTrackList.end();++it)
	//{
	//	std::cout<<it - bgmTrackList.begin()<<(*it)<<std::endl;
	//}
	for(unsigned short i = 0 ; i<bgmTrackList.size();++i)
	{
		std::cout<<"< "<<i<<" > "<<bgmTrackList[i]<<std::endl;
	}
}

void CMusicSystem::PrintSoundTrackList()
{
	//TAudioTrackList::iterator it;
	//for(it = soundTrackList.begin();it!=soundTrackList.end();++it)
	//{
	//	std::cout<<(*it)<<std::endl;
	//}

	for(unsigned short i = 0 ; i<soundTrackList.size();++i)
	{
		std::cout<<"< "<<i<<" > "<<soundTrackList[i]<<std::endl;
	}
}