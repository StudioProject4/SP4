#pragma once

//abstract factory
//
//class CFactoryShell//just a empty shell to workaround the problem of factory keep wanting to know the product type.
//{
//public:
//	CFactoryShell(){};
//	virtual ~CFactoryShell(){};
//};
class CBaseObject;

template <class product_type>
class CFactory //: public CFactoryShell
{
public:
	product_type* product;
public:

	CFactory(void)
	{
	};

	virtual ~CFactory(void)
	{
	};

	virtual void CreateProduct() = 0;
	product_type* GetProduct(){return product;};
};

class CBaseObjectFactory:public CFactory<CBaseObject>
{
public:
	CBaseObjectFactory(){};
	virtual ~CBaseObjectFactory(){};
};
