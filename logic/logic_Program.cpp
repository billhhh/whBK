/* 
* 
* function: 逻辑层森林组织结构
* 
* Date:2015-09-02
* 
*    Author: Bill Wang
*/

#include <iostream>  
#include <map>
#include <algorithm>
#include<stdlib.h>
#include "logic_Program.h"
#include "logic_Global.h"
#include "logic_Tree.h"
#include <assert.h>
#include "../TransStringNum.h"
#include "logic_ForModule.h"
#include "logic_IfModule.h"
#include "logic_WhData.h"

using namespace std;

//typedef logic_Tree tree_type;


logic_Program::logic_Program(int id,std::string prog_name)
	:mvs_ProgId(id),mvs_ProgName(prog_name)
{
	Init(); //初始化program

}

logic_Program::logic_Program(int id, std::string prog_name,std::map <int, logic_BasicModule *> imap)
	:mvs_ProgId(id),mvs_ProgName(prog_name),initModuleMap(imap)
{
	Init();
}

logic_Program::~logic_Program()
{
	prog_Destroy();
}

//除了id,prgname,其他内容都拷贝
logic_Program* logic_Program::copyPrg(logic_Program* newProgram)
{
	auto treeMap = getTreeMap();
	auto moduleMap = getModuleMap();
	auto moduleId_TreeMap = getModuleTreeMap();
	auto treeIn_IFFOR_Map = getForIfMap();
	auto fromToMap = getFromMap();
	auto toMap = getToMap();
	auto initModuleMap = getInit_m_map();
	auto varietyMap = getVarMap();

	newProgram->setTreeMap(treeMap);
	newProgram->setModuleMap(moduleMap);
	newProgram->setModuleTreeMap(mvmu_ModuleId_TreeMap);
	newProgram->setForIfMap(treeIn_IFFOR_Map);
	newProgram->setFromToMap(fromToMap);
	newProgram->setToFromMap(toMap);
	newProgram->setInitModuleMap(initModuleMap);
	newProgram->setInitVarMap(*varietyMap);

	return newProgram;

}

//普通初始化（干净的program）
void logic_Program::Init()
{
	mvmu_TreeMap.clear();
	//mvmu_TreeMap[0] = NULL;
	mvmu_ModuleMap.clear();
	//mvmu_ModuleMap[0] = NULL;  //Module 需要 getMax
	mvmu_ModuleId_TreeMap.clear();
	//mvmu_ModuleId_TreeMap[0] = NULL;

	mvvu_Conn_From_ToMap.clear();
	mvvu_Conn_To_FromMap.clear();

	mvmi_TreeId_For_IfIdMap.clear();
	//mvmi_TreeId_For_IfIdMap[0] = NULL;

	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!后台不要自己生成2001，由前端驱动
	//add_Tree(1);

	////建立module表项，仅一个开始模块
	//logic_BasicModule *bm = new logic_BasicModule();
	//mvmu_ModuleMap.insert(pair<_IdDataType , logic_BasicModule *>(bm->mvi_ModuleID,bm));

	//mvmu_ModuleId_TreeMap[1] = mvmu_TreeMap[1];
}

void logic_Program::prog_Destroy()
{
	cout<<"进入prog_Destroy"<<endl;


		//清空森林
	for(map<_IdDataType , logic_Tree *>::iterator it = mvmu_TreeMap.begin();it != mvmu_TreeMap.end(); ++it)
	{
		logic_Tree *tmpT = it->second;
		//tmpT->Destroy(tmpT->getRoot()); //这样会调用两次，堆错误
		SAFE_DELETE(tmpT);
	}

	//清空mvmu_ModuleMap
	for(map<_IdDataType , logic_BasicModule *>::iterator it = mvmu_ModuleMap.begin();it != mvmu_ModuleMap.end(); ++it)
		SAFE_DELETE(it->second);



	//清空映射表
// 	for(map<int , logic_Tree *>::iterator it = mvmu_ModuleId_TreeMap.begin();it != mvmu_ModuleId_TreeMap.end(); ++it)
// 	{
// 		logic_Tree *tmpT = it->second;
// 		//tmpT->Destroy(tmpT->getRoot()); //这样会调用两次，堆错误
// 		SAFE_DELETE(tmpT);
// 	}
}

bool logic_Program::add_Tree(_IdDataType rootId)
{
	if (mvmu_TreeMap.count(rootId)>0) //已存在，错误返回
		return false;

	logic_Tree* t = new logic_Tree(rootId);
	mvmu_TreeMap.insert(pair<_IdDataType , logic_Tree *>(t->mvi_TreeID,t));

	return true;
}

bool logic_Program::add_Tree(logic_Tree * t)
{
	if (mvmu_TreeMap.count(t->mvi_TreeID)>0) //已存在，错误返回
		return false;

	//logic_Tree *tmpTree = new logic_Tree(*t);
	mvmu_TreeMap[t->mvi_TreeID]=t;

	return true;
}

bool logic_Program::del_Tree(_IdDataType rootId)
{
	if (mvmu_TreeMap.count(rootId)==0) //不存在，删除错误
		return false;

	logic_Tree *tmpT = mvmu_TreeMap[rootId];
	SAFE_DELETE(tmpT);

	mvmu_TreeMap.erase(rootId);
	return true;
}

logic_Tree* logic_Program::search_Tree(_IdDataType rootId)
{
	if (mvmu_TreeMap.count(rootId)>0)
	{
		return mvmu_TreeMap[rootId];
	}

	throw NULL;
}

//根据树指针找ID，找到返回ID，找不到返回-1
_IdDataType logic_Program::search_Tree(logic_Tree* treePtr)
{
	if (mvmu_TreeMap.count(treePtr->mvi_TreeID)>0)
	{
		return treePtr->mvi_TreeID;
	}
	return -1;
}

//不负责释放 modulePtr 空间
bool logic_Program::add_Module(_IdDataType moduleId , logic_BasicModule* modulePtr)
{
	if (mvmu_ModuleMap.count(moduleId)>0) //已存在，错误返回
		return false;

	mvmu_ModuleMap[modulePtr->mvi_ModuleID] = modulePtr;

	return true;
}

bool logic_Program::add_Module(_IdDataType moduleId , int m_Type)
{
	if (mvmu_ModuleMap.count(moduleId)>0) //已存在，错误返回
		return false;

	logic_BasicModule *bm = NULL;
	if( 2003 == m_Type ) {

		//for
		logic_ForModule* tmpForModule = new logic_ForModule(moduleId,mvmu_TreeMap,mvmu_ModuleMap,
			mvmu_ModuleId_TreeMap,mvmi_TreeId_For_IfIdMap,mvvu_Conn_From_ToMap,mvvu_Conn_To_FromMap,
			*(this->initModuleMap[2003]));
		bm = tmpForModule;

		/// activeTree 操作放入for模块
		//得到默认activeTree，维护map
// 		logic_Tree * tmpActiveTree = tmpForModule->getCurActiveTree();
// 		mvmu_TreeMap[this->composeTreeId(moduleId)] = tmpActiveTree;

	}else if( 2004 == m_Type ) {

		//if
		logic_IfModule* tmpIfModule = new logic_IfModule(moduleId,mvmu_TreeMap,mvmu_ModuleMap,
			mvmu_ModuleId_TreeMap,mvmi_TreeId_For_IfIdMap,mvvu_Conn_From_ToMap,mvvu_Conn_To_FromMap,
			*(this->initModuleMap[2004]));
		bm = tmpIfModule;

		/// activeTree 操作放入if模块
		//得到默认的两个branch activeTree，维护map
// 		logic_Tree * tmpActiveTree = tmpIfModule->getCurActiveTree(1);
// 		mvmu_TreeMap[this->composeTreeId(moduleId,1)] = tmpActiveTree;
// 		tmpActiveTree = tmpIfModule->getCurActiveTree(2);
// 		mvmu_TreeMap[this->composeTreeId(moduleId,2)] = tmpActiveTree;

	}else //普通模块
	{
		//bm = new logic_BasicModule(moduleId,m_Type);
		bm = new logic_BasicModule(moduleId,m_Type,*(this->initModuleMap[m_Type]));
	}

	mvmu_ModuleMap.insert(pair<_IdDataType , logic_BasicModule *>(bm->mvi_ModuleID,bm));

	return true;
}

bool logic_Program::del_Module(_IdDataType moduleId)
{
	if (mvmu_ModuleMap.count(moduleId)==0) {
		//不存在，删除错误
		assert(false);
		return false;
	}

	//删除module实体
	logic_BasicModule * tmpModule = mvmu_ModuleMap[moduleId];
	mvmu_ModuleMap.erase(moduleId);

	//父类virtual析构函数，可以自动析构 for和if
	SAFE_DELETE(tmpModule);

	//删除所有连线
	this->DelAllParaConnect(moduleId);

	return true;
}

//删除关于某一模块的所有连线
void logic_Program::DelAllParaConnect(int id) {

	//处理连线
	for( map<whPort ,whPort >::iterator it = mvvu_Conn_From_ToMap.begin(); it != mvvu_Conn_From_ToMap.end(); ++it ) {

		if( id == it->first.moduleId ) {

			//如果 from 是该模块，所有这个 outModule 相关就需要删除
			whPort outPort = it->first;
			whPort inPort = mvvu_Conn_From_ToMap[outPort];
			mvvu_Conn_From_ToMap.erase(outPort);
			mvvu_Conn_To_FromMap.erase(inPort);

		}else if(id == it->second.moduleId) {

			//如果 to 是该模块
			whPort outPort = it->first;   // 相当于 whPort inPort = it->second;
			whPort inPort = mvvu_Conn_From_ToMap[outPort];
			mvvu_Conn_From_ToMap.erase(outPort);
			mvvu_Conn_To_FromMap.erase(inPort);
		}
	}
}

logic_BasicModule* logic_Program::searchModule(_IdDataType moduleId)
{
	if (mvmu_ModuleMap.count(moduleId)>0)
	{
		return mvmu_ModuleMap[moduleId];
	}

	return NULL;
}

_IdDataType logic_Program::searchModule(logic_BasicModule* modulePtr)
{
	if (mvmu_ModuleMap.count(modulePtr->mvi_ModuleID)>0)
	{
		return modulePtr->mvi_ModuleID;
	}
	return -1;
}

void logic_Program::setProgramName(const string name)
{
	mvs_ProgName = name;
}

std::string logic_Program::getName()
{
	return mvs_ProgName;
}

int logic_Program::getID()
{
	return mvs_ProgId;
}

void logic_Program::setID(int id)
{
	mvs_ProgId = id;
}

int logic_Program::getMaxModuleId() {

	if( mvmu_ModuleMap.size() == 0 )
		return 0;

	std::map<int, logic_BasicModule *>::const_iterator it = mvmu_ModuleMap.end();
	it--;
	return it->first;
}

//真正在森林中添加id，并实例化此 module
bool logic_Program::appendModule(int m_id,int pre_id,int m_type) {

	assert( mvmu_ModuleMap.count(pre_id)>=0 );

	// step1、在森林中加入这个id

	if ( 0 == pre_id ) {   //如果 pre_id 为 0 ，代表要新建一棵树

		logic_Tree *tree = new logic_Tree(m_id);
		this->add_Tree(tree);
		mvmu_TreeMap[m_id] = tree;
		mvmu_ModuleId_TreeMap[m_id] = tree;

	}else {
		//如果 pre_id 不为 0 ，插在 pre_id 后面
		if ( m_type == 2001 ) {
			return false;
		}

		logic_Tree *tree = mvmu_ModuleId_TreeMap[pre_id];
		tree->append_node(pre_id,m_id);

		mvmu_ModuleId_TreeMap[m_id] = tree;
	}

	// step2、真正生成这个module实体
	this->add_Module(m_id,m_type);

	return true;
}

bool logic_Program::frontInsModule(int m_id,int post_id,int m_type) {

	assert( mvmu_ModuleMap.count(post_id)>0 );

	if ( 0 == post_id ) {
		return false;
	}

	// step1、在森林中加入这个id

	//post模块是开始模块，不允许插入
	if ( mvmu_ModuleMap[post_id]->getModuleType() == 2001 ) {
		return false;
	}

	logic_Tree *tree = mvmu_ModuleId_TreeMap[post_id];

	if ( post_id == tree->mvi_TreeID ) { //发现后继节点是root，需要换根
		tree->exchangeRoot(m_id);
		mvmu_ModuleId_TreeMap[m_id] = tree;

		//update treeMap
		mvmu_TreeMap.erase(post_id);
		mvmu_TreeMap[m_id] = tree;

	}else{ //如果后继不是root，插入到两个点中间

		tree->insert_node(tree->getPreId(post_id),post_id,m_id);
		mvmu_ModuleId_TreeMap[m_id] = tree;
	}

	// step2、真正生成这个module实体
	this->add_Module(m_id,m_type);

	return true;
}

//单模块后插move
int logic_Program::backInsSingMove(int cur_m_id,int pre_m_id) {

	if ( pre_m_id != 0 && 0 >= (mvmu_ModuleMap.count(cur_m_id))*(mvmu_ModuleMap.count(pre_m_id)) ) {
		return -2; // 首先 cur_m_id 和 pre_m_id 都要有
	}

	//如果 cur_id 模块是开始
	if ( mvmu_ModuleMap[cur_m_id]->getModuleType() == 2001 ) {
			return -3; //模块类型错误
	}

	//注：不用新建module，只用处理树节点即可

	///// step1、插入新树节点
	logic_Tree *oldTree = mvmu_ModuleId_TreeMap[cur_m_id]; //待删除树，早点找到会更靠谱
	logic_Tree *insTree = NULL;
	if( 0 == pre_m_id ) {  ////////////必须用深拷贝，浅拷贝可能有危险

		//如果前插一棵空树

		if ( cur_m_id == oldTree->mvi_TreeID 
			&& oldTree->getRoot()->mvvu_Children.size()==0 
			) {

			///如果是前插空树，同时又是 唯一模块 错误
			return -5;
		}

		logic_TreeNode tmpCurNode( *(oldTree->node_search(cur_m_id)) ) ; //深拷贝构造到栈

		if ( tmpCurNode.mvvu_Children.size() > 1 ) {
			//如果孩子不是一个，错误
			return -4;
		}

		tmpCurNode.mvu_Parent = 0;
		tmpCurNode.mvvu_Children.clear();

		logic_TreeNode *tmpPassNode = new logic_TreeNode(tmpCurNode); //深拷贝构造到堆
		insTree = new logic_Tree(tmpPassNode); //新建一棵树，此node也必须新建，否则被下面的delnode了

		mvmu_TreeMap[insTree->mvi_TreeID] = insTree;

	}else {

		////// pre_m_id 不为0

		/////如果已存在，直接找到待插入树
		insTree = mvmu_ModuleId_TreeMap[pre_m_id];

		if( insTree->mvi_TreeID == oldTree->mvi_TreeID ) {

			//如果是本内直接move
			if ( insTree->innerTreeBackInsSingMove(pre_m_id,cur_m_id) < 0 )
				return -6; //树内move出错
			else
				return 0; //已move可直接返回

		}else {
			//树间移动
			insTree->append_node(pre_m_id,cur_m_id);
		}
	}

	///// step2、删除旧树节点（注：此处不可能有多个孩子）

	if( cur_m_id != oldTree->mvi_TreeID ) {

		//并非树根
		oldTree->del_node(cur_m_id);
	}else if(cur_m_id == oldTree->mvi_TreeID ) {

		if ( oldTree->getRoot()->mvvu_Children.size()==0 ) {

			//树中唯一模块，删除树（ 进入这个分支 pre_m_id 必然不会是0，上面已判断，详见错误-5 ）

			SAFE_DELETE(oldTree);
			mvmu_TreeMap.erase(cur_m_id);

			// Step3、（必须在此处，不然就return了）更新
			mvmu_ModuleId_TreeMap[cur_m_id] = insTree;

			return 0; //正常返回
		}else {
			//不是唯一模块

			oldTree->setFirstChildAsRoot();
		}

	}

	// Step3、更新
	mvmu_ModuleId_TreeMap[cur_m_id] = insTree;

	return 0; //正常返回
}

//前插move
//cur_m_id 是待move节点
//post_m_id 是节点后继
int logic_Program::frontInsSingMove(int cur_m_id,int post_m_id) {

	///// 上一层已判断 post_m_id 是否为 0

	if ( 0 >= (mvmu_ModuleMap.count(cur_m_id))*(mvmu_ModuleMap.count(post_m_id)) ) {
		return -2; //没找到插入点
	}

	//如果 post_m_id 模块是开始
	if ( mvmu_ModuleMap[post_m_id]->getModuleType() == 2001 ) {
		return -3; //模块类型错误
	}

	//注：不用新建module，只用处理树节点即可

	///// step1、插入新树节点
	logic_Tree *insTree = mvmu_ModuleId_TreeMap[post_m_id]; //待插入树
	logic_Tree *oldTree = mvmu_ModuleId_TreeMap[cur_m_id];  //待删除树

	int oldRootId = insTree->mvi_TreeID;
	if( post_m_id == oldRootId ) {

		//待插入节点要插在原树root之前
		if ( insTree->mvi_TreeID != oldTree->mvi_TreeID ) { //从其他树节点正常交换

			if( insTree->exchangeRoot(cur_m_id) == false )
				return -5;

			//只有 post_m_id 是根的情况，才更新tree map
			mvmu_TreeMap.erase(post_m_id);
			mvmu_TreeMap[cur_m_id] = insTree;
		} else {

			//树内交换，不用删除旧树节点，提前终止
			if( insTree->innerTreeExchangeRoot(cur_m_id) >= 0 ) {

				//只有 post_m_id 是根的情况，才更新tree map
				mvmu_TreeMap.erase(post_m_id);
				mvmu_TreeMap[cur_m_id] = insTree;

				return 0;
			} else {
				return -4; //树内交换失败
			}
		}

	}else {

		if ( insTree->mvi_TreeID == oldTree->mvi_TreeID ) { //本树操作

			if( insTree->innerTreeFrontInsSingMove(cur_m_id,post_m_id) >=0 ) {

				//树内正常操作，提前终止
				return 0;
			}else {
				return -6;
			}

		}
		//正常插入地方
		insTree->insert_node(insTree->getPreId(post_m_id),post_m_id,cur_m_id);
	}

	mvmu_ModuleId_TreeMap[cur_m_id] = insTree;

	///// step2、删除旧树节点（注：此处不可能有多个孩子）
	if( cur_m_id != oldTree->mvi_TreeID ) {

		//并非树根
		oldTree->del_node(cur_m_id);
	}else if(cur_m_id == oldTree->mvi_TreeID 
		|| oldTree->getRoot()->mvvu_Children.size()==0 ) {

			//树中唯一模块，删除树
			SAFE_DELETE(oldTree);
			mvmu_TreeMap.erase(cur_m_id);
	}

	return 0; //正常返回

}

//带孩子后插move
int logic_Program::backInsMultiMove(int cur_m_id,int pre_m_id) {

	if ( 0 != pre_m_id && 0 >= (mvmu_ModuleMap.count(cur_m_id))*(mvmu_ModuleMap.count(pre_m_id)) ) {
		return -2; // 首先 cur_m_id 和 pre_m_id 都要有
	}

	//如果 cur_id 模块是开始
	if ( mvmu_ModuleMap[cur_m_id]->getModuleType() == 2001 ) {
		return -3; //模块类型错误
	}

	//注：不用新建module，只用处理树节点即可

	/////////////开始/////////////

	///// step1、删除旧树节点
	///// 注：删除必须是第一步，不然 del_node_notConn 方法会删掉错误 parent 的孩子

	logic_Tree *oldTree = mvmu_ModuleId_TreeMap[cur_m_id]; //待删除树
	logic_TreeNode * insNode = oldTree->node_search(cur_m_id); //待插入节点（必须在此处寻找）

	if ( insNode->mvvu_Children.size() == 0 ) {
		//可能只有一个孩子
		return -4;
	}

	if( cur_m_id != oldTree->mvi_TreeID ) {

		//并非树根
		oldTree->del_node_notConn(cur_m_id); //断开 oldTree 与此节点的连接

	}else if(cur_m_id == oldTree->mvi_TreeID ) {

		//ROOT，删除树
		oldTree->del_node_notConn(cur_m_id); //如果是树根，直接将该树root置空
		SAFE_DELETE(oldTree); //放心删除树
		mvmu_TreeMap.erase(cur_m_id);
	}

	///// step2、插入新节点
	logic_Tree *insTree = NULL;
	if( 0 == pre_m_id ) { 
		//如果前插一棵空树

		insTree = new logic_Tree(insNode); //新建一棵树

		mvmu_TreeMap[insTree->mvi_TreeID] = insTree;
		mvmu_ModuleId_TreeMap[cur_m_id] = insTree;

	}else {
		/////如果已存在，直接找到待插入树
		insTree = mvmu_ModuleId_TreeMap[pre_m_id];

		logic_TreeNode * preNode = insTree->node_search(pre_m_id); //pre_m_id节点
		//如果 pre_m_id 不是叶子节点，错误返回
		if(preNode->mvvu_Children.size()>0) {
			return -4;
		}

		insTree->add_node(pre_m_id,insNode);

	}

	///// step3、更新 module tree映射
	recurs_update(insTree,insNode);

	return 0; //正常返回
}

//带祖先前插move
////////////////注：必然是插在一棵树的最前面/////////////////
int logic_Program::frontInsMultiMove(int cur_m_id,int post_m_id) {

	if ( 0 >= (mvmu_ModuleMap.count(cur_m_id)) ) {
		return -2; //没找到插入点
	}

	//如果 post_m_id 模块是开始
	if ( post_m_id != 0 && mvmu_ModuleMap[post_m_id]->getModuleType() == 2001 ) {
			return -3; //模块类型错误
	}

	//注：不用新建module，只用处理树节点即可

	if( 0 == post_m_id ) {

		//空插
		//相当于 backInsMultiMove 到背景

		logic_Tree *oldTree = mvmu_ModuleId_TreeMap[cur_m_id];

		///// step1、删除旧树节点，同时将断开部分生成新树
		logic_TreeNode * curNode = oldTree->node_search(cur_m_id);
		if( curNode->mvvu_Children.size() == 1 ) {

			logic_TreeNode * breakNode = curNode->mvvu_Children[0];
			oldTree->del_node_notConn(breakNode->getID());
			logic_Tree * newTree = new logic_Tree(breakNode);

			mvmu_TreeMap[newTree->getRoot()->getID()] = newTree;
			///// 更新 module tree映射 insNode分支
			recurs_update(newTree,newTree->getRoot());
		}else if( curNode->mvvu_Children.size() > 1 ) {
			assert(false);
		}

	} else {

		logic_Tree *insTree = mvmu_ModuleId_TreeMap[post_m_id]; //新插入树
		logic_Tree *oldTree = mvmu_ModuleId_TreeMap[cur_m_id];

		//如果 post_m_id 不是根节点，错误返回
		if( post_m_id!=insTree->mvi_TreeID ) {
			return -4;
		}

		///// step1、删除旧树节点，同时将断开部分生成新树
		logic_TreeNode * curNode = oldTree->node_search(cur_m_id);
		if( curNode->mvvu_Children.size() == 1 ) {

			logic_TreeNode * breakNode = curNode->mvvu_Children[0];
			oldTree->del_node_notConn(breakNode->getID());
			logic_Tree * newTree = new logic_Tree(breakNode);

			mvmu_TreeMap[newTree->getRoot()->getID()] = newTree;
			///// 更新 module tree映射 insNode分支
			recurs_update(newTree,newTree->getRoot());
		}else if( curNode->mvvu_Children.size() > 1 ) {
			assert(false);
		}
		
		///// step2、插入新树节点

		logic_TreeNode * insNode = insTree->getRoot(); //待插入节点
		oldTree->add_node(cur_m_id,insNode); //insTree接到oldTree上

		//必然是ROOT，直接删除原insTree
		insTree->del_node_notConn(post_m_id); //是root，直接置空
		SAFE_DELETE(insTree); //放心删除树
		mvmu_TreeMap.erase(post_m_id);

		///// 更新 module tree映射 insNode分支
		recurs_update(oldTree,insNode);

	}

	return 0; //正常返回
}

//新增孩子move
int logic_Program::addLeafMove(int cur_m_id,int pre_m_id) {

	if ( 0 >= (mvmu_ModuleMap.count(cur_m_id))*(mvmu_ModuleMap.count(pre_m_id)) ) {
		return -2; // 首先 cur_m_id 和 pre_m_id 都要有
	}

	//如果 cur_id 模块是开始
	if ( mvmu_ModuleMap[cur_m_id]->getModuleType() == 2001 ) {
			return -3; //模块类型错误
	}

	if ( addLeafCheckPre(cur_m_id,pre_m_id) < 0 ) {
		return -4;
	}

	logic_Tree *oldTree = mvmu_ModuleId_TreeMap[cur_m_id]; //待删除树
	//该节点必须是该树的根节点
	if( oldTree->mvi_TreeID != cur_m_id )
		assert(false);

	logic_Tree *insTree = mvmu_ModuleId_TreeMap[pre_m_id];
	logic_TreeNode * insNode = insTree->node_search(pre_m_id); //待插入节点
	logic_TreeNode * curNode = oldTree->getRoot(); //当前节点

	curNode->mvu_Parent = insNode;

	/// Step1、接入新节点
	insNode->mvvu_Children.push_back(curNode);

	/// Step2、删除旧树map信息
	mvmu_TreeMap.erase(cur_m_id);
	oldTree->setRoot(NULL);
	SAFE_DELETE(oldTree);

	/// Step3、更新模块树map信息
	recurs_update(insTree,curNode);

	return 0;
}

//通过一个模块id，找到所在树
logic_Tree* logic_Program::getTreeFromId(int m_id) {

	return mvmu_ModuleId_TreeMap[m_id];
}

std::map<int,logic_Tree*> logic_Program::getTreeMap() {
	return mvmu_TreeMap;
}

std::map <int ,logic_BasicModule* > logic_Program::getModuleMap() {
	return mvmu_ModuleMap;
}

std::map <int ,logic_Tree * > logic_Program::getModuleTreeMap()
{
	return mvmu_ModuleId_TreeMap;
}

void logic_Program::setModuleTreeMap(std::map <int, logic_Tree * > moduleTreeMap)
{
	mvmu_ModuleId_TreeMap = moduleTreeMap;
}

std::map <logic_Tree * ,int > logic_Program::getForIfMap()
{
	return mvmi_TreeId_For_IfIdMap;
}

void logic_Program::setForIfMap(std::map <logic_Tree *, int > forIfMap)
{
	mvmi_TreeId_For_IfIdMap = forIfMap;
}

bool logic_Program::delModule(int m_id) {

	if (mvmu_ModuleMap.count(m_id)==0) //不存在，删除错误
		return false;

	// step1、在森林中删掉这个id
	logic_Tree *tree = mvmu_ModuleId_TreeMap[m_id]; //得到所在的树

	if (m_id != tree->mvi_TreeID ) {
		///!!!!!!!!!!!!!!!!!!!!不是ROOT!!!!!!!!!!!!!!!!!!!!!!!!

		logic_TreeNode *delNode = tree->node_search(m_id);

		if(delNode->mvvu_Children.size() == 1) {

			//1、非ROOT，且只有一个孩子，正常删除
			tree->del_node(m_id);
			mvmu_ModuleId_TreeMap.erase(m_id);

		}else if(delNode->mvvu_Children.size() > 1) {

			//2、非root，有多个孩子，拆成多棵树

			//后面的孩子需要建立n颗树
			for (int i=0; i<delNode->mvvu_Children.size() ; ++i ) {

				delNode->mvvu_Children.at(i)->mvu_Parent = NULL;
				logic_Tree * tmpTree = new logic_Tree(delNode->mvvu_Children.at(i)); //新建树
				mvmu_TreeMap[tmpTree->mvi_TreeID] = tmpTree; //树map 新增
				updateMId_TreeMap(tmpTree); //更新映射表

				//如果此树（root）在 for 或 if 中，需要特殊处理
				if( mvmi_TreeId_For_IfIdMap.count(tree) > 0 ) {

					//得到容器Module
					logic_BasicModule * tmpModule = mvmu_ModuleMap[mvmi_TreeId_For_IfIdMap[tree]];

					if( tmpModule->getModuleType() == 2003 ) {

						//for
						logic_ForModule * tmpForModule = (logic_ForModule *) tmpModule;
						//不用删除原树，直接加入新树
						tmpForModule->addTree(tmpTree);

					}else if( tmpModule->getModuleType() == 2004 ) {

						//if
						logic_IfModule * tmpIfModule = (logic_IfModule *) tmpModule;
						int tmpBranchId = tmpIfModule->getTreeBranch( mvmu_ModuleId_TreeMap[m_id] );
						tmpIfModule->addTree(tmpBranchId,tmpTree);
					}

					int for_if_id = mvmi_TreeId_For_IfIdMap[tree];
					mvmi_TreeId_For_IfIdMap[tmpTree] = for_if_id;

				}
			}

			//原树不动，只须将当前节点父节点这点移除
			tree->del_node_notConn(m_id);
			SAFE_DELETE(delNode);  //正式删除此节点
			mvmu_ModuleId_TreeMap.erase(m_id);
		}

	}else {

		///!!!!!!!!!!!!!!!!!!!!!!!!!!!ROOT!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

		logic_TreeNode *oldRoot = tree->getRoot();

		if(oldRoot->mvvu_Children.size() == 1) {
			//1、且只有一个孩子，正常删除（tree没有改变，不必更新映射表）
			tree->del_node(m_id);
			mvmu_ModuleId_TreeMap.erase(m_id);

			/////// tree不变，不用更新 mvmi_TreeId_For_IfIdMap

		}else if(oldRoot->mvvu_Children.size() > 1) {

			//2、root有n个孩子，拆成n棵树，每棵树是树根

			//后面需要建立n-1颗树
			for (int i=1; i<oldRoot->mvvu_Children.size() ; ++i ) {

				oldRoot->mvvu_Children.at(i)->mvu_Parent = NULL;
				logic_Tree * tmpTree = new logic_Tree(oldRoot->mvvu_Children.at(i)); //新建树
				mvmu_TreeMap[tmpTree->mvi_TreeID] = tmpTree; //树map 新增
				updateMId_TreeMap(tmpTree); //更新映射表


				//如果此树（root）在 for 或 if 中，需要特殊处理
				if( mvmi_TreeId_For_IfIdMap.count(tree) > 0 ) {

					logic_BasicModule * tmpModule = mvmu_ModuleMap[mvmi_TreeId_For_IfIdMap[tree]];

					if( tmpModule->getModuleType() == 2003 ) {

						//for
						logic_ForModule * tmpForModule = (logic_ForModule *) tmpModule;
						//不用删除原树，直接加入新树
						tmpForModule->addTree(tmpTree);

					}else if( tmpModule->getModuleType() == 2004 ) {

						//if
						logic_IfModule * tmpIfModule = (logic_IfModule *) tmpModule;
						int tmpBranchId = tmpIfModule->getTreeBranch( mvmu_ModuleId_TreeMap[m_id] );
						tmpIfModule->addTree(tmpBranchId,tmpTree);
					}

					int for_if_id = mvmi_TreeId_For_IfIdMap[tree];
					mvmi_TreeId_For_IfIdMap[tmpTree] = for_if_id;

				}

			}

			//原树直接设置孩子为root（tree没有改变，不必更新映射表）
			tree->setFirstChildAsRoot(); //将root的唯一孩子设置为root，同时删除oldRoot
			mvmu_TreeMap.erase(m_id);
			mvmu_ModuleId_TreeMap.erase(m_id);

		}else if(oldRoot->mvvu_Children.size() == 0) {

			//树中唯一的模块，删除树
			SAFE_DELETE(mvmu_ModuleId_TreeMap[m_id]);
			mvmu_TreeMap.erase(m_id);
			mvmu_ModuleId_TreeMap.erase(m_id);

			//但如果此树（root）在 for 或 if 中，需要特殊处理
			if( mvmi_TreeId_For_IfIdMap.count(tree) > 0 ) {

				logic_BasicModule * tmpModule = mvmu_ModuleMap[mvmi_TreeId_For_IfIdMap[tree]];

				if( tmpModule->getModuleType() == 2003 ) {

					//for
					logic_ForModule * tmpForModule = (logic_ForModule *) tmpModule;
					tmpForModule->delTree( mvmu_ModuleId_TreeMap[m_id] );

				}else if( tmpModule->getModuleType() == 2004 ) {

					//if
					logic_IfModule * tmpIfModule = (logic_IfModule *) tmpModule;
					tmpIfModule->delTree( mvmu_ModuleId_TreeMap[m_id] );

				}

				mvmi_TreeId_For_IfIdMap.erase(tree); //完全删除

			}
		}
		
	}


	// step2、在map中删掉这个module实体
	this->del_Module(m_id);

	return true;
}

void logic_Program::updateMId_TreeMap(logic_Tree *tree) {
	//将一棵树中所有module tree映射改为当前tree
	this->recurs_update(tree,tree->getRoot());
}

void logic_Program::recurs_update(logic_Tree *tree,logic_TreeNode *some) {

	mvmu_ModuleId_TreeMap[some->getID()] = tree;

	//和 updateMId_TreeMap() 连用，递归更新
	for (unsigned i = 0; i < some->mvvu_Children.size(); i++) {
		recurs_update(tree,some->mvvu_Children[i]);
	}
}

bool logic_Program::addLeafModule(int pre_id,int m_id) {

	if ( 0 == pre_id ) {
		return false;
	}

	assert(mvmu_ModuleMap.count(pre_id)!=0); //不存在pre，错误

	

	return true;
}

int logic_Program::getModulePreId(int m_id) {

	if (mvmu_ModuleMap.count(m_id)==0) //不存在，错误
		return 0;

	int resid = mvmu_ModuleId_TreeMap[m_id]->getPreId(m_id);

	return resid;
}

std::vector<int > logic_Program::getModulePostId(int m_id) {

	std::vector<int > L;

	if (mvmu_ModuleMap.count(m_id) == 0) //不存在，错误
		return L;

	logic_TreeNode *tNode = mvmu_ModuleId_TreeMap[m_id]->node_search(m_id);

	if (tNode == NULL)
		return L;

	for (int i=0; i< tNode->mvvu_Children.size();++i ) {
		L.push_back(tNode->mvvu_Children.at(i)->getID());
	}

	return L;

}

//得到该模块所在树的根节点的模块id
int logic_Program::getRootModuleId(int m_id)
{
	int rootModuleId = 0;

	if (mvmu_ModuleMap.count(m_id) == 0) //不存在，错误
		return rootModuleId;

	logic_Tree* theTree = getTreeFromId(m_id);
	logic_TreeNode* rootNode = theTree->getRoot();

	rootModuleId = rootNode->getID();
	return rootModuleId;
}

//查询两个module是否在同一颗树内
bool logic_Program::IsInSameTree(int cur_m_id, int other_m_id)
{
	assert(mvmu_ModuleMap.count(cur_m_id) != 0 && mvmu_ModuleMap.count(other_m_id)); //判定是否存在

	logic_Tree* oneTree = getTreeFromId(cur_m_id);
	logic_Tree* otherTree = getTreeFromId(other_m_id);
	
	if (oneTree == otherTree)
		return true;
	else
		return false;
}


std::vector<int > logic_Program::getForModuleRootPostId(int for_Id){
	std::vector<int > L;

	if (mvmu_ModuleMap.count(for_Id) == 0) //不存在，错误
		return L;

	auto forModule = (logic_ForModule*)mvmu_ModuleMap[for_Id];
	auto activeTree = forModule->getCurActiveTree();
	auto rootNode = activeTree->getRoot();
	for(int i = 0; i < rootNode->mvvu_Children.size();++i){
		L.push_back(rootNode->mvvu_Children.at(i)->getID());
	}

	return L;
}


std::vector<int > logic_Program::getIfModuleBranchPostId(int if_id, int local_branch_id)
{
	std::vector<int > L;

	if (mvmu_ModuleMap.count(if_id) == 0) //不存在，错误
		return L;

	auto IfModule = (logic_IfModule*)mvmu_ModuleMap[if_id];
	if (!IfModule->isBranchExist(local_branch_id))
		return L; 

	auto activeTree = IfModule->getCurActiveTree(local_branch_id);
	auto rootNode = activeTree->getRoot();
	for (int i = 0; i < rootNode->mvvu_Children.size(); ++i){
		L.push_back(rootNode->mvvu_Children.at(i)->getID());
	}

	return L;
}

int logic_Program::getForModuleEndPreId(int for_id)
{
	if (mvmu_ModuleMap.count(for_id) == 0) //不存在，错误
		return 0;

	auto forModule = (logic_ForModule*)mvmu_ModuleMap[for_id];
	auto activeTree = forModule->getCurActiveTree();
	auto preId = activeTree->getPreId(-2);
	
	return preId;
}

int	logic_Program::getIfModuleEndPreId(int if_id, int local_branch_id)
{
	if (mvmu_ModuleMap.count(if_id) == 0) //不存在，错误
		return 0;

	auto IfModule = (logic_IfModule*)mvmu_ModuleMap[if_id];
	if (!IfModule->isBranchExist(local_branch_id))
		return 0;

	auto activeTree = IfModule->getCurActiveTree(local_branch_id);
	auto preId = activeTree->getPreId(-2);

	return preId;
}

std::vector<int> logic_Program::getAllTreeNodeId(int tree_id) {

	std::vector<int > L;

	if( mvmu_TreeMap.count(tree_id) <=0 ) {
		//错误，返回空集
		return L;
	}

	logic_Tree *tree = mvmu_TreeMap[tree_id];
	this->recurs_GetId(tree->getRoot(),L);

	return L;
}

void logic_Program::recurs_GetId(logic_TreeNode *some,std::vector<int> & L) {

	L.push_back(some->getID());

	//和 getAllTreeNodeId() 连用，递归get id
	for (unsigned i = 0; i < some->mvvu_Children.size(); i++) {
		recurs_GetId(some->mvvu_Children[i],L);
	}
}

std::string logic_Program::getModulePara(int type,int m_id,int p_id) {

	//MAX_VALUE = 0,//最大值
	//MIN_VALUE, //最小值
	//INIT, //初始值
	//CUR //当前值

	if ( 0 == mvmu_ModuleMap.count(m_id) ) {
		return NULL; //错误
	}

	logic_BasicPara *tPara = mvmu_ModuleMap[m_id]->getPara(p_id);
	std::string res;

	switch (type)
	{
	case 0: //max
		res = numToString<int > (tPara->mvd_Max);
		break;

	case 1: //min
		res = numToString<int > (tPara->mvd_Min);
		break;

	case 2: //init
		{
			logic_BasicPara *tInitPara = mvmu_ModuleMap[m_id]->getInitPara(p_id);
			res = tInitPara->mvs_Value;
			break;
		}

	case 3: //cur
		res = tPara->mvs_Value;
		break;

	default:
		break;
	}

	return res;

}

void logic_Program::setModulePara(int m_id,int p_id,std::string p_value) {

	if ( 0 == mvmu_ModuleMap.count(m_id) ) {
		return ; //错误
	}

	logic_BasicPara *tPara = mvmu_ModuleMap[m_id]->getPara(p_id);
	tPara->mvs_Value = p_value;
}

WinSwitcherType logic_Program::getModuleWinSwType(int m_id,int m_modeValue) {

	if ( 0 == mvmu_ModuleMap.count(m_id) ) {
		//return ; //错误
		assert(false);
	}

	logic_BasicModule *tModule = mvmu_ModuleMap[m_id];
	return tModule->getWSType(m_modeValue);
}

std::string logic_Program::getModuleWinSwValue(int m_id) {

	if ( 0 == mvmu_ModuleMap.count(m_id) ) {
		return NULL; //错误
	}

	logic_BasicModule *tModule = mvmu_ModuleMap[m_id];
	return tModule->getWSValue();

}

void logic_Program::setModuleWinSwValue(int m_id,std::string ws_value) {

	if ( 0 == mvmu_ModuleMap.count(m_id) ) {
		return ; //错误
	}

	logic_BasicModule *tModule = mvmu_ModuleMap[m_id];
	tModule->setWSValue(ws_value);
}

int logic_Program::getModuleDaisyChainValue(int m_id) {

	if ( 0 == mvmu_ModuleMap.count(m_id) ) {
		return -1; //错误
	}

	logic_BasicModule *tModule = mvmu_ModuleMap[m_id];
	return tModule->getDaisyChainValue();
}

void logic_Program::setModuleDaisyChainValue(int m_id,int chain_value) {

	if ( 0 == mvmu_ModuleMap.count(m_id) ) {
		return ; //错误
	}

	logic_BasicModule *tModule = mvmu_ModuleMap[m_id];
	tModule->setDaisyChainValue(chain_value);
}

std::vector<int > logic_Program::getModuleParamsIds(int m_id,int mode_value) {

	if ( 0 == mvmu_ModuleMap.count(m_id) ) {
		//return ; //错误
		assert(false);
	}

	logic_BasicModule *tModule = mvmu_ModuleMap[m_id];
	return tModule->getParamsIds(mode_value);
}

int logic_Program::getModuleModeValue(int m_id) {

	if ( 0 == mvmu_ModuleMap.count(m_id) ) {
		return -1; //错误
	}

	logic_BasicModule *tModule = mvmu_ModuleMap[m_id];
	return tModule->getModeValue();
}

void logic_Program::setModuleModeValue(int m_id,int mode_id) {

	if ( 0 == mvmu_ModuleMap.count(m_id) ) {
		return ; //错误
	}

	logic_BasicModule *tModule = mvmu_ModuleMap[m_id];
	tModule->setModeValue(mode_id);
}

//得到所有treenode
std::vector<logic_TreeNode *> logic_Program::getAllTreeNode(int rootID) {

	std::vector<logic_TreeNode *> L;

	if ( 0 == mvmu_ModuleMap.count(rootID) ) {
		return L; //错误
	}

	logic_Tree *tree = mvmu_TreeMap[rootID];
	this->recurs_GetNode(tree->getRoot(),L);

	return L;

}

std::map<whPort, whPort > logic_Program::getFromMap()
{
	return mvvu_Conn_From_ToMap;
}

std::map<whPort, whPort> logic_Program::getToMap()
{
	return mvvu_Conn_To_FromMap;
}


void logic_Program::setFromToMap(std::map<whPort, whPort > fromToMap)
{
	mvvu_Conn_From_ToMap = fromToMap;
}

void logic_Program::setToFromMap(std::map<whPort, whPort > toFromMap)
{
	mvvu_Conn_To_FromMap = toFromMap;
}


void logic_Program::recurs_GetNode(logic_TreeNode *some,std::vector<logic_TreeNode *> & L) {

	L.push_back(some);

	//和 getAllTreeNodeId() 连用，递归get id
	for (unsigned i = 0; i < some->mvvu_Children.size(); i++) {
		recurs_GetNode(some->mvvu_Children[i],L);
	}
}

/// \brief for if

//insert into for
bool logic_Program::insertModuleIntoFor(int m_id,int pre_id,int m_type,int for_id) {

	/////此处已必然是 append 了，且 pre_id 必然是0

	if( mvmu_ModuleMap.count(for_id) == 0 )
		return false;

	if( -1 == pre_id ) //向activeTree后面直接插入一个模块
		return this->appendActiveTreeInsertFor(m_id,m_type,for_id);

	///// Step1、调用已经写好的 appendModule() 方法，pre_id 必然是0
	this->appendModule(m_id,0,m_type);

	///// Step2、往 for 模块中加树
	logic_BasicModule * tmpModule = mvmu_ModuleMap[for_id];

	if( 2003 != tmpModule->getModuleType() ) //不是for模块，错误
		return false;

	/// type 一定是2003
	logic_ForModule *tmpForModule = (logic_ForModule *)tmpModule; //强制转换成for module
	
	if( tmpForModule->addTree(mvmu_ModuleId_TreeMap[m_id]) < 0 )
		return false;

	mvmi_TreeId_For_IfIdMap[mvmu_ModuleId_TreeMap[m_id]] = for_id;

	return true;
}

//insert into if
bool logic_Program::insertModuleIntoIf(int m_id,int pre_id,int m_type,int if_id,int branch_id) {

	/////此处已必然是 append 了，且 pre_id 必然是0

	if( mvmu_ModuleMap.count(if_id) == 0 )
		return false;

	if( -1 == pre_id ) //向activeTree后面直接插入一个模块
		return this->appendActiveTreeInsertIf(m_id,m_type,if_id,branch_id);

	///// Step1、调用已经写好的 appendModule() 方法
	this->appendModule(m_id,pre_id,m_type);

	///// Step2、往 for 模块中加树
	logic_BasicModule * tmpModule = mvmu_ModuleMap[if_id];

	if( 2004 != tmpModule->getModuleType() ) //不是if模块，错误
		return false;

	/// type 一定是2004
	logic_IfModule *tmpIfModule = (logic_IfModule *)tmpModule; //强制转换成if module
	
	if( tmpIfModule->addTree( branch_id,mvmu_ModuleId_TreeMap[m_id] ) < 0 )
		return false;

	mvmi_TreeId_For_IfIdMap[mvmu_ModuleId_TreeMap[m_id]] = if_id;

	return true;
}

// get for 当前active树
int logic_Program::getForActiveTree(int for_id) {

	if( mvmu_ModuleMap.count(for_id) == 0 )
		return -3;

	logic_BasicModule * tmpModule = mvmu_ModuleMap[for_id];

	if( 2003 != tmpModule->getModuleType() ) //不是for模块，错误
		return -4;

	/// type 一定是2003
	logic_ForModule *tmpForModule = (logic_ForModule *)tmpModule; //强制转换成for module

	logic_Tree * tree = tmpForModule->getCurActiveTree(); //可能小于0

	return tree->mvi_TreeID;
}

//if 当前active树
int logic_Program::getIfActiveTree(int if_id,int branch_id) {

	if( mvmu_ModuleMap.count(if_id) == 0 )
		return -3;

	logic_BasicModule * tmpModule = mvmu_ModuleMap[if_id];

	if( 2004 != tmpModule->getModuleType() ) //不是if模块，错误
		return -4;

	/// type 一定是2004
	logic_IfModule *tmpIfModule = (logic_IfModule *)tmpModule; //强制转换成if module

	logic_Tree * tree = tmpIfModule->getCurActiveTree(branch_id); //可能小于0

	return tree->mvi_TreeID;
}

// set for
void logic_Program::setForActiveTree(int for_id,int tree_id) {

	assert( mvmu_ModuleMap.count(for_id) > 0 ); //假定 count 大于0

	logic_BasicModule * tmpModule = mvmu_ModuleMap[for_id];

	assert( 2003 == tmpModule->getModuleType() ); //不是for模块，错误

	/// type 一定是2003
	logic_ForModule *tmpForModule = (logic_ForModule *)tmpModule; //强制转换成for module
	tmpForModule->setCurActiveTree( mvmu_ModuleId_TreeMap[tree_id] );

	return;
}

//if
void logic_Program::setIfActiveTree(int if_id,int branch_id,int tree_id) {

	assert( mvmu_ModuleMap.count(if_id) > 0 ); //假定 count 大于0

	logic_BasicModule * tmpModule = mvmu_ModuleMap[if_id];

	assert( 2004 == tmpModule->getModuleType() ); //不是if模块，错误

	/// type 一定是2004
	logic_IfModule *tmpIfModule = (logic_IfModule *)tmpModule; //强制转换成if module
	tmpIfModule->setCurActiveTree( branch_id,mvmu_ModuleId_TreeMap[tree_id] ); //可能小于0

	return;
}

//get 指定 branch的int content
int logic_Program::getIfBranchContentInt(int if_id,int branch_id) {

	if( mvmu_ModuleMap.count(if_id) == 0 )
		return -3;

	logic_BasicModule * tmpModule = mvmu_ModuleMap[if_id];

	if( 2004 != tmpModule->getModuleType() ) //不是if模块，错误
		return -4;

	/// type 一定是2004
	logic_IfModule *tmpIfModule = (logic_IfModule *)tmpModule; //强制转换成if module

	int content = tmpIfModule->getBranchContentInt(branch_id); //可能小于0

	return content;
}

//string
std::string logic_Program::getIfBranchContentStr(int if_id,int branch_id) {

	if( mvmu_ModuleMap.count(if_id) == 0 )
		return NULL;

	logic_BasicModule * tmpModule = mvmu_ModuleMap[if_id];

	if( 2004 != tmpModule->getModuleType() ) //不是if模块，错误
		return NULL;

	/// type 一定是2004
	logic_IfModule *tmpIfModule = (logic_IfModule *)tmpModule; //强制转换成if module

	std::string content = tmpIfModule->getBranchContentStr(branch_id);

	return content;
}

int logic_Program::setIfBranchContent(int if_id,int branch_id,int con_int) {

	if( mvmu_ModuleMap.count(if_id) == 0 )
		return -3;

	logic_BasicModule * tmpModule = mvmu_ModuleMap[if_id];

	if( 2004 != tmpModule->getModuleType() ) //不是if模块，错误
		return -4;

	/// type 一定是2004
	logic_IfModule *tmpIfModule = (logic_IfModule *)tmpModule; //强制转换成if module

	int flag = tmpIfModule->setBranchContent(if_id,con_int);

	return flag;
}

//重载 string
int logic_Program::setIfBranchContent(int if_id,int branch_id,std::string con_str) {

	if( mvmu_ModuleMap.count(if_id) == 0 )
		return -3;

	logic_BasicModule * tmpModule = mvmu_ModuleMap[if_id];

	if( 2004 != tmpModule->getModuleType() ) //不是if模块，错误
		return -4;

	/// type 一定是2004
	logic_IfModule *tmpIfModule = (logic_IfModule *)tmpModule; //强制转换成if module

	int flag = tmpIfModule->setBranchContent(if_id,con_str);

	return flag;
}

//增删 if 分支
int logic_Program::addIfBranch(int if_id) {

	if( mvmu_ModuleMap.count(if_id) == 0 )
		return -3;

	logic_BasicModule * tmpModule = mvmu_ModuleMap[if_id];

	if( 2004 != tmpModule->getModuleType() ) //不是for模块，错误
		return -4;

	/// type 一定是2004
	logic_IfModule *tmpIfModule = (logic_IfModule *)tmpModule; //强制转换成if module

	int newBranchId = tmpIfModule->addBranch();
	return newBranchId; //返回新增branch_id
}

//难点，需要删除分支中所有树
int logic_Program::delIfBranch(int if_id,int branch_id) {

	if( mvmu_ModuleMap.count(if_id) == 0 )
		return -3;

	logic_BasicModule * tmpModule = mvmu_ModuleMap[if_id];

	if( 2004 != tmpModule->getModuleType() ) //不是if模块，错误
		return -4;

	/// type 一定是2004
	logic_IfModule *tmpIfModule = (logic_IfModule *)tmpModule; //强制转换成if module
	if( tmpIfModule->whDelBranch(branch_id) < 0 )
		return -1; //删除失败

	//将如下操作放在if内部完成
// 	std::vector<int > L = tmpIfModule->delBranch(branch_id);
// 
// 	//已获得待删除模块树id，在外部删除树以及树中的模块
// 	for (int i=0;i < L.size();++i) {
// 		
// 		if( this->delTreeThroughId(L[i]) < 0 )
// 			return -5;
// 	}

	return 0;
}

//通过一棵树id，删除树（包括删除树中出现的模块，需要删除连线）
int logic_Program::delTreeThroughId(int id) {

	//此 id 必须是树根
	if( mvmu_TreeMap.count(id) == 0 )
		return -1;

	logic_TreeNode * root = mvmu_TreeMap[id]->getRoot();
	recurs_DelTreeNodeModule(root); //销毁模块实体

	mvmi_TreeId_For_IfIdMap.erase(mvmu_TreeMap[id]);
	SAFE_DELETE(mvmu_TreeMap[id]); //销毁树
	//抹除树痕迹
	mvmu_TreeMap.erase(id);

	return 0;
}

//完全删除一棵树所有节点的所有信息（各种实体map和connection map）
void logic_Program::recurs_DelTreeNodeModule(logic_TreeNode *some) {

	///// do sth here
	int tmpId = some->getID();
	if( mvmu_ModuleMap.count(tmpId) == 0 )
		assert(false);

	logic_BasicModule * tmpModule = mvmu_ModuleMap[tmpId];
	mvmu_ModuleMap.erase(tmpId);
	mvmu_ModuleId_TreeMap.erase(tmpId);
	SAFE_DELETE(tmpModule);

	//处理连线
	for( map<whPort ,whPort >::iterator it = mvvu_Conn_From_ToMap.begin(); it != mvvu_Conn_From_ToMap.end(); ++it ) {

		if( tmpId == it->first.moduleId ) {

			//如果 from 是该模块，所有这个 outModule 相关就需要删除
			whPort outPort = it->first;
			whPort inPort = mvvu_Conn_From_ToMap[outPort];
			mvvu_Conn_From_ToMap.erase(outPort);
			mvvu_Conn_To_FromMap.erase(inPort);

		}else if(tmpId == it->second.moduleId) {

			//如果 to 是该模块
			whPort outPort = it->first;   // 相当于 whPort inPort = it->second;
			whPort inPort = mvvu_Conn_From_ToMap[outPort];
			mvvu_Conn_From_ToMap.erase(outPort);
			mvvu_Conn_To_FromMap.erase(inPort);
		}
	}

	//和 getAllTreeNodeId() 连用，递归get id
	for (unsigned i = 0; i < some->mvvu_Children.size(); i++) {
		recurs_DelTreeNodeModule(some->mvvu_Children[i]);
	}
}

/// \brief 模块参数连线
int logic_Program::paraConnect(int out_m_id,int out_para_id,int in_m_id,int in_para_id) {

	assert( out_m_id != in_m_id );

	assert( mvmu_ModuleMap.count(out_m_id) * mvmu_ModuleMap.count(in_m_id) != 0 ); //如果找不到报错

	logic_BasicPara * outPara = mvmu_ModuleMap[out_m_id]->getPara(out_m_id);
	logic_BasicPara * inPara = mvmu_ModuleMap[in_m_id]->getPara(in_m_id);

	if( NULL == outPara || NULL == inPara ) {

		//没有那么多参数，直接错
		//assert(false);
		return -1;
	}

	//检查是否是 in 或 out
	if( outPara->getParaIOType() != PARA_OUT
		|| inPara->getParaIOType() != PARA_IN
		) {
		//assert(false);
		return -2;
	}

	//填充连线 map
	whPort outPort;
	outPort.moduleId = out_m_id;
	outPort.paraId = out_para_id;

	whPort inPort;
	inPort.moduleId = in_m_id;
	inPort.paraId = in_para_id;

	if( mvvu_Conn_From_ToMap.count(outPort)
		* mvvu_Conn_To_FromMap.count(inPort) >0
		)
		return -3; //如果已经存在

	//检测 inModule 是否是 outModule 祖先，如果是祖先则不可能连线
	logic_Tree * out_m_tree = mvmu_ModuleId_TreeMap[out_m_id];
	bool flag = out_m_tree->isAncestor(out_m_id,in_m_id);

	//如果 flag 是 false，代表可以
	if( NULL == flag ) {

		mvvu_Conn_From_ToMap[outPort] = inPort;
		mvvu_Conn_To_FromMap[inPort] = outPort;
		return 0;
	}else {
		return -4; //代表 inModule 是 outModule 祖先，不能构成连线
	}
}

//取消连线
//可通过 isOut 来用outModule或者inModule删除
void logic_Program::outParaDisconnect(int out_m_id,int out_para_id) {

	assert( mvmu_ModuleMap.count(out_m_id) != 0 ); //如果找不到报错

	logic_BasicPara * outPara = mvmu_ModuleMap[out_m_id]->getPara(out_m_id);

	if( NULL == outPara ) {

		//没有那么多参数，直接错
		assert(false);
	}

	//检查是否是 out
	if( outPara->getParaIOType() != PARA_OUT ) {

		assert(false);
	}

	//填充 Port
	whPort outPort;
	outPort.moduleId = out_m_id;
	outPort.paraId = out_para_id;

	if( mvvu_Conn_From_ToMap.count(outPort) == 0 )
		assert(false);

	whPort inPort = mvvu_Conn_From_ToMap[outPort];

	//删除map 成员
	mvvu_Conn_From_ToMap.erase(outPort);
	mvvu_Conn_To_FromMap.erase(inPort);

	return;
}

void logic_Program::inParaDisconnect(int in_m_id,int in_para_id) {

	assert( mvmu_ModuleMap.count(in_m_id) != 0 ); //如果找不到报错

	logic_BasicPara * inPara = mvmu_ModuleMap[in_m_id]->getPara(in_m_id);

	if( NULL == inPara ) {

		//没有那么多参数，直接错
		assert(false);
	}

	//检查是否是 in
	if( inPara->getParaIOType() != PARA_IN ) {
			assert(false);
	}

	//填充连线 map
	whPort inPort;
	inPort.moduleId = in_m_id;
	inPort.paraId = in_para_id;

	if( mvvu_Conn_To_FromMap.count(inPort) == 0 )
		assert(false);

	whPort outPort = mvvu_Conn_To_FromMap[inPort];

	//删除map 成员
	mvvu_Conn_From_ToMap.erase(outPort);
	mvvu_Conn_To_FromMap.erase(inPort);

	return;
}

//for move普通操作
int logic_Program::backInsSingMoveFor(int cur_m_id,int pre_m_id,int for_id) {

	assert( pre_m_id >= 0 );

	if (pre_m_id > 0)
	{
		//////如果pre_m_id != 0 则pre_m_id必须在for中
		assert(mvmi_TreeId_For_IfIdMap.count(mvmu_ModuleId_TreeMap[pre_m_id]));

		if (0 >= (mvmu_ModuleMap.count(cur_m_id))*(mvmu_ModuleMap.count(pre_m_id))
			*(mvmu_ModuleMap.count(for_id))) {
			return -2; // 首先 cur_m_id 和 pre_m_id 都要有
		}

		// cur_id 不能是开始模块
		if (mvmu_ModuleMap[cur_m_id]->getModuleType() == 2001) {
			assert(false);
			return -3; //模块类型错误
		}
	}
	logic_ForModule * tmpForModule = this->getForModuleById(for_id);

	//注：不用新建module，只用处理树节点即可

	///// step1、插入新树节点
	logic_Tree *oldTree = mvmu_ModuleId_TreeMap[cur_m_id]; //待删除树，早点找到会更靠谱
	logic_Tree *insTree = NULL;
	if( 0 == pre_m_id ) {  ////////////必须用深拷贝，浅拷贝可能有危险

		//如果前插一棵空树

		///如果是前插空树，同时又是【唯一模块】是可以的，从if或者for移过来

		logic_TreeNode tmpCurNode( *(oldTree->node_search(cur_m_id)) ) ; //深拷贝构造到栈

		if ( tmpCurNode.mvvu_Children.size() > 1 ) {
			//如果孩子不是一个，错误
			return -4;
		}

		tmpCurNode.mvu_Parent = 0;
		tmpCurNode.mvvu_Children.clear();

		logic_TreeNode *tmpPassNode = new logic_TreeNode(tmpCurNode); //深拷贝构造到堆
		insTree = new logic_Tree(tmpPassNode); //新建一棵树，此node也必须新建，否则被下面的delnode了

		mvmu_TreeMap[insTree->mvi_TreeID] = insTree;

		///////////////////////////////特殊处理for的地方///////////////////////////////

		///
		/// \brief root拖入for
		///
		this->mvmi_TreeId_For_IfIdMap[mvmu_TreeMap[cur_m_id]] = for_id; //建立for模块映射
		tmpForModule->addTree(mvmu_TreeMap[cur_m_id]); //add tree

		////////////////////////////////////////////////////////////////////////////////

	}else {

		////// pre_m_id 不为0

		//////pre_m_id必须在for中
		assert( mvmi_TreeId_For_IfIdMap.count( mvmu_ModuleId_TreeMap[pre_m_id] ) );

		/////如果已存在，直接找到待插入树
		insTree = mvmu_ModuleId_TreeMap[pre_m_id];

		if( insTree->mvi_TreeID == oldTree->mvi_TreeID ) {

			//如果是本内直接move
			if ( insTree->innerTreeBackInsSingMove(pre_m_id,cur_m_id) < 0 )
				return -6; //树内move出错
			else
				return 0; //已move可直接返回

		}else {
			//树间移动
			insTree->append_node(pre_m_id,cur_m_id);
		}
	}

	///// step2、删除旧树节点（注：此处不可能有多个孩子）

	if( cur_m_id != oldTree->mvi_TreeID ) {

		//并非树根
		oldTree->del_node(cur_m_id);
	}else if(cur_m_id == oldTree->mvi_TreeID ) {

		if ( oldTree->getRoot()->mvvu_Children.size()==0 ) {

			//树中唯一模块，删除树（ 进入这个分支 pre_m_id 也可能为0 ）

			///////////////////////////////特殊处理if和for的地方///////////////////////////////

			///
			/// \brief root移出if和for
			///
			if( mvmi_TreeId_For_IfIdMap.count(oldTree) >0 ) {

				tmpForModule->delTree(oldTree);
				mvmi_TreeId_For_IfIdMap.erase(oldTree);
			}

			///////////////////////////////////////////////////////////////////////////////////

			SAFE_DELETE(oldTree);
			mvmu_TreeMap.erase(cur_m_id);

			// Step3、（必须在此处，不然就return了）更新
			mvmu_ModuleId_TreeMap[cur_m_id] = insTree;

			return 0; //正常返回
		}else {
			//不是唯一模块

			oldTree->setFirstChildAsRoot();
		}

	}

	// Step3、更新
	mvmu_ModuleId_TreeMap[cur_m_id] = insTree;

	return 0; //正常返回

}

int logic_Program::frontInsSingMoveFor(int cur_m_id,int post_m_id,int for_id) {

	assert(post_m_id>0);

	//////post_m_id必须在for中
	assert( mvmi_TreeId_For_IfIdMap.count( mvmu_ModuleId_TreeMap[post_m_id] ) );

	if ( 0 >= (mvmu_ModuleMap.count(cur_m_id))*(mvmu_ModuleMap.count(post_m_id))
		*(mvmu_ModuleMap.count(for_id)) ) {
		return -2; //没找到插入点
	}

	//如果 post_m_id 是开始
	if ( mvmu_ModuleMap[post_m_id]->getModuleType() == 2001 ) {
			return -3; //模块类型错误
	}

	//注：不用新建module，只用处理树节点即可

	///// step1、插入新树节点
	logic_Tree *insTree = mvmu_ModuleId_TreeMap[post_m_id]; //待插入树
	logic_Tree *oldTree = mvmu_ModuleId_TreeMap[cur_m_id]; //待删除树

	int oldRootId = insTree->mvi_TreeID;
	if( post_m_id == oldRootId ) {

		//待插入节点要插在原树root之前
		if ( insTree->mvi_TreeID != oldTree->mvi_TreeID ) { //从其他树节点正常交换

			if( insTree->exchangeRoot(cur_m_id) == false )
				return -5;

			//只有 post_m_id 是根的情况，才更新tree map
			mvmu_TreeMap.erase(post_m_id);
			mvmu_TreeMap[cur_m_id] = insTree;
		} else {

			//树内交换，不用删除旧树节点，提前终止
			if( insTree->innerTreeExchangeRoot(cur_m_id) >= 0 ) {

				//只有 post_m_id 是根的情况，才更新tree map
				mvmu_TreeMap.erase(post_m_id);
				mvmu_TreeMap[cur_m_id] = insTree;

				return 0;
			} else {
				return -4; //树内交换失败
			}
		}

	}else {

		if ( insTree->mvi_TreeID == oldTree->mvi_TreeID ) { //本树操作

			if( insTree->innerTreeFrontInsSingMove(cur_m_id,post_m_id) >=0 ) {

				//树内正常操作，提前终止
				return 0;
			}else {
				return -6;
			}

		}
		//正常插入地方
		insTree->insert_node(insTree->getPreId(post_m_id),post_m_id,cur_m_id);
	}

	mvmu_ModuleId_TreeMap[cur_m_id] = insTree;

	///// step2、删除旧树节点（注：此处不可能有多个孩子）
	if( cur_m_id != oldTree->mvi_TreeID ) {

		//并非树根
		oldTree->del_node(cur_m_id);
	}else if(cur_m_id == oldTree->mvi_TreeID 
		|| oldTree->getRoot()->mvvu_Children.size()==0 ) {

			///////////////////////////////特殊处理if和for的地方///////////////////////////////

			///
			/// \brief root移出if和for
			///
			logic_ForModule * tmpForModule = this->getForModuleById(for_id);
			if( mvmi_TreeId_For_IfIdMap.count(oldTree) >0 ) {

				tmpForModule->delTree(oldTree);
				mvmi_TreeId_For_IfIdMap.erase(oldTree);
			}

			///////////////////////////////////////////////////////////////////////////////////

			//树中唯一模块，删除树
			SAFE_DELETE(oldTree);
			mvmu_TreeMap.erase(cur_m_id);
	}

	return 0; //正常返回
}

int logic_Program::backInsMultiMoveFor(int cur_m_id,int pre_m_id,int for_id) {

	//////pre_m_id必须在for中
	assert( mvmi_TreeId_For_IfIdMap.count( mvmu_ModuleId_TreeMap[pre_m_id] ) );

	//////cur_m_id 和 pre_m_id 必须在一个for中
	logic_Tree* cur_m_tree = mvmu_ModuleId_TreeMap[cur_m_id];
	logic_Tree* pre_m_tree = mvmu_ModuleId_TreeMap[pre_m_id];
	assert( mvmi_TreeId_For_IfIdMap[cur_m_tree] == mvmi_TreeId_For_IfIdMap[pre_m_tree] );

	/// 重复 backInsMultiMove 方法
	/// 重复 addLeafMove 方法
	if ( 0 >= (mvmu_ModuleMap.count(cur_m_id))*(mvmu_ModuleMap.count(pre_m_id))
		*(mvmu_ModuleMap.count(for_id)) ) {
		return -2; // 首先 cur_m_id 和 pre_m_id for_id 都要有
	}

	//如果 cur_id 模块是开始
	if ( mvmu_ModuleMap[cur_m_id]->getModuleType() == 2001 ) {
		assert(false);
		return -3; //模块类型错误
	}

	//注：不用新建module，只用处理树节点即可

	/////////////开始/////////////

	///// step1、删除旧树节点
	///// 注：删除必须是第一步，不然 del_node_notConn 方法会删掉错误 parent 的孩子

	logic_Tree *oldTree = mvmu_ModuleId_TreeMap[cur_m_id]; //待删除树
	logic_TreeNode * insNode = oldTree->node_search(cur_m_id); //待插入节点（必须在此处寻找）

	if ( insNode->mvvu_Children.size() == 0 ) {
		//可能只有一个孩子
		return -4;
	}

	if( cur_m_id != oldTree->mvi_TreeID ) {

		//并非树根
		oldTree->del_node_notConn(cur_m_id); //断开 oldTree 与此节点的连接

	}else if(cur_m_id == oldTree->mvi_TreeID ) {

		//ROOT，删除树
		oldTree->del_node_notConn(cur_m_id); //如果是树根，直接将该树root置空
		SAFE_DELETE(oldTree); //放心删除树
		mvmu_TreeMap.erase(cur_m_id);

		///////////////////////////////特殊处理if和for的地方///////////////////////////////

		///
		/// \brief root移出if和for
		///
		logic_ForModule * tmpForModule = this->getForModuleById(for_id);
		assert( mvmi_TreeId_For_IfIdMap.count(oldTree) >0 ); //必然在同一个for中

		tmpForModule->delTree(oldTree);
		mvmi_TreeId_For_IfIdMap.erase(oldTree);

		///////////////////////////////////////////////////////////////////////////////////
	}

	///// step2、插入新节点
	logic_Tree *insTree = NULL;
	if( 0 == pre_m_id ) { 
		//如果前插一棵空树

		insTree = new logic_Tree(insNode); //新建一棵树

		mvmu_TreeMap[insTree->mvi_TreeID] = insTree;
		mvmu_ModuleId_TreeMap[cur_m_id] = insTree;

	}else {
		/////如果已存在，直接找到待插入树
		insTree = mvmu_ModuleId_TreeMap[pre_m_id];

		logic_TreeNode * preNode = insTree->node_search(pre_m_id); //pre_m_id节点
		//如果 pre_m_id 不是叶子节点，错误返回
		if(preNode->mvvu_Children.size()>0) {
			return -4;
		}

		insTree->add_node(pre_m_id,insNode);

	}

	///// step3、更新 module tree映射
	recurs_update(insTree,insNode);

	return 0; //正常返回
}

int logic_Program::frontInsMultiMoveFor(int cur_m_id,int post_m_id,int for_id) {

	//////post_m_id必须在for中
	assert( mvmi_TreeId_For_IfIdMap.count( mvmu_ModuleId_TreeMap[post_m_id] ) );

	//////cur_m_id 和 post_m_id 必须在一个for中
	logic_Tree* cur_m_tree = mvmu_ModuleId_TreeMap[cur_m_id];
	logic_Tree* pre_m_tree = mvmu_ModuleId_TreeMap[post_m_id];
	assert( mvmi_TreeId_For_IfIdMap[cur_m_tree] == mvmi_TreeId_For_IfIdMap[pre_m_tree] );

	logic_ForModule * tmpForModule = this->getForModuleById(for_id);

	/// 重复 frontInsMultiMove 方法
	if( 0 == post_m_id ) {

		//空插
		//相当于 backInsMultiMove 到背景

		logic_Tree *oldTree = mvmu_ModuleId_TreeMap[cur_m_id];

		///// step1、删除旧树节点，同时将断开部分生成新树
		logic_TreeNode * curNode = oldTree->node_search(cur_m_id);
		if( curNode->mvvu_Children.size() == 1 ) {

			logic_TreeNode * breakNode = curNode->mvvu_Children[0];
			oldTree->del_node_notConn(breakNode->getID());
			logic_Tree * newTree = new logic_Tree(breakNode);

			mvmu_TreeMap[newTree->getRoot()->getID()] = newTree;

			/////////////在for中加入树///////////
			mvmi_TreeId_For_IfIdMap[newTree] = for_id;
			tmpForModule->addTree(newTree);

			///// 更新 module tree映射 insNode分支
			recurs_update(newTree,newTree->getRoot());
		}else if( curNode->mvvu_Children.size() > 1 ) {
			assert(false);
		}

	} else {

		logic_Tree *insTree = mvmu_ModuleId_TreeMap[post_m_id]; //新插入树
		logic_Tree *oldTree = mvmu_ModuleId_TreeMap[cur_m_id];

		//如果 post_m_id 不是根节点，错误返回
		if( post_m_id!=insTree->mvi_TreeID ) {
			return -4;
		}

		///// step1、删除旧树节点，同时将断开部分生成新树
		logic_TreeNode * curNode = oldTree->node_search(cur_m_id);
		if( curNode->mvvu_Children.size() == 1 ) {

			logic_TreeNode * breakNode = curNode->mvvu_Children[0];
			oldTree->del_node_notConn(breakNode->getID());
			logic_Tree * newTree = new logic_Tree(breakNode);

			mvmu_TreeMap[newTree->getRoot()->getID()] = newTree;

			/////////////在for中加入树///////////
			mvmi_TreeId_For_IfIdMap[newTree] = for_id;
			tmpForModule->addTree(newTree);

			///// 更新 module tree映射 insNode分支
			recurs_update(newTree,newTree->getRoot());
		}else if( curNode->mvvu_Children.size() > 1 ) {
			assert(false);
		}

		///// step2、插入新树节点

		logic_TreeNode * insNode = insTree->getRoot(); //待插入节点
		oldTree->add_node(cur_m_id,insNode); //insTree接到oldTree上

		//必然是ROOT，直接删除原insTree
		insTree->del_node_notConn(post_m_id); //是root，直接置空
		SAFE_DELETE(insTree); //放心删除树
		mvmu_TreeMap.erase(post_m_id);

		///////////////////////////////特殊处理if和for的地方///////////////////////////////

		///
		/// \brief 在for中删除树
		///
		assert( mvmi_TreeId_For_IfIdMap.count(insTree) >0 ); //必然在同一个for中

		tmpForModule->delTree(insTree);
		mvmi_TreeId_For_IfIdMap.erase(insTree);

		///////////////////////////////////////////////////////////////////////////////////

		///// 更新 module tree映射 insNode分支
		recurs_update(oldTree,insNode);

	}

	return 0; //正常返回
}

int logic_Program::addLeafMoveFor(int cur_m_id,int pre_m_id,int for_id) {

	//////pre_m_id必须在for中
	assert( mvmi_TreeId_For_IfIdMap.count( mvmu_ModuleId_TreeMap[pre_m_id] ) );

	//////cur_m_id 和 pre_m_id 必须在一个for中
	logic_Tree* cur_m_tree = mvmu_ModuleId_TreeMap[cur_m_id];
	logic_Tree* pre_m_tree = mvmu_ModuleId_TreeMap[pre_m_id];
	assert( mvmi_TreeId_For_IfIdMap[cur_m_tree] == mvmi_TreeId_For_IfIdMap[pre_m_tree] );

	/// 重复 addLeafMove 方法
	if ( 0 >= (mvmu_ModuleMap.count(cur_m_id))*(mvmu_ModuleMap.count(pre_m_id))
		*(mvmu_ModuleMap.count(for_id)) ) {
		return -2; // 首先 cur_m_id 和 pre_m_id for_id 都要有
	}

	//如果 cur_id 模块是开始
	if ( mvmu_ModuleMap[cur_m_id]->getModuleType() == 2001 ) {
		return -3; //模块类型错误
	}

	if ( addLeafCheckPre(cur_m_id,pre_m_id) < 0 ) {
		return -4;
	}

	logic_Tree *oldTree = mvmu_ModuleId_TreeMap[cur_m_id]; //待删除树
	//该节点必须是该树的根节点
	if( oldTree->mvi_TreeID != cur_m_id )
		assert(false);

	logic_Tree *insTree = mvmu_ModuleId_TreeMap[pre_m_id];
	logic_TreeNode * insNode = insTree->node_search(pre_m_id); //待插入节点
	logic_TreeNode * curNode = oldTree->getRoot(); //当前节点

	curNode->mvu_Parent = insNode;

	/// Step1、接入新节点
	insNode->mvvu_Children.push_back(curNode);

	/// Step2、删除旧树map信息
	mvmu_TreeMap.erase(cur_m_id);
	oldTree->setRoot(NULL);
	SAFE_DELETE(oldTree);

	///////////////////////////////特殊处理if和for的地方///////////////////////////////

	///
	/// \brief root移出if和for
	///
	logic_ForModule * tmpForModule = this->getForModuleById(for_id);
	assert( mvmi_TreeId_For_IfIdMap.count(oldTree) >0 ); //必然在一个for中

	tmpForModule->delTree(oldTree);
	mvmi_TreeId_For_IfIdMap.erase(oldTree);

	///////////////////////////////////////////////////////////////////////////////////

	/// Step3、更新模块树map信息
	recurs_update(insTree,curNode);

	return 0;

}

//通过id得到模块
logic_ForModule* logic_Program::getForModuleById(int id) {

	assert( mvmu_ModuleMap.count(id) > 0 ); //假定 count 大于0

	logic_BasicModule * tmpModule = mvmu_ModuleMap[id];
	assert( 2003 == tmpModule->getModuleType() ); //不是for模块，错误

	/// type 一定是2003
	logic_ForModule *tmpForModule = (logic_ForModule *)tmpModule; //强制转换成for module

	return tmpForModule;
}

logic_IfModule* logic_Program::getIfModuleById(int id) {

	assert( mvmu_ModuleMap.count(id) > 0 ); //假定 count 大于0

	logic_BasicModule * tmpModule = mvmu_ModuleMap[id];

	assert( 2004 == tmpModule->getModuleType() ); //不是if模块，错误

	/// type 一定是2004
	logic_IfModule *tmpIfModule = (logic_IfModule *)tmpModule; //强制转换成if module

	return tmpIfModule;
}

//rootId = moduleId*100000
//合成for和if放入tree map中的id
inline int logic_Program::composeTreeId(int for_id) {

	return for_id * ACTIVE_TREE_MAP_FACTOR;
}

//rootId = moduleId*100000+branchId
inline int logic_Program::composeTreeId(int if_id,int branch_id) {

	return if_id * ACTIVE_TREE_MAP_FACTOR + branch_id;
}

//只在接到activeTree根节点的时候调用
int logic_Program::appendActiveTreeMoveFor(int cur_m_id,int for_id) {

	//将某一模块接到 for_id activeTree后面

	if ( 0 >= (mvmu_ModuleMap.count(cur_m_id))*(mvmu_ModuleMap.count(for_id)) ) {
		assert(false);
		return -2; // 首先 cur_m_id 和 for_id 都要有
	}

	//如果 cur_id 模块是开始
	if ( mvmu_ModuleMap[cur_m_id]->getModuleType() == 2001 ) {
		assert(false);
		return -3; //模块类型错误
	}

	//得到 activeTree
	logic_Tree * curActiveTree = this->getForModuleById(for_id)->getCurActiveTree();
	logic_Tree *oldTree = mvmu_ModuleId_TreeMap[cur_m_id];

	///// Step1、插入节点
	curActiveTree->append_node(-1,cur_m_id);


	///// step2、删除旧树节点（注：此处不可能有多个孩子）
	if( cur_m_id != oldTree->mvi_TreeID ) {

		//并非树根
		oldTree->del_node(cur_m_id);
	}else if(cur_m_id == oldTree->mvi_TreeID ) {

		if ( oldTree->getRoot()->mvvu_Children.size()==0 ) {

			//树中唯一模块，删除树（ 进入这个分支 pre_m_id 也可能为0 ）

			///////////////////////////////特殊处理if和for的地方///////////////////////////////

			///
			/// \brief root移出if和for
			///
			if( mvmi_TreeId_For_IfIdMap.count(oldTree) >0 ) {
				logic_ForModule * tmpForModule = this->getForModuleById(for_id);
				tmpForModule->delTree(oldTree);
				mvmi_TreeId_For_IfIdMap.erase(oldTree);
			}

			///////////////////////////////////////////////////////////////////////////////////

			SAFE_DELETE(oldTree);
			mvmu_TreeMap.erase(cur_m_id);

			// Step3、（必须在此处，不然就return了）更新
			mvmu_ModuleId_TreeMap[cur_m_id] = curActiveTree;

			return 0; //正常返回
		}else {
			//不是唯一模块

			oldTree->setFirstChildAsRoot();
		}

	}

	// Step3、更新
	mvmu_ModuleId_TreeMap[cur_m_id] = curActiveTree;

	return 0;
}

//activeTree直接添加叶子
int logic_Program::addLeafActiveTreeMoveFor(int cur_m_id,int for_id) {

	//////cur_m_id 和 activeTree 必须在同一个for中
	logic_Tree* cur_m_tree = mvmu_ModuleId_TreeMap[cur_m_id];
	assert( mvmi_TreeId_For_IfIdMap[cur_m_tree] == for_id );

	/// 重复 addLeafMove 方法
	if ( 0 >= (mvmu_ModuleMap.count(cur_m_id))*(mvmu_ModuleMap.count(for_id)) ) {
			return -2; // 首先 cur_m_id 和 for_id 都要有
	}

	//如果 cur_id 模块是开始
	if ( mvmu_ModuleMap[cur_m_id]->getModuleType() == 2001 ) {
		return -3; //模块类型错误
	}

	logic_Tree *oldTree = mvmu_ModuleId_TreeMap[cur_m_id]; //待删除树
	//该节点必须是该树的根节点
	if( oldTree->mvi_TreeID != cur_m_id )
		assert(false);

	logic_ForModule * tmpForModule = this->getForModuleById(for_id);

	logic_Tree *insTree = tmpForModule->getCurActiveTree();
	logic_TreeNode * insNode = insTree->getRoot(); //待插入节点
	logic_TreeNode * curNode = oldTree->getRoot(); //当前节点

	curNode->mvu_Parent = insNode;

	/// Step1、接入新节点
	insNode->mvvu_Children.push_back(curNode);

	/// Step2、删除旧树map信息
	mvmu_TreeMap.erase(cur_m_id);
	oldTree->setRoot(NULL);
	SAFE_DELETE(oldTree);

	///////////////////////////////特殊处理if和for的地方///////////////////////////////

	///
	/// \brief root移出if和for
	///
	assert( mvmi_TreeId_For_IfIdMap.count(oldTree) >0 ); //必然在一个for中

	tmpForModule->delTree(oldTree);
	mvmi_TreeId_For_IfIdMap.erase(oldTree);

	///////////////////////////////////////////////////////////////////////////////////

	/// Step3、更新模块树map信息
	recurs_update(insTree,curNode);

	return 0;
}

//单模块新插入activeTree
int logic_Program::appendActiveTreeInsertFor(int m_id,int m_type,int for_id) {

	assert( mvmu_ModuleMap.count(for_id)>0 );

	// step1、在森林中加入这个id

	if ( m_type == 2001 ) {
		return false;
	}

	logic_ForModule * tmpForModule = this->getForModuleById(for_id);
	logic_Tree *tree = tmpForModule->getCurActiveTree();
	tree->append_node(-1,m_id);


	// step2、真正生成这个module实体
	this->add_Module(m_id,m_type);

	return 0;
}

///
/// \brief 特殊处理if的move操作
///
int logic_Program::backInsSingMoveIf(int cur_m_id,int pre_m_id,int if_id,int branch_id) {


	assert( pre_m_id >= 0 );

	//////pre_m_id必须在if中
	assert( mvmi_TreeId_For_IfIdMap.count( mvmu_ModuleId_TreeMap[pre_m_id] ) );

	if ( 0 >= (mvmu_ModuleMap.count(cur_m_id))*(mvmu_ModuleMap.count(pre_m_id)) 
		*(mvmu_ModuleMap.count(if_id)) ) {
			return -2; // 首先 cur_m_id 和 pre_m_id 都要有
	}

	logic_IfModule * tmpIfModule = this->getIfModuleById(if_id); //判断branch分支是否存在
	assert( tmpIfModule->isBranchExist(branch_id) == true );

	// cur_id 不能是开始模块
	if ( mvmu_ModuleMap[cur_m_id]->getModuleType() == 2001 ) {
		assert(false);
		return -3; //模块类型错误
	}

	//注：不用新建module，只用处理树节点即可

	///// step1、插入新树节点
	logic_Tree *oldTree = mvmu_ModuleId_TreeMap[cur_m_id]; //待删除树，早点找到会更靠谱
	logic_Tree *insTree = NULL;
	if( 0 == pre_m_id ) {  ////////////必须用深拷贝，浅拷贝可能有危险

		//如果前插一棵空树

		///如果是前插空树，同时又是【唯一模块】是可以的，从if或者for移过来

		logic_TreeNode tmpCurNode( *(oldTree->node_search(cur_m_id)) ) ; //深拷贝构造到栈

		if ( tmpCurNode.mvvu_Children.size() > 1 ) {
			//如果孩子不是一个，错误
			return -4;
		}

		tmpCurNode.mvu_Parent = 0;
		tmpCurNode.mvvu_Children.clear();

		logic_TreeNode *tmpPassNode = new logic_TreeNode(tmpCurNode); //深拷贝构造到堆
		insTree = new logic_Tree(tmpPassNode); //新建一棵树，此node也必须新建，否则被下面的delnode了

		mvmu_TreeMap[insTree->mvi_TreeID] = insTree;

		///////////////////////////////特殊处理if的地方///////////////////////////////

		///
		/// \brief root拖入if
		///
		this->mvmi_TreeId_For_IfIdMap[mvmu_TreeMap[cur_m_id]] = if_id; //建立模块映射
		tmpIfModule->addTree(branch_id,mvmu_TreeMap[cur_m_id]); //add tree

		////////////////////////////////////////////////////////////////////////////////

	}else {

		////// pre_m_id 不为0

		//////pre_m_id必须在if中
		assert( mvmi_TreeId_For_IfIdMap.count( mvmu_ModuleId_TreeMap[pre_m_id] ) );

		/////如果已存在，直接找到待插入树
		insTree = mvmu_ModuleId_TreeMap[pre_m_id];

		if( insTree->mvi_TreeID == oldTree->mvi_TreeID ) {

			//如果是本内直接move
			if ( insTree->innerTreeBackInsSingMove(pre_m_id,cur_m_id) < 0 )
				return -6; //树内move出错
			else
				return 0; //已move可直接返回

		}else {
			//树间移动
			insTree->append_node(pre_m_id,cur_m_id);
		}
	}

	///// step2、删除旧树节点（注：此处不可能有多个孩子）

	if( cur_m_id != oldTree->mvi_TreeID ) {

		//并非树根
		oldTree->del_node(cur_m_id);
	}else if(cur_m_id == oldTree->mvi_TreeID ) {

		if ( oldTree->getRoot()->mvvu_Children.size()==0 ) {

			//树中唯一模块，删除树（ 进入这个分支 pre_m_id 也可能为0 ）

			///////////////////////////////特殊处理if和for的地方///////////////////////////////

			///
			/// \brief root移出if和for
			///
			if( mvmi_TreeId_For_IfIdMap.count(oldTree) >0 ) {

				tmpIfModule->delTree(oldTree);
				mvmi_TreeId_For_IfIdMap.erase(oldTree);
			}

			///////////////////////////////////////////////////////////////////////////////////

			SAFE_DELETE(oldTree);
			mvmu_TreeMap.erase(cur_m_id);

			// Step3、（必须在此处，不然就return了）更新
			mvmu_ModuleId_TreeMap[cur_m_id] = insTree;

			return 0; //正常返回
		}else {
			//不是唯一模块

			oldTree->setFirstChildAsRoot();
		}

	}

	// Step3、更新
	mvmu_ModuleId_TreeMap[cur_m_id] = insTree;

	return 0; //正常返回

}

int logic_Program::frontInsSingMoveIf(int cur_m_id,int post_m_id,int if_id,int branch_id) {

	assert(post_m_id>0);

	//////post_m_id必须在if中
	assert( mvmi_TreeId_For_IfIdMap.count( mvmu_ModuleId_TreeMap[post_m_id] ) );

	if ( 0 >= (mvmu_ModuleMap.count(cur_m_id))*(mvmu_ModuleMap.count(post_m_id))
		*(mvmu_ModuleMap.count(if_id)) ) {
			return -2; //没找到插入点
	}

	logic_IfModule * tmpIfModule = this->getIfModuleById(if_id); //判断branch分支是否存在
	assert( tmpIfModule->isBranchExist(branch_id) == true );

	//如果 post_m_id 是开始
	if ( mvmu_ModuleMap[post_m_id]->getModuleType() == 2001 ) {
		return -3; //模块类型错误
	}

	//注：不用新建module，只用处理树节点即可

	///// step1、插入新树节点
	logic_Tree *insTree = mvmu_ModuleId_TreeMap[post_m_id]; //待插入树
	logic_Tree *oldTree = mvmu_ModuleId_TreeMap[cur_m_id]; //待删除树

	int oldRootId = insTree->mvi_TreeID;
	if( post_m_id == oldRootId ) {

		//待插入节点要插在原树root之前
		if ( insTree->mvi_TreeID != oldTree->mvi_TreeID ) { //从其他树节点正常交换

			if( insTree->exchangeRoot(cur_m_id) == false )
				return -5;

			//只有 post_m_id 是根的情况，才更新tree map
			mvmu_TreeMap.erase(post_m_id);
			mvmu_TreeMap[cur_m_id] = insTree;
		} else {

			//树内交换，不用删除旧树节点，提前终止
			if( insTree->innerTreeExchangeRoot(cur_m_id) >= 0 ) {

				//只有 post_m_id 是根的情况，才更新tree map
				mvmu_TreeMap.erase(post_m_id);
				mvmu_TreeMap[cur_m_id] = insTree;

				return 0;
			} else {
				return -4; //树内交换失败
			}
		}

	}else {

		if ( insTree->mvi_TreeID == oldTree->mvi_TreeID ) { //本树操作

			if( insTree->innerTreeFrontInsSingMove(cur_m_id,post_m_id) >=0 ) {

				//树内正常操作，提前终止
				return 0;
			}else {
				return -6;
			}

		}
		//正常插入地方
		insTree->insert_node(insTree->getPreId(post_m_id),post_m_id,cur_m_id);
	}

	mvmu_ModuleId_TreeMap[cur_m_id] = insTree;

	///// step2、删除旧树节点（注：此处不可能有多个孩子）
	if( cur_m_id != oldTree->mvi_TreeID ) {

		//并非树根
		oldTree->del_node(cur_m_id);
	}else if(cur_m_id == oldTree->mvi_TreeID 
		|| oldTree->getRoot()->mvvu_Children.size()==0 ) {

			///////////////////////////////特殊处理if和for的地方///////////////////////////////

			///
			/// \brief root移出if和for
			///
			if( mvmi_TreeId_For_IfIdMap.count(oldTree) >0 ) {

				tmpIfModule->delTree(oldTree);
				mvmi_TreeId_For_IfIdMap.erase(oldTree);
			}

			///////////////////////////////////////////////////////////////////////////////////

			//树中唯一模块，删除树
			SAFE_DELETE(oldTree);
			mvmu_TreeMap.erase(cur_m_id);
	}

	return 0; //正常返回
}

int logic_Program::backInsMultiMoveIf(int cur_m_id,int pre_m_id,int if_id,int branch_id) {

	//////pre_m_id必须在if中
	assert( mvmi_TreeId_For_IfIdMap.count( mvmu_ModuleId_TreeMap[pre_m_id] ) );

	//////cur_m_id 和 pre_m_id 必须在一个if中
	logic_Tree* cur_m_tree = mvmu_ModuleId_TreeMap[cur_m_id];
	logic_Tree* pre_m_tree = mvmu_ModuleId_TreeMap[pre_m_id];
	assert( mvmi_TreeId_For_IfIdMap[cur_m_tree] == mvmi_TreeId_For_IfIdMap[pre_m_tree] );

	/// 重复 backInsMultiMove 方法
	/// 重复 addLeafMove 方法
	if ( 0 >= (mvmu_ModuleMap.count(cur_m_id))*(mvmu_ModuleMap.count(pre_m_id))
		*(mvmu_ModuleMap.count(if_id)) ) {
			return -2; // 首先 cur_m_id 和 pre_m_id for_id 都要有
	}

	logic_IfModule * tmpIfModule = this->getIfModuleById(if_id); //判断branch分支是否存在
	assert( tmpIfModule->isBranchExist(branch_id) == true );

	//如果 cur_id 模块是开始
	if ( mvmu_ModuleMap[cur_m_id]->getModuleType() == 2001 ) {
		assert(false);
		return -3; //模块类型错误
	}

	//注：不用新建module，只用处理树节点即可

	/////////////开始/////////////

	///// step1、删除旧树节点
	///// 注：删除必须是第一步，不然 del_node_notConn 方法会删掉错误 parent 的孩子

	logic_Tree *oldTree = mvmu_ModuleId_TreeMap[cur_m_id]; //待删除树
	logic_TreeNode * insNode = oldTree->node_search(cur_m_id); //待插入节点（必须在此处寻找）

	if ( insNode->mvvu_Children.size() == 0 ) {
		//可能只有一个孩子
		return -4;
	}

	if( cur_m_id != oldTree->mvi_TreeID ) {

		//并非树根
		oldTree->del_node_notConn(cur_m_id); //断开 oldTree 与此节点的连接

	}else if(cur_m_id == oldTree->mvi_TreeID ) {

		//ROOT，删除树
		oldTree->del_node_notConn(cur_m_id); //如果是树根，直接将该树root置空
		SAFE_DELETE(oldTree); //放心删除树
		mvmu_TreeMap.erase(cur_m_id);

		///////////////////////////////特殊处理if和for的地方///////////////////////////////

		///
		/// \brief root移出if和for
		///
		assert( mvmi_TreeId_For_IfIdMap.count(oldTree) >0 ); //必然在同一个for中

		tmpIfModule->delTree(oldTree);
		mvmi_TreeId_For_IfIdMap.erase(oldTree);

		///////////////////////////////////////////////////////////////////////////////////
	}

	///// step2、插入新节点
	logic_Tree *insTree = NULL;
	if( 0 == pre_m_id ) { 
		//如果前插一棵空树

		insTree = new logic_Tree(insNode); //新建一棵树

		mvmu_TreeMap[insTree->mvi_TreeID] = insTree;
		mvmu_ModuleId_TreeMap[cur_m_id] = insTree;

	}else {
		/////如果已存在，直接找到待插入树
		insTree = mvmu_ModuleId_TreeMap[pre_m_id];

		logic_TreeNode * preNode = insTree->node_search(pre_m_id); //pre_m_id节点
		//如果 pre_m_id 不是叶子节点，错误返回
		if(preNode->mvvu_Children.size()>0) {
			return -4;
		}

		insTree->add_node(pre_m_id,insNode);

	}

	///// step3、更新 module tree映射
	recurs_update(insTree,insNode);

	return 0; //正常返回
}

int logic_Program::frontInsMultiMoveIf(int cur_m_id,int post_m_id,int if_id,int branch_id) {

	//////post_m_id必须在if中
	assert( mvmi_TreeId_For_IfIdMap.count( mvmu_ModuleId_TreeMap[post_m_id] ) );

	//////cur_m_id 和 post_m_id 必须在一个if中
	logic_Tree* cur_m_tree = mvmu_ModuleId_TreeMap[cur_m_id];
	logic_Tree* pre_m_tree = mvmu_ModuleId_TreeMap[post_m_id];
	assert( mvmi_TreeId_For_IfIdMap[cur_m_tree] == mvmi_TreeId_For_IfIdMap[pre_m_tree] );

	/// 重复 frontInsMultiMove 方法
	if ( 0 >= (mvmu_ModuleMap.count(cur_m_id))*(mvmu_ModuleMap.count(post_m_id))
		*(mvmu_ModuleMap.count(if_id)) ) {
			return -2; //没找到插入点
	}

	logic_IfModule * tmpIfModule = this->getIfModuleById(if_id); //判断branch分支是否存在
	assert( tmpIfModule->isBranchExist(branch_id) == true );

	//如果 post_m_id 模块是开始
	if ( mvmu_ModuleMap[post_m_id]->getModuleType() == 2001 ) {
		return -3; //模块类型错误
	}

	//注：不用新建module，只用处理树节点即可

	/// 重复 frontInsMultiMove 方法
	if( 0 == post_m_id ) {

		//空插
		//相当于 backInsMultiMove 到背景

		logic_Tree *oldTree = mvmu_ModuleId_TreeMap[cur_m_id];

		///// step1、删除旧树节点，同时将断开部分生成新树
		logic_TreeNode * curNode = oldTree->node_search(cur_m_id);
		if( curNode->mvvu_Children.size() == 1 ) {

			logic_TreeNode * breakNode = curNode->mvvu_Children[0];
			oldTree->del_node_notConn(breakNode->getID());
			logic_Tree * newTree = new logic_Tree(breakNode);

			mvmu_TreeMap[newTree->getRoot()->getID()] = newTree;

			/////////////在if中加入树///////////
			mvmi_TreeId_For_IfIdMap[newTree] = if_id;
			tmpIfModule->addTree(branch_id,newTree);

			///// 更新 module tree映射 insNode分支
			recurs_update(newTree,newTree->getRoot());
		}else if( curNode->mvvu_Children.size() > 1 ) {
			assert(false);
		}

	} else {

		logic_Tree *insTree = mvmu_ModuleId_TreeMap[post_m_id]; //新插入树
		logic_Tree *oldTree = mvmu_ModuleId_TreeMap[cur_m_id];

		//如果 post_m_id 不是根节点，错误返回
		if( post_m_id!=insTree->mvi_TreeID ) {
			return -4;
		}

		///// step1、删除旧树节点，同时将断开部分生成新树
		logic_TreeNode * curNode = oldTree->node_search(cur_m_id);
		if( curNode->mvvu_Children.size() == 1 ) {

			logic_TreeNode * breakNode = curNode->mvvu_Children[0];
			oldTree->del_node_notConn(breakNode->getID());
			logic_Tree * newTree = new logic_Tree(breakNode);

			mvmu_TreeMap[newTree->getRoot()->getID()] = newTree;

			/////////////在for中加入树///////////
			mvmi_TreeId_For_IfIdMap[newTree] = if_id;
			tmpIfModule->addTree(branch_id,newTree);

			///// 更新 module tree映射 insNode分支
			recurs_update(newTree,newTree->getRoot());
		}else if( curNode->mvvu_Children.size() > 1 ) {
			assert(false);
		}

		///// step2、插入新树节点

		logic_TreeNode * insNode = insTree->getRoot(); //待插入节点
		oldTree->add_node(cur_m_id,insNode); //insTree接到oldTree上

		//必然是ROOT，直接删除原insTree
		insTree->del_node_notConn(post_m_id); //是root，直接置空
		SAFE_DELETE(insTree); //放心删除树
		mvmu_TreeMap.erase(post_m_id);

		///////////////////////////////特殊处理if和for的地方///////////////////////////////

		///
		/// \brief 在if中删除树
		///
		assert( mvmi_TreeId_For_IfIdMap.count(insTree) >0 ); //必然在同一个for中

		tmpIfModule->delTree(insTree);
		mvmi_TreeId_For_IfIdMap.erase(insTree);

		///////////////////////////////////////////////////////////////////////////////////

		///// 更新 module tree映射 insNode分支
		recurs_update(oldTree,insNode);

	}

	return 0; //正常返回
}

int logic_Program::addLeafMoveIf(int cur_m_id,int pre_m_id,int if_id,int branch_id) {

	//////pre_m_id必须在if中
	assert( mvmi_TreeId_For_IfIdMap.count( mvmu_ModuleId_TreeMap[pre_m_id] ) );

	//////cur_m_id 和 pre_m_id 必须在一个if中
	logic_Tree* cur_m_tree = mvmu_ModuleId_TreeMap[cur_m_id];
	logic_Tree* pre_m_tree = mvmu_ModuleId_TreeMap[pre_m_id];
	assert( mvmi_TreeId_For_IfIdMap[cur_m_tree] == mvmi_TreeId_For_IfIdMap[pre_m_tree] );

	/// 重复 addLeafMove 方法
	if ( 0 >= (mvmu_ModuleMap.count(cur_m_id))*(mvmu_ModuleMap.count(pre_m_id))
		*(mvmu_ModuleMap.count(if_id)) ) {
			return -2; // 首先 cur_m_id 和 pre_m_id if_id 都要有
	}

	logic_IfModule * tmpIfModule = this->getIfModuleById(if_id); //判断branch分支是否存在
	assert( tmpIfModule->isBranchExist(branch_id) == true );

	//如果 cur_id 模块是开始
	if ( mvmu_ModuleMap[cur_m_id]->getModuleType() == 2001 ) {
		return -3; //模块类型错误
	}

	if ( addLeafCheckPre(cur_m_id,pre_m_id) < 0 ) {
		return -4;
	}

	logic_Tree *oldTree = mvmu_ModuleId_TreeMap[cur_m_id]; //待删除树
	//该节点必须是该树的根节点
	if( oldTree->mvi_TreeID != cur_m_id )
		assert(false);

	logic_Tree *insTree = mvmu_ModuleId_TreeMap[pre_m_id];
	logic_TreeNode * insNode = insTree->node_search(pre_m_id); //待插入节点
	logic_TreeNode * curNode = oldTree->getRoot(); //当前节点

	curNode->mvu_Parent = insNode;

	/// Step1、接入新节点
	insNode->mvvu_Children.push_back(curNode);

	/// Step2、删除旧树map信息
	mvmu_TreeMap.erase(cur_m_id);
	oldTree->setRoot(NULL);
	SAFE_DELETE(oldTree);

	///////////////////////////////特殊处理if和for的地方///////////////////////////////

	///
	/// \brief root移出if和for
	///
	assert( mvmi_TreeId_For_IfIdMap.count(oldTree) >0 ); //必然在一个for中

	tmpIfModule->delTree(oldTree);
	mvmi_TreeId_For_IfIdMap.erase(oldTree);

	///////////////////////////////////////////////////////////////////////////////////

	/// Step3、更新模块树map信息
	recurs_update(insTree,curNode);

	return 0;
}

//只在接到activeTree根节点的时候调用

//单模块接入activeTree
int logic_Program::appendActiveTreeMoveIf(int cur_m_id,int if_id,int branch_id) {

	//将某一模块接到 branch activeTree后面

	if ( 0 >= (mvmu_ModuleMap.count(cur_m_id))*(mvmu_ModuleMap.count(if_id)) ) {
		assert(false);
		return -2; // 首先 cur_m_id 和 if_id 都要有
	}

	logic_IfModule * tmpIfModule = this->getIfModuleById(if_id); //判断branch分支是否存在
	assert( tmpIfModule->isBranchExist(branch_id) == true );

	//如果 cur_id 模块是开始
	if ( mvmu_ModuleMap[cur_m_id]->getModuleType() == 2001 ) {
		assert(false);
		return -3; //模块类型错误
	}

	//得到 activeTree
	logic_Tree * curActiveTree = tmpIfModule->getCurActiveTree(branch_id);
	logic_Tree *oldTree = mvmu_ModuleId_TreeMap[cur_m_id];

	///// Step1、插入节点
	curActiveTree->append_node(-1,cur_m_id);


	///// step2、删除旧树节点（注：此处不可能有多个孩子）
	if( cur_m_id != oldTree->mvi_TreeID ) {

		//并非树根
		oldTree->del_node(cur_m_id);
	}else if(cur_m_id == oldTree->mvi_TreeID ) {

		if ( oldTree->getRoot()->mvvu_Children.size()==0 ) {

			//树中唯一模块，删除树（ 进入这个分支 pre_m_id 也可能为0 ）

			///////////////////////////////特殊处理if和for的地方///////////////////////////////

			///
			/// \brief root移出if和for
			///
			if( mvmi_TreeId_For_IfIdMap.count(oldTree) >0 ) {
				tmpIfModule->delTree(oldTree);
				mvmi_TreeId_For_IfIdMap.erase(oldTree);
			}

			///////////////////////////////////////////////////////////////////////////////////

			SAFE_DELETE(oldTree);
			mvmu_TreeMap.erase(cur_m_id);

			// Step3、（必须在此处，不然就return了）更新
			mvmu_ModuleId_TreeMap[cur_m_id] = curActiveTree;

			return 0; //正常返回
		}else {
			//不是唯一模块

			oldTree->setFirstChildAsRoot();
		}

	}

	// Step3、更新
	mvmu_ModuleId_TreeMap[cur_m_id] = curActiveTree;

	return 0;
}

//activeTree直接添加叶子
int logic_Program::addLeafActiveTreeMoveIf(int cur_m_id,int if_id,int branch_id) {

	//////cur_m_id 和 activeTree 必须在同一个if中
	logic_Tree* cur_m_tree = mvmu_ModuleId_TreeMap[cur_m_id];
	assert( mvmi_TreeId_For_IfIdMap[cur_m_tree] == if_id );

	/// 重复 addLeafMove 方法
	if ( 0 >= (mvmu_ModuleMap.count(cur_m_id))*(mvmu_ModuleMap.count(if_id)) ) {
		return -2; // 首先 cur_m_id 和 for_id 都要有
	}

	logic_IfModule * tmpIfModule = this->getIfModuleById(if_id); //判断branch分支是否存在
	assert( tmpIfModule->isBranchExist(branch_id) == true );

	//如果 cur_id 模块是开始
	if ( mvmu_ModuleMap[cur_m_id]->getModuleType() == 2001 ) {
		return -3; //模块类型错误
	}

	logic_Tree *oldTree = mvmu_ModuleId_TreeMap[cur_m_id]; //待删除树
	//该节点必须是该树的根节点
	if( oldTree->mvi_TreeID != cur_m_id )
		assert(false);

	logic_Tree *insTree = tmpIfModule->getCurActiveTree(branch_id);
	logic_TreeNode * insNode = insTree->getRoot(); //待插入节点
	logic_TreeNode * curNode = oldTree->getRoot(); //当前节点

	curNode->mvu_Parent = insNode;

	/// Step1、接入新节点
	insNode->mvvu_Children.push_back(curNode);

	/// Step2、删除旧树map信息
	mvmu_TreeMap.erase(cur_m_id);
	oldTree->setRoot(NULL);
	SAFE_DELETE(oldTree);

	///////////////////////////////特殊处理if和for的地方///////////////////////////////

	///
	/// \brief root移出if和for
	///
	assert( mvmi_TreeId_For_IfIdMap.count(oldTree) >0 ); //必然在一个for中

	tmpIfModule->delTree(oldTree);
	mvmi_TreeId_For_IfIdMap.erase(oldTree);

	///////////////////////////////////////////////////////////////////////////////////

	/// Step3、更新模块树map信息
	recurs_update(insTree,curNode);

	return 0;
}

//单模块新插入activeTree
int logic_Program::appendActiveTreeInsertIf(int m_id,int m_type,int if_id,int branch_id) {

	assert( mvmu_ModuleMap.count(if_id)>0 );

	logic_IfModule * tmpIfModule = this->getIfModuleById(if_id); //判断branch分支是否存在
	assert( tmpIfModule->isBranchExist(branch_id) == true );

	// step1、在森林中加入这个id

	if ( m_type == 2001 ) {
		return false;
	}

	logic_Tree *tree = tmpIfModule->getCurActiveTree(branch_id);
	tree->append_node(-1,m_id);


	// step2、真正生成这个module实体
	this->add_Module(m_id,m_type);

	return 0;
}

//从prj初始化prog
//初始化 “变量”map，v_map是引用
void logic_Program::setInitVarMap(std::map<int  ,logic_VarModule*> &v_map) {

	this->prjVariety = &v_map; //初始化prj 变量 map
}


std::map<int, logic_VarModule*>* logic_Program::getVarMap()
{
	return prjVariety;
}


//初始化 initModule，init_m_map是副本
void logic_Program::setInitModuleMap(std::map <int, logic_BasicModule *> init_m_map) {

	this->initModuleMap = init_m_map; //初始化 所有init module副本
}

std::map <int, logic_BasicModule *> logic_Program::getInit_m_map()
{
	return initModuleMap;
}

///
/// \brief 获取根节点
/// \para 容器编号，如果是0，获取最外层root集合
/// \return 根节点集合
///

//获取program大画布rootsId
std::vector<int > logic_Program::findRootsInContainer() {

	vector<int > L;
	map<int , logic_Tree * > map = mvmu_TreeMap;

	//剔除所有不用的root
	for( std::map<logic_Tree * ,int >::iterator it = mvmi_TreeId_For_IfIdMap.begin();it != mvmi_TreeId_For_IfIdMap.end() ; ++it) {

		map.erase(it->first->mvi_TreeID);
	}

	for( std::map<int ,logic_Tree * >::iterator it = map.begin();it != map.end() ; ++it) {

		if( it->first >= ACTIVE_TREE_MAP_FACTOR )
			continue;

		L.push_back(it->first);
	}

	return L;
}

//重载：获取指定 for 中 rootsId
std::vector<int > logic_Program::findRootsInContainer(int for_id) {

	assert( mvmu_ModuleMap.count(for_id)>0 );
	logic_ForModule * tmpForModule = this->getForModuleById(for_id);

	return tmpForModule->findAllRoots();
}

//重载：获取指定 if 中 rootsId
std::vector<int > logic_Program::findRootsInContainer(int if_id,int branch_id) {

	assert( mvmu_ModuleMap.count(if_id)>0 );
	logic_IfModule * tmpIfModule = this->getIfModuleById(if_id);

	return tmpIfModule->findBranchAllRoots(branch_id);
}

//连线时检测：只有一种情况有问题，即连接自己的祖先
//（其实判断这两个模块如果在一棵树就有问题）
//para： cur_id是连线出口模块，another_id是被连接模块
//
int logic_Program::addLeafCheckPre(int cur_id,int another_id) {

	if ( mvmu_ModuleId_TreeMap[cur_id]->mvi_TreeID 
		== mvmu_ModuleId_TreeMap[another_id]->mvi_TreeID ) {

		return -1;
	}

	return 0;
}

void logic_Program::setModuleMap(std::map <int ,logic_BasicModule* > moduleMap)
{
	mvmu_ModuleMap = moduleMap;
}

void logic_Program::setTreeMap(std::map<int,logic_Tree*> treeMap)
{
	mvmu_TreeMap = treeMap;
}


//!!!!!!!!!!!!!!!!!!!!编译!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!//
whPort logic_Program::getLinkstartwhport(whPort in)
{
	assert(mvvu_Conn_To_FromMap.find(in) != mvvu_Conn_To_FromMap.end());
	return mvvu_Conn_To_FromMap[in];
	
}

std::map<logic_Tree* ,int> logic_Program::getIfforidmaptree()
{
	return mvmi_TreeId_For_IfIdMap;
}
//!!!!!!!!!!!!!!!!!!!!编译!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!//

///
/// \brief 创建我的模块
///

//session1：是否可以创建我的模块，前后端第一次会话
//接口传id列表，返回是否可创建

///1、判断所有模块必须都连通（如果不连通直接pass）
///错误信息：请确保所有模块都已连接，并且共享同一个开始模块
///2、DFS，如果发现有的分支没有覆盖到，则错误
///错误信息：请在选定内容中包含所有并行模块。

///
/// \return -1 代表包含开始模块
///         -2 表示不是一棵树
///         -3 表示验证单分支出错
///          0 表示可以正常创建
///         -4 表示某节点并非所有孩子都被选中
///         -5 表示有多个连通域
///
int logic_Program::canMyBlocks(std::vector<int > ids) {

	assert( mvmu_ModuleMap.count(ids[0])>0 ); //不含此模块

	int vsize = ids.size();
	logic_Tree * tree = mvmu_ModuleId_TreeMap[ids[0]];
	std::map <int , int > idsMap;

	//填充flagMap
	for (int i=0;i<vsize;i++) {

		assert( mvmu_ModuleMap.count(ids[i])>0 ); //不含此模块

		if ( mvmu_ModuleMap[ids[0]]->getModuleType() )
			return -1;

		if ( mvmu_ModuleId_TreeMap[ids[0]]->mvi_TreeID != tree->mvi_TreeID )
			return -2;

		idsMap[ids[i]] = 1; //插入该值
	}

	//先用BFS扫出第一个节点，此节点一定是层数最低的节点（之一）
	std::queue<logic_TreeNode *> q;
	q.push(tree->getRoot());
	logic_TreeNode * n = NULL;
	MyBlockS1_bfsFindStartNode(q,idsMap,n);

	if( NULL == n )
		assert(false);

	//处理单分支情况
	///
	/// \return 0 表示处理完毕，>0 表示不止一个分支，<0 出错
	///
	int res = MyBlockS1_SingleBranchProc(n,idsMap);
	if( res < 0 )
		return -3;
	else if( 0 == res )
		return 0;

	//对tree进行DFS
	res = 0;
	MyBlockS1_DFSJudge(n,res,idsMap);
	if( res < 0 )
		return -4;

	//此时连通域都已遍历完
	if( idsMap.empty() == false )
		return -5;

	return 0; //可以创建
}

///
/// \brief 深度优先搜索判断是否可以建立我的模块，分支次数必然大于1
/// \para res 表示结果 负数表示不可建立，idsMap 标识是否有id（将find时间缩减到O(1)）
///
void logic_Program::MyBlockS1_DFSJudge( logic_TreeNode *some, int res, std::map <int , int > &idsMap ) {

	//判断标准：当start后,branchCnt>1时，保证当前节点以下所有节点都在其中

	if( res < 0 )
		return;

	int curId = some->getID();
	if( idsMap.count(curId) > 0 ) {
		idsMap.erase(curId);
	}

	//搜寻自己的所有孩子是否都在IDSMap中
	//已进行剪枝
	for (unsigned i = 0; i < some->mvvu_Children.size(); i++) {

		if( idsMap.count(some->mvvu_Children[i]->getID()) == 0 )
			res = -1;
		else
			MyBlockS1_DFSJudge(some->mvvu_Children[i],res,idsMap);
	}

	//看自己的兄弟是否存在，如果存在可以继续
	logic_TreeNode *pa = some->mvu_Parent;
	for (int i=0;i<pa->mvvu_Children.size();i++) {
		if( idsMap.count(pa->mvvu_Children[i]->getID()) == 0 )
			MyBlockS1_DFSJudge(some->mvvu_Children[i],res,idsMap);
	}

}

//用bfs找出判断起始节点
void logic_Program::MyBlockS1_bfsFindStartNode(std::queue<logic_TreeNode *> &q,std::map <int , int > idsMap, logic_TreeNode * &findNode) {

	if( findNode != NULL ) //找到了
		return;

	if ( q.empty() == true )
		return;

	logic_TreeNode *node = q.front();
	q.pop();
	if( idsMap.count(node->getID()) > 0 ) {
		findNode = node;
		return;
	}

	//否则加入子女
	for(int i=0;i<node->mvvu_Children.size();++i)
		q.push(node->mvvu_Children[i]);

	MyBlockS1_bfsFindStartNode(q,idsMap,findNode);
}

///
/// \brief 处理单分支情况
/// \return 0 表示处理完毕，>0 表示不止一个分支，<0 出错
///
int logic_Program::MyBlockS1_SingleBranchProc(logic_TreeNode * curNode, std::map <int , int > idsMap) {

	//直接作为单分支情况处理
	while ( idsMap.empty() == false ) {

		if( idsMap.count(curNode->getID()) > 0 ) {
			idsMap.erase(curNode->getID());
		} else {
			//不空但是IDSMap并没有这个节点，证明不是单分支，且这个分支没包含完整，出错
			return -1;
		}

		if ( curNode->mvvu_Children.size() == 0 && idsMap.empty() == false ) {
			//已到叶子节点，但是此处idsMap并没有空
			return 1; //不是一个分支
		}

		curNode = curNode->mvvu_Children[0];

	}
	
	return 0;
}
