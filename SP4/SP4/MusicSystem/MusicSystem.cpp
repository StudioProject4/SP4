#include "MusicSystem.h"

CMusicSystem * CMusicSystem::Instance = NULL;

CMusicSystem::CMusicSystem()
:
	MusicEngine(NULL)
	,BGM(NULL)
	,BGMfx(NULL)
	,BGMName(" ")
	,CurrentSoundTrack(0)
	,CurrentBGMTrack(0)
{
	std::cout << "Music system init" << std::endl;
	for(unsigned short i = 0 ; i< MAXSOUND; ++i)
	{
		SoundList[i] = NULL;
		SoundTracks[i] = " ";
		SoundFx[i] = NULL;
		SoundEffectList[i] = EFFECT_NONE; 
		SoundNameList[i] = " ";
	}
	for(unsigned short i = 0 ; i< MAXBGM; ++i)
	{
		BGMTracks[i] = " ";
		BGMSoundEffectMode = EFFECT_NONE; 
	}
	PlayerPosition.set(0,0,0);
	PlayerDirection.set(0,0,1);

	MusicEngine = createIrrKlangDevice();

	if(!MusicEngine)
	{
		//printf("Could not startup engine\n");
		inited = false;
	}else
	{
		//cout << "inited"<<endl;
		inited = true;

	}
}
CMusicSystem::~CMusicSystem()
{
	inited = false;
	//for(unsigned short i = 0 ; i< MAXSOUND; ++i)
	//{
	//	SoundList[i] = NULL;
	//	SoundTracks[i] = " ";
	//	SoundFx[i] = NULL;
	//	SoundEffectList[i] = EFFECT_NONE; 
	//}
	//for(unsigned short i = 0 ; i< MAXBGM; ++i)
	//{
	//	BGMTracks[i] = " ";
	//	BGMSoundEffectMode = EFFECT_NONE; 
	//}
	std::cout << "Music system destroyed" << std::endl;
	MusicEngine->drop();
}
CMusicSystem * CMusicSystem::GetInstance()
{
	if(Instance == NULL)
	{
		Instance = new CMusicSystem();
	}
	return Instance;
}

void CMusicSystem::playBGM(string name,bool soundeffect,SoundEffectMode mode )
{
	//cout << "Playing:"<< name <<endl;
	BGMName = name;
	if(soundeffect)
	{
		BGM = MusicEngine->play2D(name.c_str(),true,false,true, ESM_AUTO_DETECT, true);
		BGMfx = BGM->getSoundEffectControl();
		BGMSoundEffectMode = mode;
		
	}else
	{
		BGM = MusicEngine->play2D(name.c_str(),true,false,true);
		BGMSoundEffectMode = EFFECT_NONE;
	}
}
void CMusicSystem::playSound(string name,bool soundeffect,SoundEffectMode mode )
{
	ISound * dummy = NULL;
	int emptyslot = DatabaseTool::FindEmptySlot(SoundList,MAXSOUND,dummy);
	SoundEffectList[emptyslot] = mode;
	SoundNameList[emptyslot] = name;
	if(soundeffect)
	{
	
		SoundList[emptyslot] = MusicEngine->play2D(name.c_str(),false,false,true, ESM_AUTO_DETECT, true);
		SoundFx[emptyslot] = SoundList[emptyslot]->getSoundEffectControl();
	}else
	{
	
		SoundList[emptyslot] = MusicEngine->play2D(name.c_str(),false,false,true);
	}
}
void CMusicSystem::playBGMTrack(unsigned short position,bool soundeffect,SoundEffectMode mode )
{
	//if(position > MAXBGM)
	//{
	//	position = MAXBGM;
	//}else
	//	if(position < 0)
	//	{
	//		position = 0;
	//	}
	position = DatabaseTool::Clamp(position,0,MAXBGM);
	playBGM(BGMTracks[position],soundeffect);
	CurrentBGMTrack = position;
	BGMSoundEffectMode = mode;
}
void CMusicSystem::playSoundTrack(unsigned short position,bool soundeffect,SoundEffectMode mode )
{
	//if(position > MAXSOUND)
	//{
	//	position = MAXSOUND;
	//}else
	//	if(position < 0)
	//	{
	//		position = 0;
	//	}
		position = DatabaseTool::Clamp(position,0,MAXSOUND);
	playSound(SoundTracks[position],soundeffect);
	CurrentSoundTrack = position;
	SoundEffectList[position] = mode;
}
void CMusicSystem::TraveseTrack(bool NextBgm,bool NextSound,bool forward,bool warp,bool OnSoundEffect,SoundEffectMode mode)
{
	string stringdummy = " ";
	cout << "tranvsering" << endl;
	if(forward)
	{
		if(NextBgm)
		{
			StopAllMusic(false,true);
			++CurrentBGMTrack;
			if(warp)
			{			
				CurrentBGMTrack = DatabaseTool::Warp(CurrentBGMTrack,0,DatabaseTool::FindLastPositionOfList(BGMTracks,MAXBGM,stringdummy));
			}else
			{
				CurrentBGMTrack = DatabaseTool::Clamp(CurrentBGMTrack,0,MAXBGM);
			}
				
			playBGMTrack(CurrentBGMTrack,OnSoundEffect,mode);
		}
		if(NextSound)
		{
			//sound effect usually does not stop,only stop when it expires,
			++CurrentSoundTrack;
			if(warp)
			{
				CurrentSoundTrack = DatabaseTool::Warp(CurrentSoundTrack,0,DatabaseTool::FindLastPositionOfList(SoundTracks,MAXSOUND,stringdummy));
			}else
			{
				CurrentSoundTrack = DatabaseTool::Clamp(CurrentSoundTrack,0,MAXSOUND);
			}
			cout << "tring to play" << CurrentSoundTrack << endl;
			playSoundTrack(CurrentSoundTrack,OnSoundEffect,mode);
		}
	}else
	{
		if(NextBgm)
		{
			StopAllMusic(false,true);
			--CurrentBGMTrack;
			if(warp)
			{
				CurrentBGMTrack = DatabaseTool::Warp(CurrentBGMTrack,0,DatabaseTool::FindLastPositionOfList(BGMTracks,MAXBGM,stringdummy));
			}else
			{
				CurrentBGMTrack = DatabaseTool::Clamp(CurrentBGMTrack,0,MAXBGM);
			}
			playBGMTrack(CurrentBGMTrack,OnSoundEffect,mode);
		}
		if(NextSound)
		{
			//sound effect usually does not stop,only stop when it expires,
			--CurrentSoundTrack;
			if(warp)
			{
				CurrentSoundTrack = DatabaseTool::Warp(CurrentSoundTrack,0,DatabaseTool::FindLastPositionOfList(SoundTracks,MAXSOUND,stringdummy));
			}else
			{
				CurrentSoundTrack = DatabaseTool::Clamp(CurrentSoundTrack,0,MAXSOUND);
			}
			playSoundTrack(CurrentSoundTrack,OnSoundEffect,mode);
		}
	}
}
void CMusicSystem::SwitchBGMSoundEffect(SoundEffectMode mode,bool on)
{
	//Do note that many of the effect here need more details to really see their purpose;
	if(BGMfx != NULL)
	{
	BGMfx->disableAllEffects();
	BGMSoundEffectMode = mode;
	switch(mode)
	{
		case EFFECT_ECHO:
				if(on)
				{
					BGMfx->enableEchoSoundEffect();
				}else
				{
					BGMfx->disableEchoSoundEffect();
				}
			break;
		case EFFECT_DISTORTION:
				if(on)
				{
					BGMfx->enableDistortionSoundEffect();
				}else
				{
					BGMfx->disableDistortionSoundEffect();
				}
			break;
		case EFFECT_WAVE:
				if(on)
				{
					BGMfx->enableWavesReverbSoundEffect();
				}else
				{
					BGMfx->disableWavesReverbSoundEffect();
				}
			break;
		case EFFECT_CHORUS:
				if(on)
				{
					BGMfx->enableChorusSoundEffect();
				}else
				{
					BGMfx->disableChorusSoundEffect();
				}
			break;
		case EFFECT_COMPRESSOR://need more detalied info to use it true effect
				if(on)
				{
					BGMfx->enableCompressorSoundEffect();
				}else
				{
					BGMfx->disableCompressorSoundEffect();
				}
			break;
		case EFFECT_FLANGER:
				if(on)
				{
					BGMfx->enableFlangerSoundEffect();
				}else
				{
					BGMfx->disableFlangerSoundEffect();
				}
			break;
		case EFFECT_GARGLE:
				if(on)
				{
					BGMfx->enableGargleSoundEffect();
				}else
				{
					BGMfx->disableGargleSoundEffect();
				}
			break;
		case EFFECT_I3DL2:
				if(on)
				{
					BGMfx->enableI3DL2ReverbSoundEffect();
				}else
				{
					BGMfx->disableI3DL2ReverbSoundEffect();
				}
			break;
		case EFFECT_PARAM://need more detalied info to use it true effect
				if(on)
				{
					BGMfx->enableParamEqSoundEffect();
				}else
				{
					BGMfx->disableParamEqSoundEffect();
				}
			break;

		case EFFECT_NONE:
		case EFFECT_TOTAL:
		default:
			cout <<"ERROR: Unhandled SoundEffect Mode"<<endl;
			break;
	}
	}else
	{
		cout << "ERROR: BGM sound effect Pointer is NULL"<<endl;
	}
}
void CMusicSystem::SwitchSoundEffect(SoundEffectMode mode,unsigned short position,bool on)
{
		//Do note that many of the effect here need more details to really see their purpose;
	if(SoundFx[position]!=NULL)
	{
	SoundFx[position]->disableAllEffects();
	SoundEffectList[position] = mode;
	switch(mode)
	{
		case EFFECT_ECHO:
				if(on)
				{
					SoundFx[position]->enableEchoSoundEffect();
				}else
				{
					SoundFx[position]->disableEchoSoundEffect();
				}
			break;
		case EFFECT_DISTORTION:
				if(on)
				{
					SoundFx[position]->enableDistortionSoundEffect();
				}else
				{
					SoundFx[position]->disableDistortionSoundEffect();
				}
			break;
		case EFFECT_WAVE:
				if(on)
				{
					SoundFx[position]->enableWavesReverbSoundEffect();
				}else
				{
					SoundFx[position]->disableWavesReverbSoundEffect();
				}
			break;
		case EFFECT_CHORUS:
				if(on)
				{
					SoundFx[position]->enableChorusSoundEffect();
				}else
				{
					SoundFx[position]->disableChorusSoundEffect();
				}
			break;
		case EFFECT_COMPRESSOR://need more detalied info to use it true effect
				if(on)
				{
					SoundFx[position]->enableCompressorSoundEffect();
				}else
				{
					SoundFx[position]->disableCompressorSoundEffect();
				}
			break;
		case EFFECT_FLANGER:
				if(on)
				{
					SoundFx[position]->enableFlangerSoundEffect();
				}else
				{
					SoundFx[position]->disableFlangerSoundEffect();
				}
			break;
		case EFFECT_GARGLE:
				if(on)
				{
					SoundFx[position]->enableGargleSoundEffect();
				}else
				{
					SoundFx[position]->disableGargleSoundEffect();
				}
			break;
		case EFFECT_I3DL2:
				if(on)
				{
					SoundFx[position]->enableI3DL2ReverbSoundEffect();
				}else
				{
					SoundFx[position]->disableI3DL2ReverbSoundEffect();
				}
			break;
		case EFFECT_PARAM://need more detalied info to use it true effect
				if(on)
				{
					SoundFx[position]->enableParamEqSoundEffect();
				}else
				{
					SoundFx[position]->disableParamEqSoundEffect();
				}
			break;

		case EFFECT_NONE:
		case EFFECT_TOTAL:
		default:
			cout <<"ERROR: Unhandled SoundEffect Mode"<<endl;
			break;
	}
	}else
	{
		cout << "ERROR: "<<"Sound Effect Pointer Position: "<<position<<"  is NULL"<<endl;
	}
}
void CMusicSystem::InsertBGMTrack(string name)
{
	string dummy = " ";
	if(!DatabaseTool::CheckDuplicate(BGMTracks,MAXBGM,name))
	{
		BGMTracks[DatabaseTool::FindEmptySlot(BGMTracks,MAXBGM,dummy)] = name;
	}else
	{
		cout << "Duplicate BGM track inseertion detected"<<endl;
	}
}
void CMusicSystem::InsertSoundTrack(string name)
{
	string dummy = " ";
	if(!DatabaseTool::CheckDuplicate(SoundTracks,MAXSOUND,name))
	{
		SoundTracks[DatabaseTool::FindEmptySlot(SoundTracks,MAXSOUND,dummy)] = name;
	}
	else
	{
		cout << "Duplicate Sound track inseertion detected"<<endl;
	}
}
void CMusicSystem::InsertBGMTrack(string name, unsigned short position)
{
	//if(position > MAXBGM)
	//{
	//	position = MAXBGM;
	//}else
	//	if(position < 0)
	//	{
	//		position = 0;
	//	}
	position = DatabaseTool::Clamp(position,0,MAXBGM);
	BGMTracks[position] = name;
}
void CMusicSystem::InsertSoundTrack(string name, unsigned short position)
{
	//if(position > MAXSOUND)
	//{
	//	position = MAXSOUND;
	//}else
	//	if(position < 0)
	//	{
	//		position = 0;
	//	}
	position = DatabaseTool::Clamp(position,0,MAXSOUND);
	SoundTracks[position] = name;
}
void CMusicSystem::setBGMVolume(int v)
{
	//if(v >100)
	//{
	//	v = 100;
	//}else
	//	if(v< 0)
	//	{
	//		v = 0;
	//	}
	v = DatabaseTool::Clamp(v,0,100);
	float newVolume = (float)v/100;

	BGM->setVolume(newVolume);
}
void CMusicSystem::setAllSoundVolume(int v)
{
	//if(v >100)
	//{
	//	v = 100;
	//}else
	//	if(v< 0)
	//	{
	//		v = 0;
	//	}
	v = DatabaseTool::Clamp(v,0,100);
	float newVolume = (float)v/100;
	//cout << newVolume;
	for(unsigned short i = 0 ; i < MAXSOUND; ++i)
	{
		if(SoundList[i] != NULL)
		{
			SoundList[i]->setVolume(newVolume);
			
		}else
		{
			break;
		}
	}
}
void CMusicSystem::setBGMVolume(float v)
{
	if(BGM )
	{
		BGM->setVolume(v);
	}else
	{
		cout << "BGM NULL pointer error"<<endl;
	}
}
void CMusicSystem::setAllSoundVolume(float v)
{
	for(unsigned short i = 0 ; i < MAXSOUND; ++i)
	{
		if(SoundList[i] != NULL)
		{
			SoundList[i]->setVolume(v);
		}else
		{
			break;
		}
	}
}

void CMusicSystem::pauseAll(bool mode)
{
	if(mode)
	{
		MusicEngine->setAllSoundsPaused();
	}else
	{
		MusicEngine->setAllSoundsPaused(false);
	}
}
void CMusicSystem::ResetBGMVarible(bool removetrack)
{
	if(BGM != NULL)
	{
		BGM->stop();
	}
	BGM = NULL;
	if(BGMfx != NULL)
	{	
		BGMfx->disableAllEffects();
	}
	BGMfx = NULL;
	BGMSoundEffectMode = EFFECT_NONE;
	BGMName = " ";
	if(removetrack)
	{
		for(unsigned short i = 0 ; i <MAXBGM; ++i)
		{
			BGMTracks[i] = " ";
		}
	}
}
void CMusicSystem::ResetBGMVarible(unsigned short position,bool removetrack)
{
	if(BGM != NULL)
	{
		BGM->stop();
	}
	BGM = NULL;
	if(BGMfx != NULL)
	{
		BGMfx->disableAllEffects();
	}
	BGMfx = NULL;
	BGMName = " ";
	BGMSoundEffectMode = EFFECT_NONE;
	if(removetrack)
	{
		
		BGMTracks[position] = " ";
		
	}
	string dummy = " ";
	DatabaseTool::BubblesortRestack(BGMTracks,MAXSOUND,dummy);
}
void CMusicSystem::ResetSoundVarible(bool removetrack)
{
	if(removetrack)
	{
		for(unsigned short i = 0; i<MAXSOUND ; ++i)
		{
			if(SoundList[i]!= NULL)
			{
				SoundList[i]->stop();
			}
			SoundList[i] = NULL;
			if(SoundFx[i] != NULL)
			{
				SoundFx[i]->disableAllEffects();
			}
			SoundFx[i] = NULL;
			SoundEffectList[i] = EFFECT_NONE;
			SoundTracks[i] = " ";
			SoundNameList[i] = " ";
			SoundPosition[i].SetZero();
		}
	}else
	{
		for(unsigned short i = 0; i<MAXSOUND ; ++i)
		{
			if(SoundList[i]!= NULL)
			{
				SoundList[i]->stop();
			}
			SoundList[i] = NULL;
			if(SoundFx[i] != NULL)
			{
				SoundFx[i]->disableAllEffects();
			}
			SoundFx[i] = NULL;
			SoundEffectList[i] = EFFECT_NONE;
			SoundNameList[i] = " ";
			SoundPosition[i].SetZero();
			
		}
	}
}
void CMusicSystem::ResetSoundVarible(unsigned short position, bool removetrack)
{
	if(SoundList[position]!= NULL)
	{
		SoundList[position]->stop();
	}
	SoundList[position] = NULL;
	if(SoundFx[position] != NULL)
	{
		SoundFx[position]->disableAllEffects();
	}
	SoundFx[position] = NULL;
	SoundEffectList[position] = EFFECT_NONE;
	SoundNameList[position] = " ";
	SoundPosition[position].SetZero();
	if(removetrack)
	{
		SoundTracks[position] = " ";
	}



	string dummy = " ";
	ISound *dummy2 = NULL;
	ISoundEffectControl* dummy3 = NULL;
	Vector3 dummy4;
	DatabaseTool::BubblesortRestack(SoundTracks,MAXSOUND,dummy);
	DatabaseTool::BubblesortRestack(SoundList,MAXSOUND,dummy2);
	DatabaseTool::BubblesortRestack(SoundEffectList,MAXSOUND,NULL);
	DatabaseTool::BubblesortRestack(SoundNameList,MAXSOUND,dummy);
	DatabaseTool::BubblesortRestack(SoundPosition,MAXSOUND,dummy4);
}
void CMusicSystem::RemoveAllMusic(bool removeTrack)
{
	//BGM = NULL;
	//if(BGMfx != NULL)
	//{
	//	BGMfx->disableAllEffects();
	//}
	//BGMfx = NULL;
	//BGMSoundEffectMode = EFFECT_NONE;
	ResetBGMVarible(removeTrack);
	ResetSoundVarible(removeTrack);
	//if(removeTrack)
	//{
		//for(unsigned short i = 0 ; i < MAXBGM; ++i)
		//{
		//	BGMTracks[i] = " ";

		//}
		//for(unsigned short i = 0 ; i < MAXSOUND; ++i)
		//{
		//	SoundList[i] = NULL;
		//	SoundTracks[i] = " ";
		//	SoundFx[i]->disableAllEffects();
		//	SoundFx[i] = NULL;
		//	SoundEffectList[i] = EFFECT_NONE;
		//}
	//}else
	//{
		
	//	for(unsigned short i = 0 ; i < MAXSOUND; ++i)
	//	{
	//		SoundList[i] = NULL;
	//		SoundFx[i]->disableAllEffects();
	//		SoundFx[i] = NULL;
	//		SoundEffectList[i] = EFFECT_NONE;
	//	}
	//}

}
void CMusicSystem::StopSoundTrack(unsigned short position,bool RemoveSoundTrack)
{
	position = DatabaseTool::Clamp(position,0,MAXSOUND);
	//cout <<"stoping:: "<<  position<<endl;
	if(SoundList[position] != NULL)
	{
		/*SoundList[position]->stop();
		SoundList[position]= NULL;
		SoundFx[position]->disableAllEffects();
		SoundFx[position] = NULL;
		SoundEffectList[position] = EFFECT_NONE;
		if(RemoveSoundTrack)
		{
			SoundTracks[position] = " ";
		}*/
		ResetSoundVarible(position,RemoveSoundTrack);



	}else
	{
		cout <<"ERROR: trying to stop an NUll Sound Pointer"<<endl;
	}

}


void CMusicSystem::StopAllMusic(bool SoundOnly,bool bgmOnly)
{
	if(bgmOnly)
	{
		//cout << " BGM stop"<<endl;
		if(BGM!= NULL)
		{
			//BGM->stop();
			//BGM = NULL;
			//BGMfx = NULL;
			//BGMSoundEffectMode = EFFECT_NONE;
			ResetBGMVarible();
		}else
		{
			cout << "ERROR:: Attempting to stop NULL bgm Pointer"<<endl;
		}
	}else
	{
		if(SoundOnly)
		{
			cout << " All sound stop"<<endl;
			//for(unsigned short i = 0 ; i < MAXSOUND; ++i)
			//{
			//	if(SoundList[i] != NULL)
			//	{
			//		SoundList[i]->stop();
			//		SoundList[i]= NULL;
			//		SoundFx[i] = NULL;
			//		SoundEffectList[i] = EFFECT_NONE;
			//	}else
			//	{
			//		break;
			//	}
			//}
			ResetSoundVarible();
		}else
		{
			cout << "All Music Stopped"<<endl;
			MusicEngine->stopAllSounds();
			RemoveAllMusic();
		}
	}
}

void CMusicSystem::MuteAll(bool mode)
{
	if(mode)
	{
		if(BGM!= NULL)
		{
			BGM->setVolume(0.0f);
		}
		for(unsigned short i = 0 ; i < MAXSOUND; ++i)
		{
			if(SoundList[i] != NULL)
			{
				SoundList[i]->setVolume(0.0f);
			}else
			{
				break;
			}
		}
	}else
	{
		if(BGM!= NULL)
		{
			BGM->setVolume(1.0f);
		}
		for(unsigned short i = 0 ; i < MAXSOUND; ++i)
		{
			if(SoundList[i] != NULL)
			{
				SoundList[i]->setVolume(1.0f);
			}else
			{
				break;
			}
		}
	}
}	
unsigned short CMusicSystem::getCurrentSoundTrackPosition()
{
	return CurrentSoundTrack;
}
unsigned short CMusicSystem::getCurrentBGMTrackPosition()
{
	return CurrentBGMTrack;
}
string CMusicSystem::CheckCurrentBGM()
{
	return BGMTracks[CurrentBGMTrack];
}
string CMusicSystem::CheckCurrentSound()
{
	return SoundTracks[CurrentSoundTrack];
}
string CMusicSystem::printSoundEffectModeText(SoundEffectMode mode)
{
	switch(mode)
	{
		case EFFECT_DISTORTION:
			return "EFFECT_DISTORTION";
			break;
		case EFFECT_ECHO:
			return "EFFECT_ECHO";
			break;
		case EFFECT_WAVE:
			return "EFFECT_WAVE";
			break;
		case EFFECT_CHORUS:
			return "EFFECT_CHORUS";
			break;
		case EFFECT_COMPRESSOR:
			return "EFFECT_COMPRESSOR";
			break;
		case EFFECT_FLANGER:
			return "EFFECT_FLANGER";
			break;
		case EFFECT_GARGLE:
			return "EFFECT_GARGLE";
			break;
		case EFFECT_I3DL2:
			return "EFFECT_I3DL2";
			break;
		case EFFECT_PARAM:
			return "EFFECT_PARAM";
			break;
		case EFFECT_NONE:
			return "EFFECT_NONE";
			break;
		case EFFECT_TOTAL:
			return "EFFECT_TOTAL";
			break;
		default:
			return "Unhandle Effect mode Printng";
			break;
	}
}
void CMusicSystem::printBGMTracks()
{
	cout <<endl;
	cout << "Registered BGM Tracks list"<<endl;
	for(unsigned short i = 0 ; i<MAXBGM; ++i)
	{
		if(CurrentBGMTrack == i)
		{
			cout << ">>";
		}
		cout << " < "<< i << " > "<< BGMTracks[i]<<endl;
	}
}
void CMusicSystem::printSoundTracks()
{
	cout <<endl;
	cout << "Registered Sound Tracks list"<<endl;
	for(unsigned short i = 0 ; i<MAXSOUND; ++i)
	{
		if(CurrentSoundTrack == i)
		{
			cout << ">>";
		}
		cout << " < "<< i << " > "<< SoundTracks[i]<<endl;
	}
}
unsigned short CMusicSystem::getLastBGMTrackCount()
{
	return DatabaseTool::FindLastPositionOfList(BGMTracks, MAXBGM, " ");
	
}
unsigned short CMusicSystem::getLastSoundTrackCount()
{
	return DatabaseTool::FindLastPositionOfList(SoundTracks, MAXBGM, " ");
}
void CMusicSystem::CheckUp()
{
	printBGMTracks();
	printSoundTracks();
	cout << "\nBGM POINTER List: ";
	cout << " < "<< 0 << " > "<< BGM<<" Sound Effect: "<<printSoundEffectModeText(BGMSoundEffectMode)<<" FileName: "<< BGMName<<endl;
	cout << "\nSound POINTER List: "<<endl;
	for(unsigned short i = 0 ; i<MAXSOUND; ++i)
	{
		//full cout
		cout << " < "<< i << " > "<< SoundList[i]<<" Sound Effect: "<<printSoundEffectModeText(SoundEffectList[i])<<" FileName: "<< SoundNameList[i]<<" Pos: "<<SoundPosition[i]<<endl;
	
		//if(SoundList[i] != NULL)
		//{
		//	cout << "< "<< i << " > "<<"NOT NULL "<<"Sound Effect:"<<printSoundEffectModeText(SoundEffectList[i])<<" FileName:"<< SoundNameList[i]<<" Pos: "<<SoundPosition[i]<<endl;
		//}
		//else
		//{
		//	cout << "< "<< i << " > "<<"NULL POINTER "<<"Sound Effect:"<<printSoundEffectModeText(SoundEffectList[i])<<" FileName:"<< SoundNameList[i]<<" Pos: "<<SoundPosition[i]<<endl;
		//}
	}
}
void CMusicSystem::AutoPlayNextTrack()//not working
{
	//static bool tranverseNow = false;
	
	if (SoundList[CurrentSoundTrack] != NULL)
	{
		if (SoundList[CurrentSoundTrack]->isFinished())
		{
			
			cout << "Next tracking" << endl;

			TraveseTrack(false, true, true, true);
			//CheckUp();
			//system("pause");//somehow it need to system pause to work fine ?????? Wth....
		}
	}
	
}
void CMusicSystem::Test()
{
}


















///////////////////////////////
////Author:: Kee Yang
//////////////////////////////