#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string>
//#include <sstream>

namespace ToolLibrary
{

	template<typename output_type>
	inline output_type ConvertAlphabetToASCIINumber(char inputalphabet)
	{
		return (output_type)inputalphabet;
	}

	template<typename input_type>
	inline char ConvertASCIINumberToAlphabet( input_type inputnumber )
	{
		return static_cast<char>('A' - 1 + inputnumber);
	}

	template <typename output_type >
	inline output_type ConvertStringToNumber(std::string inputstring)
	{	
		return (output_type)atoi(inputstring.c_str());
	}

	template <typename input_type>
	inline std::string ConvertNumberToString(input_type inputnumber,int radix = 10)
	{
		char buffer[50];
		itoa (inputnumber,buffer,radix);
		return buffer;
	}

	template <typename input_type>
	inline std::string CheckTypeName(input_type input)
	{
		return typeid(input).name();
	}

	template<typename input_type>
	bool modulateNumber(input_type number , short module)
	{
		if(number%module == 0)
		{
			return true;
		}else
		{
			return false;
		}
	}

	template <typename type>
	void PrintVectorList(std::vector<type>* source)
	{
		for(unsigned short i = 0 ; i<source->size();++i)
		{
			std::cout<<(*source)[i]<<std::endl;
		}
	}

	template <typename Type1,typename Type2,typename Type3>
	inline bool CheckThreesholdInPercent(Type1 currentvalue,Type2 maxvalue,Type3 leverinpercent,bool morethanoperator = true )
	{
		bool result = false;

		float convertedpercenttonumber = maxvalue * leverinpercent *0.01;
		//std::cout <<"convertedpercenttonumber: "<<convertedpercenttonumber<<std::endl;

		if(morethanoperator == true)
		{
			if(currentvalue >convertedpercenttonumber)
			{
				result =  true;
			}else
			{
				result = false;
			}
		}else
		{
			if(currentvalue <convertedpercenttonumber)
			{
				result = true;
			}else
			{
				result = false;
			}
		}

		return result;
	}

	template<typename type>
	inline bool CheckEvenNumber(type number)
	{
		if(number%2 == 0)
		{
			return true;
		}else
		{
			return false;
		}
	};

	//untested
	template<typename T>
	inline const T& AddConst(T& t)
	{
		return t;
	};

	//template<typename type>
	//inline std::string convertIntToString(type value)
	//{
	//	ostringstream convert;
	//	convert.str(string());
	//	convert.clear();

	//	convert << value;

	//	return convert.str();

	//	//unreachable
	//	//convert.str(string());
	//	//convert.clear();
	//};

	template<typename type>
	inline std::string JoinAndGetString(std::vector<type> source,std::string connector = ", ",bool removetailchar = true)
	{
		std::string result = "";

		for(ushort i = 0 ; i < source.size();++i)
		{

			result += source[i] + connector ;	
		}

		if(removetailchar)
		{
			if (result.size () > 0)
			{
				result.resize (result.size () - connector.size());
			}
		}

		return result;
	};
	//template <typename type>
	//inline std::string ConvertNumberToString2( type inputnumber )
	//{
	//	ostringstream ss;
	//	ss << inputnumber;
	//	return ss.str();
	//}
};