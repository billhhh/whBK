/* 
* 
* function: “我的模块”实体类实现
* 
* Date:2015-03-05
* 
*    Author: Bill Wang
*/

#include "logic_MyBlocksModule.h"

///
/// \brief 构造函数+析构函数
///
logic_MyBlocksModule::logic_MyBlocksModule()
	:mvi_MyBlockProg(NULL) {

}

logic_MyBlocksModule::logic_MyBlocksModule(logic_MyBlocksProgram *mbprog)
	:mvi_MyBlockProg(mbprog) {

}

logic_MyBlocksModule::~logic_MyBlocksModule() {

}
