/* 
* 
* function: if 模块实现文件
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
		//调用父类的构造函数 初始化id和type
		Init(); //初始化
}

//完整map构造函数，方便for内部析构操作
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

	Destroy(); //销毁内置所有对象
}

void logic_IfModule::Init() {

	mvmu_BranchMap.clear();
	mvmis_Tree_BranchMap.clear();

	/// init声明两个默认branch
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

	//将activeTree加入treeMap
	(*treeMap)[this->composeActiveTreeId(1)] = newBranch.curActiveTree;
	(*treeMap)[this->composeActiveTreeId(2)] = newBranch2.curActiveTree;
}

//返回 指定 branch 当前激活树id
logic_Tree * logic_IfModule::getCurActiveTree(int branch_id) {

	//没找到，错误
	if( mvmu_BranchMap.count(branch_id)<=0 )
		return NULL;

	return mvmu_BranchMap[branch_id].curActiveTree;
}

int logic_IfModule::setCurActiveTree(int branch_id,logic_Tree * tree) {

	//没找到此 branch，错误
	if( mvmu_BranchMap.count(branch_id)<=0 )
		return -1;

	//没找到此 tree
	if ( mvmis_Tree_BranchMap.count(tree) <= 0 )
		return -2;

	mvmu_BranchMap[branch_id].curActiveTree = tree;
	return 0;
}

///// \向指定 branch 中添加一棵树
///// \return 返回错误类型，正常返回0
int logic_IfModule::addTree(int branch_id,logic_Tree * tree) {

	//没找到此 branch，错误
	if( mvmu_BranchMap.count(branch_id)<=0 )
		return -1;

	//已经有该树了
	if( mvmis_Tree_BranchMap.count(tree) > 0 )
		return -2;

	mvmis_Tree_BranchMap[tree] = branch_id;

	return 0;
}

///// \删除一棵树
int logic_IfModule::delTree(logic_Tree * tree) {

	//并没有找到该树
	if( mvmis_Tree_BranchMap.count(tree) == 0 )
		return -1;

	int tmpBranchId = this->getTreeBranch(tree);
	//如果是当前激活树被删，置空
	if( tree->mvi_TreeID == tmpBranchId )
		mvmu_BranchMap[tmpBranchId].curActiveTree = NULL;

	mvmis_Tree_BranchMap.erase(tree);

	return 0;
}


///
/// \brief get set 某个 branch 参数
///

//get 指定 branch的int content
int logic_IfModule::getBranchContentInt(int branch_id) {

	//找不到该branch，错误
	if( mvmu_BranchMap.count(branch_id)==0 )
		return -1;

	return mvmu_BranchMap[branch_id].contentInt;
}

//string
std::string logic_IfModule::getBranchContentStr(int branch_id) {

	//找不到该branch，错误
	if( mvmu_BranchMap.count(branch_id)==0 )
		return NULL;

	return mvmu_BranchMap[branch_id].contentStr;
}

///// \返回不同错误代码，正常返回0
int logic_IfModule::setBranchContent(int branch_id,int con_int) {

	//找不到该branch，错误
	if( mvmu_BranchMap.count(branch_id)==0 )
		return -1;

	mvmu_BranchMap[branch_id].contentInt = con_int;

	return 0;
}

//重载 string
int logic_IfModule::setBranchContent(int branch_id,std::string con_str) {

	//找不到该branch，错误
	if( mvmu_BranchMap.count(branch_id)==0 )
		return -1;

	mvmu_BranchMap[branch_id].contentStr = con_str;

	return 0;

}


/////增加一个branch，需要初始化 whBranch 实体
int logic_IfModule::addBranch() {

	int max_branch_id = this->getMaxBranchId();
	max_branch_id++;

	whBranch newBranch;
	newBranch.curActiveTree = NULL;
	newBranch.contentInt = INT_MIN;
	newBranch.contentStr = "";

	mvmu_BranchMap[max_branch_id] = newBranch;

	//将activeTree加入treeMap
	(*treeMap)[this->composeActiveTreeId(max_branch_id)] = newBranch.curActiveTree;

	return max_branch_id;
}

//删除一个branch
//返回需要在外面删除的树id列表
std::vector<int > logic_IfModule::delBranch(int branch_id) {

	std::vector<int > L;

	//当残余branch数量只有2个或以下，不允许删除
	if( mvmu_BranchMap.size() <= 3 )
		return L;

	//找不到该branch，错误
	if( mvmu_BranchMap.count(branch_id)==0 )
		return L;

	//遍历，收集待删除的树 id 列表
	for(std::map<logic_Tree *  ,int >::iterator it = mvmis_Tree_BranchMap.begin(); it != mvmis_Tree_BranchMap.end() ; ++it ) {

		if(  branch_id == it->second ) {

			L.push_back(it->first->mvi_TreeID);
			mvmis_Tree_BranchMap.erase(it);
		}
	}

	mvmu_BranchMap.erase(branch_id);

	//如果被删掉的分支是默认分支，将默认分支设置为第一个分支
	if( branch_id == this->mvi_DefaultBranch ) {

		std::map<int, whBranch >::iterator it = mvmu_BranchMap.begin();
		++it;
		this->mvi_DefaultBranch = it->first;
	}

	return L;
}

//方便累加
int logic_IfModule::getMaxBranchId() {

	if( mvmu_BranchMap.size() == 0 )
		return 0;

	std::map<int, whBranch >::const_iterator it = mvmu_BranchMap.end();
	it--;
	return it->first;
}

//获得某个tree属于哪个branch
int logic_IfModule::getTreeBranch(logic_Tree * tree) {

	return mvmis_Tree_BranchMap[tree];
}


///////////////////新增删除/////////////
//析构是删掉所有树和模块
void logic_IfModule::Destroy() {

	//析构函数调用，销毁所有包含模块

	for (std::map<int ,whBranch>::iterator it = mvmu_BranchMap.begin(); it != mvmu_BranchMap.end() ; ++it ) {

		whDelBranch(it->first);  //删除所有分支
	}

}

//从内部删除一个branch
int logic_IfModule::whDelBranch(int branch_id) {

	//当残余branch数量只有2个或以下，不允许删除
	if( mvmu_BranchMap.size() <= 2 )
		return -1;

	//找不到该branch，错误
	if( mvmu_BranchMap.count(branch_id)==0 )
		return L;

	//遍历，收集待删除的树 id 列表
	for(std::map<logic_Tree *  ,int >::iterator it = mvmis_Tree_BranchMap.begin(); it != mvmis_Tree_BranchMap.end() ; ++it ) {

		if(  branch_id == it->second ) {

			L.push_back(it->first->mvi_TreeID);
			mvmis_Tree_BranchMap.erase(it);
		}
	}

	mvmu_BranchMap.erase(branch_id);

	//如果被删掉的分支是默认分支，将默认分支设置为第一个分支
	if( branch_id == this->mvi_DefaultBranch ) {

		std::map<int, whBranch >::iterator it = mvmu_BranchMap.begin();
		++it;
		this->mvi_DefaultBranch = it->first;
	}

	/// Step1、销毁所有包含树（不包括 activeTree）
	for (int i = 0;i<mvvu_treeList.size() ;++i) {

		DelTreeThroughPointer(mvvu_treeList[i]);
	}

	/// Step2、销毁 activeTree
	DelActiveTree(branch_id);
}

//通过树指针，完全销毁树中的模块
void logic_IfModule::DelTreeThroughPointer(logic_Tree * tree) {

	logic_TreeNode * root = tree->getRoot();
	recurs_DelTreeModule(root); //销毁模块实体

	mvmis_Tree_BranchMap.erase(tree);
	treeForIfmap->erase(tree);
	SAFE_DELETE(tree); //销毁树
	//抹除树痕迹
	treeMap->erase(tree->mvi_TreeID);
}

//删除本模块的 activeTree
void logic_IfModule::DelActiveTree(int branch_id) {

	logic_Tree * activeTree = mvmu_BranchMap[branch_id].curActiveTree;
	logic_TreeNode * root = activeTree->getRoot();

	for (int i=0;i<root->mvvu_Children.size();++i) {
		//销毁没颗子树中的模块
		recurs_DelTreeModule(root->mvvu_Children[i]);
	}

	SAFE_DELETE(activeTree); //销毁树

	//抹除activeTree痕迹
	treeMap->erase( this->composeActiveTreeId(branch_id) );
}

//完全删除一棵树所有节点的所有信息（各种实体map和connection map）
void logic_IfModule::recurs_DelTreeModule(logic_TreeNode *some) {

	///// do sth here
	int tmpId = some->getID();
	if( moduleMap->count(tmpId) == 0 )
		assert(false);

	DelModule(tmpId);

	//和 getAllTreeNodeId() 连用，递归get id
	for (unsigned i = 0; i < some->mvvu_Children.size(); i++) {
		recurs_DelTreeModule(some->mvvu_Children[i]);
	}
}

//销毁关于一个module的一切信息
void logic_IfModule::DelModule(int id) {

	//删除所有map
	moduleMap->erase(id);
	mTreeMap->erase(id);

	DelAllParaConnect(id);
}

//删除关于某一模块的所有连线
void logic_IfModule::DelAllParaConnect(int id) {

	//处理连线
	for( map<whPort ,whPort >::iterator it = connFromToMap->begin(); it != connFromToMap->end(); ++it ) {

		if( id == it->first.moduleId ) {

			//如果 from 是该模块，所有这个 outModule 相关就需要删除
			whPort outPort = it->first;
			whPort inPort = (*connFromToMap)[outPort];
			connFromToMap->erase(outPort);
			connToFromMap->erase(inPort);

		}else if(id == it->second.moduleId) {

			//如果 to 是该模块
			whPort outPort = it->first;   // 相当于 whPort inPort = it->second;
			whPort inPort = (*connFromToMap)[outPort];
			connFromToMap->erase(outPort);
			connToFromMap->erase(inPort);
		}
	}
}
