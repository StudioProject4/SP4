#ifndef __BASEOBJECT_H__
#define __BASEOBJECT_H__

#include "Vector3.h"
#include "Entity.h"
#include "Physics.h"
#include <vector>
class CSprite;
class Cell;

//class CSpatialPartion;
//
//struct SIndex2D
//{
//	short x;
//	short y;
//	SIndex2D()
//		:x(-1)
//		,y(-1)
//	{};
//};
//class CIndexContainer
//{
//public: 
//	friend CSpatialPartion;
//public:
//	std::vector<SIndex2D> indexOfCellsStretchedAcrossed;
//
//	CIndexContainer()
//	{};
//
//	std::vector<Cell*> GetCellsStretchedAcrossed()
//	{
//
//	};
//};

class CBaseObject:public CEntity
{
public:
	CPhysics phys;
	bool active;
	Vector3 pos;
	Vector3 dir;
	short cellvectorindex;
	Cell* ownerCell;
	CSprite * theSprite;


	//for testing spatial partition of big object in multple cell
	Vector3 TopLeft;
	Vector3 BottomRight;
	Vector3 TopLeftCellIndex;
	Vector3 BottomRightCellIndex;
	std::vector<Cell*> ownerCellNeo;
	std::vector<Vector3>celltomodify;
	short cellVectorIndexNeo;
	//std::vector<CIndexContainer> listOfCellsScretchAcross;
public:
	CBaseObject()
		:active(true)
		,cellvectorindex(-1)
		,cellVectorIndexNeo(-1)
	{};
	virtual ~CBaseObject(){};
	
	virtual bool OnCollision(CBaseObject* a_obj) = 0;
	virtual bool Render() = 0;

	virtual bool Update() = 0;
	virtual bool Init() = 0;
	virtual bool Reset()= 0;
	virtual bool CleanUp() = 0;
};


#endif