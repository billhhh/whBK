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
#include "logic_XmlIO.h"

logic_Controller::logic_Controller() {
	Init();
}

void logic_Controller::Init() {
	//��ʼ�� Global
	prjMap.clear();
	//prjMap[0] = NULL;

 	curPrjId=0;
 	curProgId=0;

	//��ʼ�� init Module map
	this->initModuleMapFunc();

}

int logic_Controller::ctrlNewPrj() {

	int max_prj_id = this->getMaxPrjId(); //��õ�ǰ��� prj �� ID
	max_prj_id++; //�� prj ID

	//logic_Project * tprj = new logic_Project(max_prj_id,genNewPrjName(max_prj_id));
	logic_Project * tprj = new logic_Project(max_prj_id,genNewPrjName(max_prj_id),this->mvmu_InitModuleMap);
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

	if( !curPrjId )
		assert(false);

	logic_Project * tCurPrj = prjMap[curPrjId];
	curProgId = tCurPrj->newProgram();

	return curProgId;
}

int logic_Controller::getMaxPrjId() {

	if( prjMap.size() == 0 )
		return 0;

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

	if( !curPrjId )
		assert(false);

	logic_Project * tCurPrj = prjMap[curPrjId];
	assert( NULL != tCurPrj->getProgram(id) );

	curProgId = id;
}

//�õ���ǰ��prjId
int  logic_Controller::ctrlGetCurPrj()
{
	return curPrjId;
}
//�ڵ�ǰ prj �� prog �£������ module id�����ۼ�
int logic_Controller::ctrlNewModuleAddId() {

	if( !curPrjId || !curProgId )
		assert(false);

	logic_Project * tCurPrj = prjMap[curPrjId];
	int res = tCurPrj->getProgMaxModuleId(curProgId);
	res++;

	return res;
}

//����progNameɾ����program
bool logic_Controller::ctrlDeleteProgram(const std::string progName)
{
	if( !curPrjId )
		assert(false);

	logic_Project * tCurPrj = prjMap[curPrjId];
	return tCurPrj->deleteProgram(progName);

}

//����progPath����program
bool logic_Controller::ctrlImportProgram(const std::string progPath)
{
	if( !curPrjId )
		assert(false);

	logic_Project* tCurPrj = prjMap[curPrjId];

	return tCurPrj->importProgram(progPath);
}

//����progPath,��programID��program�ļ�
bool logic_Controller::ctrlExportProgram(const std::string progPath, int progId)
{
	if( !curPrjId )
		assert(false);

	logic_Project* tCurPrj = prjMap[curPrjId];
	auto prjMap = tCurPrj->getAllProgram();
	if (prjMap.count(progId) < 0)
	{
		assert(prjMap.count(progId));
		return false;
	}
	auto program = prjMap[progId];

	logic_XmlIO IOControl;
	return IOControl.I0_ExportProgram(progPath,*program);

}

//������Ŀ������program����
std::vector<std::string> logic_Controller::ctrlGetProgName(int prjID)
{
	std::vector<std::string> allProgName;

	if (prjMap.count(prjID) <= 0)  //���prjID������
		return allProgName;
	else
	{
		logic_Project * tCurPrj = prjMap[prjID];
		auto progMap = tCurPrj->getAllProgram();
		for (auto progIndex : progMap)
		{
			auto prog = progIndex.second;
			std::string progName = prog->getName();
			allProgName.push_back(progName);
		}
		return allProgName;
	}
}

//������Ŀ�����б������Զ���ı����ṹ��
std::vector<VarProperty> logic_Controller::ctrlGetVariety(int prjID)
{
	std::vector<VarProperty> allVariety;

	if (prjMap.count(prjID) <= 0)  //���prjID������
		return allVariety;
	else
	{
		logic_Project * tCurPrj = prjMap[prjID];
		auto varietyMap = tCurPrj->getPrjVariety();
		for (auto varIndex : varietyMap)
		{
			VarProperty var;
			auto variety = varIndex.second;
			var.type = variety->getVarietyType(); 
			var.name = variety->getName();
		}
		return allVariety;
	}
}

//copyһ��program�����ҷ����µ�program name
std::string logic_Controller::ctrlCopyProgram(const std::string progName)
{
	if( !curPrjId )
		assert(false);

	logic_Project * tCurPrj = prjMap[curPrjId];
	return tCurPrj->copyProgram(progName);
}


//���ģ�飬����ǰ��id�����ǰ��Ϊ0�������½���
bool logic_Controller::ctrlAppendModule(int pre_id,int m_type) {

	if( !curPrjId || !curProgId )
		assert(false);

	logic_Project * tCurPrj = prjMap[curPrjId];
	logic_Program * tCurProg = tCurPrj->getProgram(curProgId);

	int max_module_id = tCurProg->getMaxModuleId();
	max_module_id++;

	bool flag = tCurProg->appendModule(max_module_id,pre_id,m_type);
	
	return flag;
}

//ǰ��ģ�飬�������½���ʱ����
bool logic_Controller::ctrlFrontInsModule(int post_id,int m_type) {

	if( !curPrjId || !curProgId )
		assert(false);

	assert(post_id); //post_id ����Ϊ 0

	logic_Project * tCurPrj = prjMap[curPrjId];
	logic_Program * tCurProg = tCurPrj->getProgram(curProgId);

	int max_module_id = tCurProg->getMaxModuleId();
	max_module_id++;

	bool flag = tCurProg->frontInsModule(max_module_id,post_id,m_type);

	return flag;
}

bool logic_Controller::ctrlAddLeafModule(int pre_id,int m_id) {

	if( !curPrjId || !curProgId )
		assert(false);

	assert(pre_id); //pre_id ����Ϊ 0

	logic_Project * tCurPrj = prjMap[curPrjId];
	logic_Program * tCurProg = tCurPrj->getProgram(curProgId);

	bool flag = tCurProg->addLeafModule(pre_id,m_id);

	return flag;

}

// get ����prj map������xml�־û���
std::map <int ,logic_Project* > logic_Controller::getAllPrj() {

	return prjMap;
}

//get ��ǰprj
int logic_Controller::getCurPrjId()
{
	return curPrjId;
}



//ɾ��ģ��
bool logic_Controller::ctrlDelModule(int m_id) {

	if( !curPrjId || !curProgId )
		assert(false);

	logic_Project * tCurPrj = prjMap[curPrjId];
	logic_Program * tCurProg = tCurPrj->getProgram(curProgId);

	return tCurProg->delModule(m_id);
}

//��ѯģ��ǰ��id
int logic_Controller::ctrlGetPreId(int m_id) {

	if( !curPrjId || !curProgId )
		assert(false);

	logic_Project * tCurPrj = prjMap[curPrjId];
	logic_Program * tCurProg = tCurPrj->getProgram(curProgId);

	return tCurProg->getModulePreId(m_id);
}

//��ѯģ����id��
std::vector<int > logic_Controller::ctrlGetPostId(int m_id) {

	if( !curPrjId || !curProgId )
		assert(false);

	logic_Project * tCurPrj = prjMap[curPrjId];
	logic_Program * tCurProg = tCurPrj->getProgram(curProgId);

	return tCurProg->getModulePostId(m_id);

}

//��ѯm_id���������ĸ��ڵ��ģ��id
int logic_Controller::ctrlGetRootModuleId(int m_id)
{
	if( !curPrjId || !curProgId )
		assert(false);

	logic_Project * tCurPrj = prjMap[curPrjId];
	logic_Program * tCurProg = tCurPrj->getProgram(curProgId);

	return tCurProg->getRootModuleId(m_id);
}

//��ѯ����module�Ƿ���ͬһ������
bool logic_Controller::ctrlIsInSameTree(int cur_m_id, int other_m_id){

	if( !curPrjId || !curProgId )
		assert(false);

	logic_Project * tCurPrj = prjMap[curPrjId];
	logic_Program * tCurProg = tCurPrj->getProgram(curProgId);

	return tCurProg->IsInSameTree(cur_m_id, other_m_id);
}

//��ѯforģ���ڲ��ĺ��ģ��
std::vector<int > logic_Controller::ctrlGetForPostId(int for_m_id)
{
	if( !curPrjId || !curProgId )
		assert(false);

	logic_Project * tCurPrj = prjMap[curPrjId];
	logic_Program * tCurProg = tCurPrj->getProgram(curProgId);

	return tCurProg->getForModuleRootPostId(for_m_id);
}

//��ѯifģ���ĳ��branch�����к�̽ڵ�
std::vector<int > logic_Controller::ctrlGetIfBranchPostId(int if_id, int global_branch_id)
{
	if( !curPrjId || !curProgId )
		assert(false);

	logic_Project * tCurPrj = prjMap[curPrjId];
	logic_Program * tCurProg = tCurPrj->getProgram(curProgId);

	int local_branch_id;
	decryptBranchId(global_branch_id, if_id, local_branch_id);

	return tCurProg->getIfModuleBranchPostId(if_id, local_branch_id);
}

int logic_Controller::ctrlGetForEndPreId(int for_id)
{
	if( !curPrjId || !curProgId )
		assert(false);

	logic_Project * tCurPrj = prjMap[curPrjId];
	logic_Program * tCurProg = tCurPrj->getProgram(curProgId);

	return tCurProg->getForModuleEndPreId(for_id);
}

//��ѯifģ���ui_branch_id��-2�ڵ�ǰ��
int	logic_Controller::ctrlGetIfEndPreId(int if_id, int ui_branch_id)
{
	if( !curPrjId || !curProgId )
		assert(false);

	logic_Project * tCurPrj = prjMap[curPrjId];
	logic_Program * tCurProg = tCurPrj->getProgram(curProgId);

	int local_branch_id;
	decryptBranchId(ui_branch_id, if_id, local_branch_id);

	return tCurProg->getIfModuleEndPreId(if_id, local_branch_id);
}


std::string logic_Controller::ctrlGetParameter(int type,int m_id,int p_id) {

	if( !curPrjId || !curProgId )
		assert(false);

	logic_Project * tCurPrj = prjMap[curPrjId];
	logic_Program * tCurProg = tCurPrj->getProgram(curProgId);

	return tCurProg->getModulePara(type,m_id,p_id);
}

void logic_Controller::ctrlSetParameter(int m_id,int p_id,std::string p_value) {

	if( !curPrjId || !curProgId )
		assert(false);

	logic_Project * tCurPrj = prjMap[curPrjId];
	logic_Program * tCurProg = tCurPrj->getProgram(curProgId);

	tCurProg->setModulePara(m_id,p_id,p_value);
}

WinSwitcherType logic_Controller::ctrlGetWinSwType(int m_id,int m_modeValue) {

	if( !curPrjId || !curProgId )
		assert(false);

	logic_Project * tCurPrj = prjMap[curPrjId];
	logic_Program * tCurProg = tCurPrj->getProgram(curProgId);

	return tCurProg->getModuleWinSwType(m_id,m_modeValue);
}

std::string logic_Controller::ctrlGetWinSwValue(int m_id) {

	if( !curPrjId || !curProgId )
		assert(false);

	logic_Project * tCurPrj = prjMap[curPrjId];
	logic_Program * tCurProg = tCurPrj->getProgram(curProgId);

	return tCurProg->getModuleWinSwValue(m_id);
}

void logic_Controller::ctrlSetWinSwValue(int m_id,std::string ws_value) {

	if( !curPrjId || !curProgId )
		assert(false);

	logic_Project * tCurPrj = prjMap[curPrjId];
	logic_Program * tCurProg = tCurPrj->getProgram(curProgId);

	tCurProg->setModuleWinSwValue(m_id,ws_value);
}

int logic_Controller::ctrlGetDaisyChainValue(int m_id) {

	if( !curPrjId || !curProgId )
		assert(false);

	logic_Project * tCurPrj = prjMap[curPrjId];
	logic_Program * tCurProg = tCurPrj->getProgram(curProgId);

	return tCurProg->getModuleDaisyChainValue(m_id);
}

void logic_Controller::ctrlSetDaisyChainValue(int m_id,int chain_value) {

	if( !curPrjId || !curProgId )
		assert(false);

	logic_Project * tCurPrj = prjMap[curPrjId];
	logic_Program * tCurProg = tCurPrj->getProgram(curProgId);

	tCurProg->setModuleDaisyChainValue(m_id,chain_value);
}

std::vector<int > logic_Controller::ctrlGetParamsIds(int m_id,int mode_value) {

	if( !curPrjId || !curProgId )
		assert(false);

	logic_Project * tCurPrj = prjMap[curPrjId];
	logic_Program * tCurProg = tCurPrj->getProgram(curProgId);

	return tCurProg->getModuleParamsIds(m_id,mode_value);
}

int logic_Controller::ctrlGetModeValue(int m_id) {

	if( !curPrjId || !curProgId )
		assert(false);

	logic_Project * tCurPrj = prjMap[curPrjId];
	logic_Program * tCurProg = tCurPrj->getProgram(curProgId);

	return tCurProg->getModuleModeValue(m_id);
}

void logic_Controller::ctrlSetModeValue(int m_id,int mode_id) {

	if( !curPrjId || !curProgId )
		assert(false);

	logic_Project * tCurPrj = prjMap[curPrjId];
	logic_Program * tCurProg = tCurPrj->getProgram(curProgId);

	tCurProg->setModuleModeValue(m_id,mode_id);
}

int logic_Controller::ctrlFrontInsSingMove(int cur_m_id,int post_m_id) {

	if( !curPrjId || !curProgId )
		assert(false);

	if ( post_m_id <= 0 ) {
		return -1; //����� id ����
	}

	//ǰ�� move
	logic_Project * tCurPrj = prjMap[curPrjId];
	logic_Program * tCurProg = tCurPrj->getProgram(curProgId);

	return tCurProg->frontInsSingMove(cur_m_id,post_m_id);
}

int logic_Controller::ctrlBackInsSingMove(int cur_m_id,int pre_m_id) {

	if( !curPrjId || !curProgId )
		assert(false);

	//��� move ��append
	//////!!!!! pre_m_id ����Ϊ0�����Ƶ�һ��������

	logic_Project * tCurPrj = prjMap[curPrjId];
	logic_Program * tCurProg = tCurPrj->getProgram(curProgId);

	return tCurProg->backInsSingMove(cur_m_id,pre_m_id);
}

//������ǰ�� move
int logic_Controller::ctrlFrontInsMultiMove(int cur_m_id,int post_m_id) {

	if( !curPrjId || !curProgId )
		assert(false);

	if ( post_m_id < 0 ) { //����Ϊ0
		assert(false); //����� id ����
	}

	//ǰ�� move
	logic_Project * tCurPrj = prjMap[curPrjId];
	logic_Program * tCurProg = tCurPrj->getProgram(curProgId);

	return tCurProg->frontInsMultiMove(cur_m_id,post_m_id);
}

//�����Ӻ�� move
int logic_Controller::ctrlBackInsMultiMove(int cur_m_id,int pre_m_id) {

	if( !curPrjId || !curProgId )
		assert(false);

	//��� move ��append
	//////!!!!! pre_m_id ����Ϊ0�����������ӣ��Ƶ�һ��������

	logic_Project * tCurPrj = prjMap[curPrjId];
	logic_Program * tCurProg = tCurPrj->getProgram(curProgId);

	return tCurProg->backInsMultiMove(cur_m_id,pre_m_id);
}

//��������move
int logic_Controller::ctrlAddLeafMove(int cur_m_id,int pre_m_id) {

	if( !curPrjId || !curProgId )
		assert(false);

	logic_Project * tCurPrj = prjMap[curPrjId];
	logic_Program * tCurProg = tCurPrj->getProgram(curProgId);

	return tCurProg->addLeafMove(cur_m_id,pre_m_id);
}


///
/// \brief for��if����
///        ע�⣺ui_branch_id��Ҫ���߼���ϳɺͷֿ�
/// \para ���붼��ui_branch_id�������������һ������������ȷ��branch_id
///

//insert into for
bool logic_Controller::ctrlInsertModule_For(int pre_id,bool isFI,int m_type,int for_id) {

	if( !curPrjId || !curProgId )
		assert(false);

	///���ô˺����Ĳ����д������� m_id ��ǰ��id���ұ�ȻΪ0
	if ( pre_id > 0 ) {

		//Ϊ0���·���for
		//Ϊ-1���²���activeTree
		assert(false);
		return false;
	}

	if ( false != isFI) //���벻��ǰ�壨���Ǻ�壩���������
		return false;

	logic_Project * tCurPrj = prjMap[curPrjId];
	logic_Program * tCurProg = tCurPrj->getProgram(curProgId);

	int max_module_id = tCurProg->getMaxModuleId();
	max_module_id++;

	bool flag = tCurProg->insertModuleIntoFor(max_module_id,pre_id,m_type,for_id); //��������һ�㽫��id����for

	return flag; //���سɹ�����־
}

//insert into if
bool logic_Controller::ctrlInsertModule_If(int pre_id,bool isFI,int m_type,int if_id,int ui_branch_id) {

	if( !curPrjId || !curProgId )
		assert(false);

	///���ô˺����Ĳ����д������� m_id ��ǰ��id���ұ�ȻΪ0
	if ( 0 != pre_id )
		return false;

	if ( false != isFI) //���벻��ǰ�壬�������
		return false;

	logic_Project * tCurPrj = prjMap[curPrjId];
	logic_Program * tCurProg = tCurPrj->getProgram(curProgId);

	int max_module_id = tCurProg->getMaxModuleId();
	max_module_id++;

	int branch_id = this->decryptBranchId(ui_branch_id);
	bool flag = tCurProg->insertModuleIntoIf(max_module_id,pre_id,m_type,if_id,branch_id); //��������һ�㽫��id����if

	return flag; //���سɹ�����־
}

// get for ��ǰ������
int logic_Controller::ctrlGetForActiveTree(int for_id) {

	if( !curPrjId || !curProgId )
		assert(false);

	logic_Project * tCurPrj = prjMap[curPrjId];
	logic_Program * tCurProg = tCurPrj->getProgram(curProgId);

	return tCurProg->getForActiveTree(for_id);
}

//if
int logic_Controller::ctrlGetIfActiveTree(int if_id,int ui_branch_id) {

	if( !curPrjId || !curProgId )
		assert(false);

	logic_Project * tCurPrj = prjMap[curPrjId];
	logic_Program * tCurProg = tCurPrj->getProgram(curProgId);

	int branch_id = this->decryptBranchId(ui_branch_id);
	return tCurProg->getIfActiveTree(if_id,branch_id);
}

// set for ��ǰ������
void logic_Controller::ctrlSetForActiveTree(int for_id,int tree_id) {

	if( !curPrjId || !curProgId )
		assert(false);

	logic_Project * tCurPrj = prjMap[curPrjId];
	logic_Program * tCurProg = tCurPrj->getProgram(curProgId);

	tCurProg->setForActiveTree(for_id,tree_id);
}

//if
void logic_Controller::ctrlSetIfActiveTree(int if_id,int ui_branch_id,int tree_id) {

	if( !curPrjId || !curProgId )
		assert(false);

	logic_Project * tCurPrj = prjMap[curPrjId];
	logic_Program * tCurProg = tCurPrj->getProgram(curProgId);

	int branch_id = this->decryptBranchId(ui_branch_id);
	tCurProg->setIfActiveTree(if_id,branch_id,tree_id);
}

//get ָ�� branch��int content
int logic_Controller::ctrlGetIfBranchContentInt(int if_id,int ui_branch_id) {

	if( !curPrjId || !curProgId )
		assert(false);

	logic_Project * tCurPrj = prjMap[curPrjId];
	logic_Program * tCurProg = tCurPrj->getProgram(curProgId);

	int branch_id = this->decryptBranchId(ui_branch_id);
	return tCurProg->getIfBranchContentInt(if_id,branch_id);
}

//string
std::string logic_Controller::ctrlGetIfBranchContentStr(int if_id,int ui_branch_id) {

	if( !curPrjId || !curProgId )
		assert(false);

	logic_Project * tCurPrj = prjMap[curPrjId];
	logic_Program * tCurProg = tCurPrj->getProgram(curProgId);

	int branch_id = this->decryptBranchId(ui_branch_id);
	return tCurProg->getIfBranchContentStr(if_id,branch_id);
}

int logic_Controller::ctrlSetIfBranchContent(int if_id,int ui_branch_id,int con_int) {

	if( !curPrjId || !curProgId )
		assert(false);

	logic_Project * tCurPrj = prjMap[curPrjId];
	logic_Program * tCurProg = tCurPrj->getProgram(curProgId);

	int branch_id = this->decryptBranchId(ui_branch_id);
	return tCurProg->setIfBranchContent(if_id,branch_id,con_int);
}

//���� string
int logic_Controller::ctrlSetIfBranchContent(int if_id,int ui_branch_id,std::string con_str) {

	if( !curPrjId || !curProgId )
		assert(false);

	logic_Project * tCurPrj = prjMap[curPrjId];
	logic_Program * tCurProg = tCurPrj->getProgram(curProgId);

	int branch_id = this->decryptBranchId(ui_branch_id);
	return tCurProg->setIfBranchContent(if_id,branch_id,con_str);
}

//��ɾ if ��֧
int logic_Controller::ctrlAddIfBranch(int if_id) {

	if( !curPrjId || !curProgId )
		assert(false);

	logic_Project * tCurPrj = prjMap[curPrjId];
	logic_Program * tCurProg = tCurPrj->getProgram(curProgId);

	int newBranchId = tCurProg->addIfBranch(if_id);
	int ui_branch_id = encryptBranchId(if_id,newBranchId);

	return ui_branch_id;
}

//�ѵ㣬��Ҫɾ����֧��������
int logic_Controller::ctrlDelIfBranch(int if_id,int ui_branch_id) {

	if( !curPrjId || !curProgId )
		assert(false);

	logic_Project * tCurPrj = prjMap[curPrjId];
	logic_Program * tCurProg = tCurPrj->getProgram(curProgId);

	int branch_id = this->decryptBranchId(ui_branch_id);
	return tCurProg->delIfBranch(if_id,branch_id);
}

/// \brief ģ���������
int logic_Controller::ctrlParaConnect(int out_m_id,int out_para_id,int in_m_id,int in_para_id) {

	if( !curPrjId || !curProgId )
		assert(false);

	logic_Project * tCurPrj = prjMap[curPrjId];
	logic_Program * tCurProg = tCurPrj->getProgram(curProgId);

	return tCurProg->paraConnect(out_m_id,out_para_id,in_m_id,in_para_id);
}

//ȡ�����ߣ���ͨ�� isOut ����outModule����inModuleɾ��
void logic_Controller::ctrlOutParaDisconnect(int out_m_id,int out_para_id) {

	if( !curPrjId || !curProgId )
		assert(false);

	logic_Project * tCurPrj = prjMap[curPrjId];
	logic_Program * tCurProg = tCurPrj->getProgram(curProgId);

	tCurProg->outParaDisconnect(out_m_id,out_para_id);
}

void logic_Controller::ctrlInParaDisconnect(int in_m_id,int in_para_id) {

	if( !curPrjId || !curProgId )
		assert(false);

	logic_Project * tCurPrj = prjMap[curPrjId];
	logic_Program * tCurProg = tCurPrj->getProgram(curProgId);

	tCurProg->inParaDisconnect(in_m_id,in_para_id);
}

///
/// \brief �ӽ��� ui_branch_id
///

//���� ���ؼ��ܺ�id
int logic_Controller::encryptBranchId(int if_id,int branch_id) {

	//��һ��32λ unsigned �����ֳɣ�
	///��16λ��moduleId����15λ��branchId������λ������������Ϊ����
	int ui_branch_id = if_id<<15;
	ui_branch_id += branch_id;

	assert( ui_branch_id > 0 );

	return ui_branch_id;
}

//����
void logic_Controller::decryptBranchId(int ui_branch_id,int &if_id,int &branch_id) {

	assert( ui_branch_id > 0 );

	if( ui_branch_id < 0x7FFF )
		return ; //�����û�и�λ

	//��16λ�ȷֳ���
	if_id = ui_branch_id >> 15;
	branch_id = ui_branch_id & 0x7FFF; //Ĩȥ��λ
}

//����
int logic_Controller::decryptBranchId(int ui_branch_id) {

	assert( ui_branch_id > 0 );

	if( ui_branch_id < 0x7FFF )
		return ui_branch_id; //�����û�и�λ

	int branch_id = ui_branch_id & 0x7FFF; //Ĩȥ��λ
	return branch_id;
}

///
/// \brief for��if��move����
///
/// \para move_type
///       case 0:��ģ��ֱ�Ӻ�� move����һ��ģ���һ�����ƶ�����һ������
///       case 1:��ģ��ֱ��ǰ��
///       case 2:�����Ӻ�� move�������ߣ�ֻ�ܽ�������ĳ��Ҷ�ӽڵ㣩
///       case 3:������ǰ�� move��ǰ���ߣ�ֻ�ܽ���һ����root����ԭroot����Ϊ��ʼģ�飩
int logic_Controller::ctrlMoveModuleFor(int cur_m_id,int other_m_id,int move_type,int for_id) {

	if( !curPrjId || !curProgId )
		assert(false);

	logic_Project * tCurPrj = prjMap[curPrjId];
	logic_Program * tCurProg = tCurPrj->getProgram(curProgId);

	if( -1 == other_m_id ) {

		//����ǽӵ�activeTree�ĺ���
		assert( 0 == move_type || 4 == move_type ); //����Ϊ0

		if( 0 == move_type )
			return tCurProg->appendActiveTreeMoveFor(cur_m_id,for_id);

		else if( 4 == move_type ) //ֱ����һ��Ҷ��
			return tCurProg->addLeafActiveTreeMoveFor(cur_m_id,for_id);

	}else {

		//�������ͨmove
		if ( 0 == move_type) //��ģ���� move
			return tCurProg->backInsSingMoveFor(cur_m_id,other_m_id,for_id);

		else if( 1 == move_type) //��ģ��ǰ�� move
			return tCurProg->frontInsSingMoveFor(cur_m_id,other_m_id,for_id);

		else if( 2 == move_type) //�����Ӻ�� move
			return tCurProg->backInsMultiMoveFor(cur_m_id,other_m_id,for_id);

		else if( 3 == move_type) //������ǰ�� move
			return tCurProg->frontInsMultiMoveFor(cur_m_id,other_m_id,for_id);

		else if( 4 == move_type ) //����Ҷ�� move��ֱ�����ߣ�
			return tCurProg->addLeafMoveFor(cur_m_id,other_m_id,for_id);
	}
}

int logic_Controller::ctrlMoveModuleIf(int cur_m_id,int other_m_id,int move_type,int if_id,int ui_branch_id) {

	if( !curPrjId || !curProgId )
		assert(false);

	logic_Project * tCurPrj = prjMap[curPrjId];
	logic_Program * tCurProg = tCurPrj->getProgram(curProgId);

	int branch_id = this->decryptBranchId(ui_branch_id);
	if( -1 == other_m_id ) {

		//����ǽӵ�activeTree�ĺ���
		assert( 0 == move_type || 4 == move_type ); //����Ϊ0

		if( 0 == move_type )
			return tCurProg->appendActiveTreeMoveIf(cur_m_id,if_id,branch_id);

		else if( 4 == move_type ) //ֱ����һ��Ҷ��
			return tCurProg->addLeafActiveTreeMoveIf(cur_m_id,if_id,branch_id);

	}else {

		//�������ͨmove
		if ( 0 == move_type) //��ģ���� move
			return tCurProg->backInsSingMoveIf(cur_m_id,other_m_id,if_id,branch_id);

		else if( 1 == move_type) //��ģ��ǰ�� move
			return tCurProg->frontInsSingMoveIf(cur_m_id,other_m_id,if_id,branch_id);

		else if( 2 == move_type) //�����Ӻ�� move
			return tCurProg->backInsMultiMoveIf(cur_m_id,other_m_id,if_id,branch_id);

		else if( 3 == move_type) //������ǰ�� move
			return tCurProg->frontInsMultiMoveIf(cur_m_id,other_m_id,if_id,branch_id);

		else if( 4 == move_type ) //����Ҷ�� move��ֱ�����ߣ�
			return tCurProg->addLeafMoveIf(cur_m_id,other_m_id,if_id,branch_id);
	}
}

///init module map����
void logic_Controller::initModuleMapFunc() {

	//�˴�Ӧ���־û�xml������������ԭʼ�� mvmu_InitModuleMap

	logic_XmlIO io;
	io.IO_Initial(this->mvmu_InitModuleMap);
}

///
/// \brief ��ȡ���ڵ�
/// \para ������ţ������0����ȡ�����root����
/// \return ���ڵ㼯��
///
std::vector<int > logic_Controller::ctrlFindRootsInContainer(int containerId) {

	if( !curPrjId || !curProgId )
		assert(false);

	logic_Project * tCurPrj = prjMap[curPrjId];
	logic_Program * tCurProg = tCurPrj->getProgram(curProgId);

	if( 0 == containerId ) //�󻭲�
		return tCurProg->findRootsInContainer();
	else if( containerId < 0x7FFF ) //for
		return tCurProg->findRootsInContainer(containerId);
	else {

		int if_id;
		int branch_id;
		decryptBranchId(containerId,if_id,branch_id);
		return tCurProg->findRootsInContainer(if_id,branch_id);
	}
}

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!�־û�����!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
bool logic_Controller::ctrlSaveCurProject()
{
	if( !curPrjId || !curProgId )
		assert(false);

	logic_Project * tCurPrj = prjMap[curPrjId];
	auto fileName = tCurPrj->getPrjName();

	if(fileName == "")
	{
		//���ô����޷��Կյ�ַ�洢
		assert(false);
		return false;
	}
	logic_XmlIO IOControl ;

	return IOControl.IO_SavePrj(fileName, *tCurPrj);
}


bool logic_Controller::ctrlSaveProject(const std::string fileName, int prjId)
{
	if( !curPrjId || !curProgId )
		assert(false);

	logic_Project * tCurPrj = prjMap[curPrjId];
	logic_XmlIO IOControl ;

	return IOControl.IO_SavePrj(fileName, *tCurPrj);
}


bool logic_Controller::ctrlLoadProject(const std::string fileName)
{
	logic_XmlIO* IOControl = new logic_XmlIO();
	auto newPrjId = ctrlNewPrj();
	auto newPrj = prjMap[newPrjId];

	return IOControl->IO_FillPrj(fileName, *newPrj);
}

logic_Program* logic_Controller::ctrlGetCurProgram()
{
	if( !curPrjId || !curProgId )
		assert(false);

	logic_Project * tCurPrj = prjMap[curPrjId];
	logic_Program * tCurProg = tCurPrj->getProgram(curProgId);

	return tCurProg;
}



std::map <int, logic_BasicModule *> logic_Controller::ctrlGetInitMap() {
	return this->mvmu_InitModuleMap;
}

void logic_Controller::debug_displayTree(logic_Project* prj)
{
	std::map <int, logic_Program *> progMap = prj->getAllProgram();
	for(auto prgMapIndex:progMap)
	{
		auto prg = prgMapIndex.second;
		std::cout<<"This is program "<<prg->getID()<<std::endl;
		auto prgTreeMap = prg->getTreeMap();
		for(auto treeIndex : prgTreeMap)
		{
			//if(treeIndex==*(prgTreeMap.begin()))
			//	continue;
			logic_Tree* tree = treeIndex.second;
			logic_TreeNode* rootNode = tree->getRoot();
			std::cout<<"This is tree "<<tree->getRoot()->getID()<<std::endl;
			debug_displayTreeUtility(rootNode);
			std::cout<<"---------------------"<<std::endl;
		}
		std::cout<<"------------------------------------------"<<std::endl;
	}

}


void logic_Controller::debug_displayTreeUtility(logic_TreeNode* node)
{
	std::queue<logic_TreeNode*> nodeQueue1,nodeQueue2;
	nodeQueue1.push(node);
	while (!nodeQueue1.empty()||!nodeQueue2.empty())
	{
		while (!nodeQueue1.empty())
		{
			node = nodeQueue1.front();
			std::cout << node->getID() << "��";
			nodeQueue1.pop();
			auto children = node->mvvu_Children;
			if (!children.empty())
			{
				for (auto index : children)
				{
					if (index != *(children.end()-1))
					{
						std::cout << index->getID() << ",";
						nodeQueue2.push(index);
					}
					else
					{
						std::cout << index->getID();
						nodeQueue2.push(index);
					}
				}
				
			}
			std::cout << "��   ";
		}
		if(nodeQueue1.empty())
			std::cout << std::endl;
		while(!nodeQueue2.empty())
		{
			node = nodeQueue2.front();
			std::cout << node->getID() << "��";
			nodeQueue2.pop();
			auto children = node->mvvu_Children;
			if (!children.empty())
			{
				for (auto index : children)
				{
					if (index != *(children.end() - 1))
					{
						std::cout << index->getID() << ",";
						nodeQueue1.push(index);
					}
					else
					{
						std::cout << index->getID();
						nodeQueue1.push(index);
					}
				}

			}
			std::cout << "��   ";
		}
		if(nodeQueue2.empty())
			std::cout << std::endl;
	}
}

///
/// \brief �ҵ�ģ��
///
//session1���Ƿ���Դ����ҵ�ģ�飬ǰ��˵�һ�λỰ
//�ӿڴ�id�б������Ƿ�ɴ���
int logic_Controller::ctrlCanMyBlocks(std::vector<int > ids) {

	if( !curPrjId || !curProgId )
		assert(false);

	assert( ids.size() > 0 );

	logic_Project * tCurPrj = prjMap[curPrjId];
	logic_Program * tCurProg = tCurPrj->getProgram(curProgId);

	return tCurProg->canMyBlocks(ids);
}

// get\set��ǰprogram����
std::string logic_Controller::ctrlGetCurProgName() {

	if( !curPrjId || !curProgId )
		assert(false);

	logic_Project * tCurPrj = prjMap[curPrjId];
	logic_Program * tCurProg = tCurPrj->getProgram(curProgId);

	return tCurProg->getName();
}

void logic_Controller::ctrlSetCurProgName(std::string name) {

	if( !curPrjId || !curProgId )
		assert(false);

	logic_Project * tCurPrj = prjMap[curPrjId];
	logic_Program * tCurProg = tCurPrj->getProgram(curProgId);

	tCurProg->setProgramName(name);
}

// get\set��ǰ��Ŀ����
std::string logic_Controller::ctrlGetCurPrjName() {

	if( !curPrjId || !curProgId )
		assert(false);

	logic_Project * tCurPrj = prjMap[curPrjId];
	return tCurPrj->getPrjName();
}

void logic_Controller::ctrlSetCurPrjName(std::string name) {

	if( !curPrjId || !curProgId )
		assert(false);

	logic_Project * tCurPrj = prjMap[curPrjId];
	tCurPrj->setPrjName(name);
}
