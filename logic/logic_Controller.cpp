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

logic_Controller::logic_Controller() {
	Init();
}

void logic_Controller::Init() {
	//初始化 Global
	prjMap.clear();
	//prjMap[0] = NULL;

 	curPrjId=0;
 	curProgId=0;
}

int logic_Controller::ctrlNewPrj() {

	int max_prj_id = this->getMaxPrjId(); //获得当前最大 prj 的 ID
	max_prj_id++; //新 prj ID

	logic_Project * tprj = new logic_Project(max_prj_id,genNewPrjName(max_prj_id));
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

	logic_Project * tCurPrj = prjMap[curPrjId];
	assert( NULL != tCurPrj->getProgram(id) );

	curProgId = id;
}

//在当前 prj 和 prog 下，找最大 module id，并累加
int logic_Controller::ctrlNewModuleAddId() {

	logic_Project * tCurPrj = prjMap[curPrjId];
	int res = tCurPrj->getProgMaxModuleId(curProgId);
	res++;

	return res;
}

//后接模块，传入前驱id，如果前驱为0，代表新建树
bool logic_Controller::ctrlAppendModule(int pre_id,int m_type) {

	logic_Project * tCurPrj = prjMap[curPrjId];
	logic_Program * tCurProg = tCurPrj->getProgram(curProgId);

	int max_module_id = tCurProg->getMaxModuleId();
	max_module_id++;

	bool flag = tCurProg->appendModule(max_module_id,pre_id,m_type);
	
	return flag;
}

//前插模块，不允许新建树时调用
bool logic_Controller::ctrlFrontInsModule(int post_id,int m_type) {

	assert(post_id); //post_id 不能为 0

	logic_Project * tCurPrj = prjMap[curPrjId];
	logic_Program * tCurProg = tCurPrj->getProgram(curProgId);

	int max_module_id = tCurProg->getMaxModuleId();
	max_module_id++;

	bool flag = tCurProg->frontInsModule(max_module_id,post_id,m_type);

	return flag;
}

bool logic_Controller::ctrlAddLeafModule(int pre_id,int m_type) {

	assert(pre_id); //pre_id 不能为 0

	logic_Project * tCurPrj = prjMap[curPrjId];
	logic_Program * tCurProg = tCurPrj->getProgram(curProgId);

	int max_module_id = tCurProg->getMaxModuleId();
	max_module_id++;

	bool flag = tCurProg->addLeafModule(max_module_id,pre_id,m_type);

	return flag;

}

// get 所有prj map【方便xml持久化】
std::map <int ,logic_Project* > logic_Controller::getAllPrj() {
	return prjMap;
}

//删除模块
bool logic_Controller::ctrlDelModule(int m_id) {

	logic_Project * tCurPrj = prjMap[curPrjId];
	logic_Program * tCurProg = tCurPrj->getProgram(curProgId);

	return tCurProg->delModule(m_id);
}

//查询模块前驱id
int logic_Controller::ctrlGetPreId(int m_id) {

	logic_Project * tCurPrj = prjMap[curPrjId];
	logic_Program * tCurProg = tCurPrj->getProgram(curProgId);

	return tCurProg->getModulePreId(m_id);
}

//查询模块后继id表
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
		return -1; //插入点 id 错误
	}

	//前插 move
	logic_Project * tCurPrj = prjMap[curPrjId];
	logic_Program * tCurProg = tCurPrj->getProgram(curProgId);

	return tCurProg->frontInsSingMove(cur_m_id,post_m_id);
}

int logic_Controller::ctrlBackInsSingMove(int cur_m_id,int pre_m_id) {

	//后插 move 类append
	//////!!!!! pre_m_id 可能为0，即移到一棵新树上

	logic_Project * tCurPrj = prjMap[curPrjId];
	logic_Program * tCurProg = tCurPrj->getProgram(curProgId);

	return tCurProg->backInsSingMove(cur_m_id,pre_m_id);
}

//带祖先前插 move
int logic_Controller::ctrlFrontInsMultiMove(int cur_m_id,int post_m_id) {

	if ( post_m_id <= 0 ) {
		return -1; //插入点 id 错误
	}

	//前插 move
	logic_Project * tCurPrj = prjMap[curPrjId];
	logic_Program * tCurProg = tCurPrj->getProgram(curProgId);

	return tCurProg->frontInsMultiMove(cur_m_id,post_m_id);
}

//带孩子后插 move
int logic_Controller::ctrlBackInsMultiMove(int cur_m_id,int pre_m_id) {

	//后插 move 类append
	//////!!!!! pre_m_id 可能为0，即（带孩子）移到一棵新树上

	logic_Project * tCurPrj = prjMap[curPrjId];
	logic_Program * tCurProg = tCurPrj->getProgram(curProgId);

	return tCurProg->backInsMultiMove(cur_m_id,pre_m_id);
}

//新增孩子move
int logic_Controller::ctrlAddLeafMove(int cur_m_id,int pre_m_id) {

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

	///调用此函数的参数中传过来的 m_id 即前驱id，且必然为0
	if ( 0 != pre_id )
		return false;

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

	logic_Project * tCurPrj = prjMap[curPrjId];
	logic_Program * tCurProg = tCurPrj->getProgram(curProgId);

	return tCurProg->getForActiveTree(for_id);
}

//if
int logic_Controller::ctrlGetIfActiveTree(int if_id,int ui_branch_id) {

	logic_Project * tCurPrj = prjMap[curPrjId];
	logic_Program * tCurProg = tCurPrj->getProgram(curProgId);

	int branch_id = this->decryptBranchId(ui_branch_id);
	return tCurProg->getIfActiveTree(if_id,branch_id);
}

// set for 当前激活树
void logic_Controller::ctrlSetForActiveTree(int for_id,int tree_id) {

	logic_Project * tCurPrj = prjMap[curPrjId];
	logic_Program * tCurProg = tCurPrj->getProgram(curProgId);

	tCurProg->setForActiveTree(for_id,tree_id);
}

//if
void logic_Controller::ctrlSetIfActiveTree(int if_id,int ui_branch_id,int tree_id) {

	logic_Project * tCurPrj = prjMap[curPrjId];
	logic_Program * tCurProg = tCurPrj->getProgram(curProgId);

	int branch_id = this->decryptBranchId(ui_branch_id);
	tCurProg->setIfActiveTree(if_id,branch_id,tree_id);
}

//get 指定 branch的int content
int logic_Controller::ctrlGetIfBranchContentInt(int if_id,int ui_branch_id) {

	logic_Project * tCurPrj = prjMap[curPrjId];
	logic_Program * tCurProg = tCurPrj->getProgram(curProgId);

	int branch_id = this->decryptBranchId(ui_branch_id);
	return tCurProg->getIfBranchContentInt(if_id,branch_id);
}

//string
std::string logic_Controller::ctrlGetIfBranchContentStr(int if_id,int ui_branch_id) {

	logic_Project * tCurPrj = prjMap[curPrjId];
	logic_Program * tCurProg = tCurPrj->getProgram(curProgId);

	int branch_id = this->decryptBranchId(ui_branch_id);
	return tCurProg->getIfBranchContentStr(if_id,branch_id);
}

int logic_Controller::ctrlSetIfBranchContent(int if_id,int ui_branch_id,int con_int) {

	logic_Project * tCurPrj = prjMap[curPrjId];
	logic_Program * tCurProg = tCurPrj->getProgram(curProgId);

	int branch_id = this->decryptBranchId(ui_branch_id);
	return tCurProg->setIfBranchContent(if_id,branch_id,con_int);
}

//重载 string
int logic_Controller::ctrlSetIfBranchContent(int if_id,int ui_branch_id,std::string con_str) {

	logic_Project * tCurPrj = prjMap[curPrjId];
	logic_Program * tCurProg = tCurPrj->getProgram(curProgId);

	int branch_id = this->decryptBranchId(ui_branch_id);
	return tCurProg->setIfBranchContent(if_id,branch_id,con_str);
}

//增删 if 分支
int logic_Controller::ctrlAddIfBranch(int if_id) {

	logic_Project * tCurPrj = prjMap[curPrjId];
	logic_Program * tCurProg = tCurPrj->getProgram(curProgId);

	int newBranchId = tCurProg->addIfBranch(if_id);
	int ui_branch_id = encryptBranchId(if_id,newBranchId);

	return ui_branch_id;
}

//难点，需要删除分支中所有树
int logic_Controller::ctrlDelIfBranch(int if_id,int ui_branch_id) {

	logic_Project * tCurPrj = prjMap[curPrjId];
	logic_Program * tCurProg = tCurPrj->getProgram(curProgId);

	int branch_id = this->decryptBranchId(ui_branch_id);
	return tCurProg->delIfBranch(if_id,branch_id);
}

/// \brief 模块参数连线
int logic_Controller::ctrlParaConnect(int out_m_id,int out_para_id,int in_m_id,int in_para_id) {

	logic_Project * tCurPrj = prjMap[curPrjId];
	logic_Program * tCurProg = tCurPrj->getProgram(curProgId);

	return tCurProg->paraConnect(out_m_id,out_para_id,in_m_id,in_para_id);
}

//取消连线，可通过 isOut 来用outModule或者inModule删除
void logic_Controller::ctrlOutParaDisconnect(int out_m_id,int out_para_id) {

	logic_Project * tCurPrj = prjMap[curPrjId];
	logic_Program * tCurProg = tCurPrj->getProgram(curProgId);

	tCurProg->outParaDisconnect(out_m_id,out_para_id);
}

void logic_Controller::ctrlInParaDisconnect(int in_m_id,int in_para_id) {

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

	//高16位先分出来
	if_id = ui_branch_id >> 15;
	branch_id = ui_branch_id & 0x7FFF; //抹去高位
}

//解密
int logic_Controller::decryptBranchId(int ui_branch_id) {

	assert( ui_branch_id > 0 );

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

	logic_Project * tCurPrj = prjMap[curPrjId];
	logic_Program * tCurProg = tCurPrj->getProgram(curProgId);

	if( -1 == other_m_id ) {

		//如果是接到activeTree的后面
		assert( 0 == move_type ); //必须为0

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
	}
}

int logic_Controller::ctrlMoveModuleIf(int cur_m_id,int other_m_id,int move_type,int if_id,int ui_branch_id) {

	return 0;
}
