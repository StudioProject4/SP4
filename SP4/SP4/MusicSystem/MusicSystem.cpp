#include "MusicSystem.h"

#include <assert.h>
//#define NDEBUG 

CMusicSystem* CMusicSystem::instance = 0;

CMusicSystem::CMusicSystem(void)
	:engine(0)
	,currentBgmTrack(0)
	,currentSoundTrack(0)
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
CAudio* CMusicSystem::FetchSound()
{
	CAudio* a_audio = 0;
	if(!soundPool.empty())
	{
		TAudioList::iterator it;
		for(it = soundPool.begin(); it != soundPool.end();++it)
		{
			if((*it)->CheckIsFinished() == true)
			{
				if((*it)->CheckValidAudioPtr())
				{
					(*it)->Drop();
				}
				a_audio = (*it);
				break;
			}
		}
	}
	if(a_audio == 0)
	{
		a_audio = new CAudio();
		soundPool.push_back(a_audio);
	}
	
	return a_audio;
}

CAudio* CMusicSystem::FindSound(std::string name)
{

	CAudio* result = (*soundList.find(name)).second;
	
	//assert(result && "Sound Object not Found");

	return result;
}

CAudio* CMusicSystem::FindBgm(std::string name)
{
	CAudio* result = (*bgmList.find(name)).second;
	//assert(result && "BGM Object not Found");
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
			a_audio->SetId(bgmTrackList.size()-1);
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
			a_audio->SetId(soundTrackList.size()-1);
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
		newAudio->SetDimension(2);
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
		newAudio->SetDimension(2);
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
		newAudio->SetDimension(3);
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
		newAudio->SetDimension(3);
		newAudio->SetIsPaused();
		if(newAudio->CheckValidAudioPtr())
		{
			RegisterSound(newAudio,newAudio->GetAudioName());
			return true;
		}
		
	}
	return false;
}


bool CMusicSystem::PlayBgmTrack(std::string trackname,bool setLoop)
{
	if(engine)
	{
		CAudio* a_audio = FindBgm(trackname);
		
		if(a_audio)
		{
			a_audio->active = true;
			a_audio->SetIsLooped(setLoop);
			this->currentBgmTrack = a_audio->GetId();
			a_audio->ResetPlayPosition();
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

bool CMusicSystem::PlayBgmTrack(unsigned short trackindex,bool setLoop)
{
	if(trackindex <bgmTrackList.size())
	{
		if(engine)
		{		
			return PlayBgmTrack(bgmTrackList[trackindex],setLoop);	
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

bool CMusicSystem::EnableBgmTrackSoundEffect(std::string trackname)
{
	if(engine)
	{
		CAudio* a_audio = FindBgm(trackname);
		if(a_audio)
		{
			return a_audio->EnableAudioEffectControl();
		}
	}
	return false;
}

bool CMusicSystem::EnableBgmTrackSoundEffect(unsigned short trackindex)
{
	if(trackindex <bgmTrackList.size())
	{
		if(engine)
		{
			return EnableBgmTrackSoundEffect(bgmTrackList[trackindex]);		
		}
	}
	return false;
}

bool CMusicSystem::SetBgmTrackPlayPosition(std::string trackname,int millSecPosition)
{
	if(engine)
	{
		CAudio* a_audio = FindBgm(trackname);
		if(a_audio)
		{
			return a_audio->SetPlayPosition(millSecPosition);
		}
	}
	return false;
}

bool CMusicSystem::SetBgmTrackPlayPosition(unsigned short trackindex,int millSecPosition)
{
	if(trackindex <bgmTrackList.size())
	{
		if(engine)
		{
			return SetBgmTrackPlayPosition(bgmTrackList[trackindex],millSecPosition);		
		}
	}
	return false;
}

bool CMusicSystem::ResetBgmTrackPlayPosition(std::string trackname)
{
	if(engine)
	{
		CAudio* a_audio = FindBgm(trackname);
		if(a_audio)
		{
			return a_audio->ResetPlayPosition();
		}
	}
	return false;
}

bool CMusicSystem::ResetBgmTrackPlayPosition(unsigned short trackindex)
{
	if(trackindex <bgmTrackList.size())
	{
		if(engine)
		{
			return ResetBgmTrackPlayPosition(bgmTrackList[trackindex]);		
		}
	}
	return false;
}

bool CMusicSystem::PlaySoundTrack(unsigned short trackindex,bool setLoop)
{
	if(trackindex <soundTrackList.size())
	{
		if(engine)
		{
			return PlaySoundTrack(soundTrackList[trackindex],setLoop);

		}
	}
	return false;
}

bool CMusicSystem::PlaySoundTrack(std::string trackname,bool setLoop)
{
	if(engine)
	{
		CAudio* a_audio = FindSound(trackname);
		if(a_audio)
		{
			a_audio->active = true;
			a_audio->SetIsLooped(setLoop);
			this->currentSoundTrack = a_audio->GetId();
			a_audio->ResetPlayPosition();
			return a_audio->SetIsPaused(false);	
		}
	}
	return false;
}
bool CMusicSystem::PlaySoundPoolTrack2D(std::string trackname,bool setLoop,bool audioEffect)
{
	
	CAudio* a_audio = FetchSound();
	if(a_audio)
	{
		CAudio* sample_audio = FindSound(trackname);
		if(sample_audio)
		{
			(*a_audio) = (*sample_audio); 

			if(a_audio->GetDimension() == 2)
			{
				a_audio->Init(this->CreateSampleAudio2D(a_audio->GetFileName().c_str(),setLoop,audioEffect),a_audio->GetFileName().c_str(),a_audio->GetAudioName());
			}
			
			a_audio->ResetPlayPosition();
			a_audio->SetIsPaused(false);
			a_audio->active = true;

			return true;
		}
	}
	return false;
}

bool CMusicSystem::PlaySoundPoolTrack3D(std::string trackname,irrklang::vec3df pos,bool setLoop,bool audioEffect)
{
	CAudio* a_audio = FetchSound();
	//a_audio->PrintDebugInformation();
	if(a_audio)
	{
		CAudio* sample_audio = FindSound(trackname);
		if(sample_audio)
		{
			(*a_audio) = (*sample_audio); 

			a_audio->Init(this->CreateSampleAudio3D(a_audio->GetFileName().c_str(),pos,setLoop,audioEffect),a_audio->GetFileName().c_str(),a_audio->GetAudioName());
			a_audio->ResetPlayPosition();
			a_audio->SetIsPaused(false);
			a_audio->active = true;
			//a_audio->PrintDebugInformation();
			return true;
		}
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
bool CMusicSystem::EnableSoundTrackSoundEffect(std::string trackname)
{
	if(engine)
	{
		CAudio* a_audio = FindSound(trackname);
		if(a_audio)
		{
			return a_audio->EnableAudioEffectControl();
		}
	}
	return false;
}

bool CMusicSystem::EnableSoundTrackSoundEffect(unsigned short trackindex)
{
	if(trackindex <soundTrackList.size())
	{
		if(engine)
		{
			return EnableSoundTrackSoundEffect(soundTrackList[trackindex]);	
		}
	}
	return false;
}

bool CMusicSystem::SetSoundTrackPlayPosition(std::string trackname,int millSecPosition)
{
	if(engine)
	{
		CAudio* a_audio = FindSound(trackname);
		if(a_audio)
		{
			return a_audio->SetPlayPosition(millSecPosition);
		}
	}
	return false;
}

bool CMusicSystem::SetSoundTrackPlayPosition(unsigned short trackindex,int millSecPosition)
{
	if(trackindex <soundTrackList.size())
	{
		if(engine)
		{
			return SetSoundTrackPlayPosition(soundTrackList[trackindex],millSecPosition);	
		}
	}
	return false;
}

bool CMusicSystem::ResetSoundTrackPlayPosition(std::string trackname)
{
	if(engine)
	{
		CAudio* a_audio = FindSound(trackname);
		if(a_audio)
		{
			return a_audio->ResetPlayPosition();
		}
	}
	return false;
}

bool CMusicSystem::ResetSoundTrackPlayPosition(unsigned short trackindex)
{
	if(trackindex <soundTrackList.size())
	{
		if(engine)
		{
			return ResetSoundTrackPlayPosition(soundTrackList[trackindex]);	
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
		TAudioMap::iterator it;

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
		TAudioMap::iterator it;

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

		TAudioMap::iterator it;

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
//bool CMusicSystem::SwitchBgmTrack(std::string audioname)
//{
//	if(engine)
//	{
//		return true;
//	}
//	return false;
//}
//
//bool CMusicSystem::SwitchBgmTrack(unsigned short trackindex)
//{
//	if(engine)
//	{
//		return true;
//	}
//	return false;
//}

bool CMusicSystem::TranverseBgmTrack(bool forward,bool warp)
{
	if(engine)
	{
		if(forward)
		{
			ResetBgmTrackPlayPosition((unsigned short)currentBgmTrack);
			PauseBgmTrack(currentBgmTrack);
			++currentBgmTrack;

			if(warp)
			{
				if((unsigned short)currentBgmTrack>=bgmTrackList.size())
				{
					currentBgmTrack = 0;
				}
			}
			//std::cout<<"bgm size"<<bgmTrackList.size()<<std::endl;
			//std::cout<<"Current Bgm Track"<<currentBgmTrack<<std::endl;
			PlayBgmTrack(currentBgmTrack);
		}else
		{
			ResetBgmTrackPlayPosition(currentBgmTrack);
			PauseBgmTrack(currentBgmTrack);
			--currentBgmTrack;
			if(warp)
			{
				if(currentBgmTrack<0)
				{
					currentBgmTrack = bgmTrackList.size()-1;
				}
			}
			//std::cout<<"bgm size"<<bgmTrackList.size()<<std::endl;
			//std::cout<<"Current Bgm Track"<<currentBgmTrack<<std::endl;
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
			//PauseSoundTrack(currentSoundTrack);
			//std::cout<<"Current sound Track before"<<currentSoundTrack<<std::endl;
			++currentSoundTrack;
			//std::cout<<"Current sound Track after"<<currentSoundTrack<<std::endl;
			if(warp)
			{
				//std::cout<<"Current sound Track warping"<<currentSoundTrack<<std::endl;
				if((unsigned short)currentSoundTrack>=soundTrackList.size())
				{
					//std::cout<<"Setting current sound index to 0"<<std::endl;
					currentSoundTrack = 0;
				}
			}
			//std::cout<<"Current sound Track "<<currentSoundTrack<<std::endl;
			PlaySoundTrack(currentSoundTrack);
		}else
		{
			//PauseSoundTrack(currentSoundTrack);
			--currentSoundTrack;
			if(warp)
			{
				if(currentSoundTrack<0)
				{
					currentSoundTrack = soundTrackList.size()-1;
				}
			}
			//std::cout<<"Current sound Track"<<currentSoundTrack<<std::endl;
			PlaySoundTrack(currentSoundTrack);
		}
		return true;
	}
	return false;
}
bool CMusicSystem::StopCurrentBGM()
{
	if(engine)
	{
		this->PauseBgmTrack(currentBgmTrack);
		this->ResetBgmTrackPlayPosition(currentBgmTrack);
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
		//std::cout<<"cleaning"<<std::endl;
		engine->stopAllSounds();

		TAudioMap::iterator it;
		TAudioList::iterator it2;

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
		for(it2 = soundPool.begin(); it2!= soundPool.end();++it2)
		{
			(*it2)->CleanUp();
			(*it2) = 0;
		}
		soundPool.clear();
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
		//std::cout<<"releasing"<<std::endl;
		engine->drop();
		engine = nullptr;
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
			engine = nullptr;
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

short CMusicSystem::GetCurrentBgmTrackIndex()
{
	return this->currentBgmTrack;
};

short CMusicSystem::GetCurrentSoundTrackIndex()
{
	return this->currentSoundTrack;
}

void CMusicSystem::PrintCurrentBgmTrack()
{
	//std::cout<<currentBgmTrack<<std::endl;
	//std::cout<<bgmTrackList.size()<<std::endl;
	std::cout<<std::endl;
	if((unsigned short)currentBgmTrack >=0 && (unsigned short)currentBgmTrack<bgmTrackList.size())
	{
		CAudio *a_audio = FindBgm(bgmTrackList[currentBgmTrack]);
		if(a_audio)
		{
			a_audio->PrintDebugPointer();
			a_audio->PrintDebugId();
			a_audio->PrintDebugAudioName();
			a_audio->PrintDebugFileName();
			a_audio->PrintDebugPlayPosition();
			a_audio->PrintDebugPosition();
		}else
		{
			std::cout<<"<ERROR> No Bgm Found"<<std::endl;
		}
	}else
	{
		std::cout<<"<ERROR> Bgm Index out of bound "<<std::endl;
	}
}
	
CAudio* CMusicSystem::GetCurrentBgm()
{
	return FindBgm(bgmTrackList[currentBgmTrack]);
}

CAudio* CMusicSystem::GetCurrentSound()
{
	return FindSound(soundTrackList[currentSoundTrack]);
}

void CMusicSystem::PrintCurrentSoundTrack()
{
	//std::cout<<currentBgmTrack<<std::endl;
	//std::cout<<bgmTrackList.size()<<std::endl;
	std::cout<<std::endl;
	if((unsigned short)currentSoundTrack >=0 && (unsigned short)currentSoundTrack<soundTrackList.size())
	{
		CAudio *a_audio = FindSound(soundTrackList[(unsigned short)currentSoundTrack]);
		if(a_audio)
		{
			a_audio->PrintDebugPointer();
			a_audio->PrintDebugId();
			a_audio->PrintDebugAudioName();
			a_audio->PrintDebugFileName();
			a_audio->PrintDebugPlayPosition();
			a_audio->PrintDebugPosition();
		}else
		{
			std::cout<<"<ERROR> No Sound Found"<<std::endl;
		}
	}else
	{
		std::cout<<"<ERROR> Sound Index out of bound "<<std::endl;
	}
}

void CMusicSystem::PrintDebugInformation()
{
	this->PrintBgmListSize();
	this->PrintSoundListSize();
	this->PrintBgmTrackList();
	this->PrintSoundTrackList();
}

void CMusicSystem::PrintSoundListSize()
{
	std::cout<<std::endl;
	std::cout<<"Sound Track List Size: "<<soundList.size()<<std::endl;
}

void CMusicSystem::PrintBgmListSize()
{
	std::cout<<std::endl;
	std::cout<<"Bgm Track List Size: "<<bgmList.size()<<std::endl;
}

void CMusicSystem::PrintBgmTrackList()
{
	//TAudioTrackList::iterator it;

	//for(it = bgmTrackList.begin();it!=bgmTrackList.end();++it)
	//{
	//	std::cout<<it - bgmTrackList.begin()<<(*it)<<std::endl;
	//}
	std::cout<<std::endl;
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
	std::cout<<std::endl;
	for(unsigned short i = 0 ; i<soundTrackList.size();++i)
	{
		std::cout<<"< "<<i<<" > "<<soundTrackList[i]<<std::endl;
	}
}

void CMusicSystem::PrintSoundPoolList()
{
	std::cout<<std::endl;
	for(unsigned short i = 0 ; i<soundPool.size();++i)
	{
		std::cout<<"< "<<i<<" > "; soundPool[i]->PrintDebugInformation();
	}
}

void CMusicSystem::PrintSoundPoolListSize()
{
	std::cout<<std::endl;
	std::cout<<"Sound Pool List Size: "<<soundPool.size()<<std::endl;
}