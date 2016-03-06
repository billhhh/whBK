/* 
* 
* function: 逻辑层我的模块program类实现
* 
* Date:2015-09-02
* 
*    Author: Bill Wang
*/

#include "logic_MyBlocksProgram.h"

logic_MyBlocksProgram::logic_MyBlocksProgram(int id, std::string prog_name
											 ,std::map <int, logic_BasicModule *> init_map //初始化模块map
											 ,std::vector <logic_BasicPara *> plist //输入输出列表
											 ,std::map <int, logic_BasicModule *> module_map //传入module_map
											 ,logic_Tree *tree //传入树结构
											 )
	:logic_Program(id,prog_name,init_map) {

		//分配输入输出参数模块   //开始模块+传入模块

}
