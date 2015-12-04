/* 
* 
* function: ��Ϣ�ӿ�ʵ���ļ�
* 
* Date:2015-10-21
* 
*    Author: Bill Wang
*/

#include "msgInterface.h"

using namespace std;

///!!!!!!!!!!!!!!!!!!!!!!!!!�½�!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

/// \brief �½�project
/// \return ��prjID
int msgInterface::newPrj() {

	return ctrl.ctrlNewPrj();
}

/// \brief ��һ��project
void msgInterface::openPrj() {

}

/// \brief �½�program
/// \return ��ID
int msgInterface::newProg() {

	return ctrl.ctrlNewProg();
}

/// \brief �½�ModuleID++
/// \return ��ID
int msgInterface::newModuleAddId() {

	return ctrl.ctrlNewModuleAddId();
}

/// \brief �ı�curPrj��curProg
void msgInterface::setCurPrj(int prjID) {

}

void msgInterface::setCurProg(int progID) {

}



///!!!!!!!!!!!!!!!!!!!!!!!!!ģ���ڲ�����!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

/// \brief get��set����
string msgInterface::getParameter(GetPType type,int m_id,int p_id) {

	return ctrl.ctrlGetParameter(type,m_id,p_id);
}

void msgInterface::setParameter(int m_id,int p_id,std::string p_value) {

	ctrl.ctrlSetParameter(m_id,p_id,p_value);
}


/// \brief get��set�˿�ѡ����
WinSwitcherType msgInterface::getWinSwType(int m_id,int m_modeValue) {

	return ctrl.ctrlGetWinSwType(m_id,m_modeValue);
}

string msgInterface::getWinSwValue(int m_id) {

	return ctrl.ctrlGetWinSwValue(m_id);
}

void msgInterface::setWinSwValue(int m_id,std::string ws_value) {

	ctrl.ctrlSetWinSwValue(m_id,ws_value);
}

/// \brief get��set����
int msgInterface::getDaisyChainValue(int m_id) {

	return ctrl.ctrlGetDaisyChainValue(m_id);
}

void msgInterface::setDaisyChainValue(int m_id,int chain_value) {

	ctrl.ctrlSetDaisyChainValue(m_id,chain_value);
}

/// \brief get��ʾԤ��
bool msgInterface::getPreView(int m_id) {

	return NULL;
}

/// \brief ��ѯ����IDs������ id �б�
std::vector<int > msgInterface::getParamsIds(int m_id,int mode_value) {

	return ctrl.ctrlGetParamsIds(m_id,mode_value);
}

/// \brief get��setģʽѡ����
int msgInterface::getModeValue(int m_id) {

	return ctrl.ctrlGetModeValue(m_id);
}

void msgInterface::setModeValue(int m_id,int mode_id) {

	ctrl.ctrlSetModeValue(m_id,mode_id);
}


///!!!!!!!!!!!!!!!!!!!!!!!!!ģ������!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
/// \brief ���ģ��
/// \para ǰ������ģ��id����ǰ�壨true�����Ǻ�壬���������͵�ģ���¼���
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

/// \brief ɾ��ģ��
bool msgInterface::deleteModule(int m_id) {
	return ctrl.ctrlDelModule(m_id);
}

/// \brief �ƶ�ģ��ģ��
///
/// \para ����˵һ�� move_type
///       case 1:��ģ��ֱ�Ӻ�� move����һ��ģ���һ�����ƶ�����һ������
///       case 2:��ģ��ֱ��ǰ��
///       case 3:�����Ӻ�� move�������ߣ�ֻ�ܽ�������ĳ��Ҷ�ӽڵ㣩
///       case 4:������ǰ�� move��ǰ���ߣ�ֻ�ܽ���һ����root����ԭroot����Ϊ��ʼģ�飩
///
/// \return ���ش����ţ���������0
int msgInterface::moveModule(int cur_m_id,int other_m_id,MoveType move_type) {

	if ( BACK_SINGLE == move_type) //��ģ���� move
		return ctrl.ctrlBackInsSingMove(cur_m_id,other_m_id);

	else if( FRONT_SINGLE == move_type) //��ģ��ǰ�� move
		return ctrl.ctrlFrontInsSingMove(cur_m_id,other_m_id);

	else if( BACK_MULTI == move_type) //�����Ӻ�� move
		return ctrl.ctrlBackInsMultiMove(cur_m_id,other_m_id);

	else if( FRONT_MULTI == move_type) //������ǰ�� move
		return ctrl.ctrlFrontInsMultiMove(cur_m_id,other_m_id);
}

/// \brief ��ѯǰ���ͺ��
int msgInterface::getPreId(int m_id) {

	return ctrl.ctrlGetPreId(m_id);
}

vector<int > msgInterface::getPostId(int m_id) {

	return ctrl.ctrlGetPostId(m_id);
}



/// \brief for ifģ�飬����
/// parent_id ���������һ��for��
bool msgInterface::insertModule(int m_id,bool isFI,int m_type,int for_id) {

	return ctrl.ctrlInsertModule_For(m_id,isFI,m_type,for_id);
}

/// ui_branch_id�����id�����������һ�� if ����һ����֧��
bool msgInterface::insertModule(int m_id,bool isFI,int m_type,int if_id,int ui_branch_id) {

	return ctrl.ctrlInsertModule_If(m_id,isFI,m_type,if_id,ui_branch_id);
}

//���ص�ǰ������id��ע������id��
//for
int msgInterface::getActiveTree(int for_id) {

	return ctrl.ctrlGetForActiveTree(for_id);
}

//if ������
int msgInterface::getActiveTree(int if_id,int ui_branch_id) {

	return ctrl.ctrlGetIfActiveTree(if_id,ui_branch_id);
}

// set ��ǰ������id
//for
void msgInterface::setActiveTree(int for_id,int tree_id) {

	return ctrl.ctrlSetForActiveTree(for_id,tree_id);
}

//if
void msgInterface::setActiveTree(int if_id,int ui_branch_id,int tree_id) {

	return ctrl.ctrlSetIfActiveTree(if_id,ui_branch_id,tree_id);
}

/// get set if ĳ�� branch ����
//get ָ�� branch��int content
int msgInterface::getIfBranchContentInt(int if_id,int ui_branch_id) {

	return ctrl.ctrlGetIfBranchContentInt(if_id,ui_branch_id);
}

//string content
std::string msgInterface::getIfBranchContentStr(int if_id,int ui_branch_id) {

	return ctrl.ctrlGetIfBranchContentStr(if_id,ui_branch_id);
}

///// \���ز�ͬ������룬��������0������
int msgInterface::setIfBranchContent(int if_id,int ui_branch_id,int con_int) {

	return ctrl.ctrlSetIfBranchContent(if_id,ui_branch_id,con_int);
}

//���� string
int msgInterface::setIfBranchContent(int if_id,int ui_branch_id,std::string con_str) {

	return ctrl.ctrlSetIfBranchContent(if_id,ui_branch_id,con_str);
}

//��ɾ if ��֧
int msgInterface::addIfBranch(int if_id) {

	return ctrl.ctrlAddIfBranch(if_id);
}

//�ѵ㣬��Ҫɾ����֧��������
int msgInterface::delIfBranch(int if_id,int ui_branch_id) {

	return ctrl.ctrlDelIfBranch(if_id,ui_branch_id);
}

/// \brief ģ���������
int msgInterface::paraConnect(int out_m_id,int out_para_id,int in_m_id,int in_para_id) {

	return ctrl.ctrlParaConnect(out_m_id,out_para_id,in_m_id,in_para_id);
}

//ȡ�����ߣ���ͨ�� isOut ����outModule����inModuleɾ��
void msgInterface::paraDisconnect(int m_id,int para_id,bool isOut) {

	if( true == isOut )
		ctrl.ctrlOutParaDisconnect(m_id,para_id);
	else
		ctrl.ctrlInParaDisconnect(m_id,para_id);
}

///��for if ��ص����� move
/// \para cur_m_id ָ���Ǳ��϶�������ģ��id��other_m_id ָ���Ǳ������ܵ�ģ��id
/// \para move_type �ƶ�ģʽ��container_id Ŀ�ĵ�����id��ui_branch_id ǰ�˵��������id
/// \return ���ش����ţ���������0
int msgInterface::moveModuleForIf(int cur_m_id,int other_m_id,
					MoveType move_type,int container_id,int ui_branch_id
					) {

	if( container_id == ui_branch_id ) //Ŀ�ĵ���forģ��
		return ;
	else 
}

/// \brief �����ҵ�ģ��
