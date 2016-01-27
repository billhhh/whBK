/* 
* 
* function: �߼��������
* 
* Date:2015-11-05
* 
*    Author: Bill Wang
*/

#pragma once
#include "logic_BasicModule.h"
#include <map>
#include "logic_PrjPropertyGlobal.h"

class logic_VarModule :
	public logic_BasicModule
{
public:
	logic_VarModule(void);
	explicit logic_VarModule(int id,VarietyType type,const std::string value);
	~logic_VarModule(void);

	std::string getType();     //��������ת��
	std::string getValue();
	std::string getID();       //��������ת��

	//��ȡVarMap��д�봰��ѡ����
	void setVariety(std::map<int ,logic_VarModule*> vMap);

private:
	//type and the value
	VarietyType varType;
	std::string varValue;
};

