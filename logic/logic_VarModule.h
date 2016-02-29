/* 
* 
* function: �߼��������
* 
* Date:2015-11-05
* 
*    Author: Bill Wang
*/

#pragma once
#include<sstream>
#include "logic_BasicModule.h"
#include "logic_PrjPropertyGlobal.h"
#include "logic_Global.h"

class logic_VarModule :
	public logic_BasicModule
{
public:
	logic_VarModule(void);
	explicit logic_VarModule(_IdDataType id,VarietyType type,const std::string value);
	~logic_VarModule(void);

	std::string getType();     //����֮ǰIO�����Ѿ����˺ܶ��ˣ����ر���������getVarietyType��������
	std::string getValue();
	std::string getID();      
	
	VarietyType getVarietyType();
	void setName(std::string name);
	std::string getName();      
private:
	//type and the value
	_IdDataType varietyID;
	VarietyType varType;
	std::string varValue;
	std::string varName;
};

