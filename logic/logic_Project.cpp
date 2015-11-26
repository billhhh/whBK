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


logic_Project::logic_Project(int id,std::string name)
	:mvstr_PrjId(id),mvstr_PrjName(name)
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

	logic_Program * prog = new logic_Program(1,"Program");//第一个program
	mvvu_ProgMap[1] = prog;
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

std::map<_IdDataType ,logic_VarModule*> logic_Project::getPrjVariety()
{
	return mvmu_PrjVariety;
}

//重载新建program，完全自动化新建program
int logic_Project::newProgram() {
	int max_prog_id = getMaxProgId();
	max_prog_id ++;

	logic_Program * tprog = new logic_Program(max_prog_id,genNewProgName(max_prog_id));
	mvvu_ProgMap[max_prog_id] = tprog;

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
