#pragma once
#include "logic_BasicModule.h"
#include "logic_Global.h"



class logic_VarModule :
	public logic_BasicModule
{
public:
	logic_VarModule(void);
	explicit logic_VarModule(_IdDataType id,VarietyType type,const std::string value);
	~logic_VarModule(void);

	std::string getType();     //带有类型转换
	std::string getValue();
	std::string getID();       //带有类型转换

private:
	//type and the value
	_IdDataType varietyID;
	VarietyType varType;
	std::string varValue;
};

