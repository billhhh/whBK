/* 
* 
* function: 逻辑层 project 类
* 
* Date:2015-09-04
* 
*    Author: Bill Wang
*/

#include "logic_Project.h"
#include "logic_Program.h"
#include <iostream> 
#include <sstream> 
#include <string>
#include <assert.h>
#include "logic_XmlIO.h"


logic_Project::logic_Project(int id,std::string name)
	:mvstr_PrjId(id),mvstr_PrjName(name)
{
	Init();
}

logic_Project::logic_Project(int id,std::string name,std::map <int, logic_BasicModule *> imap)
	:mvstr_PrjId(id),mvstr_PrjName(name),initModuleMap(imap)
{
	Init();
}

logic_Project::~logic_Project()
{
	prj_Destroy();
}

//!!!!!初始化干净的prj
void logic_Project::Init() {
	mvvu_ProgMap.clear();
	//mvvu_ProgMap[0] = NULL;
	mvmu_PrjVariety.clear();
	//mvmu_PrjVariety[0] = NULL;

	projectFilePath = "";

	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!让前端去驱动来新建program
	//logic_Program * prog = new logic_Program(1,"Program");//第一个program
	//mvvu_ProgMap[1] = prog;
}

//销毁当前prj对象
void logic_Project::prj_Destroy() {
	//清空mvvu_ProgMap，安全释放
	for(std::map<int , logic_Program *>::iterator it = mvvu_ProgMap.begin();it != mvvu_ProgMap.end(); ++it)
		SAFE_DELETE(it->second);
}

void logic_Project::setPrjName(const std::string name)
{
	mvstr_PrjName = name;
}

std::string logic_Project::getPrjName()
{
	return mvstr_PrjName;
}

void logic_Project::setPrjDescription(const std::string description)
{
	mvstr_PrjDescription = description;
}

std::string logic_Project::getPrjDescription()
{
	return mvstr_PrjDescription;
}

void logic_Project::setPrjPhotoPath(const std::string path)
{
	mvstr_PhotoPath = path;
}

std::string logic_Project::getPrjPhotoPath()
{
	return mvstr_PhotoPath;
}

void logic_Project::setPrjVariety(const _IdDataType id, logic_VarModule* varModule)
{
	mvmu_PrjVariety[id] = varModule;
}

void logic_Project::setPrjVarietyMap(std::map<_IdDataType ,logic_VarModule*> PrjVariety)
{
	mvmu_PrjVariety = PrjVariety;
}


std::map<_IdDataType ,logic_VarModule*> logic_Project::getPrjVariety()
{
	return mvmu_PrjVariety;
}

//重载新建program，完全自动化新建program
int logic_Project::newProgram() {
	int max_prog_id = getMaxProgId();
	max_prog_id ++;

	//logic_Program * tprog = new logic_Program(max_prog_id,genNewProgName(max_prog_id));
	logic_Program * tprog = new logic_Program(max_prog_id,genNewProgName(max_prog_id),this->initModuleMap);
	mvvu_ProgMap[max_prog_id] = tprog;

	//初始化新 prog 特殊参数
	tprog->setInitVarMap(this->mvmu_PrjVariety);
	tprog->setInitModuleMap(this->initModuleMap);

	return max_prog_id;
}

//重载newProgram，只用传入program ID 和 name
void logic_Project::newProgram(int id,std::string name) {
	logic_Program * prog = new logic_Program(id,name);
	mvvu_ProgMap[id] = prog;
}

//重载newProgram
void logic_Project::newProgram(int id,logic_Program* program)
{
	mvvu_ProgMap[id] = program;
}

logic_Program* logic_Project::getProgram(int id)
{
	return mvvu_ProgMap[id];
}

std::string logic_Project::copyProgram(const std::string progName)
{
	auto prgId = getProgId(progName);
	if (prgId == 0)  //如果不存在
		return "";
	
	auto program = getProgram(prgId);
	auto newProgramId = newProgram();
	auto newName = genNewProgName(newProgramId);
	auto newProgram = getProgram(newProgramId);
	//深拷贝过程
	newProgram = program->copyPrg(newProgram);

	return newName;
}

//根据progName删除该program
bool logic_Project::deleteProgram(const std::string progName)
{
	auto prgId = getProgId(progName);
	if (prgId == 0)  //如果不存在
		return false;

	auto program = getProgram(prgId);
	mvvu_ProgMap.erase(prgId);

	//还要把curProg设置为0
	

	return true;

}

//import一个program文件
void logic_Project::addProgram(logic_Program* prg)
{
	auto prgId = prg->getID();
	mvvu_ProgMap[prgId] = prg;

}

void logic_Project::setProgram(std::map <int ,logic_Program* > programMap)
{
	mvvu_ProgMap = programMap;
}



int logic_Project::getMaxProgId() {

	if( mvvu_ProgMap.size() == 0 )
		return 0;

	std::map<int, logic_Program *>::const_iterator it = mvvu_ProgMap.end();
	it--;
	return it->first;
}

std::string logic_Project::genNewProgName(int id) {
	std::string idStr = whIntToString(id);
	std::string res = "Program";
	res.append(idStr);
	return res;
}

//根据项目名得到项目ID
int logic_Project::getProgId(std::string progName)
{
	int programID = 0;
	auto progMap = getAllProgram();
	for (auto index : progMap)
	{
		auto prgName = index.second->getName();
		if (prgName == progName)
		{
			auto prgId = index.second->getID();
			return prgId;
		}
	}
	return 0;
}


std::string logic_Project::whIntToString(int aa) {
	if ( 0 == aa )
		return "";

	std::stringstream ss;
	ss<<aa;
	std::string s1 = ss.str();
	return s1;
}

int logic_Project::getProgMaxModuleId(int prog_id) {

	assert( mvvu_ProgMap.count(prog_id)>0 );
	logic_Program * tprog = mvvu_ProgMap[prog_id];
	
	return tprog->getMaxModuleId();
}

std::string logic_Project::getPrjPhotoDscrpt() {

	return NULL;
}

std::map <int ,logic_Program* > logic_Project::getAllProgram() {
	return mvvu_ProgMap;
}

//【XmlIO】 根据路径名导入一个program
bool logic_Project::importProgram(std::string progPath)
{
	logic_XmlIO* IOControl = new logic_XmlIO();
	return IOControl->IO_ImportProgram(progPath,this);
}

//初始化 initModule，init_m_map是副本
void logic_Project::setInitModuleMap(std::map <int, logic_BasicModule *> init_m_map) {

	this->initModuleMap = init_m_map; //初始化 所有init module副本
}

//project id 生成就无法改变
int logic_Project::getPrjId() {

	return mvstr_PrjId;
}

void logic_Project::setPrjId(int id) {

	this->mvstr_PrjId = id;
}

std::string logic_Project::getPrjFilePath()
{
	return projectFilePath;
}


void logic_Project::setPrjFilePath(std::string filePath)
{
	projectFilePath = filePath;
}

