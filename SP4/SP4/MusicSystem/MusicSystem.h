#include <iostream>
#include <conio.h>
//#include <IRRKLANG/irrKlang.h>
//#include "include/irrKlang.h"
#include <IRRKLANG\irrKlang.h>
#include <string>
#include "DatabaseTool.h"
#include "../Vector3.h"
using namespace std;
using namespace irrklang;
//#pragma comment(lib, "irrKlang.lib") // link with irrKlang.dll
#define MAXSOUND 10
#define MAXBGM 10
//class CSoundBase
//{
//public:
//	enum SoundEffectMode
//	{
//		EFFECT_NONE = 0,
//		EFFECT_DISTORTION,
//		EFFECT_ECHO,
//		EFFECT_WAVE,
//		EFFECT_CHORUS,
//		EFFECT_COMPRESSOR,
//		EFFECT_FLANGER,
//		EFFECT_GARGLE,
//		EFFECT_I3DL2,
//		EFFECT_PARAM,
//		EFFECT_TOTAL
//	};
//
//	CSoundBase():
//		SoundMode(EFFECT_NONE)
//		,SoundPointer(NULL)
//		,SoundEffectPointer(NULL)
//		,name(" ")
//	{
//
//	}
//	~CSoundBase()
//	{
//
//	}
//	ISound * SoundPointer;
//	ISoundEffectControl* SoundEffectPointer;
//	SoundEffectMode SoundMode;
//	string name;
//	Vector3 Pos;
//};//only until i finish everything then i realize that i could have put them into class for better management =P
class CMusicSystem
{
public:
	enum SoundEffectMode
	{
		EFFECT_NONE = 0,
		EFFECT_DISTORTION,
		EFFECT_ECHO,
		EFFECT_WAVE,
		EFFECT_CHORUS,
		EFFECT_COMPRESSOR,
		EFFECT_FLANGER,
		EFFECT_GARGLE,
		EFFECT_I3DL2,
		EFFECT_PARAM,
		EFFECT_TOTAL
	};

private:
	//static const unsigned short MAXSOUND = 10;//whether #define or do static both can work.The difference is just that if don use define, outside cannot see
	//static const unsigned short MAXBGM = 10;

	static CMusicSystem * Instance;
	ISoundEngine* MusicEngine;

	ISound * BGM;
	ISoundEffectControl* BGMfx;
	SoundEffectMode BGMSoundEffectMode;
	string BGMName;

	ISound * SoundList[MAXSOUND];
	ISoundEffectControl* SoundFx[MAXSOUND];
	SoundEffectMode SoundEffectList[MAXSOUND];
	string SoundNameList[MAXSOUND];
	Vector3 SoundPosition[MAXSOUND];
	//the fact that i am bubblesorting these parallel array.they are prone to mismatch,especially the Namelist.However,the program should still run fine.
	//moving them to their own class will help to solve this management problem,but i am lazy to move them all now.

	string BGMTracks[MAXBGM];
	string SoundTracks[MAXSOUND];
	unsigned short CurrentSoundTrack;
	unsigned short CurrentBGMTrack;
	
protected:

	bool inited;

	CMusicSystem();
	void RemoveAllMusic(bool removeTrack = false);
	void ResetBGMVarible(bool removetrack = false);
	void ResetBGMVarible(unsigned short position, bool removetrack = false);
	void ResetSoundVarible(bool removetrack = false);
	void ResetSoundVarible(unsigned short position, bool removetrack = false);



public:

	vec3df PlayerPosition;//i don care whether who can access =P
	vec3df PlayerDirection;
	~CMusicSystem();
	static CMusicSystem * GetInstance();
	
	void playBGM(string name,bool soundeffect = false,SoundEffectMode mode =EFFECT_NONE );
	void playSound(string name,bool soundeffect = false,SoundEffectMode mode =EFFECT_NONE);
	void playBGMTrack(unsigned short position,bool soundeffect = false,SoundEffectMode mode =EFFECT_NONE);
	void playSoundTrack(unsigned short position,bool soundeffect = false,SoundEffectMode mode =EFFECT_NONE);
	void TraveseTrack(bool NextBgm,bool NextSound,bool forward = true,bool warp = false,bool OnSoundEffect = false,SoundEffectMode mode =EFFECT_NONE);

	void InsertBGMTrack(string name);
	void InsertSoundTrack(string name);
	void InsertBGMTrack(string name,unsigned short position);
	void InsertSoundTrack(string name,unsigned short position);

	void setBGMVolume(int v);
	void setBGMVolume(float v);
	void setAllSoundVolume(int v);
	void setAllSoundVolume(float v);
	
	void MuteAll(bool mode = true);
	void pauseAll(bool mode = true);
	void StopAllMusic(bool soundOnly = false,bool bgmOnly = false);
	void StopSoundTrack(unsigned short position,bool RemoveSoundTrack = false ); 

	void SwitchBGMSoundEffect(SoundEffectMode mode,bool on = true);
	void SwitchSoundEffect(SoundEffectMode mode,unsigned short position,bool on = true);

	void AutoPlayNextTrack();

	void printBGMTracks();
	void printSoundTracks();
	string printSoundEffectModeText(SoundEffectMode mode);
	string CheckCurrentBGM();
	string CheckCurrentSound();


	unsigned short getCurrentSoundTrackPosition();
	unsigned short getCurrentBGMTrackPosition();
	unsigned short getLastBGMTrackCount();
	unsigned short getLastSoundTrackCount();
	void CheckUp();
	void Test();
	
};









///////////////////////////////
////Author:: Kee Yang
//////////////////////////////