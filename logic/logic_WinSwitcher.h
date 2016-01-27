/* 
* 
* function: 端口选择器实体
* 
* Date:2015-9-1
* 
*    Author: Bill Wang
*/

#ifndef _LOGIC_WIN_SWITHCER_H_
#define _LOGIC_WIN_SWITHCER_H_

#include <string>
#include <vector>

//端口选择器类型
enum WinSwitcherType{
	WS_NONE = 0,
	WS_NAME,
	WS_PORT_SINGLE,//单端口
	WS_PORT_DOUBLE,//双端口
	WS_VALUE_TEXT,//值 文本
	WS_VALUE_INT,//值 数字 整型
	WS_VALUE_DOUBLE,//值 数字 浮点型
	WS_VALUE_BOOL,//值 逻辑
	WS_FILE_PATH, //文件路径
	WS_INPORT //端口输入
};

class WinSwitcher
{
public:
	WinSwitcherType mve_WSType;
	std::string mvs_WSValue;
	int mvi_ChainLayer; //菊链层号

	std::vector<int ,std::string > mvvu_PopUp;

protected:
private:
};

#endif
