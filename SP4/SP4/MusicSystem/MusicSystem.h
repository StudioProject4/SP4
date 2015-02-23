#pragma once

#include "Audio.h"

#include <map>
//#include <list>
#include <vector>

class CMusicSystem//the main music engine
{
public:
	ISoundEngine* engine;

	typedef std::map<std::string,CAudio*> TAudioList;
	typedef std::vector<std::string> TAudioTrackList;
	TAudioList bgmList; // list of the real bgm audio;
	TAudioList soundList;// list of the real sound audio;
	TAudioTrackList bgmTrackList;//tracking of which current bgm track it is at.
	TAudioTrackList soundTrackList;//tracking of which current bgm track it is at.
	short currentBgmTrack;
	short currentSoundTrack;
	static CMusicSystem* instance;
private:
	bool allSoundPaused;
	bool allSoundMuted;
	//unsigned short unregisteredAudioCount;
private:
	CMusicSystem(void);
	bool Init();
	bool CleanUp();
	bool Release();
	irrklang::ISound* CreateSampleAudio2D(const char* filename,bool withLoop = false ,bool withAudioEffect = true);
	irrklang::ISound* CreateSampleAudio3D(const char* filename,irrklang::vec3df pos = irrklang::vec3df(0.f,0.f,0.f),bool withLoop = false ,bool withAudioEffect = true);
public:
	static CMusicSystem* GetInstance();
	~CMusicSystem(void);

	//Search And Get CAudio obj from soundlist
	CAudio* FindSound(std::string name);

	//Search And Get CAudio obj from Bgm
	CAudio* FindBgm(std::string name);

	//add CAudio class to be managed under bgmlist,if nametoberegister is untouched, passed in audio name will be use to be registerd.
	bool RegisterBgm(CAudio * a_audio, std::string nametoberegister = "nil" );

	//add CAudio class to be managed under soundlist,if nametoberegister is untouched, passed in audio name will be use to be registerd.
	bool RegisterSound(CAudio * a_audio, std::string nametoberegister = "nil");
	
	//Automatically create and add a CAudio class using the music filename inside bgmlist,if nametoberegister is untouched, passed in audio filename will be use to be registerd.
	bool RegisterBgm2D(std::string filename,std::string nametoberegister = "nil" , bool withLoop = true ,bool withSoundEffectControl = true );

	////Automatically create and add a CAudio class using the music filename inside soundlist,if nametoberegister is untouched, passed in audio filename will be use to be registerd.
	bool RegisterSound2D(std::string filename, std::string nametoberegister = "nil", bool withLoop = false ,bool withSoundEffectControl = true);
	
	////Automatically create and add a CAudio class using the music filename inside bgmlist,if nametoberegister is untouched, passed in audio filename will be use to be registerd.
	bool RegisterBgm3D(std::string filename,std::string nametoberegister = "nil",irrklang::vec3df pos = irrklang::vec3df(0.f,0.f,0.f), bool withLoop = true ,bool withSoundEffectControl = true );
	
	////Automatically create and add a CAudio class using the music filename inside soundlist,if nametoberegister is untouched, passed in audio filename will be use to be registerd.
	bool RegisterSound3D(std::string filename, std::string nametoberegister = "nil",irrklang::vec3df pos = irrklang::vec3df(0.f,0.f,0.f), bool withLoop = false ,bool withSoundEffectControl = true);

	//Manupilate a valid bgm track
	bool PlayBgmTrack(unsigned short trackindex,bool setLoop = true);
	bool PauseBgmTrack(unsigned short trackindex,bool pause = true);
	bool PlayBgmTrack(std::string trackname,bool setLoop = true);
	bool PauseBgmTrack(std::string trackname,bool pause = true);
	bool EnableBgmTrackSoundEffect(std::string trackname);
	bool EnableBgmTrackSoundEffect(unsigned short trackindex);
	bool SetBgmTrackPlayPosition(std::string trackname,int millSecPosition);
	bool SetBgmTrackPlayPosition(unsigned short trackindex,int millSecPosition);
	bool ResetBgmTrackPlayPosition(std::string trackname);
	bool ResetBgmTrackPlayPosition(unsigned short trackindex);

	//Manupilate a valid sound track
	bool PlaySoundTrack(unsigned short trackindex,bool setLoop = false);
	bool PauseSoundTrack(unsigned short trackindex,bool pause = true);
	bool PlaySoundTrack(std::string trackname,bool setLoop = false);
	bool PauseSoundTrack(std::string trackname,bool pause = true);
	bool EnableSoundTrackSoundEffect(std::string trackname);
	bool EnableSoundTrackSoundEffect(unsigned short trackindex);
	bool SetSoundTrackPlayPosition(std::string trackname,int millSecPosition);
	bool SetSoundTrackPlayPosition(unsigned short trackindex,int millSecPosition);
	bool ResetSoundTrackPlayPosition(std::string trackname);
	bool ResetSoundTrackPlayPosition(unsigned short trackindex);

	//mute all audio
	bool Mute();

	//unmute all audio
	bool UnMute();

	//resume all audio
	bool Resume();

	//pause all audio
	bool Pause();

	//stop all audio
	bool StopAllSounds();

	//traverse to next or previous officially registered bgm track
	bool TranverseBGMTrack(bool forward = true, bool warp = true);

	//traverse to next or previous officially registered sound track
	bool TranverseSoundTrack(bool forward = true, bool warp = true);

	//switch between pause or unpause all audio
	bool TogglePause();

	//switch between mute or unmute all audio
	bool ToggleMute();

	//check if the audio with the passed in name is still playing
	bool CheckAudioIsPlaying(std::string audioname);

	//check if the audio with the passed in name is still playing
	bool CheckAudioIsPlaying(const char* audioname);

	// Check Current Bgm track index
	short GetCurrentBgmTrackIndex();

	// Check Current sound track index
	short GetCurrentSoundTrackIndex();

	//set all audio to the volume.
	bool SetAllAudioVolume(float volume);

	//reset the whole music system
	bool Reset();

	//exit the music system
	bool Exit();

	//Creating irrklang sound pointer with protection,2D
	irrklang::ISound* CreateIrrklangISound2D(const char* filename,bool playLooped = false,bool startPauseed  = false,bool track  = false ,irrklang::E_STREAM_MODE mode = irrklang::ESM_AUTO_DETECT,bool enableSoundEffect = false);
	//Creating irrklang sound pointer with protection,3D
	irrklang::ISound* CreateIrrklangISound3D(const char* filename,irrklang::vec3df pos,bool playLooped = false,bool startPauseed  = false,bool track  = false ,irrklang::E_STREAM_MODE mode = irrklang::ESM_AUTO_DETECT,bool enableSoundEffect = false);

	//print out some debug information
	void PrintSoundListSize();
	void PrintBgmListSize();
	void PrintDebugInformation();
	void PrintBgmTrackList();
	void PrintSoundTrackList();
};

