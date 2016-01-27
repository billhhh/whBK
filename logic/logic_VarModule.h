/* 
* 
* function: 逻辑层变量类
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

	std::string getType();     //带有类型转换
	std::string getValue();
	std::string getID();       //带有类型转换

	//读取VarMap，写入窗口选择器
	void setVariety(std::map<int ,logic_VarModule*> vMap);

private:
	//type and the value
	VarietyType varType;
	std::string varValue;
};

