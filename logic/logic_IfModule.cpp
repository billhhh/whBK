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

// 	whBranch newBranch;
// 	newBranch.curActiveTree = NULL;
// 	newBranch.contentInt = INT_MIN;
// 	newBranch.contentStr = "";
// 	mvmu_BranchMap[0] = newBranch; ////////mvmu_BranchMap Ҫ��max

	mvmis_Tree_BranchMap.clear();
}

//���� ָ�� branch ��ǰ������id
logic_Tree * logic_IfModule::getCurActiveTree(int branch_id) {

	//û�ҵ�������
	if( mvmu_BranchMap.count(branch_id)<=0 )
		return NULL;

	return mvmu_BranchMap[branch_id].curActiveTree;
}

int logic_IfModule::setCurActiveTree(int branch_id,logic_Tree * tree) {

	//û�ҵ��� branch������
	if( mvmu_BranchMap.count(branch_id)<=0 )
		return -1;

	//û�ҵ��� tree
	if ( mvmis_Tree_BranchMap.count(tree) <= 0 )
		return -2;

	mvmu_BranchMap[branch_id].curActiveTree = tree;
	return 0;
}

///// \��ָ�� branch �����һ����
///// \return ���ش������ͣ���������0
int logic_IfModule::addTree(int branch_id,logic_Tree * tree) {

	//û�ҵ��� branch������
	if( mvmu_BranchMap.count(branch_id)<=0 )
		return -1;

	//�Ѿ��и�����
	if( mvmis_Tree_BranchMap.count(tree) > 0 )
		return -2;

	mvmis_Tree_BranchMap[tree] = branch_id;

	return 0;
}

///// \ɾ��һ����
int logic_IfModule::delTree(logic_Tree * tree) {

	//��û���ҵ�����
	if( mvmis_Tree_BranchMap.count(tree) == 0 )
		return -1;

	mvmis_Tree_BranchMap.erase(tree);

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
	newBranch.curActiveTree = NULL;
	newBranch.contentInt = INT_MIN;
	newBranch.contentStr = "";

	mvmu_BranchMap[max_branch_id] = newBranch;

	return max_branch_id;
}

//ɾ��һ��branch
//������Ҫ������ɾ������id�б�
std::vector<int > logic_IfModule::delBranch(int branch_id) {

	std::vector<int > L;

	//������branch����ֻ��2�������£�������ɾ��
	if( mvmu_BranchMap.size() <= 3 )
		return L;

	//�Ҳ�����branch������
	if( mvmu_BranchMap.count(branch_id)==0 )
		return L;

	//�������ռ���ɾ������ id �б�
	for(std::map<logic_Tree *  ,int >::iterator it = mvmis_Tree_BranchMap.begin(); it != mvmis_Tree_BranchMap.end() ; ++it ) {

		if(  branch_id == it->second ) {

			L.push_back(it->first->mvi_TreeID);
			mvmis_Tree_BranchMap.erase(it);
		}
	}

	mvmu_BranchMap.erase(branch_id);

	//�����ɾ���ķ�֧��Ĭ�Ϸ�֧����Ĭ�Ϸ�֧����Ϊ��һ����֧
	if( branch_id == this->mvi_DefaultBranch ) {

		std::map<int, whBranch >::iterator it = mvmu_BranchMap.begin();
		++it;
		this->mvi_DefaultBranch = it->first;
	}

	return L;
}

//�����ۼ�
int logic_IfModule::getMaxBranchId() {

	if( mvmu_BranchMap.size() == 0 )
		return 0;

	std::map<int, whBranch >::const_iterator it = mvmu_BranchMap.end();
	it--;
	return it->first;
}
