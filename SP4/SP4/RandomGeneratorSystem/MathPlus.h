#ifndef MATHPLUS_H
#define MATHPLUS_H
#include "../MyMath.h"
#include <iostream>//for debug purpose,can be remove if so desired

namespace MathPlus//This file purpose is to add on to Mr Tang's MyMath library
/////////////////////////
//Author::Kee Yang =D
/////////////////////////
{
	inline bool RangeCheck(int value, int min, int max)
	{
		if (value >= min && value <= max)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	inline float Sinusodial(float amplitude, float angular, float time, float phrase)
	{
		//y = A sin(ω t + φ)
		return (amplitude * sin(angular * time + phrase));
	}
	inline float SinCurve(float radian)
	{
		return (sin(radian));
	}
	inline float CosCurve(float radian)
	{
		return (cos(radian));
	}
	inline float TanCurve(float radian)
	{
		return (tan(radian));
	}
	inline float PokemonHpStatFormula(float base, float ImplictValue, float ExplictValue, float level)
	{

		return ((ImplictValue + 2 * base + (ExplictValue *0.25f)) * level / 100) + 10 + level;

	}
	inline float PokemonStatFormula(float base, float ImplictValue, float ExplictValue, float level, float boost)
	{
		return (((ImplictValue + 2 * base + (ExplictValue *0.25f)) * level / 100) + 5) * boost;
	}
}

class CRawData
{
public:
	unsigned short fcurrentindex;
	unsigned short bcurrentindex;
	static const unsigned short listsize = 10;
	short intervel;
	unsigned short PositiveIntergalData[listsize];
	short NegativeIntergalData[listsize];

	CRawData()
	{
		bcurrentindex = fcurrentindex = 0;
		intervel = 10;

		for (short i = 0; i < listsize; ++i)
		{
			PositiveIntergalData[i] = (i * intervel);
			NegativeIntergalData[i] = ((i * intervel) * -1);
		}
	};
	CRawData(short intervalue)
	{
		bcurrentindex = fcurrentindex = 0;
		intervel = intervalue;

		for (short i = 0; i < listsize; ++i)
		{
			PositiveIntergalData[i] = (i * intervel);
			NegativeIntergalData[i] = ((i * intervel) * -1);
		}
	};
	CRawData(bool randomIntervel, bool onceRandom, short intervalue = 10)//if using random intervel,don't bother setting third parameter
	{
		if (randomIntervel)
		{
			Math::InitRNG();
			bcurrentindex = fcurrentindex = 0;
			if (onceRandom)
			{
				intervel = Math::RandIntMinMax(2, 9);
			}

			for (short i = 0; i < listsize; ++i)
			{
				if (onceRandom == false)
				{
					intervel = Math::RandIntMinMax(2, 9);
				}
				PositiveIntergalData[i] = (i * intervel);
				NegativeIntergalData[i] = ((i * intervel) * -1);
			}
		}
		else
		{
			bcurrentindex = fcurrentindex = 0;
			intervel = intervalue;

			for (short i = 0; i < listsize; ++i)
			{
				PositiveIntergalData[i] = (i * intervel);
				NegativeIntergalData[i] = ((i * intervel) * -1);
			}
		}
	};
	~CRawData()
	{

	};
	inline void ReInitValues(bool randomIntervel, bool onceRandom, short intervalue = 10)
	{
		if (randomIntervel)
		{
			bcurrentindex = fcurrentindex = 0;
			if (onceRandom)
			{
				intervel = Math::RandIntMinMax(2, 9);
			}

			for (short i = 0; i < listsize; ++i)
			{
				if (onceRandom == false)
				{
					intervel = Math::RandIntMinMax(2, 9);
				}
				PositiveIntergalData[i] = (i * intervel);
				NegativeIntergalData[i] = ((i * intervel) * -1);
			}
		}
		else
		{
			bcurrentindex = fcurrentindex = 0;
			intervel = intervalue;

			for (short i = 0; i < listsize; ++i)
			{
				PositiveIntergalData[i] = (i * intervel);
				NegativeIntergalData[i] = ((i * intervel) * -1);
			}
		}
	};
	inline unsigned short getAdjIndex(bool forward, short inputindex)
	{
		short returnindex = 0;

		if (forward)
		{
			returnindex = inputindex + 1;
			if (returnindex > listsize)
			{
				returnindex = listsize;
			}
		}
		else
		{
			returnindex = inputindex - 1;
			if (returnindex < 0)
			{
				returnindex = 0;
			}
		}

		return returnindex;
	};
	inline unsigned short getAdjIndex(bool forward, bool warp = false)
	{
		short returnindex = 0;

		if (forward)
		{
			returnindex = fcurrentindex + 1;
			if (returnindex > listsize)
			{
				if (warp)
				{
					returnindex = 0;
				}
				else
				{
					returnindex = listsize;
				}

			}
		}
		else
		{
			returnindex = bcurrentindex - 1;
			if (returnindex < 0)
			{
				if (warp)
				{
					returnindex = listsize;
				}
				else
				{
					returnindex = 0;
				}
			}
		}

		return returnindex;
	};
	inline void TranverseSelfIndex(bool forward, bool warp)
	{
		if (forward)
		{
			fcurrentindex = getAdjIndex(true, warp);
		}
		else
		{
			bcurrentindex = getAdjIndex(false, warp);
		}

	}
	inline void PrintData()
	{
		std::cout << "PositiveIntergalData" << std::endl;
		for (unsigned short i = 0; i < listsize; ++i)
		{
			std::cout << " < " << i << " > " << PositiveIntergalData[i] << std::endl;
		}

		std::cout << "NegativeIntergalData" << std::endl;
		for (unsigned short i = 0; i < listsize; ++i)
		{
			std::cout << " < " << i << " > " << NegativeIntergalData[i] << std::endl;
		}
	}

};




#endif