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

using namespace std;

logic_IfModule::logic_IfModule(int id)
	:logic_BasicModule(id,2004){
		//���ø���Ĺ��캯�� ��ʼ��id��type
		Init(); //��ʼ��
}

//����map���캯��������for�ڲ���������
logic_IfModule::logic_IfModule(int id,
								 std::map <int,logic_Tree *> &tree_map,
								 std::map <int, logic_BasicModule *> &module_map,
								 std::map <int ,logic_Tree * > &m_tree_map,
								 std::map <logic_Tree * ,int > &tree_forif_map,
								 std::map<whPort, whPort > &conn_fromto_map,
								 std::map<whPort, whPort > &conn_tofrom_map
								 ):treeMap(&tree_map),moduleMap(&module_map),mTreeMap(&m_tree_map),
								 treeForIfmap(&tree_forif_map),connFromToMap(&conn_fromto_map),connToFromMap(&conn_tofrom_map)
{
	Init();
}

logic_IfModule::~logic_IfModule() {

	Destroy(); //�����������ж���
}

void logic_IfModule::Init() {

	mvmu_BranchMap.clear();
	mvmis_Tree_BranchMap.clear();

	/// init��������Ĭ��branch
	//branch 1
	whBranch newBranch;
	newBranch.curActiveTree = new logic_Tree(-1);
	newBranch.contentInt = INT_MIN;
	newBranch.contentStr = "";
	mvmu_BranchMap[1] = newBranch;

	//branch 2
	whBranch newBranch2;
	newBranch2.curActiveTree = new logic_Tree(-1);
	newBranch2.contentInt = INT_MIN;
	newBranch2.contentStr = "";
	mvmu_BranchMap[2] = newBranch2;

	//��activeTree����treeMap
	(*treeMap)[this->composeActiveTreeId(1)] = newBranch.curActiveTree;
	(*treeMap)[this->composeActiveTreeId(2)] = newBranch2.curActiveTree;
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

	int tmpBranchId = this->getTreeBranch(tree);
	//����ǵ�ǰ��������ɾ���ÿ�
	if( tree->mvi_TreeID == tmpBranchId )
		mvmu_BranchMap[tmpBranchId].curActiveTree = NULL;

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

	//��activeTree����treeMap
	(*treeMap)[this->composeActiveTreeId(max_branch_id)] = newBranch.curActiveTree;

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

//���ĳ��tree�����ĸ�branch
int logic_IfModule::getTreeBranch(logic_Tree * tree) {

	return mvmis_Tree_BranchMap[tree];
}


///////////////////����ɾ��/////////////
//������ɾ����������ģ��
void logic_IfModule::Destroy() {

	//�����������ã��������а���ģ��

	for (std::map<int ,whBranch>::iterator it = mvmu_BranchMap.begin(); it != mvmu_BranchMap.end() ; ++it ) {

		whDelBranch(it->first);  //ɾ�����з�֧
	}

}

//���ڲ�ɾ��һ��branch
int logic_IfModule::whDelBranch(int branch_id) {

	//������branch����ֻ��2�������£�������ɾ��
	if( mvmu_BranchMap.size() <= 2 )
		return -1;

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

	/// Step1���������а������������� activeTree��
	for (int i = 0;i<mvvu_treeList.size() ;++i) {

		DelTreeThroughPointer(mvvu_treeList[i]);
	}

	/// Step2������ activeTree
	DelActiveTree(branch_id);
}

//ͨ����ָ�룬��ȫ�������е�ģ��
void logic_IfModule::DelTreeThroughPointer(logic_Tree * tree) {

	logic_TreeNode * root = tree->getRoot();
	recurs_DelTreeModule(root); //����ģ��ʵ��

	mvmis_Tree_BranchMap.erase(tree);
	treeForIfmap->erase(tree);
	SAFE_DELETE(tree); //������
	//Ĩ�����ۼ�
	treeMap->erase(tree->mvi_TreeID);
}

//ɾ����ģ��� activeTree
void logic_IfModule::DelActiveTree(int branch_id) {

	logic_Tree * activeTree = mvmu_BranchMap[branch_id].curActiveTree;
	logic_TreeNode * root = activeTree->getRoot();

	for (int i=0;i<root->mvvu_Children.size();++i) {
		//����û�������е�ģ��
		recurs_DelTreeModule(root->mvvu_Children[i]);
	}

	SAFE_DELETE(activeTree); //������

	//Ĩ��activeTree�ۼ�
	treeMap->erase( this->composeActiveTreeId(branch_id) );
}

//��ȫɾ��һ�������нڵ��������Ϣ������ʵ��map��connection map��
void logic_IfModule::recurs_DelTreeModule(logic_TreeNode *some) {

	///// do sth here
	int tmpId = some->getID();
	if( moduleMap->count(tmpId) == 0 )
		assert(false);

	DelModule(tmpId);

	//�� getAllTreeNodeId() ���ã��ݹ�get id
	for (unsigned i = 0; i < some->mvvu_Children.size(); i++) {
		recurs_DelTreeModule(some->mvvu_Children[i]);
	}
}

//���ٹ���һ��module��һ����Ϣ
void logic_IfModule::DelModule(int id) {

	//ɾ������map
	moduleMap->erase(id);
	mTreeMap->erase(id);

	DelAllParaConnect(id);
}

//ɾ������ĳһģ�����������
void logic_IfModule::DelAllParaConnect(int id) {

	//��������
	for( map<whPort ,whPort >::iterator it = connFromToMap->begin(); it != connFromToMap->end(); ++it ) {

		if( id == it->first.moduleId ) {

			//��� from �Ǹ�ģ�飬������� outModule ��ؾ���Ҫɾ��
			whPort outPort = it->first;
			whPort inPort = (*connFromToMap)[outPort];
			connFromToMap->erase(outPort);
			connToFromMap->erase(inPort);

		}else if(id == it->second.moduleId) {

			//��� to �Ǹ�ģ��
			whPort outPort = it->first;   // �൱�� whPort inPort = it->second;
			whPort inPort = (*connFromToMap)[outPort];
			connFromToMap->erase(outPort);
			connToFromMap->erase(inPort);
		}
	}
}
