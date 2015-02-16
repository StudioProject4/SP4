#pragma once
//#include "UnitEnumLibrary.h"

template<class type1>
class CMind//AI controller of the thing//FMS
{
	public:
		type1 mindstate;

	public:
		CMind(type1 a_mindstate)
			:mindstate(a_mindstate)
		{

		};


		virtual ~CMind(void)
		{
		}

		 //ai logic//main loop
		virtual void Think(void) = 0;
		virtual void ChangeState(type1 a_state) = 0;
		virtual void ChangeState(unsigned short a_state) = 0;
		virtual type1 GetState(){return mindstate;};
};

