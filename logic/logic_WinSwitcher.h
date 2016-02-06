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
	WS_PORT_SINGLE,//单端口（单选，变量也是这个）
	WS_PORT_DOUBLE,//双端口
	WS_VALUE_TEXT,//值 文本
	WS_VALUE_INT,//值 数字 整型
	WS_VALUE_DOUBLE,//值 数字 浮点型
	WS_VALUE_BOOL,//值 逻辑
	WS_FILE_PATH, //文件路径
	WS_INPORT //端口输入（应该根据原有Type判断输入类型是什么）
};

class WinSwitcher
{
public:
	std::string WSName; //为了鼠标放在上面的时候显示
	WinSwitcherType mve_WSType; //如果发现是“端口输入”模式，那就应该去外面找连线
	std::string mvs_WSValue;
	int mvi_ChainLayer; //菊链层号

	std::vector<std::string > mvvu_PopUp;

protected:
private:
};

#endif
