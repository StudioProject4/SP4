#ifndef DATABASETOOL_H
#define DATABASETOOL_H

///////////////////////////////
////Author:: Kee Yang
//////////////////////////////
namespace DatabaseTool
{
	template <typename Ttype,typename Ttype2,typename Ttype3>
	inline Ttype2 FindLastPositionOfList(Ttype list[],Ttype2 listsize,Ttype3 teminator)
	{
		Ttype2 result = -1 ; 
		for(Ttype2  i = 0; i<listsize; ++i)
		{
			if(list[i] != teminator)
			{
				++result;
			}else
			{
				break;
			}
		}
		return result;
	}
	template <typename Ttype>
	inline Ttype SimpleFindTargetPosition(Ttype list[],Ttype listsize,Ttype target)
	{

		for(Ttype i = 0; i<listsize; ++i)
		{
			if(list[i] == target)
			{
				return i;
			}
		}
	}


	template <typename Ttype, typename Ttype2>
	inline bool CheckDuplicate(Ttype list[],Ttype2 listsize,Ttype target)
	{
		bool duplicate = false;
		for(Ttype2 i = 0 ; i < listsize ; ++i)
		{
			if(list[i] == target)
			{
				duplicate = true;
			}
		}

		return duplicate;
	}
	template <typename Ttype,typename Ttype2>
	inline Ttype2 FindEmptySlot(Ttype list[],Ttype2 listsize,Ttype terminator)
	{
		Ttype2 result = -1;
		for(Ttype2 i = 0 ; i<listsize;++i)
		{
			if(list[i] == terminator)
			{
				result = i;
				break;
			}
		}

		if(result == -1)
		{
			result = listsize;
			cout << "List storage maxed out,overiding last slot";
		}
		return result;
	}
	template <typename Ttype>
	inline Ttype Clamp(Ttype value, Ttype min, Ttype max)
	{
		if(value > max)
		{
			value = max;
		}else
			if(value <min)
			{
				value = min;
			}
		return value;
	}

	template <typename Ttype,typename Ttype2>
	inline Ttype Clamp(Ttype value, Ttype2 min, Ttype2 max)
	{
		if(value > max)
		{
			value = max;
		}else
			if(value <min)
			{
				value = min;
			}
		return value;
	}
	template <typename Ttype>
	inline Ttype Warp(Ttype value, Ttype min, Ttype max)
	{
		if(value > max)
		{
			value = min;
		}else
			if(value <min)
			{
				value = max;
			}
		return value;
	}
	template <typename Ttype,typename Ttype2>
	inline Ttype2 Warp(Ttype2 value, Ttype min, Ttype max)
	{
		if(value > max)
		{
			value = min;
		}else
			if(value <min)
			{
				value = max;
			}
		return value;
	}
	template <typename Ttype,typename Ttype2>
	inline Ttype* BubblesortRestack (Ttype list[], Ttype2 length,Ttype ignore )
	{
		for(Ttype2 iter = 1; iter<length; iter++)
		{
			for(Ttype2 index = 0 ; index <length - iter; ++index)
			{
				//if(list[index] < list[index+1])
				if(list[index] == ignore)
				{
					Ttype temp = list[index];
					list[index] = list[index+1];
					list[index+1] = temp;
				}
			}
		}
		return list;
	}
	template <typename Ttype,typename Ttype2,typename Ttype3>
	inline Ttype* BubblesortRestack (Ttype list[], Ttype2 length,Ttype3 ignore )
	{
		for(Ttype2 iter = 1; iter<length; iter++)
		{
			for(Ttype2 index = 0 ; index <length - iter; ++index)
			{
				//if(list[index] < list[index+1])
				if(list[index] == ignore)
				{
					Ttype temp = list[index];
					list[index] = list[index+1];
					list[index+1] = temp;
				}
			}
		}
		return list;
	}

}
#endif