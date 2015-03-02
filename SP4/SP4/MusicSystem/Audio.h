#pragma once

#include <iostream>
#include <string>

#include <IRRKLANG\irrKlang.h>

using namespace irrklang;


class CAudio//provding a ease of level of control and bad pointer protection
{
public:
	bool active;//to mark whether this isound is using,not to be confused with check with isPlaying.because of the way some sound is organized for play and some are not,addition marking is needed
	ISound* audio;
	unsigned short dimension;
	ISoundEffectControl* audioEffectControl;
	std::string audioname;
	std::string filename;
	unsigned short id;
private:
	//irrklang::vec3df* position;
public:
	CAudio()
		:
		active(false)
		,id(0)
		,dimension(2)
		,audio(0)
		,audioEffectControl(0)
		,audioname("nil")
		,filename("nil")
	{
	}
	~CAudio()
	{
		//std::cout<<"Audio "<<filename<<" is deleted"<<std::endl;
	}
	inline bool ResetPlayPosition()
	{
		if(audio)
		{
			return audio->setPlayPosition(0);
		}
		return false;
	}
	inline int GetPlayLength()
	{
		if(audio)
		{
			return audio->getPlayLength();
		}
		return false;
	}
	inline int GetPlayPosition()
	{
		if(audio)
		{
			return audio->getPlayPosition();
		}
		return false;
	}
	inline void SetDimension(unsigned short numOfD)
	{
		this->dimension = numOfD;
	}
	inline unsigned short GetDimension()
	{
		return this->dimension;
	}
	inline bool SetPlayPosition(int millisecPosition)
	{
		if(audio)
		{
			return audio->setPlayPosition(millisecPosition);	
		}
		return false;
	}
	inline bool CheckValidAudioEffectControlPtr()
	{
		if(audioEffectControl)
		{
			return true;
		}
		return false;
	}
	inline bool CheckValidAudioPtr()
	{
		if(audio)
		{
			return true;
		}
		return false;
	}
	inline bool Init(ISound* pointerfromengine,std::string filename,std::string audioname = "nil")
	{
		if(pointerfromengine)
		{
			audio = pointerfromengine;
			//position = &audio->getPosition();
			SetFileName(filename);

			if(audioname != "nil")
			{
				//std::cout<<"nil audio name"<<std::endl;				
				SetAudioName(audioname);
			}else
			{
				//std::cout<<"not audio name"<<std::endl;
				SetAudioName(filename);
			}

			return true;
		}
		return false;
	}

	inline bool CleanUp()
	{
		//PrintDebugAudioName();
		//PrintDebugFileName();
		//std::cout<<"Got cleaned"<<std::endl;
		return StopAndRelease();
	}

	inline bool Stop()
	{
		if(audio)
		{
			audio->stop();
			return true;
		}
		return false;
	}
	inline bool Drop()
	{
		if(audio)
		{
			return audio->drop();
		}
		return false;
	}
	inline bool StopAndRelease()
	{
		if(audio)
		{
			Stop();
			Drop();
			audio = 0;
			return true;

			//if(audio->drop())
			//{
			//	audio = 0;
			//	std::cout<<"dropped"<<std::endl;
			//	return true;
			//}
			//return false;
		}
		return false;
	}
	inline bool Release()
	{
		if(audio)
		{
			Drop();
			audio = 0;
			return true;
			//if(Drop())
			//{
			//	audio = 0;
			//	return true;
			//}
		}
		return false;
	};
	inline float GetAudioMaximumDistance()
	{
		if(audio)
		{
			return audio->getMaxDistance();		
		}
		return 0;
	}
	inline float GetAudioMinimumDistance()
	{
		if(audio)
		{
			return audio->getMinDistance();		
		}
		return 0;
	}
	//distance of which audio cannot get anymore quieter
	inline bool SetAudioMaximunDistance(float distance)
	{
		if(audio)
		{
			audio->setMaxDistance(distance);
			return true;
		}
		return false;
	}

	//distance of which the audio cannot get anymore louder
	inline bool SetAudioMinimunDistance(float distance)
	{
		if(audio)
		{
			audio->setMinDistance(distance);
			return true;
		}
		return false;
	}

	inline float GetPositionX()
	{	
		if(audio)
		{
			return audio->getPosition().X;
		}
		return 0 ;
	}
	inline float GetPositionY()
	{		
		if(audio)
		{
			return audio->getPosition().Y;
		}
		return 0 ;
	}
	inline float GetPositionZ()
	{
		if(audio)
		{
			return audio->getPosition().Z;
		}
		return 0 ;
	}
	inline float* GetPositionArray3D()
	{
		if(audio)
		{
			float temp[3] = {0,0,0};
			irrklang::vec3df *vectemp = &audio->getPosition();
			temp[0] = vectemp->X;
			temp[1] = vectemp->Y;
			temp[2] = vectemp->Z;
			return temp;
		}
		return 0;
	};

	inline irrklang::vec3df GetPositionVec3df()
	{
		if(audio)
		{
			return audio->getPosition();
		}
		return  irrklang::vec3df(0,0,0) ;
	}
	inline bool SetPositionX(float x)
	{
		if(audio)
		{
			audio->setPosition(irrklang::vec3df(x,GetPositionY(),GetPositionZ()));
			return true;
		}
		return false;
	}
	inline bool SetPositionY(float y)
	{
		if(audio)
		{
			audio->setPosition(irrklang::vec3df(GetPositionX(),y,GetPositionZ()));
			return true;
		}
		return false;
	}
	inline bool SetPositionZ(float z)
	{
		if(audio)
		{
			audio->setPosition(irrklang::vec3df(GetPositionX(),GetPositionY(),z));
			return true;
		}
		return false;
	}
	inline bool SetPosition(irrklang::vec3df newPosition)
	{
		if(audio)
		{
			audio->setPosition(newPosition);
			return true;
		}
		return false;
	}
	inline bool SetPosition(float x,float y,float z)
	{
		if(audio)
		{
			audio->setPosition(irrklang::vec3df(x,y,z));
			return true;
		}
		return false;
	}
	inline bool SetPosition(float newPosition[3])
	{
		if(audio)
		{
			audio->setPosition(irrklang::vec3df(newPosition[0],newPosition[1],newPosition[3]));
			return true;
		}
		return false;
	}
	inline bool SetVolume(float volume)
	{
		if(audio)
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
			//std::cout<<volume<<std::endl;
			audio->setVolume(volume);
			return true;
		}
		return false;
	}
	inline float GetVolume()
	{
		if(audio)
		{
			return audio->getVolume();
		}
		return 0;
	}
	inline bool CheckIsPaused()
	{
		if(audio)
		{
			return audio->getIsPaused();
		}
		return false;
	}
	inline bool CheckIsFinished()
	{
		if(audio)
		{
			return audio->isFinished();
		}
		return false;
	}
	inline bool CheckIsLooped()
	{
		if(audio)
		{
			return audio->isLooped();
		}
		return false;
	}
	inline bool SetIsLooped(bool looped)
	{
		if(audio)
		{
			audio->setIsLooped(looped);
			return true;
		}
		return false;
	}
	inline bool SetIsPaused(bool paused = true)
	{
		if(audio)
		{
			audio->setIsPaused(paused);
			return true;
		}
		return false;
	}
	inline bool EnableAudioEffectControl()
	{	
		if(audio)
		{
			if(!audioEffectControl)
			{
				audioEffectControl = audio->getSoundEffectControl();
				return true;
			}
		}
		return false;
	}
	inline bool DisableAllAudioEffect()
	{
		if(audio)
		{
			if(audioEffectControl)
			{
				audioEffectControl->disableAllEffects();
				return true;
			}
		}
		return false;	
	}
	inline bool EnableChorusEffect(float wetDryMix = 50.f,float depth = 10.f,float feedback = 25.f,float frequency = 1.100000024f,bool sineWaveForm = true,float delay = 16.f,int phrase = 90)
	{	
		if(audio)
		{
			if(audioEffectControl)
			{
				audioEffectControl->enableChorusSoundEffect(wetDryMix,depth,feedback,frequency,sineWaveForm,delay,phrase);
				return true;
			}	
		}
		return false;
	}

	inline bool Move(float newPosition[3])
	{
		if(audio)
		{
			float* ownposition = GetPositionArray3D();
			SetPosition(ownposition[0] + newPosition[0],ownposition[1] + newPosition[1],ownposition[2] + newPosition[2]);
			return true;
		}
		return false;
	}
	inline bool Move(float x,float y,float z)
	{
		if(audio)
		{
			float* ownposition = GetPositionArray3D();
			SetPosition(ownposition[0] + x,ownposition[1] + y,ownposition[2] + z);
			return true;
		}
		return false;
	}
	inline bool Move(irrklang::vec3df newPosition)
	{
		if(audio)
		{
			irrklang::vec3df *ownposition = &GetPositionVec3df();
			SetPosition(ownposition->X + newPosition.X,ownposition->Y + newPosition.Y,ownposition->Z + newPosition.Z);
			return true;
		}
		return false;
	}
	inline unsigned short GetId()
	{
		return this->id;
	}
	inline void SetId(unsigned short id)
	{
		this->id = id;
	}
	inline void SetFileName(std::string filename)
	{
		this->filename = filename;
	}
	inline void SetFileName(const char* filename)
	{
		this->filename = filename;
	}

	inline std::string GetFileName()
	{
		return filename;
	}
	inline void SetAudioName(std::string audioname)
	{
		this->audioname = audioname;
	}
	inline void SetAudioName(const char* audioname)
	{
		this->audioname = audioname;
	}
	inline std::string GetAudioName()
	{
		return audioname;
	}
	inline void PrintDebugId()
	{
		std::cout<<"Audio ID: "<< id<<std::endl;
	}
	inline void PrintDebugIsPaused()
	{
		printf("Paused: %s", this->CheckIsPaused()?"true":"false\n");
	}
	inline void PrintDebugIsFinished()
	{
		printf("Finished: %s", this->CheckIsFinished()?"true":"false\n");
	}
	inline void PrintDebugIsLooped()
	{
		printf("Looped: %s", this->CheckIsLooped()?"true":"false\n");
	}
	inline void PrintDebugPlayPosition()
	{
		std::cout<<"Play Position: "<< GetPlayPosition()<<std::endl;
	}
	inline void PrintDebugPosition()
	{
		std::cout<<"Position: X: "<<GetPositionX()<<" , "<<GetPositionY()<<" , "<<GetPositionZ()<<std::endl;
	}
	inline void PrintDebugFileName()
	{
		std::cout<<"FileName: "<<filename<<std::endl;
	}
	inline void PrintDebugAudioName()
	{
		std::cout<<"Audio Name: "<<audioname<<std::endl;
	}
	inline void PrintDebugPointer()
	{
		std::cout<<"Audio Pointer: "<<audio<<std::endl;
		std::cout<<"Audio SFX Pointer: "<<audioEffectControl<<std::endl;
	}
	inline void PrintDebugNumberOfDimension()
	{
		std::cout<<"Dimension: "<<dimension<<std::endl;
	}
	inline void PrintDebugInformation()
	{	
		std::cout<<std::endl;
		PrintDebugPointer();
		PrintDebugId();
		PrintDebugNumberOfDimension();
		PrintDebugFileName();
		PrintDebugAudioName();
		PrintDebugIsPaused();
		PrintDebugIsLooped();
		PrintDebugIsFinished();
		PrintDebugPlayPosition();
		PrintDebugPosition();
	};
};