#include <iostream>
#include "MusicSystem.h"
//#include <algorithm>


using namespace std;

bool Func2()
{
	std::cout<<"Func2"<<std::endl;
	return true;
}
bool Func1()
{
	std::cout<<"Func1"<<std::endl;
	return true;
}

void main()
{
	//ISoundEngine* MusicEngine = createIrrKlangDevice();
	////ISound* test = MusicEngine->play2D("bgm2.mp3",true,false,true, ESM_AUTO_DETECT, true);
	////std::cout<<test->drop()<<std::endl;
	////test->stop();
	//

	////delete test;
	////MusicEngine->drop();
	//CAudio test;
	//test.Init(MusicEngine->play3D("bgm2.mp3",irrklang::vec3df(0,0,0),true,false,true, ESM_AUTO_DETECT, true));
	//test.SetPosition(1,1,1);
	//std::cout<<test.GetPositionArray3D()[0]<<std::endl;
	//std::cout<<test.GetPositionArray3D()[1]<<std::endl;
	//std::cout<<test.GetPositionArray3D()[2]<<std::endl;


	CMusicSystem* MS = CMusicSystem::GetInstance();
	MS->RegisterBgm2D("bgm1.mp3");
	MS->RegisterBgm2D("bgm2.mp3");
	MS->RegisterBgm2D("bgm3.mp3");
	MS->RegisterBgm2D("bgm4.mp3");
	MS->RegisterBgm2D("bgm5.mp3");
	MS->RegisterBgm2D("bgm6.mp3");
	MS->RegisterBgm2D("bgm7.mp3");
	MS->RegisterBgm2D("bgm8.mp3");
	MS->RegisterBgm2D("bgm9.mp3");
	MS->PrintBgmTrackList();
	MS->PlayBgmTrack(1);
	//MS->PlaySoundTrack("bgm1.mp3");


	//CAudio test;
	//test.Init(MS->engine->play3D("bgm2.mp3",irrklang::vec3df(0,0,0),true,false,true, ESM_AUTO_DETECT, true),"bgm2.mp3");
	//test.PrintDebugAudioName();
	//test.PrintDebugFileName();
	//test.Stop();

	//MS->CreateIrrklangISound2D("bgm2.mp3");
	//hello.Stop();
	//MS->CreateIrrklangISound2D("bgm4.mp3");
	//MS->engine->play2D("bgm6.mp3");

	//result->stop();
	//MS->RegisterAudioAsBgm(&test);
	//std::vector<std::string> vec;
	//vec.push_back("apple");
	//vec.push_back("pear");
	//vec.push_back("orange");
	//vec.push_back("orange");
	//vec.push_back("kiwi");
	//vec.push_back("pear");
	//vec.push_back("apple");

	//for(short i =0 ; i<vec.size();++i)
	//{
	//	std::cout<<vec[i]<<std::endl;
	//}
	////std::sort(vec.begin(),vec.end());
	////std::vector<std::string>::iterator it = std::unique(vec.begin(),vec.end());
	////vec.resize( std::distance(vec.begin(),it) );
	//if(std::binary_search (vec.begin(), vec.end(), "kiwi"))
	//{
	//	std::cout<<"Found"<<std::endl;
	//}else
	//{
	//	std::cout<<"not Found"<<std::endl;
	//}
	//std::cout<<"\nLater\n"<<std::endl;
	//for(short i =0 ; i<vec.size();++i)
	//{
	//	std::cout<<vec[i]<<std::endl;
	//}
	int choice = 0;
	float testtemp[3] = {1,1,1};
	bool continuee = true;
	while(continuee)
	{
		cin>>choice;
		switch(choice)
		{
			case 1:
				//test->Move(1,1,1);
				//test->PrintDebugPosition();
				//MS->PauseBgmTrack("bgm3.mp3");
				//choice = 0;
				//MS->UnMute();
				MS->PlayBgmTrack(6);
			break;

			case 2:
				MS->Pause();
				//MS->ToggleMute();
				//test->Move(-1,-1,-1);
				//test->PrintDebugPosition();
				choice = 0;
			break;

			case 3:
				MS->Resume();
				//MS->PlayBgmTrack("bgm3.mp3");
				//test->SetAudioMaximunDistance(20000000);
				//std::cout<<test->GetAudioMinimumDistance()<<std::endl;
				//test.PrintDebugPosition();
				choice = 0;
			break;

			case 4:
				MS->TogglePause();
				//test->SetAudioMaximunDistance(0.1f);
				//std::cout<<test->GetAudioMinimumDistance()<<std::endl;
				
				//test.PrintDebugPosition();
				choice = 0;
			break;
			case 5:
				MS->TranverseBGMTrack();
				break;
			default:
				continuee = false;
				break;
		}
	};
	//std::cout<<test.EnableAudioEffectControl();
	//std::cout<<test.EnableChorusEffect(100,100,5);
	//std::cout<<test.DisableAllAudioEffect();

	//std::cout<<test.StopAndRelease();
	//test.SetVolume(7676);
	//test.audio->setPosition(irrklang::vec3df(10,10,10));
	//std::cout<<test.audio->getPosition().X<<std::endl;
	//std::cout<<test.audio->getPosition().Y<<std::endl;
	//std::cout<<test.audio->getPosition().Z<<std::endl;
	//test.audio->stop();
	//
	//test.audio->drop();
	//delete test.audio;
	//test.CleanUp();
	MS->Exit();
	system("pause");
};