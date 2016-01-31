/* 
* 
* function: 逻辑层基本 Module 实体类
* 
* Date:2015-09-01
* 
*    Author: Bill Wang
*/

#ifndef _LOGIC_BASIC_MODULE_H_
#define _LOGIC_BASIC_MODULE_H_

#include <string>
#include <vector>
#include "logic_BasicPara.h"
#include "logic_WinSwitcher.h"
#include "logic_ParaPointer.h"

class logic_BasicModule
{
public:
	int mvi_ModuleID;

	/////构造函数和析构函数
	explicit logic_BasicModule();//默认生成start
	explicit logic_BasicModule(int id);//默认生成start
	explicit logic_BasicModule(int id,int moduleType); //根据信息，自动填充其他信息
	////深拷贝构造函数
	explicit logic_BasicModule(int id,int moduleType,const logic_BasicModule &bm);
	virtual ~logic_BasicModule();

	/////!!! useless !!!!!!!!!!!!
	bool changeMode(int modeID,std::vector <logic_BasicPara *> & ParaReturnList); //修改模式，获取特定模式的参数列表
	bool changeParaValue(int paraID,std::string value); //修改参数值，就要修改当前代码片
	bool changeWinSwicher();
	////////////////////////////////

	logic_BasicPara* getPara(int p_id); //返回某一参数的引用
	logic_BasicPara* getInitPara(int p_id); //返回某一init参数的引用

	int getModuleType();

	WinSwitcherType getWSType(int m_modeValue);
	std::string getWSValue();
	void setWSValue(std::string ws_value);

	int getDaisyChainValue();
	void setDaisyChainValue(int chain_value);

	std::vector<int > getParamsIds(int mode_value);

	int getModeValue(); //IO 和 前台都需要
	void setModeValue(int mode_id); //设置模式选择器

	////!!!!!!!!!!!!!!!!!!!【XmlIO】!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	std::vector <logic_BasicPara*> getCurParaList(); //get 当前模式 的所有参数
	WinSwitcherType getCurWSType(); //得到当前 端口选择器 type

	void setCurParaList(std::vector <logic_BasicPara*> paraList);

	/////!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	/////合成代码
	bool generateCodeBlocks();

//protected:
	int mvi_CurModeID; //当前模式
	int mvs_ModuleType; //模块类型 方便去xml load
	std::string mvs_CurCodeBlocks; //代码片

	bool mvb_IsRun; //是否在运行中
	//bool mvb_IsConnectStart; //有没有跟开始模块相连

	//模式选择器总表，初始化load进来
	std::vector <logic_ParaPointer *> mvvu_ModeMenu;
	std::vector <logic_BasicPara *> mvvu_ParaList; //参数列表
	std::vector <std::string > mvvu_CodeBlocksList; //代码片列表---对应不同模式

	std::vector <logic_BasicPara *> mvvu_InitParaList; //init参数列表

	//当前端口选择器，包括菊链层号
	WinSwitcher mve_CurWinSwitcher;

private:
	void Init(); //负责初始化操作
	void Destroy(); //在析构时调用

};

#endif // !_BASIC_MODULE_H_

