/* 
* 
* function: 消息接口实现文件
* 
* Date:2015-10-21
* 
*    Author: Bill Wang
*/

#include "msgInterface.h"

using namespace std;

///!!!!!!!!!!!!!!!!!!!!!!!!!新建!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

/// \brief 新建project
/// \return 新prjID
int msgInterface::newPrj() {

	return ctrl.ctrlNewPrj();
}

/// \brief 打开一个project
void msgInterface::openPrj() {

}

/// \brief 新建program
/// \return 新ID
int msgInterface::newProg() {

	return ctrl.ctrlNewProg();
}

/// \brief 新建ModuleID++
/// \return 新ID
int msgInterface::newModuleAddId() {

	return ctrl.ctrlNewModuleAddId();
}

/// \brief 改变curPrj和curProg
void msgInterface::setCurPrj(int prjID) {

}

void msgInterface::setCurProg(int progID) {

}



///!!!!!!!!!!!!!!!!!!!!!!!!!模块内部操作!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

/// \brief get、set参数
string msgInterface::getParameter(GetPType type,int m_id,int p_id) {

	return ctrl.ctrlGetParameter(type,m_id,p_id);
}

void msgInterface::setParameter(int m_id,int p_id,std::string p_value) {

	ctrl.ctrlSetParameter(m_id,p_id,p_value);
}


/// \brief get、set端口选择器
WinSwitcherType msgInterface::getWinSwType(int m_id,int m_modeValue) {

	return ctrl.ctrlGetWinSwType(m_id,m_modeValue);
}

string msgInterface::getWinSwValue(int m_id) {

	return ctrl.ctrlGetWinSwValue(m_id);
}

void msgInterface::setWinSwValue(int m_id,std::string ws_value) {

	ctrl.ctrlSetWinSwValue(m_id,ws_value);
}

/// \brief get、set菊链
int msgInterface::getDaisyChainValue(int m_id) {

	return ctrl.ctrlGetDaisyChainValue(m_id);
}

void msgInterface::setDaisyChainValue(int m_id,int chain_value) {

	ctrl.ctrlSetDaisyChainValue(m_id,chain_value);
}

/// \brief get显示预览
bool msgInterface::getPreView(int m_id) {

	return NULL;
}

/// \brief 查询参数IDs，返回 id 列表
std::vector<int > msgInterface::getParamsIds(int m_id,int mode_value) {

	return ctrl.ctrlGetParamsIds(m_id,mode_value);
}

/// \brief get、set模式选择器
int msgInterface::getModeValue(int m_id) {

	return ctrl.ctrlGetModeValue(m_id);
}

void msgInterface::setModeValue(int m_id,int mode_id) {

	ctrl.ctrlSetModeValue(m_id,mode_id);
}


///!!!!!!!!!!!!!!!!!!!!!!!!!模块间操作!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
/// \brief 添加模块
/// \para 前驱或后继模块id，是前插（true）还是后插，是哪种类型的模块新加入
bool msgInterface::insertModule(int m_id,bool isFI,int m_type) {

	if ( false == isFI)
		return ctrl.ctrlAppendModule(m_id,m_type);

	else
		return ctrl.ctrlFrontInsModule(m_id,m_type);
}


////////!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

bool msgInterface::addLeafModule(int pre_id,int m_type) {

	return ctrl.ctrlAddLeafModule(pre_id,m_type);
}

/// \brief 删除模块
bool msgInterface::deleteModule(int m_id) {
	return ctrl.ctrlDelModule(m_id);
}

/// \brief 移动模块模块
///
/// \para 着重说一下 move_type
///       case 1:单模块直接后插 move（即一个模块从一棵树移动到另一棵树）
///       case 2:单模块直接前插
///       case 3:带孩子后插 move（后有线，只能接在树的某个叶子节点）
///       case 4:带孩子前插 move（前有线，只能接在一棵树root处，原root不能为开始模块）
///
/// \return 返回错误编号，正常返回0
int msgInterface::moveModule(int cur_m_id,int other_m_id,MoveType move_type) {

	if ( BACK_SINGLE == move_type) //单模块后插 move
		return ctrl.ctrlBackInsSingMove(cur_m_id,other_m_id);

	else if( FRONT_SINGLE == move_type) //单模块前插 move
		return ctrl.ctrlFrontInsSingMove(cur_m_id,other_m_id);

	else if( BACK_MULTI == move_type) //带孩子后插 move
		return ctrl.ctrlBackInsMultiMove(cur_m_id,other_m_id);

	else if( FRONT_MULTI == move_type) //带祖先前插 move
		return ctrl.ctrlFrontInsMultiMove(cur_m_id,other_m_id);
}

/// \brief 查询前驱和后继
int msgInterface::getPreId(int m_id) {

	return ctrl.ctrlGetPreId(m_id);
}

vector<int > msgInterface::getPostId(int m_id) {

	return ctrl.ctrlGetPostId(m_id);
}



/// \brief for if模块，重载
/// parent_id 代表放入哪一个for中
bool msgInterface::insertModule(int m_id,bool isFI,int m_type,int for_id) {

	return ctrl.ctrlInsertModule_For(m_id,isFI,m_type,for_id);
}

/// ui_branch_id，组合id，代表放入哪一个 if 的哪一个分支中
bool msgInterface::insertModule(int m_id,bool isFI,int m_type,int if_id,int ui_branch_id) {

	return ctrl.ctrlInsertModule_If(m_id,isFI,m_type,if_id,ui_branch_id);
}

//返回当前激活树id【注意是树id】
//for
int msgInterface::getActiveTree(int for_id) {

	return ctrl.ctrlGetForActiveTree(for_id);
}

//if 激活树
int msgInterface::getActiveTree(int if_id,int ui_branch_id) {

	return ctrl.ctrlGetIfActiveTree(if_id,ui_branch_id);
}

// set 当前激活树id
//for
void msgInterface::setActiveTree(int for_id,int tree_id) {

	return ctrl.ctrlSetForActiveTree(for_id,tree_id);
}

//if
void msgInterface::setActiveTree(int if_id,int ui_branch_id,int tree_id) {

	return ctrl.ctrlSetIfActiveTree(if_id,ui_branch_id,tree_id);
}

/// get set if 某个 branch 参数
//get 指定 branch的int content
int msgInterface::getIfBranchContentInt(int if_id,int ui_branch_id) {

	return ctrl.ctrlGetIfBranchContentInt(if_id,ui_branch_id);
}

//string content
std::string msgInterface::getIfBranchContentStr(int if_id,int ui_branch_id) {

	return ctrl.ctrlGetIfBranchContentStr(if_id,ui_branch_id);
}

///// \返回不同错误代码，正常返回0，重载
int msgInterface::setIfBranchContent(int if_id,int ui_branch_id,int con_int) {

	return ctrl.ctrlSetIfBranchContent(if_id,ui_branch_id,con_int);
}

//重载 string
int msgInterface::setIfBranchContent(int if_id,int ui_branch_id,std::string con_str) {

	return ctrl.ctrlSetIfBranchContent(if_id,ui_branch_id,con_str);
}

//增删 if 分支
int msgInterface::addIfBranch(int if_id) {

	return ctrl.ctrlAddIfBranch(if_id);
}

//难点，需要删除分支中所有树
int msgInterface::delIfBranch(int if_id,int ui_branch_id) {

	return ctrl.ctrlDelIfBranch(if_id,ui_branch_id);
}

/// \brief 模块参数连线
int msgInterface::paraConnect(int out_m_id,int out_para_id,int in_m_id,int in_para_id) {

	return ctrl.ctrlParaConnect(out_m_id,out_para_id,in_m_id,in_para_id);
}

//取消连线，可通过 isOut 来用outModule或者inModule删除
void msgInterface::paraDisconnect(int m_id,int para_id,bool isOut) {

	if( true == isOut )
		ctrl.ctrlOutParaDisconnect(m_id,para_id);
	else
		ctrl.ctrlInParaDisconnect(m_id,para_id);
}

///跟for if 相关的所有 move
/// \para cur_m_id 指的是被拖动的主动模块id，other_m_id 指的是被动接受的模块id
/// \para move_type 移动模式，container_id 目的地容器id，ui_branch_id 前端的奇葩设计id
/// \return 返回错误编号，正常返回0
int msgInterface::moveModuleForIf(int cur_m_id,int other_m_id,
					MoveType move_type,int container_id,int ui_branch_id
					) {

	if( container_id == ui_branch_id ) //目的地是for模块
		return ;
	else 
}

/// \brief 创建我的模块
