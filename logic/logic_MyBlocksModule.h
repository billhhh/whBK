/* 
* 
* function: “我的模块”实体类
* 
* Date:2015-09-08
* 
*    Author: Bill Wang
*/

#ifndef _LOGIC_MY_BLOCKS_MODULE_H_
#define _LOGIC_MY_BLOCKS_MODULE_H_

#include "logic_BasicModule.h"
#include "logic_MyBlocksProgram.h"
#include "logic_Global.h"
#include <map>
#include <string>

class logic_MyBlocksModule
	: public logic_BasicModule
{
public:
	//属于哪个program
	//int mvi_MyBlockProgID;
	logic_MyBlocksProgram *mvi_MyBlockProg;
	std::string MyBlockName;

	logic_MyBlocksModule();
	explicit logic_MyBlocksModule(logic_MyBlocksProgram *mbprog);
	~logic_MyBlocksModule();

protected:

private:

};

#endif // !_BASIC_MODULE_H_

