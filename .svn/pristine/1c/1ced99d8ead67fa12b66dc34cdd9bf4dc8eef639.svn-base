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
	char id[500];                     //500注意，可能会溢出
	_itoa_s(varietyID,id,10);
	return id;
}



std::string logic_VarModule::getType()
{
	char type[10];
	_itoa_s(varType,type,10);
	return type;
}


std::string logic_VarModule::getValue()
{

	return varValue;
}

