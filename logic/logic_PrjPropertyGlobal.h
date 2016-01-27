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
	TEXT = 0,          //文本
	NUM,       //数字
	BOOL,       //逻辑
	NUM_ARR,  //数字阵列
	BOOL_ARR   //逻辑阵列
};

typedef struct
{
	VarietyType type;
	std::string name;
}VarProperty;

#endif
