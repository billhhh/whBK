/* 
* 
* function: 项目属性全局变量
* 
* Date:2016-01-27
* 
*    Author: Bill Wang
*/

#ifndef _LOGIC_PRJ_PROPERTY_GLOBAL_H_
#define _LOGIC_PRJ_PROPERTY_GLOBAL_H_

#include <string>

enum VarietyType{  //变量类型
	Text = 0,          //文本
	Numeric,       //数字 
	Boolean,       //逻辑
	NumericArray,  //数字阵列
	BooleanArray   //逻辑阵列
};

typedef struct
{
	VarietyType type;
	std::string name;
}VarProperty;

#endif
