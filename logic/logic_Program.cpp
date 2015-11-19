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

using namespace std;

//typedef logic_Tree tree_type;


logic_Program::logic_Program(int id,std::string prog_name)
	:mvs_ProgId(id),mvs_ProgName(prog_name)
{
	Init(); //初始化program

}

logic_Program::~logic_Program()
{
	prog_Destroy();
}

//普通初始化（干净的program）
void logic_Program::Init()
{
	mvmu_TreeMap.clear();
	//mvmu_TreeMap[0] = NULL;
	mvmu_ModuleMap.clear();
	mvmu_ModuleMap[0] = NULL;  //Module 需要 getMax
	mvmu_ModuleId_TreeMap.clear();
	//mvmu_ModuleId_TreeMap[0] = NULL;

	mvvu_ModulePortLineList.clear();
	//mvvu_ModulePortLineList[0] = NULL;
	mvmi_TreeId_For_IfIdMap.clear();
	//mvmi_TreeId_For_IfIdMap[0] = NULL;

	add_Tree(1);

	//建立module表项，仅一个开始模块
	logic_BasicModule *bm = new logic_BasicModule();
	mvmu_ModuleMap.insert(pair<_IdDataType , logic_BasicModule *>(bm->mvi_ModuleID,bm));

	mvmu_ModuleId_TreeMap[1] = mvmu_TreeMap[1];
}

void logic_Program::prog_Destroy()
{
	cout<<"进入prog_Destroy"<<endl;

	//清空mvmu_ModuleMap，安全释放
	for(map<_IdDataType , logic_BasicModule *>::iterator it = mvmu_ModuleMap.begin();it != mvmu_ModuleMap.end(); ++it)
		SAFE_DELETE(it->second);

	//清空森林
	for(map<_IdDataType , logic_Tree *>::iterator it = mvmu_TreeMap.begin();it != mvmu_TreeMap.end(); ++it)
	{
		logic_Tree *tmpT = it->second;
		//tmpT->Destroy(tmpT->getRoot()); //这样会调用两次，堆错误
		SAFE_DELETE(tmpT);
	}

	//清空映射表
	for(map<int , logic_Tree *>::iterator it = mvmu_ModuleId_TreeMap.begin();it != mvmu_ModuleId_TreeMap.end(); ++it)
	{
		logic_Tree *tmpT = it->second;
		//tmpT->Destroy(tmpT->getRoot()); //这样会调用两次，堆错误
		SAFE_DELETE(tmpT);
	}
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

	logic_BasicModule *bm = new logic_BasicModule(moduleId,m_Type);
	mvmu_ModuleMap.insert(pair<_IdDataType , logic_BasicModule *>(bm->mvi_ModuleID,bm));

	return true;
}

bool logic_Program::del_Module(_IdDataType moduleId)
{
	if (mvmu_ModuleMap.count(moduleId)==0) //不存在，删除错误
		return false;

	mvmu_ModuleMap.erase(moduleId);
	return true;
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

int logic_Program::getMaxModuleId() {
	std::map<int, logic_BasicModule *>::const_iterator it = mvmu_ModuleMap.end();
	it--;
	return it->first;
}

//真正在森林中添加id，并实例化此 module
bool logic_Program::appendModule(int m_id,int pre_id,int m_type) {

	assert( mvmu_ModuleMap.count(pre_id)>0 );

	// step1、在森林中加入这个id

	if ( 0 == pre_id ) {   //如果 pre_id 为 0 ，代表要新建一棵树

		logic_Tree *tree = new logic_Tree(m_id);
		this->add_Tree(tree);
		mvmu_TreeMap[m_id] = tree;
		mvmu_ModuleId_TreeMap[m_id] = tree;

	}else {
		//如果 pre_id 不为 0 ，插在 pre_id 后面
		if ( mvmu_ModuleMap[pre_id]->getModuleType() == 2001 && m_type == 2001 ) {
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

	//都是开始模块，不允许插入
	if ( mvmu_ModuleMap[post_id]->getModuleType() == 2001 && m_type == 2001 ) {
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

//前插move
//cur_m_id 是待move节点
//post_m_id 是节点后继
int logic_Program::frontInsSingMove(int cur_m_id,int post_m_id) {

	if ( 0 >= (mvmu_ModuleMap.count(cur_m_id))*(mvmu_ModuleMap.count(post_m_id)) ) {
		return -2; //没找到插入点
	}

	//如果 post_m_id 和 cur_id 模块都是开始
	if ( mvmu_ModuleMap[cur_m_id]->getModuleType() == 2001 
		&& mvmu_ModuleMap[post_m_id]->getModuleType() == 2001 ) {
			return -3; //模块类型错误
	}

	//注：不用新建module，只用处理树节点即可

	///// step1、插入新树节点
	logic_Tree *insTree = mvmu_ModuleId_TreeMap[post_m_id]; //待插入树
	logic_Tree *oldTree = mvmu_ModuleId_TreeMap[cur_m_id]; //待删除树

	int oldRootId = insTree->mvi_TreeID;
	if( post_m_id == oldRootId ) {
		
		//待插入节点要插在原树root之前
		mvmu_TreeMap.erase(post_m_id);
		insTree->exchangeRoot(cur_m_id);
	}else {

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

	//只有 post_m_id 是根的情况，才更新tree map
	if( post_m_id == oldRootId )
		mvmu_TreeMap[cur_m_id] = insTree;

	return 0; //正常返回

}

//单模块后插move
int logic_Program::backInsSingMove(int cur_m_id,int pre_m_id) {

	if ( 0 >= (mvmu_ModuleMap.count(cur_m_id))*(mvmu_ModuleMap.count(pre_m_id)) ) {
		return -2; // 首先 cur_m_id 和 pre_m_id 都要有
	}

	//如果 pre_id 和 cur_id 模块都是开始
	if ( mvmu_ModuleMap[cur_m_id]->getModuleType() == 2001 
		&& mvmu_ModuleMap[pre_m_id]->getModuleType() == 2001 ) {
			return -3; //模块类型错误
	}

	//注：不用新建module，只用处理树节点即可

	///// step1、插入新树节点
	logic_Tree *oldTree = mvmu_ModuleId_TreeMap[cur_m_id]; //待删除树，早点找到会更靠谱
	logic_Tree *insTree = NULL;
	if( 0 == pre_m_id ) {  ////////////必须用深拷贝，浅拷贝可能有危险

		//如果前插一棵空树

		if ( cur_m_id == oldTree->mvi_TreeID && oldTree->getRoot()->mvvu_Children.size()==0 ) {

			//如果是前插空树，同时又是 唯一模块 错误
			return -5;
		}

		logic_TreeNode tmpCurNode( *(mvmu_ModuleId_TreeMap[cur_m_id]->node_search(cur_m_id)) ) ; //拷贝构造

		if ( tmpCurNode.mvvu_Children.size() > 1 ) {
			//如果孩子不是一个，错误
			return -4;
		}

		tmpCurNode.mvu_Parent = 0;
		tmpCurNode.mvvu_Children.clear();

		logic_TreeNode *tmpPassNode = new logic_TreeNode(tmpCurNode); //深拷贝构造
		insTree = new logic_Tree(tmpPassNode); //新建一棵树，此node也必须新建，否则被下面的delnode了

		mvmu_TreeMap[insTree->mvi_TreeID] = insTree;

	}else {

		////// pre_m_id 不为0

		/////如果已存在，直接找到待插入树
		insTree = mvmu_ModuleId_TreeMap[pre_m_id];
		insTree->append_node(pre_m_id,cur_m_id);
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

//带祖先前插move
////////////////注：必然是插在一棵树的最前面/////////////////
int logic_Program::frontInsMultiMove(int cur_m_id,int post_m_id) {

	if ( 0 >= (mvmu_ModuleMap.count(cur_m_id))*(mvmu_ModuleMap.count(post_m_id)) ) {
		return -2; //没找到插入点
	}

	//如果 post_m_id 和 cur_id 模块都是开始
	if ( mvmu_ModuleMap[cur_m_id]->getModuleType() == 2001 
		&& mvmu_ModuleMap[post_m_id]->getModuleType() == 2001 ) {
			return -3; //模块类型错误
	}

	//注：不用新建module，只用处理树节点即可

	///// step1、插入新树节点
	/////!!!!!!!!!!!!特别注意这里，这里的 insTree 和 oldtree 调换，可以转换为后插!!!!!!!!!!!!!!
	logic_Tree *insTree = mvmu_ModuleId_TreeMap[cur_m_id]; //待插入树
	logic_Tree *oldTree = mvmu_ModuleId_TreeMap[post_m_id]; //待删除树

	//如果 post_m_id 不是根节点，错误返回
	if( post_m_id!=oldTree->mvi_TreeID ) {
		return -4;
	}

	///////////////////////////////////////
	logic_TreeNode * insNode = oldTree->getRoot(); //待插入节点
	insTree->add_node(cur_m_id,insNode);

	///// step2、删除旧树节点

	//必然是ROOT，直接删除树
	oldTree->del_node_notConn(post_m_id); //断开 oldTree 此节点后的所有连接
	SAFE_DELETE(oldTree); //放心删除树
	mvmu_TreeMap.erase(post_m_id);

	///// step3、更新 module tree映射

	recurs_update(insTree,insNode);


	return 0; //正常返回
}

//带孩子后插move
int logic_Program::backInsMultiMove(int cur_m_id,int pre_m_id) {

	if ( 0 >= (mvmu_ModuleMap.count(cur_m_id))*(mvmu_ModuleMap.count(pre_m_id)) ) {
		return -2; // 首先 cur_m_id 和 pre_m_id 都要有
	}

	//如果 pre_id 和 cur_id 模块都是开始
	if ( mvmu_ModuleMap[cur_m_id]->getModuleType() == 2001 
		&& mvmu_ModuleMap[pre_m_id]->getModuleType() == 2001 ) {
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

bool logic_Program::delModule(int m_id) {

	if (mvmu_ModuleMap.count(m_id)==0) //不存在，删除错误
		return false;

	// step1、在森林中删掉这个id
	logic_Tree *tree = mvmu_ModuleId_TreeMap[m_id]; //得到所在的树

	if (m_id != tree->mvi_TreeID ) {

		logic_TreeNode *delNode = tree->node_search(m_id);

		if(delNode->mvvu_Children.size() == 1) {

			//1、非ROOT，且只有一个孩子，正常删除
			tree->del_node(m_id);
			mvmu_ModuleId_TreeMap.erase(m_id);

		}else if(delNode->mvvu_Children.size() > 1) {

			//2、有多个孩子，拆成多棵树

			//后面的孩子需要建立n颗树
			for (int i=0; i<delNode->mvvu_Children.size() ; ++i ) {

				delNode->mvvu_Children.at(i)->mvu_Parent = NULL;
				logic_Tree * tmpTree = new logic_Tree(delNode->mvvu_Children.at(i)); //新建树
				mvmu_TreeMap[tmpTree->mvi_TreeID] = tmpTree; //树map 新增
				updateMId_TreeMap(tmpTree); //更新映射表
			}

			//原树不动，只须将当前节点父节点这点移除
			tree->del_node_notConn(m_id);
			SAFE_DELETE(delNode);  //正式删除此节点
			mvmu_ModuleId_TreeMap.erase(m_id);
		}

	}else {

		//ROOT
		logic_TreeNode *oldRoot = tree->getRoot();

		if(oldRoot->mvvu_Children.size() == 1) {
			//1、且只有一个孩子，正常删除（tree没有改变，不必更新映射表）
			tree->del_node(m_id);
			mvmu_ModuleId_TreeMap.erase(m_id);

		}else if(oldRoot->mvvu_Children.size() > 1) {

			//2、root有n个孩子，拆成n棵树，每棵树是树根

			//后面需要建立n-1颗树
			for (int i=1; i<oldRoot->mvvu_Children.size() ; ++i ) {

				oldRoot->mvvu_Children.at(i)->mvu_Parent = NULL;
				logic_Tree * tmpTree = new logic_Tree(oldRoot->mvvu_Children.at(i)); //新建树
				mvmu_TreeMap[tmpTree->mvi_TreeID] = tmpTree; //树map 新增
				updateMId_TreeMap(tmpTree); //更新映射表
			}

			//原树直接设置孩子为root（tree没有改变，不必更新映射表）
			tree->setFirstChildAsRoot();
			mvmu_ModuleId_TreeMap.erase(m_id);

		}else if(oldRoot->mvvu_Children.size() == 0) {

			//树中唯一的模块，删除树
			SAFE_DELETE(mvmu_ModuleId_TreeMap[m_id]);
			mvmu_TreeMap.erase(m_id);
			mvmu_ModuleId_TreeMap.erase(m_id);
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

bool logic_Program::addLeafModule(int m_id,int pre_id,int m_type) {

	if ( 0 == pre_id ) {
		return false;
	}

	//如果 pre_id 不为 0 ，插在 pre_id 后面
	if ( mvmu_ModuleMap[pre_id]->getModuleType() == 2001 && m_type == 2001 ) {
		return false;
	}

	logic_Tree *tree = mvmu_ModuleId_TreeMap[pre_id];
	tree->add_node(pre_id,m_id);

	mvmu_ModuleId_TreeMap[m_id] = tree;

	// step2、真正生成这个module实体
	this->add_Module(m_id,m_type);

	return true;
}

int logic_Program::getModulePreId(int m_id) {

	if (mvmu_ModuleMap.count(m_id)==0) //不存在，错误
		return -1;

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

		break;

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

void logic_Program::recurs_GetNode(logic_TreeNode *some,std::vector<logic_TreeNode *> & L) {

	L.push_back(some);

	//和 getAllTreeNodeId() 连用，递归get id
	for (unsigned i = 0; i < some->mvvu_Children.size(); i++) {
		recurs_GetNode(some->mvvu_Children[i],L);
	}
}
