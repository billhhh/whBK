/* 
* 
* function: 逻辑层我的模块program
* 
* Date:2015-09-02
* 
*    Author: Bill Wang
*/

#ifndef _LOGIC_MY_BLOCKS_PROGRAM_H_
#define _LOGIC_MY_BLOCKS_PROGRAM_H_

#include "logic_Program.h"
#include "logic_BasicModule.h"
//#include "logic_BasicPara.h"

class logic_MyBlocksProgram
	: public logic_Program
{
public:
	//std::vector <logic_BasicPara *> mvvu_ParaList; //我的模块参数列表（包括输入输出）
	logic_BasicModule InputModule; //输入参数模块
	logic_BasicModule OutputModule; //输出参数模块

protected:

private:

};


#endif
