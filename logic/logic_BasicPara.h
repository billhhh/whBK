/* 
* 
* function: 参数实体类，包含一个具体的参数
* 
* Date:2015-09-01
* 
*    Author: Bill Wang
*/

#ifndef _LOGIC_BASIC_PARA_H_
#define _LOGIC_BASIC_PARA_H_

#include <string>

enum ParaIOType{
	PARA_IN = 0,
	PARA_OUT
};

enum ParaType{
	PARA_LOGIC = 0,//逻辑
	PARA_NUM, //数字
	PARA_TEXT, //文本
	PARA_MULTI, //多选
	PARA_INPORT //端口输入
};

class logic_BasicPara
{
public:
	int mvi_ParaID;
	ParaIOType mve_IOType; //in或者是out
	ParaType mve_ParaType;
	std::string mvs_Value; //参数值
	int mvd_Min;//范围值
	int mvd_Max;

	bool mvb_IsInport; //是否连线接入

	//返回参数类型
	ParaType getParaType() {
		return mve_ParaType;
	}

	//返回是输入还是输出，返回枚举类型
	ParaIOType getParaIOType() {
		return mve_IOType;
	}

	std::string getValue() {
		return mvs_Value;
	}

protected:


private:

};

#endif
