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
#include "logic_Global.h"
#include <map>

class logic_MyBlocksModule
	: public logic_BasicModule
{
public:
	int mvi_MyBlockProgID; //属于哪个program，是program的ID

	logic_MyBlocksModule();
	explicit logic_MyBlocksModule(int mbprog_id);
	~logic_MyBlocksModule();

protected:

private:

};

#endif // !_BASIC_MODULE_H_

