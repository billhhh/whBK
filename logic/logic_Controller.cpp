/* 
* 
* function: logic层工作控制类实现，完成大部分逻辑工作，在project上一层
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
	//初始化 Global
	prjMap.clear();
	//prjMap[0] = NULL;

 	curPrjId=0;
 	curProgId=0;

	//初始化 init Module map
	this->initModuleMapFunc();

}

int logic_Controller::ctrlNewPrj() {

	int max_prj_id = this->getMaxPrjId(); //获得当前最大 prj 的 ID
	max_prj_id++; //新 prj ID

	//logic_Project * tprj = new logic_Project(max_prj_id,genNewPrjName(max_prj_id));
	logic_Project * tprj = new logic_Project(max_prj_id,genNewPrjName(max_prj_id),this->mvmu_InitModuleMap);
	prjMap[max_prj_id] = tprj;

	curPrjId = max_prj_id;
	curProgId = 1;

	return curPrjId; //新建prj鼠标焦点会在当前prj
}

std::string logic_Controller::genNewPrjName(int id) {
	std::string idStr = whIntToString(id);
	std::string res = "项目";
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
	
	//如果没有这个 id 的 prj 直接报错
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

//得到当前的prjId
int  logic_Controller::ctrlGetCurPrj()
{
	return curPrjId;
}
//在当前 prj 和 prog 下，找最大 module id，并累加
int logic_Controller::ctrlNewModuleAddId() {

	if( !curPrjId || !curProgId )
		assert(false);

	logic_Project * tCurPrj = prjMap[curPrjId];
	int res = tCurPrj->getProgMaxModuleId(curProgId);
	res++;

	return res;
}

//根据progName删除该program
bool logic_Controller::ctrlDeleteProgram(const std::string progName)
{
	if( !curPrjId )
		assert(false);

	logic_Project * tCurPrj = prjMap[curPrjId];
	return tCurPrj->deleteProgram(progName);

}

//根据progPath导入program
bool logic_Controller::ctrlImportProgram(const std::string progPath)
{
	if( !curPrjId )
		assert(false);

	logic_Project* tCurPrj = prjMap[curPrjId];

	return tCurPrj->importProgram(progPath);
}

//根据progPath,和programID导program文件
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

//返回项目的所有program名称
std::vector<std::string> logic_Controller::ctrlGetProgName(int prjID)
{
	std::vector<std::string> allProgName;

	if (prjMap.count(prjID) <= 0)  //如果prjID不存在
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

//返回项目的所有变量（自定义的变量结构）
std::vector<VarProperty> logic_Controller::ctrlGetVariety(int prjID)
{
	std::vector<VarProperty> allVariety;

	if (prjMap.count(prjID) <= 0)  //如果prjID不存在
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

//copy一个program，并且返回新的program name
std::string logic_Controller::ctrlCopyProgram(const std::string progName)
{
	if( !curPrjId )
		assert(false);

	logic_Project * tCurPrj = prjMap[curPrjId];
	return tCurPrj->copyProgram(progName);
}


//后接模块，传入前驱id，如果前驱为0，代表新建树
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

//前插模块，不允许新建树时调用
bool logic_Controller::ctrlFrontInsModule(int post_id,int m_type) {

	if( !curPrjId || !curProgId )
		assert(false);

	assert(post_id); //post_id 不能为 0

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

	assert(pre_id); //pre_id 不能为 0

	logic_Project * tCurPrj = prjMap[curPrjId];
	logic_Program * tCurProg = tCurPrj->getProgram(curProgId);

	bool flag = tCurProg->addLeafModule(pre_id,m_id);

	return flag;

}

// get 所有prj map【方便xml持久化】
std::map <int ,logic_Project* > logic_Controller::getAllPrj() {

	return prjMap;
}

//get 当前prj
int logic_Controller::getCurPrjId()
{
	return curPrjId;
}



//删除模块
bool logic_Controller::ctrlDelModule(int m_id) {

	if( !curPrjId || !curProgId )
		assert(false);

	logic_Project * tCurPrj = prjMap[curPrjId];
	logic_Program * tCurProg = tCurPrj->getProgram(curProgId);

	return tCurProg->delModule(m_id);
}

//查询模块前驱id
int logic_Controller::ctrlGetPreId(int m_id) {

	if( !curPrjId || !curProgId )
		assert(false);

	logic_Project * tCurPrj = prjMap[curPrjId];
	logic_Program * tCurProg = tCurPrj->getProgram(curProgId);

	return tCurProg->getModulePreId(m_id);
}

//查询模块后继id表
std::vector<int > logic_Controller::ctrlGetPostId(int m_id) {

	if( !curPrjId || !curProgId )
		assert(false);

	logic_Project * tCurPrj = prjMap[curPrjId];
	logic_Program * tCurProg = tCurPrj->getProgram(curProgId);

	return tCurProg->getModulePostId(m_id);

}

//查询m_id的所在树的根节点的模块id
int logic_Controller::ctrlGetRootModuleId(int m_id)
{
	if( !curPrjId || !curProgId )
		assert(false);

	logic_Project * tCurPrj = prjMap[curPrjId];
	logic_Program * tCurProg = tCurPrj->getProgram(curProgId);

	return tCurProg->getRootModuleId(m_id);
}

//查询两个module是否在同一颗树内
bool logic_Controller::ctrlIsInSameTree(int cur_m_id, int other_m_id){

	if( !curPrjId || !curProgId )
		assert(false);

	logic_Project * tCurPrj = prjMap[curPrjId];
	logic_Program * tCurProg = tCurPrj->getProgram(curProgId);

	return tCurProg->IsInSameTree(cur_m_id, other_m_id);
}

//查询for模块内部的后继模块
std::vector<int > logic_Controller::ctrlGetForPostId(int for_m_id)
{
	if( !curPrjId || !curProgId )
		assert(false);

	logic_Project * tCurPrj = prjMap[curPrjId];
	logic_Program * tCurProg = tCurPrj->getProgram(curProgId);

	return tCurProg->getForModuleRootPostId(for_m_id);
}

//查询if模块的某个branch的所有后继节点
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

//查询if模块的ui_branch_id的-2节点前驱
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
		return -1; //插入点 id 错误
	}

	//前插 move
	logic_Project * tCurPrj = prjMap[curPrjId];
	logic_Program * tCurProg = tCurPrj->getProgram(curProgId);

	return tCurProg->frontInsSingMove(cur_m_id,post_m_id);
}

int logic_Controller::ctrlBackInsSingMove(int cur_m_id,int pre_m_id) {

	if( !curPrjId || !curProgId )
		assert(false);

	//后插 move 类append
	//////!!!!! pre_m_id 可能为0，即移到一棵新树上

	logic_Project * tCurPrj = prjMap[curPrjId];
	logic_Program * tCurProg = tCurPrj->getProgram(curProgId);

	return tCurProg->backInsSingMove(cur_m_id,pre_m_id);
}

//带祖先前插 move
int logic_Controller::ctrlFrontInsMultiMove(int cur_m_id,int post_m_id) {

	if( !curPrjId || !curProgId )
		assert(false);

	if ( post_m_id < 0 ) { //可以为0
		assert(false); //插入点 id 错误
	}

	//前插 move
	logic_Project * tCurPrj = prjMap[curPrjId];
	logic_Program * tCurProg = tCurPrj->getProgram(curProgId);

	return tCurProg->frontInsMultiMove(cur_m_id,post_m_id);
}

//带孩子后插 move
int logic_Controller::ctrlBackInsMultiMove(int cur_m_id,int pre_m_id) {

	if( !curPrjId || !curProgId )
		assert(false);

	//后插 move 类append
	//////!!!!! pre_m_id 可能为0，即（带孩子）移到一棵新树上

	logic_Project * tCurPrj = prjMap[curPrjId];
	logic_Program * tCurProg = tCurPrj->getProgram(curProgId);

	return tCurProg->backInsMultiMove(cur_m_id,pre_m_id);
}

//新增孩子move
int logic_Controller::ctrlAddLeafMove(int cur_m_id,int pre_m_id) {

	if( !curPrjId || !curProgId )
		assert(false);

	logic_Project * tCurPrj = prjMap[curPrjId];
	logic_Program * tCurProg = tCurPrj->getProgram(curProgId);

	return tCurProg->addLeafMove(cur_m_id,pre_m_id);
}


///
/// \brief for和if处理
///        注意：ui_branch_id需要在逻辑层合成和分开
/// \para 传入都是ui_branch_id，但是输入给下一级函数的是正确的branch_id
///

//insert into for
bool logic_Controller::ctrlInsertModule_For(int pre_id,bool isFI,int m_type,int for_id) {

	if( !curPrjId || !curProgId )
		assert(false);

	///调用此函数的参数中传过来的 m_id 即前驱id，且必然为0
	if ( pre_id > 0 ) {

		//为0：新放入for
		//为-1：新插入activeTree
		assert(false);
		return false;
	}

	if ( false != isFI) //必须不是前插（必是后插），否则错误
		return false;

	logic_Project * tCurPrj = prjMap[curPrjId];
	logic_Program * tCurProg = tCurPrj->getProgram(curProgId);

	int max_module_id = tCurProg->getMaxModuleId();
	max_module_id++;

	bool flag = tCurProg->insertModuleIntoFor(max_module_id,pre_id,m_type,for_id); //具体在下一层将树id放入for

	return flag; //返回成功与否标志
}

//insert into if
bool logic_Controller::ctrlInsertModule_If(int pre_id,bool isFI,int m_type,int if_id,int ui_branch_id) {

	if( !curPrjId || !curProgId )
		assert(false);

	///调用此函数的参数中传过来的 m_id 即前驱id，且必然为0
	if ( 0 != pre_id )
		return false;

	if ( false != isFI) //必须不是前插，否则错误
		return false;

	logic_Project * tCurPrj = prjMap[curPrjId];
	logic_Program * tCurProg = tCurPrj->getProgram(curProgId);

	int max_module_id = tCurProg->getMaxModuleId();
	max_module_id++;

	int branch_id = this->decryptBranchId(ui_branch_id);
	bool flag = tCurProg->insertModuleIntoIf(max_module_id,pre_id,m_type,if_id,branch_id); //具体在下一层将树id放入if

	return flag; //返回成功与否标志
}

// get for 当前激活树
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

// set for 当前激活树
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

//get 指定 branch的int content
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

//重载 string
int logic_Controller::ctrlSetIfBranchContent(int if_id,int ui_branch_id,std::string con_str) {

	if( !curPrjId || !curProgId )
		assert(false);

	logic_Project * tCurPrj = prjMap[curPrjId];
	logic_Program * tCurProg = tCurPrj->getProgram(curProgId);

	int branch_id = this->decryptBranchId(ui_branch_id);
	return tCurProg->setIfBranchContent(if_id,branch_id,con_str);
}

//增删 if 分支
int logic_Controller::ctrlAddIfBranch(int if_id) {

	if( !curPrjId || !curProgId )
		assert(false);

	logic_Project * tCurPrj = prjMap[curPrjId];
	logic_Program * tCurProg = tCurPrj->getProgram(curProgId);

	int newBranchId = tCurProg->addIfBranch(if_id);
	int ui_branch_id = encryptBranchId(if_id,newBranchId);

	return ui_branch_id;
}

//难点，需要删除分支中所有树
int logic_Controller::ctrlDelIfBranch(int if_id,int ui_branch_id) {

	if( !curPrjId || !curProgId )
		assert(false);

	logic_Project * tCurPrj = prjMap[curPrjId];
	logic_Program * tCurProg = tCurPrj->getProgram(curProgId);

	int branch_id = this->decryptBranchId(ui_branch_id);
	return tCurProg->delIfBranch(if_id,branch_id);
}

/// \brief 模块参数连线
int logic_Controller::ctrlParaConnect(int out_m_id,int out_para_id,int in_m_id,int in_para_id) {

	if( !curPrjId || !curProgId )
		assert(false);

	logic_Project * tCurPrj = prjMap[curPrjId];
	logic_Program * tCurProg = tCurPrj->getProgram(curProgId);

	return tCurProg->paraConnect(out_m_id,out_para_id,in_m_id,in_para_id);
}

//取消连线，可通过 isOut 来用outModule或者inModule删除
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
/// \brief 加解密 ui_branch_id
///

//加密 返回加密后id
int logic_Controller::encryptBranchId(int if_id,int branch_id) {

	//把一个32位 unsigned 整数分成：
	///高16位做moduleId，低15位做branchId，符号位保留（不允许为负）
	int ui_branch_id = if_id<<15;
	ui_branch_id += branch_id;

	assert( ui_branch_id > 0 );

	return ui_branch_id;
}

//解密
void logic_Controller::decryptBranchId(int ui_branch_id,int &if_id,int &branch_id) {

	assert( ui_branch_id > 0 );

	if( ui_branch_id < 0x7FFF )
		return ; //如果并没有高位

	//高16位先分出来
	if_id = ui_branch_id >> 15;
	branch_id = ui_branch_id & 0x7FFF; //抹去高位
}

//解密
int logic_Controller::decryptBranchId(int ui_branch_id) {

	assert( ui_branch_id > 0 );

	if( ui_branch_id < 0x7FFF )
		return ui_branch_id; //如果并没有高位

	int branch_id = ui_branch_id & 0x7FFF; //抹去高位
	return branch_id;
}

///
/// \brief for与if的move操作
///
/// \para move_type
///       case 0:单模块直接后插 move（即一个模块从一棵树移动到另一棵树）
///       case 1:单模块直接前插
///       case 2:带孩子后插 move（后有线，只能接在树的某个叶子节点）
///       case 3:带孩子前插 move（前有线，只能接在一棵树root处，原root不能为开始模块）
int logic_Controller::ctrlMoveModuleFor(int cur_m_id,int other_m_id,int move_type,int for_id) {

	if( !curPrjId || !curProgId )
		assert(false);

	logic_Project * tCurPrj = prjMap[curPrjId];
	logic_Program * tCurProg = tCurPrj->getProgram(curProgId);

	if( -1 == other_m_id ) {

		//如果是接到activeTree的后面
		assert( 0 == move_type || 4 == move_type ); //必须为0

		if( 0 == move_type )
			return tCurProg->appendActiveTreeMoveFor(cur_m_id,for_id);

		else if( 4 == move_type ) //直接添一个叶子
			return tCurProg->addLeafActiveTreeMoveFor(cur_m_id,for_id);

	}else {

		//如果是普通move
		if ( 0 == move_type) //单模块后插 move
			return tCurProg->backInsSingMoveFor(cur_m_id,other_m_id,for_id);

		else if( 1 == move_type) //单模块前插 move
			return tCurProg->frontInsSingMoveFor(cur_m_id,other_m_id,for_id);

		else if( 2 == move_type) //带孩子后插 move
			return tCurProg->backInsMultiMoveFor(cur_m_id,other_m_id,for_id);

		else if( 3 == move_type) //带祖先前插 move
			return tCurProg->frontInsMultiMoveFor(cur_m_id,other_m_id,for_id);

		else if( 4 == move_type ) //新增叶子 move（直接连线）
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

		//如果是接到activeTree的后面
		assert( 0 == move_type || 4 == move_type ); //必须为0

		if( 0 == move_type )
			return tCurProg->appendActiveTreeMoveIf(cur_m_id,if_id,branch_id);

		else if( 4 == move_type ) //直接添一个叶子
			return tCurProg->addLeafActiveTreeMoveIf(cur_m_id,if_id,branch_id);

	}else {

		//如果是普通move
		if ( 0 == move_type) //单模块后插 move
			return tCurProg->backInsSingMoveIf(cur_m_id,other_m_id,if_id,branch_id);

		else if( 1 == move_type) //单模块前插 move
			return tCurProg->frontInsSingMoveIf(cur_m_id,other_m_id,if_id,branch_id);

		else if( 2 == move_type) //带孩子后插 move
			return tCurProg->backInsMultiMoveIf(cur_m_id,other_m_id,if_id,branch_id);

		else if( 3 == move_type) //带祖先前插 move
			return tCurProg->frontInsMultiMoveIf(cur_m_id,other_m_id,if_id,branch_id);

		else if( 4 == move_type ) //新增叶子 move（直接连线）
			return tCurProg->addLeafMoveIf(cur_m_id,other_m_id,if_id,branch_id);
	}
}

///init module map函数
void logic_Controller::initModuleMapFunc() {

	//此处应读持久化xml，填满整个最原始的 mvmu_InitModuleMap

	logic_XmlIO io;
	io.IO_Initial(this->mvmu_InitModuleMap);
}

///
/// \brief 获取根节点
/// \para 容器编号，如果是0，获取最外层root集合
/// \return 根节点集合
///
std::vector<int > logic_Controller::ctrlFindRootsInContainer(int containerId) {

	if( !curPrjId || !curProgId )
		assert(false);

	logic_Project * tCurPrj = prjMap[curPrjId];
	logic_Program * tCurProg = tCurPrj->getProgram(curProgId);

	if( 0 == containerId ) //大画布
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

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!持久化部分!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
bool logic_Controller::ctrlSaveCurProject()
{
	if( !curPrjId || !curProgId )
		assert(false);

	logic_Project * tCurPrj = prjMap[curPrjId];
	auto fileName = tCurPrj->getPrjName();

	if(fileName == "")
	{
		//调用错误，无法对空地址存储
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
			std::cout << node->getID() << "（";
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
			std::cout << "）   ";
		}
		if(nodeQueue1.empty())
			std::cout << std::endl;
		while(!nodeQueue2.empty())
		{
			node = nodeQueue2.front();
			std::cout << node->getID() << "（";
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
			std::cout << "）   ";
		}
		if(nodeQueue2.empty())
			std::cout << std::endl;
	}
}

///
/// \brief 我的模块
///
//session1：是否可以创建我的模块，前后端第一次会话
//接口传id列表，返回是否可创建
int logic_Controller::ctrlCanMyBlocks(std::vector<int > ids) {

	if( !curPrjId || !curProgId )
		assert(false);

	assert( ids.size() > 0 );

	logic_Project * tCurPrj = prjMap[curPrjId];
	logic_Program * tCurProg = tCurPrj->getProgram(curProgId);

	return tCurProg->canMyBlocks(ids);
}

// get\set当前program名称
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

// get\set当前项目名称
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
