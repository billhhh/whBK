#include "logic_VarModule.h"


logic_VarModule::logic_VarModule(void)
{
}

logic_VarModule::logic_VarModule(_IdDataType id,VarietyType type,const std::string value)
	:varietyID(id),varType(type),varValue(value)
{
}


logic_VarModule::~logic_VarModule(void)
{
}


std::string logic_VarModule::getID()
{
	std::stringstream ss;
	ss << varietyID;
	return ss.str();
}

VarietyType logic_VarModule::getVarietyType()
{
	return varType;
}

void logic_VarModule::setName(std::string name)
{
	varName = name;
}

std::string logic_VarModule::getName()
{
	return varName;
}


std::string logic_VarModule::getType()
{
	std::stringstream ss;
	ss << varType;
	return ss.str();
}


std::string logic_VarModule::getValue()
{

	return varValue;
}

