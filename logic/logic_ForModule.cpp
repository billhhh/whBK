/* 
* 
* function: for 模块实现文件
* 
* Date:2015-11-13
* 
*    Author: Bill Wang
*/

#include "logic_ForModule.h"
#include <assert.h>
#include "logic_WhData.h"

using namespace std;

logic_ForModule::logic_ForModule(int id)
	:logic_BasicModule(id,2003){
		//调用父类的构造函数 初始化id和type
		Init(); //初始化
}

//完整map构造函数，方便for内部析构操作
logic_ForModule::logic_ForModule(int id,
						 std::map <int,logic_Tree *> &tree_map,
						 std::map <int, logic_BasicModule *> &module_map,
						 std::map <int ,logic_Tree * > &m_tree_map,
						 std::map <logic_Tree * ,int > &tree_forif_map,
						 std::map<whPort, whPort > &conn_fromto_map,
						 std::map<whPort, whPort > &conn_tofrom_map,
						 const logic_BasicModule &bm
						 ):logic_BasicModule(id,2003,bm),treeMap(&tree_map),moduleMap(&module_map),mTreeMap(&m_tree_map),
						 treeForIfmap(&tree_forif_map),connFromToMap(&conn_fromto_map),connToFromMap(&conn_tofrom_map)
{
	Init();
}

logic_ForModule::~logic_ForModule() {

	Destroy(); //销毁内置所有对象
}

void logic_ForModule::Init() {

	//初始化类
	mvvu_treeList.clear();
	mvi_CurActiveTree = new logic_Tree(-1); //activeTree root节点编号为-1
	mvi_CurActiveTree->append_node(-1,-2); //结束节点

	//将activeTree加入treeMap
	(*treeMap)[this->composeActiveTreeId()] = mvi_CurActiveTree;
}

//返回当前激活树
logic_Tree * logic_ForModule::getCurActiveTree() {

	return mvi_CurActiveTree;
}

//设置当前激活树
void logic_ForModule::setCurActiveTree(logic_Tree * tree) {

	mvi_CurActiveTree = tree;
}

//向 For Module 添加一棵树 id，返回错误类型，正常返回0
int logic_ForModule::addTree(logic_Tree * tree) {

	int id = tree->mvi_TreeID;
	if ( mvvu_treeList.count(id) > 0 ){
		//发现已存在，错误返回
		return -1;
	}

	mvvu_treeList[id] = tree;
	return 0;
}

//在 For Module 中删除树 id，返回错误类型，正常返回0
int logic_ForModule::delTree(logic_Tree * tree) {

	int id = tree->mvi_TreeID;
	if ( mvvu_treeList.count(id) == 0 ){
		//发现待删除树id并不存在存在，错误返回
		return -1;
	}

	//如果是当前激活树被删，置空
	if( tree->mvi_TreeID == this->mvi_CurActiveTree->mvi_TreeID )
		this->mvi_CurActiveTree = NULL;

	mvvu_treeList.erase(id);
	return 0;
}


///////////////////新增删除/////////////
//析构是删掉所有树和模块
void logic_ForModule::Destroy() {

	//析构函数调用，销毁所有包含模块

	///// Step1、销毁所有包含树（不包括 activeTree）
	///// 注意：此时应该包含对program中的map的销毁
	//for (auto index : mvvu_treeList) {
	//	auto tree = index.second;
	//	DelTreeThroughPointer(tree);
	//}

	///// Step2、销毁 activeTree
	//DelActiveTree();
}

//通过树指针，完全销毁树中的模块
void logic_ForModule::DelTreeThroughPointer(logic_Tree * tree) {

	logic_TreeNode * root = tree->getRoot();
	recurs_DelTreeModule(root); //销毁模块实体

	treeForIfmap->erase(tree);

	//抹除树痕迹
	treeMap->erase(tree->mvi_TreeID);
	
	SAFE_DELETE(tree); //销毁树
	
}

//删除本模块的 activeTree
void logic_ForModule::DelActiveTree() {

	logic_TreeNode * root = mvi_CurActiveTree->getRoot();

	//跳过-2节点
	for (int i=0;i<root->mvvu_Children.size();++i) {
		//销毁每颗子树中的模块
		auto childId = root->mvvu_Children[i]->getID();
		if (childId != -2)
		{
			recurs_DelTreeModule(root->mvvu_Children[i]);
		}
	}

	SAFE_DELETE(mvi_CurActiveTree); //销毁树
	//抹除activeTree痕迹
	treeMap->erase( composeActiveTreeId() );
}

//完全删除一棵树所有节点的所有信息（各种实体map和connection map）
void logic_ForModule::recurs_DelTreeModule(logic_TreeNode *some) {

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
void logic_ForModule::DelModule(int id) {

	//删除所有map
	moduleMap->erase(id);
	mTreeMap->erase(id);

	DelAllParaConnect(id);
}

//删除关于某一模块的所有连线
void logic_ForModule::DelAllParaConnect(int id) {

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

//返回该 for 模块所有树root节点
std::vector<int > logic_ForModule::findAllRoots() {

	vector <int > L;
	for( std::map<int ,logic_Tree * >::iterator it = mvvu_treeList.begin();it != mvvu_treeList.end() ; ++it) {

		L.push_back(it->first);
	}

	logic_TreeNode * root = mvi_CurActiveTree->getRoot();
	L.push_back(root->getID());

	return L;
}

void logic_ForModule::recurs_GetId(logic_TreeNode *some,std::vector<int> & L) {

	L.push_back(some->getID());

	//和 getAllTreeNodeId() 连用，递归get id
	for (unsigned i = 0; i < some->mvvu_Children.size(); i++) {
		recurs_GetId(some->mvvu_Children[i],L);
	}
}

//返回该 for 模块Active树所有节点
std::vector<int > logic_ForModule::findAllRootsActive() {

	vector <int > L;

	logic_TreeNode * root = mvi_CurActiveTree->getRoot();
	this->recurs_GetId(root,L);

	std::vector<int>::iterator it = L.begin();
	L.erase(it);

	return L;
}

//获得（本层，不包括进一层的for或if中的模块id）所有模块id
std::vector<int > logic_ForModule::getAllModuleId() {

	vector<int > v;

	//处理activeTree
	recurs_GetId(mvi_CurActiveTree->getRoot(),v);
	v.erase(v.begin()); //删掉-1和-2节点
	v.erase(v.end());

	for (int i=0;i<mvvu_treeList.size();++i) {
		logic_Tree *tree = mvvu_treeList[i];
		recurs_GetId(tree->getRoot(),v);
	}

	return v;
}
