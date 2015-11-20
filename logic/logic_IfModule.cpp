/* 
* 
* function: if ģ��ʵ���ļ�
* 
* Date:2015-11-14
* 
*    Author: Bill Wang
*/

#include "logic_IfModule.h"
#include <limits.h>

// #define INT_MAX 0x7fffffff
// #define INT_MIN 0x80000000

logic_IfModule::logic_IfModule(int id)
	:logic_BasicModule(id,2004){
		//���ø���Ĺ��캯�� ��ʼ��id��type
		Init(); //��ʼ��
}

logic_IfModule::~logic_IfModule() {

	//���������ಢ������ʲô
	//���������࣬����������
}

void logic_IfModule::Init() {

	mvmu_BranchMap.clear();
	whBranch newBranch;
	newBranch.curActiveTree = -1;
	newBranch.contentInt = INT_MIN;
	newBranch.contentStr = "";
	mvmu_BranchMap[0] = newBranch; ////////mvmu_BranchMap Ҫ��max

	mvmis_TreeId_BranchMap.clear();
}

//���� ָ�� branch ��ǰ������id
int logic_IfModule::getCurActiveTree(int branch_id) {

	//û�ҵ�������
	if( mvmu_BranchMap.count(branch_id)<=0 )
		return -1;

	return mvmu_BranchMap[branch_id].curActiveTree;
}

int logic_IfModule::setCurActiveTree(int branch_id,int tree_id) {

	//û�ҵ��� branch������
	if( mvmu_BranchMap.count(branch_id)<=0 )
		return -1;

	//û�ҵ��� tree
	if ( mvmis_TreeId_BranchMap.count(tree_id)<=0 )
		return -2;

	mvmu_BranchMap[branch_id].curActiveTree = tree_id;
	return 0;
}

///// \��ָ�� branch �����һ����
///// \return ���ش������ͣ���������0
int logic_IfModule::addTreeId(int branch_id,int tree_id) {

	//û�ҵ��� branch������
	if( mvmu_BranchMap.count(branch_id)<=0 )
		return -1;

	//�Ѿ��и�����
	if( mvmis_TreeId_BranchMap.count(tree_id) > 0 )
		return -2;

	mvmis_TreeId_BranchMap[tree_id] = branch_id;

	return 0;
}

///// \ɾ��һ����
int logic_IfModule::delTreeId(int tree_id) {

	//��û���ҵ�����
	if( mvmis_TreeId_BranchMap.count(tree_id) == 0 )
		return -1;

	mvmis_TreeId_BranchMap.erase(tree_id);

	return 0;
}


///
/// \brief get set ĳ�� branch ����
///

//get ָ�� branch��int content
int logic_IfModule::getBranchContentInt(int branch_id) {

	//�Ҳ�����branch������
	if( mvmu_BranchMap.count(branch_id)==0 )
		return -1;

	return mvmu_BranchMap[branch_id].contentInt;
}

//string
std::string logic_IfModule::getBranchContentStr(int branch_id) {

	//�Ҳ�����branch������
	if( mvmu_BranchMap.count(branch_id)==0 )
		return NULL;

	return mvmu_BranchMap[branch_id].contentStr;
}

///// \���ز�ͬ������룬��������0
int logic_IfModule::setBranchContent(int branch_id,int con_int) {

	//�Ҳ�����branch������
	if( mvmu_BranchMap.count(branch_id)==0 )
		return -1;

	mvmu_BranchMap[branch_id].contentInt = con_int;

	return 0;
}

//���� string
int logic_IfModule::setBranchContent(int branch_id,std::string con_str) {

	//�Ҳ�����branch������
	if( mvmu_BranchMap.count(branch_id)==0 )
		return -1;

	mvmu_BranchMap[branch_id].contentStr = con_str;

	return 0;

}


/////����һ��branch����Ҫ��ʼ�� whBranch ʵ��
int logic_IfModule::addBranch() {

	int max_branch_id = this->getMaxBranchId();
	max_branch_id++;

	whBranch newBranch;
	newBranch.curActiveTree = -1;
	newBranch.contentInt = INT_MIN;
	newBranch.contentStr = "";

	mvmu_BranchMap[max_branch_id] = newBranch;

	return 0;
}

//ɾ��һ��branch
int logic_IfModule::delBranch(int branch_id) {

	//�Ҳ�����branch������
	if( mvmu_BranchMap.count(branch_id)==0 )
		return -1;

	mvmu_BranchMap.erase(branch_id);
	return 0;
}

//�����ۼ�
int logic_IfModule::getMaxBranchId() {

	std::map<int, whBranch >::const_iterator it = mvmu_BranchMap.end();
	it--;
	return it->first;
}
