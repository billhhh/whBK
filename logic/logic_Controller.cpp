/* 
* 
* function: logic�㹤��������ʵ�֣���ɴ󲿷��߼���������project��һ��
* 
* Date:2015-10-21
* 
*    Author: Bill Wang
*/

#include "logic_Controller.h"
#include "logic_Project.h"
#include "logic_Program.h"
#include <iostream> 
#include <sstream> 
#include <string>
#include <assert.h>

logic_Controller::logic_Controller() {
	Init();
}

void logic_Controller::Init() {
	//��ʼ�� Global
	prjMap.clear();
	prjMap[0] = NULL;

 	curPrjId=0;
 	curProgId=0;
}

int logic_Controller::ctrlNewPrj() {

	int max_prj_id = this->getMaxPrjId(); //��õ�ǰ��� prj �� ID
	max_prj_id++; //�� prj ID

	logic_Project * tprj = new logic_Project(max_prj_id,genNewPrjName(max_prj_id));
	prjMap[max_prj_id] = tprj;

	curPrjId = max_prj_id;
	curProgId = 1;

	return curPrjId; //�½�prj��꽹����ڵ�ǰprj
}

std::string logic_Controller::genNewPrjName(int id) {
	std::string idStr = whIntToString(id);
	std::string res = "��Ŀ";
	res.append(idStr);
	return res;
}

std::string logic_Controller::whIntToString(int aa) {
	if ( 0 == aa )
		return "";

	std::stringstream ss;
	ss<<aa;
	std::string s1 = ss.str();
	return s1;
}

int logic_Controller::ctrlNewProg() {

	logic_Project * tCurPrj = prjMap[curPrjId];
	curProgId = tCurPrj->newProgram();

	return curProgId;
}

int logic_Controller::getMaxPrjId() {
	std::map<int ,logic_Project* >::const_iterator it = prjMap.end();
	it--;
	return it->first;
}

void logic_Controller::ctrlSetCurPrj(int id) {
	
	//���û����� id �� prj ֱ�ӱ���
	assert( prjMap.count(id)>0 );

	curPrjId = id;

}

void logic_Controller::ctrlSetCurProg(int id) {

	logic_Project * tCurPrj = prjMap[curPrjId];
	assert( NULL != tCurPrj->getProgram(id) );

	curProgId = id;
}

//�ڵ�ǰ prj �� prog �£������ module id�����ۼ�
int logic_Controller::ctrlNewModuleAddId() {

	logic_Project * tCurPrj = prjMap[curPrjId];
	int res = tCurPrj->getProgMaxModuleId(curProgId);
	res++;

	return res;
}

//���ģ�飬����ǰ��id�����ǰ��Ϊ0�������½���
bool logic_Controller::ctrlAppendModule(int pre_id,int m_type) {

	logic_Project * tCurPrj = prjMap[curPrjId];
	logic_Program * tCurProg = tCurPrj->getProgram(curProgId);

	int max_module_id = tCurProg->getMaxModuleId();
	max_module_id++;

	bool flag = tCurProg->appendModule(max_module_id,pre_id,m_type);
	
	return flag;
}

//ǰ��ģ�飬�������½���ʱ����
bool logic_Controller::ctrlFrontInsModule(int post_id,int m_type) {

	assert(post_id); //post_id ����Ϊ 0

	logic_Project * tCurPrj = prjMap[curPrjId];
	logic_Program * tCurProg = tCurPrj->getProgram(curProgId);

	int max_module_id = tCurProg->getMaxModuleId();
	max_module_id++;

	bool flag = tCurProg->frontInsModule(max_module_id,post_id,m_type);

	return flag;
}

bool logic_Controller::ctrlAddLeafModule(int pre_id,int m_type) {

	assert(pre_id); //pre_id ����Ϊ 0

	logic_Project * tCurPrj = prjMap[curPrjId];
	logic_Program * tCurProg = tCurPrj->getProgram(curProgId);

	int max_module_id = tCurProg->getMaxModuleId();
	max_module_id++;

	bool flag = tCurProg->addLeafModule(max_module_id,pre_id,m_type);

	return flag;

}

// get ����prj map������xml�־û���
std::map <int ,logic_Project* > logic_Controller::getAllPrj() {
	return prjMap;
}

//ɾ��ģ��
bool logic_Controller::ctrlDelModule(int m_id) {

	logic_Project * tCurPrj = prjMap[curPrjId];
	logic_Program * tCurProg = tCurPrj->getProgram(curProgId);

	return tCurProg->delModule(m_id);
}

//��ѯģ��ǰ��id
int logic_Controller::ctrlGetPreId(int m_id) {

	logic_Project * tCurPrj = prjMap[curPrjId];
	logic_Program * tCurProg = tCurPrj->getProgram(curProgId);

	return tCurProg->getModulePreId(m_id);
}

//��ѯģ����id��
std::vector<int > logic_Controller::ctrlGetPostId(int m_id) {

	logic_Project * tCurPrj = prjMap[curPrjId];
	logic_Program * tCurProg = tCurPrj->getProgram(curProgId);

	return tCurProg->getModulePostId(m_id);

}

std::string logic_Controller::ctrlGetParameter(int type,int m_id,int p_id) {

	logic_Project * tCurPrj = prjMap[curPrjId];
	logic_Program * tCurProg = tCurPrj->getProgram(curProgId);

	return tCurProg->getModulePara(type,m_id,p_id);
}

void logic_Controller::ctrlSetParameter(int m_id,int p_id,std::string p_value) {

	logic_Project * tCurPrj = prjMap[curPrjId];
	logic_Program * tCurProg = tCurPrj->getProgram(curProgId);

	tCurProg->setModulePara(m_id,p_id,p_value);
}

WinSwitcherType logic_Controller::ctrlGetWinSwType(int m_id,int m_modeValue) {

	logic_Project * tCurPrj = prjMap[curPrjId];
	logic_Program * tCurProg = tCurPrj->getProgram(curProgId);

	return tCurProg->getModuleWinSwType(m_id,m_modeValue);
}

std::string logic_Controller::ctrlGetWinSwValue(int m_id) {

	logic_Project * tCurPrj = prjMap[curPrjId];
	logic_Program * tCurProg = tCurPrj->getProgram(curProgId);

	return tCurProg->getModuleWinSwValue(m_id);
}

void logic_Controller::ctrlSetWinSwValue(int m_id,std::string ws_value) {

	logic_Project * tCurPrj = prjMap[curPrjId];
	logic_Program * tCurProg = tCurPrj->getProgram(curProgId);

	tCurProg->setModuleWinSwValue(m_id,ws_value);
}

int logic_Controller::ctrlGetDaisyChainValue(int m_id) {

	logic_Project * tCurPrj = prjMap[curPrjId];
	logic_Program * tCurProg = tCurPrj->getProgram(curProgId);

	return tCurProg->getModuleDaisyChainValue(m_id);
}

void logic_Controller::ctrlSetDaisyChainValue(int m_id,int chain_value) {

	logic_Project * tCurPrj = prjMap[curPrjId];
	logic_Program * tCurProg = tCurPrj->getProgram(curProgId);

	tCurProg->setModuleDaisyChainValue(m_id,chain_value);
}

std::vector<int > logic_Controller::ctrlGetParamsIds(int m_id,int mode_value) {

	logic_Project * tCurPrj = prjMap[curPrjId];
	logic_Program * tCurProg = tCurPrj->getProgram(curProgId);

	return tCurProg->getModuleParamsIds(m_id,mode_value);
}

int logic_Controller::ctrlGetModeValue(int m_id) {

	logic_Project * tCurPrj = prjMap[curPrjId];
	logic_Program * tCurProg = tCurPrj->getProgram(curProgId);

	return tCurProg->getModuleModeValue(m_id);
}

void logic_Controller::ctrlSetModeValue(int m_id,int mode_id) {

	logic_Project * tCurPrj = prjMap[curPrjId];
	logic_Program * tCurProg = tCurPrj->getProgram(curProgId);

	tCurProg->setModuleModeValue(m_id,mode_id);
}

int logic_Controller::ctrlFrontInsSingMove(int cur_m_id,int post_m_id) {

	if ( post_m_id <= 0 ) {
		return -1; //����� id ����
	}

	//ǰ�� move
	logic_Project * tCurPrj = prjMap[curPrjId];
	logic_Program * tCurProg = tCurPrj->getProgram(curProgId);

	return tCurProg->frontInsSingMove(cur_m_id,post_m_id);
}

int logic_Controller::ctrlBackInsSingMove(int cur_m_id,int pre_m_id) {

	//��� move ��append
	//////!!!!! pre_m_id ����Ϊ0�����Ƶ�һ��������

	logic_Project * tCurPrj = prjMap[curPrjId];
	logic_Program * tCurProg = tCurPrj->getProgram(curProgId);

	return tCurProg->backInsSingMove(cur_m_id,pre_m_id);
}

//������ǰ�� move
int logic_Controller::ctrlFrontInsMultiMove(int cur_m_id,int post_m_id) {

	if ( post_m_id <= 0 ) {
		return -1; //����� id ����
	}

	//ǰ�� move
	logic_Project * tCurPrj = prjMap[curPrjId];
	logic_Program * tCurProg = tCurPrj->getProgram(curProgId);

	return tCurProg->frontInsMultiMove(cur_m_id,post_m_id);
}

//�����Ӻ�� move
int logic_Controller::ctrlBackInsMultiMove(int cur_m_id,int pre_m_id) {

	//��� move ��append
	//////!!!!! pre_m_id ����Ϊ0�����������ӣ��Ƶ�һ��������

	logic_Project * tCurPrj = prjMap[curPrjId];
	logic_Program * tCurProg = tCurPrj->getProgram(curProgId);

	return tCurProg->backInsMultiMove(cur_m_id,pre_m_id);
}

//insert into for
bool logic_Controller::ctrlInsertModule_For(int pre_id,bool isFI,int m_type,int for_id) {

	///���ô˺����Ĳ����д������� m_id ��ǰ��id���ұ�ȻΪ0
	if ( 0 != pre_id )
		return false;

	if ( false != isFI) //���벻��ǰ�壬�������
		return false;

	logic_Project * tCurPrj = prjMap[curPrjId];
	logic_Program * tCurProg = tCurPrj->getProgram(curProgId);

	int max_module_id = tCurProg->getMaxModuleId();
	max_module_id++;

	bool flag = tCurProg->insertModuleIntoFor(max_module_id,pre_id,m_type,for_id); //��������һ�㽫��id����for

	return flag; //���سɹ�����־
}

//insert into if
bool logic_Controller::ctrlInsertModule_If(int pre_id,bool isFI,int m_type,int if_id,int branch_id) {

	///���ô˺����Ĳ����д������� m_id ��ǰ��id���ұ�ȻΪ0
	if ( 0 != pre_id )
		return false;

	if ( false != isFI) //���벻��ǰ�壬�������
		return false;

	logic_Project * tCurPrj = prjMap[curPrjId];
	logic_Program * tCurProg = tCurPrj->getProgram(curProgId);

	int max_module_id = tCurProg->getMaxModuleId();
	max_module_id++;

	bool flag = tCurProg->insertModuleIntoIf(max_module_id,pre_id,m_type,if_id,branch_id); //��������һ�㽫��id����if

	return flag; //���سɹ�����־
}

// get for ��ǰ������
int logic_Controller::ctrlGetForActiveTree(int for_id) {

	logic_Project * tCurPrj = prjMap[curPrjId];
	logic_Program * tCurProg = tCurPrj->getProgram(curProgId);

	return tCurProg->getForActiveTree(for_id);
}

//if
int logic_Controller::ctrlGetIfActiveTree(int if_id,int branch_id) {

	logic_Project * tCurPrj = prjMap[curPrjId];
	logic_Program * tCurProg = tCurPrj->getProgram(curProgId);

	return tCurProg->getIfActiveTree(if_id,branch_id);
}

// set for ��ǰ������
void logic_Controller::ctrlSetForActiveTree(int for_id,int tree_id) {

	logic_Project * tCurPrj = prjMap[curPrjId];
	logic_Program * tCurProg = tCurPrj->getProgram(curProgId);

	tCurProg->setForActiveTree(for_id,tree_id);
}

//if
void logic_Controller::ctrlSetIfActiveTree(int if_id,int branch_id,int tree_id) {

	logic_Project * tCurPrj = prjMap[curPrjId];
	logic_Program * tCurProg = tCurPrj->getProgram(curProgId);

	tCurProg->setIfActiveTree(if_id,branch_id,tree_id);
}

//get ָ�� branch��int content
int logic_Controller::ctrlGetIfBranchContentInt(int if_id,int branch_id) {

	logic_Project * tCurPrj = prjMap[curPrjId];
	logic_Program * tCurProg = tCurPrj->getProgram(curProgId);

	return tCurProg->getIfBranchContentInt(if_id,branch_id);
}

//string
std::string logic_Controller::ctrlGetIfBranchContentStr(int if_id,int branch_id) {

	logic_Project * tCurPrj = prjMap[curPrjId];
	logic_Program * tCurProg = tCurPrj->getProgram(curProgId);

	return tCurProg->getIfBranchContentStr(if_id,branch_id);
}