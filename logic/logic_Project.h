/* 
* 
* function: 逻辑层 project 类
* 
* Date:2015-09-04
* 
*    Author: Bill Wang
*/

#ifndef _LOGIC_PROJECT_H_
#define _LOGIC_PROJECT_H_

#include <map>
#include <string>
#include <stdlib.h>
#include "logic_Program.h"
#include "logic_VarModule.h"
#include "logic_BasicModule.h"
#include "logic_Graph.h"

class logic_Project
{
public:
	explicit logic_Project(int id,std::string name);
	explicit logic_Project(int id,std::string name,std::map <int, logic_BasicModule *> imap);
	~logic_Project();


	//set and get
	int getPrjId();//project id 生成就无法改变
	void setPrjId(int id);

	void setPrjName(const std::string name);
	std::string getPrjName();

	void setPrjDescription(const std::string description);
	std::string getPrjDescription();

	void setPrjPhotoPath(const std::string path);
	std::string getPrjPhotoPath();

	void setPrjVariety(const _IdDataType, logic_VarModule*);
	std::map<_IdDataType ,logic_VarModule*> getPrjVariety();

	//新增program
	int newProgram(); //重载新建program，完全自动化新建program，返回新建program ID
	void newProgram(int id,std::string name); //重载新建program，只用传入program ID 和 name
	void newProgram(int id,logic_Program* program);
	logic_Program* getProgram(int id);

	//获得最大 ProgID，方便累计
	int getMaxProgId();
	int getProgMaxModuleId(int prog_id);

	std::string getPrjPhotoDscrpt(); // 【XmlIO】
	std::map <int ,logic_Program* > getAllProgram();  //【XmlIO】

	//初始化 initModule，init_m_map是副本
	void setInitModuleMap(std::map <int, logic_BasicModule *> init_m_map);

	///
	/// \brief 方便xml
	///
	void setProgram(std::map <int ,logic_Program* > programMap);
	void setPrjVarietyMap(std::map<_IdDataType ,logic_VarModule*>);

	/////////////////////////////////////////////////////////

private:
	/**************变量名称表和循环名称表*****************/
	int mvstr_PrjId;              // project ID
	std::string mvstr_PrjName;    // project name
	std::string mvstr_PrjDescription;
	std::string mvstr_PhotoPath;

	//program map
	std::map <int, logic_Program *> mvvu_ProgMap;
	//变量（整个prj通用） my virable and its type
	std::map<_IdDataType ,logic_VarModule*> mvmu_PrjVariety;

	//!!!!!!!init module map，保存所有的初始化 Module 指针 map 副本!!!!!!!
	///
	/// \brief load from xml which is on the disk
	///
	std::map <int, logic_BasicModule *> initModuleMap;

	std::map<int, logic_Graph *> graghMap;

//工具private函数
private:
	void Init();
	void prj_Destroy();

	std::string whIntToString(int i);
	std::string genNewProgName(int id); //生成新 prj 的名字

};

#endif
