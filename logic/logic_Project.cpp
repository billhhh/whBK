/* 
* 
* function: �߼��� project ��
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

logic_Project::logic_Project(int id,std::string name,std::map <int, logic_BasicModule *> imap)
	:mvstr_PrjId(id),mvstr_PrjName(name),initModuleMap(imap)
{
	Init();
}

logic_Project::~logic_Project()
{
	prj_Destroy();
}

//!!!!!��ʼ���ɾ���prj
void logic_Project::Init() {
	mvvu_ProgMap.clear();
	//mvvu_ProgMap[0] = NULL;
	mvmu_PrjVarietyMap.clear();
	//mvmu_PrjVariety[0] = NULL;

	logic_Program * prog = new logic_Program(1,"Program");//��һ��program
	mvvu_ProgMap[1] = prog;
}

//���ٵ�ǰprj����
void logic_Project::prj_Destroy() {
	//���mvvu_ProgMap����ȫ�ͷ�
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

void logic_Project::addPrjVariety(const _IdDataType id, VarProperty var)
{
	mvmu_PrjVarietyMap[id] = var;
}

std::map<_IdDataType ,VarProperty> logic_Project::getPrjVarietyMap()
{
	return mvmu_PrjVarietyMap;
}

//�����½�program����ȫ�Զ����½�program
int logic_Project::newProgram() {
	int max_prog_id = getMaxProgId();
	max_prog_id ++;

	//logic_Program * tprog = new logic_Program(max_prog_id,genNewProgName(max_prog_id));
	logic_Program * tprog = new logic_Program(max_prog_id,genNewProgName(max_prog_id),this->initModuleMap);
	mvvu_ProgMap[max_prog_id] = tprog;

	//��ʼ���� prog �������
	tprog->setInitVarMap(this->mvmu_PrjVarietyMap);
	tprog->setInitModuleMap(this->initModuleMap);

	return max_prog_id;
}

//����newProgram��ֻ�ô���program ID �� name
void logic_Project::newProgram(int id,std::string name) {
	logic_Program * prog = new logic_Program(id,name);
	mvvu_ProgMap[id] = prog;
}

//����newProgram
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

//��ʼ�� initModule��init_m_map�Ǹ���
void logic_Project::setInitModuleMap(std::map <int, logic_BasicModule *> init_m_map) {

	this->initModuleMap = init_m_map; //��ʼ�� ����init module����
}

//project id ���ɾ��޷��ı�
int logic_Project::getPrjId() {

	return mvstr_PrjId;
}

void logic_Project::setPrjId(int id) {

	this->mvstr_PrjId = id;
}


///
/// \brief ����xml
///
void logic_Project::setProgram(std::map <int ,logic_Program* > programMap)
{
	mvvu_ProgMap = programMap;
}

void logic_Project::setPrjVarietyMap(std::map<_IdDataType ,VarProperty> map)
{
	mvmu_PrjVarietyMap = map;
}
