/* 
* 
* function: �߼���ɭ����֯�ṹ
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

using namespace std;

//typedef logic_Tree tree_type;


logic_Program::logic_Program(int id,std::string prog_name)
	:mvs_ProgId(id),mvs_ProgName(prog_name)
{
	Init(); //��ʼ��program

}

logic_Program::~logic_Program()
{
	prog_Destroy();
}

//��ͨ��ʼ�����ɾ���program��
void logic_Program::Init()
{
	mvmu_TreeMap.clear();
	//mvmu_TreeMap[0] = NULL;
	mvmu_ModuleMap.clear();
	mvmu_ModuleMap[0] = NULL;  //Module ��Ҫ getMax
	mvmu_ModuleId_TreeMap.clear();
	//mvmu_ModuleId_TreeMap[0] = NULL;

	mvvu_ModulePortLineList.clear();
	//mvvu_ModulePortLineList[0] = NULL;
	mvmi_TreeId_For_IfIdMap.clear();
	//mvmi_TreeId_For_IfIdMap[0] = NULL;

	add_Tree(1);

	//����module�����һ����ʼģ��
	logic_BasicModule *bm = new logic_BasicModule();
	mvmu_ModuleMap.insert(pair<_IdDataType , logic_BasicModule *>(bm->mvi_ModuleID,bm));

	mvmu_ModuleId_TreeMap[1] = mvmu_TreeMap[1];
}

void logic_Program::prog_Destroy()
{
	cout<<"����prog_Destroy"<<endl;

	//���mvmu_ModuleMap����ȫ�ͷ�
	for(map<_IdDataType , logic_BasicModule *>::iterator it = mvmu_ModuleMap.begin();it != mvmu_ModuleMap.end(); ++it)
		SAFE_DELETE(it->second);

	//���ɭ��
	for(map<_IdDataType , logic_Tree *>::iterator it = mvmu_TreeMap.begin();it != mvmu_TreeMap.end(); ++it)
	{
		logic_Tree *tmpT = it->second;
		//tmpT->Destroy(tmpT->getRoot()); //������������Σ��Ѵ���
		SAFE_DELETE(tmpT);
	}

	//���ӳ���
	for(map<int , logic_Tree *>::iterator it = mvmu_ModuleId_TreeMap.begin();it != mvmu_ModuleId_TreeMap.end(); ++it)
	{
		logic_Tree *tmpT = it->second;
		//tmpT->Destroy(tmpT->getRoot()); //������������Σ��Ѵ���
		SAFE_DELETE(tmpT);
	}
}

bool logic_Program::add_Tree(_IdDataType rootId)
{
	if (mvmu_TreeMap.count(rootId)>0) //�Ѵ��ڣ����󷵻�
		return false;

	logic_Tree* t = new logic_Tree(rootId);
	mvmu_TreeMap.insert(pair<_IdDataType , logic_Tree *>(t->mvi_TreeID,t));

	return true;
}

bool logic_Program::add_Tree(logic_Tree * t)
{
	if (mvmu_TreeMap.count(t->mvi_TreeID)>0) //�Ѵ��ڣ����󷵻�
		return false;

	//logic_Tree *tmpTree = new logic_Tree(*t);
	mvmu_TreeMap[t->mvi_TreeID]=t;

	return true;
}

bool logic_Program::del_Tree(_IdDataType rootId)
{
	if (mvmu_TreeMap.count(rootId)==0) //�����ڣ�ɾ������
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

//������ָ����ID���ҵ�����ID���Ҳ�������-1
_IdDataType logic_Program::search_Tree(logic_Tree* treePtr)
{
	if (mvmu_TreeMap.count(treePtr->mvi_TreeID)>0)
	{
		return treePtr->mvi_TreeID;
	}
	return -1;
}

//�������ͷ� modulePtr �ռ�
bool logic_Program::add_Module(_IdDataType moduleId , logic_BasicModule* modulePtr)
{
	if (mvmu_ModuleMap.count(moduleId)>0) //�Ѵ��ڣ����󷵻�
		return false;

	mvmu_ModuleMap[modulePtr->mvi_ModuleID] = modulePtr;

	return true;
}

bool logic_Program::add_Module(_IdDataType moduleId , int m_Type)
{
	if (mvmu_ModuleMap.count(moduleId)>0) //�Ѵ��ڣ����󷵻�
		return false;

	logic_BasicModule *bm = new logic_BasicModule(moduleId,m_Type);
	mvmu_ModuleMap.insert(pair<_IdDataType , logic_BasicModule *>(bm->mvi_ModuleID,bm));

	return true;
}

bool logic_Program::del_Module(_IdDataType moduleId)
{
	if (mvmu_ModuleMap.count(moduleId)==0) //�����ڣ�ɾ������
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

//������ɭ��������id����ʵ������ module
bool logic_Program::appendModule(int m_id,int pre_id,int m_type) {

	assert( mvmu_ModuleMap.count(pre_id)>0 );

	// step1����ɭ���м������id

	if ( 0 == pre_id ) {   //��� pre_id Ϊ 0 ������Ҫ�½�һ����

		logic_Tree *tree = new logic_Tree(m_id);
		this->add_Tree(tree);
		mvmu_TreeMap[m_id] = tree;
		mvmu_ModuleId_TreeMap[m_id] = tree;

	}else {
		//��� pre_id ��Ϊ 0 ������ pre_id ����
		if ( mvmu_ModuleMap[pre_id]->getModuleType() == 2001 && m_type == 2001 ) {
			return false;
		}

		logic_Tree *tree = mvmu_ModuleId_TreeMap[pre_id];
		tree->append_node(pre_id,m_id);

		mvmu_ModuleId_TreeMap[m_id] = tree;
	}

	// step2�������������moduleʵ��
	this->add_Module(m_id,m_type);

	return true;
}

bool logic_Program::frontInsModule(int m_id,int post_id,int m_type) {

	assert( mvmu_ModuleMap.count(post_id)>0 );

	if ( 0 == post_id ) {
		return false;
	}

	// step1����ɭ���м������id

	//���ǿ�ʼģ�飬����������
	if ( mvmu_ModuleMap[post_id]->getModuleType() == 2001 && m_type == 2001 ) {
		return false;
	}

	logic_Tree *tree = mvmu_ModuleId_TreeMap[post_id];

	if ( post_id == tree->mvi_TreeID ) { //���ֺ�̽ڵ���root����Ҫ����
		tree->exchangeRoot(m_id);
		mvmu_ModuleId_TreeMap[m_id] = tree;

		//update treeMap
		mvmu_TreeMap.erase(post_id);
		mvmu_TreeMap[m_id] = tree;

	}else{ //�����̲���root�����뵽�������м�

		tree->insert_node(tree->getPreId(post_id),post_id,m_id);
		mvmu_ModuleId_TreeMap[m_id] = tree;
	}

	// step2�������������moduleʵ��
	this->add_Module(m_id,m_type);

	return true;
}

//ǰ��move
//cur_m_id �Ǵ�move�ڵ�
//post_m_id �ǽڵ���
int logic_Program::frontInsSingMove(int cur_m_id,int post_m_id) {

	if ( 0 >= (mvmu_ModuleMap.count(cur_m_id))*(mvmu_ModuleMap.count(post_m_id)) ) {
		return -2; //û�ҵ������
	}

	//��� post_m_id �� cur_id ģ�鶼�ǿ�ʼ
	if ( mvmu_ModuleMap[cur_m_id]->getModuleType() == 2001 
		&& mvmu_ModuleMap[post_m_id]->getModuleType() == 2001 ) {
			return -3; //ģ�����ʹ���
	}

	//ע�������½�module��ֻ�ô������ڵ㼴��

	///// step1�����������ڵ�
	logic_Tree *insTree = mvmu_ModuleId_TreeMap[post_m_id]; //��������
	logic_Tree *oldTree = mvmu_ModuleId_TreeMap[cur_m_id]; //��ɾ����

	int oldRootId = insTree->mvi_TreeID;
	if( post_m_id == oldRootId ) {
		
		//������ڵ�Ҫ����ԭ��root֮ǰ
		mvmu_TreeMap.erase(post_m_id);
		insTree->exchangeRoot(cur_m_id);
	}else {

		//��������ط�
		insTree->insert_node(insTree->getPreId(post_m_id),post_m_id,cur_m_id);
	}

	mvmu_ModuleId_TreeMap[cur_m_id] = insTree;

	///// step2��ɾ�������ڵ㣨ע���˴��������ж�����ӣ�
	if( cur_m_id != oldTree->mvi_TreeID ) {

		//��������
		oldTree->del_node(cur_m_id);
	}else if(cur_m_id == oldTree->mvi_TreeID 
		|| oldTree->getRoot()->mvvu_Children.size()==0 ) {

			//����Ψһģ�飬ɾ����
			SAFE_DELETE(oldTree);
			mvmu_TreeMap.erase(cur_m_id);
	}

	//ֻ�� post_m_id �Ǹ���������Ÿ���tree map
	if( post_m_id == oldRootId )
		mvmu_TreeMap[cur_m_id] = insTree;

	return 0; //��������

}

//��ģ����move
int logic_Program::backInsSingMove(int cur_m_id,int pre_m_id) {

	if ( 0 >= (mvmu_ModuleMap.count(cur_m_id))*(mvmu_ModuleMap.count(pre_m_id)) ) {
		return -2; // ���� cur_m_id �� pre_m_id ��Ҫ��
	}

	//��� pre_id �� cur_id ģ�鶼�ǿ�ʼ
	if ( mvmu_ModuleMap[cur_m_id]->getModuleType() == 2001 
		&& mvmu_ModuleMap[pre_m_id]->getModuleType() == 2001 ) {
			return -3; //ģ�����ʹ���
	}

	//ע�������½�module��ֻ�ô������ڵ㼴��

	///// step1�����������ڵ�
	logic_Tree *oldTree = mvmu_ModuleId_TreeMap[cur_m_id]; //��ɾ����������ҵ��������
	logic_Tree *insTree = NULL;
	if( 0 == pre_m_id ) {  ////////////�����������ǳ����������Σ��

		//���ǰ��һ�ÿ���

		if ( cur_m_id == oldTree->mvi_TreeID && oldTree->getRoot()->mvvu_Children.size()==0 ) {

			//�����ǰ�������ͬʱ���� Ψһģ�� ����
			return -5;
		}

		logic_TreeNode tmpCurNode( *(mvmu_ModuleId_TreeMap[cur_m_id]->node_search(cur_m_id)) ) ; //��������

		if ( tmpCurNode.mvvu_Children.size() > 1 ) {
			//������Ӳ���һ��������
			return -4;
		}

		tmpCurNode.mvu_Parent = 0;
		tmpCurNode.mvvu_Children.clear();

		logic_TreeNode *tmpPassNode = new logic_TreeNode(tmpCurNode); //�������
		insTree = new logic_Tree(tmpPassNode); //�½�һ��������nodeҲ�����½������������delnode��

		mvmu_TreeMap[insTree->mvi_TreeID] = insTree;

	}else {

		////// pre_m_id ��Ϊ0

		/////����Ѵ��ڣ�ֱ���ҵ���������
		insTree = mvmu_ModuleId_TreeMap[pre_m_id];
		insTree->append_node(pre_m_id,cur_m_id);
	}

	///// step2��ɾ�������ڵ㣨ע���˴��������ж�����ӣ�

	if( cur_m_id != oldTree->mvi_TreeID ) {

		//��������
		oldTree->del_node(cur_m_id);
	}else if(cur_m_id == oldTree->mvi_TreeID ) {

		if ( oldTree->getRoot()->mvvu_Children.size()==0 ) {

			//����Ψһģ�飬ɾ������ ���������֧ pre_m_id ��Ȼ������0���������жϣ��������-5 ��

			SAFE_DELETE(oldTree);
			mvmu_TreeMap.erase(cur_m_id);

			// Step3���������ڴ˴�����Ȼ��return�ˣ�����
			mvmu_ModuleId_TreeMap[cur_m_id] = insTree;

			return 0; //��������
		}else {
			//����Ψһģ��

			oldTree->setFirstChildAsRoot();
		}

	}

	// Step3������
	mvmu_ModuleId_TreeMap[cur_m_id] = insTree;

	return 0; //��������
}

//������ǰ��move
////////////////ע����Ȼ�ǲ���һ��������ǰ��/////////////////
int logic_Program::frontInsMultiMove(int cur_m_id,int post_m_id) {

	if ( 0 >= (mvmu_ModuleMap.count(cur_m_id))*(mvmu_ModuleMap.count(post_m_id)) ) {
		return -2; //û�ҵ������
	}

	//��� post_m_id �� cur_id ģ�鶼�ǿ�ʼ
	if ( mvmu_ModuleMap[cur_m_id]->getModuleType() == 2001 
		&& mvmu_ModuleMap[post_m_id]->getModuleType() == 2001 ) {
			return -3; //ģ�����ʹ���
	}

	//ע�������½�module��ֻ�ô������ڵ㼴��

	///// step1�����������ڵ�
	/////!!!!!!!!!!!!�ر�ע���������� insTree �� oldtree ����������ת��Ϊ���!!!!!!!!!!!!!!
	logic_Tree *insTree = mvmu_ModuleId_TreeMap[cur_m_id]; //��������
	logic_Tree *oldTree = mvmu_ModuleId_TreeMap[post_m_id]; //��ɾ����

	//��� post_m_id ���Ǹ��ڵ㣬���󷵻�
	if( post_m_id!=oldTree->mvi_TreeID ) {
		return -4;
	}

	///////////////////////////////////////
	logic_TreeNode * insNode = oldTree->getRoot(); //������ڵ�
	insTree->add_node(cur_m_id,insNode);

	///// step2��ɾ�������ڵ�

	//��Ȼ��ROOT��ֱ��ɾ����
	oldTree->del_node_notConn(post_m_id); //�Ͽ� oldTree �˽ڵ�����������
	SAFE_DELETE(oldTree); //����ɾ����
	mvmu_TreeMap.erase(post_m_id);

	///// step3������ module treeӳ��

	recurs_update(insTree,insNode);


	return 0; //��������
}

//�����Ӻ��move
int logic_Program::backInsMultiMove(int cur_m_id,int pre_m_id) {

	if ( 0 >= (mvmu_ModuleMap.count(cur_m_id))*(mvmu_ModuleMap.count(pre_m_id)) ) {
		return -2; // ���� cur_m_id �� pre_m_id ��Ҫ��
	}

	//��� pre_id �� cur_id ģ�鶼�ǿ�ʼ
	if ( mvmu_ModuleMap[cur_m_id]->getModuleType() == 2001 
		&& mvmu_ModuleMap[pre_m_id]->getModuleType() == 2001 ) {
			return -3; //ģ�����ʹ���
	}

	//ע�������½�module��ֻ�ô������ڵ㼴��

	/////////////��ʼ/////////////
	
	///// step1��ɾ�������ڵ�
	///// ע��ɾ�������ǵ�һ������Ȼ del_node_notConn ������ɾ������ parent �ĺ���

	logic_Tree *oldTree = mvmu_ModuleId_TreeMap[cur_m_id]; //��ɾ����
	logic_TreeNode * insNode = oldTree->node_search(cur_m_id); //������ڵ㣨�����ڴ˴�Ѱ�ң�

	if ( insNode->mvvu_Children.size() == 0 ) {
		//����ֻ��һ������
		return -4;
	}

	if( cur_m_id != oldTree->mvi_TreeID ) {

		//��������
		oldTree->del_node_notConn(cur_m_id); //�Ͽ� oldTree ��˽ڵ������

	}else if(cur_m_id == oldTree->mvi_TreeID ) {

		//ROOT��ɾ����
		oldTree->del_node_notConn(cur_m_id); //�����������ֱ�ӽ�����root�ÿ�
		SAFE_DELETE(oldTree); //����ɾ����
		mvmu_TreeMap.erase(cur_m_id);
	}

	///// step2�������½ڵ�
	logic_Tree *insTree = NULL;
	if( 0 == pre_m_id ) { 
		//���ǰ��һ�ÿ���

		insTree = new logic_Tree(insNode); //�½�һ����

		mvmu_TreeMap[insTree->mvi_TreeID] = insTree;
		mvmu_ModuleId_TreeMap[cur_m_id] = insTree;

	}else {
		/////����Ѵ��ڣ�ֱ���ҵ���������
		insTree = mvmu_ModuleId_TreeMap[pre_m_id];

		logic_TreeNode * preNode = insTree->node_search(pre_m_id); //pre_m_id�ڵ�
		//��� pre_m_id ����Ҷ�ӽڵ㣬���󷵻�
		if(preNode->mvvu_Children.size()>0) {
			return -4;
		}

		insTree->add_node(pre_m_id,insNode);

	}

	///// step3������ module treeӳ��
	recurs_update(insTree,insNode);

	return 0; //��������
}

//ͨ��һ��ģ��id���ҵ�������
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

	if (mvmu_ModuleMap.count(m_id)==0) //�����ڣ�ɾ������
		return false;

	// step1����ɭ����ɾ�����id
	logic_Tree *tree = mvmu_ModuleId_TreeMap[m_id]; //�õ����ڵ���

	if (m_id != tree->mvi_TreeID ) {

		logic_TreeNode *delNode = tree->node_search(m_id);

		if(delNode->mvvu_Children.size() == 1) {

			//1����ROOT����ֻ��һ�����ӣ�����ɾ��
			tree->del_node(m_id);
			mvmu_ModuleId_TreeMap.erase(m_id);

		}else if(delNode->mvvu_Children.size() > 1) {

			//2���ж�����ӣ���ɶ����

			//����ĺ�����Ҫ����n����
			for (int i=0; i<delNode->mvvu_Children.size() ; ++i ) {

				delNode->mvvu_Children.at(i)->mvu_Parent = NULL;
				logic_Tree * tmpTree = new logic_Tree(delNode->mvvu_Children.at(i)); //�½���
				mvmu_TreeMap[tmpTree->mvi_TreeID] = tmpTree; //��map ����
				updateMId_TreeMap(tmpTree); //����ӳ���
			}

			//ԭ��������ֻ�뽫��ǰ�ڵ㸸�ڵ�����Ƴ�
			tree->del_node_notConn(m_id);
			SAFE_DELETE(delNode);  //��ʽɾ���˽ڵ�
			mvmu_ModuleId_TreeMap.erase(m_id);
		}

	}else {

		//ROOT
		logic_TreeNode *oldRoot = tree->getRoot();

		if(oldRoot->mvvu_Children.size() == 1) {
			//1����ֻ��һ�����ӣ�����ɾ����treeû�иı䣬���ظ���ӳ�����
			tree->del_node(m_id);
			mvmu_ModuleId_TreeMap.erase(m_id);

		}else if(oldRoot->mvvu_Children.size() > 1) {

			//2��root��n�����ӣ����n������ÿ����������

			//������Ҫ����n-1����
			for (int i=1; i<oldRoot->mvvu_Children.size() ; ++i ) {

				oldRoot->mvvu_Children.at(i)->mvu_Parent = NULL;
				logic_Tree * tmpTree = new logic_Tree(oldRoot->mvvu_Children.at(i)); //�½���
				mvmu_TreeMap[tmpTree->mvi_TreeID] = tmpTree; //��map ����
				updateMId_TreeMap(tmpTree); //����ӳ���
			}

			//ԭ��ֱ�����ú���Ϊroot��treeû�иı䣬���ظ���ӳ�����
			tree->setFirstChildAsRoot();
			mvmu_ModuleId_TreeMap.erase(m_id);

		}else if(oldRoot->mvvu_Children.size() == 0) {

			//����Ψһ��ģ�飬ɾ����
			SAFE_DELETE(mvmu_ModuleId_TreeMap[m_id]);
			mvmu_TreeMap.erase(m_id);
			mvmu_ModuleId_TreeMap.erase(m_id);
		}
		
	}


	// step2����map��ɾ�����moduleʵ��
	this->del_Module(m_id);

	return true;
}

void logic_Program::updateMId_TreeMap(logic_Tree *tree) {
	//��һ����������module treeӳ���Ϊ��ǰtree
	this->recurs_update(tree,tree->getRoot());
}

void logic_Program::recurs_update(logic_Tree *tree,logic_TreeNode *some) {

	mvmu_ModuleId_TreeMap[some->getID()] = tree;

	//�� updateMId_TreeMap() ���ã��ݹ����
	for (unsigned i = 0; i < some->mvvu_Children.size(); i++) {
		recurs_update(tree,some->mvvu_Children[i]);
	}
}

bool logic_Program::addLeafModule(int m_id,int pre_id,int m_type) {

	if ( 0 == pre_id ) {
		return false;
	}

	//��� pre_id ��Ϊ 0 ������ pre_id ����
	if ( mvmu_ModuleMap[pre_id]->getModuleType() == 2001 && m_type == 2001 ) {
		return false;
	}

	logic_Tree *tree = mvmu_ModuleId_TreeMap[pre_id];
	tree->add_node(pre_id,m_id);

	mvmu_ModuleId_TreeMap[m_id] = tree;

	// step2�������������moduleʵ��
	this->add_Module(m_id,m_type);

	return true;
}

int logic_Program::getModulePreId(int m_id) {

	if (mvmu_ModuleMap.count(m_id)==0) //�����ڣ�����
		return -1;

	int resid = mvmu_ModuleId_TreeMap[m_id]->getPreId(m_id);

	return resid;
}

std::vector<int > logic_Program::getModulePostId(int m_id) {

	std::vector<int > L;

	if (mvmu_ModuleMap.count(m_id) == 0) //�����ڣ�����
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
		//���󣬷��ؿռ�
		return L;
	}

	logic_Tree *tree = mvmu_TreeMap[tree_id];
	this->recurs_GetId(tree->getRoot(),L);

	return L;
}

void logic_Program::recurs_GetId(logic_TreeNode *some,std::vector<int> & L) {

	L.push_back(some->getID());

	//�� getAllTreeNodeId() ���ã��ݹ�get id
	for (unsigned i = 0; i < some->mvvu_Children.size(); i++) {
		recurs_GetId(some->mvvu_Children[i],L);
	}
}

std::string logic_Program::getModulePara(int type,int m_id,int p_id) {

	//MAX_VALUE = 0,//���ֵ
	//MIN_VALUE, //��Сֵ
	//INIT, //��ʼֵ
	//CUR //��ǰֵ

	if ( 0 == mvmu_ModuleMap.count(m_id) ) {
		return NULL; //����
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
		return ; //����
	}

	logic_BasicPara *tPara = mvmu_ModuleMap[m_id]->getPara(p_id);
	tPara->mvs_Value = p_value;
}

WinSwitcherType logic_Program::getModuleWinSwType(int m_id,int m_modeValue) {

	if ( 0 == mvmu_ModuleMap.count(m_id) ) {
		//return ; //����
		assert(false);
	}

	logic_BasicModule *tModule = mvmu_ModuleMap[m_id];
	return tModule->getWSType(m_modeValue);
}

std::string logic_Program::getModuleWinSwValue(int m_id) {

	if ( 0 == mvmu_ModuleMap.count(m_id) ) {
		return NULL; //����
	}

	logic_BasicModule *tModule = mvmu_ModuleMap[m_id];
	return tModule->getWSValue();

}

void logic_Program::setModuleWinSwValue(int m_id,std::string ws_value) {

	if ( 0 == mvmu_ModuleMap.count(m_id) ) {
		return ; //����
	}

	logic_BasicModule *tModule = mvmu_ModuleMap[m_id];
	tModule->setWSValue(ws_value);
}

int logic_Program::getModuleDaisyChainValue(int m_id) {

	if ( 0 == mvmu_ModuleMap.count(m_id) ) {
		return -1; //����
	}

	logic_BasicModule *tModule = mvmu_ModuleMap[m_id];
	return tModule->getDaisyChainValue();
}

void logic_Program::setModuleDaisyChainValue(int m_id,int chain_value) {

	if ( 0 == mvmu_ModuleMap.count(m_id) ) {
		return ; //����
	}

	logic_BasicModule *tModule = mvmu_ModuleMap[m_id];
	tModule->setDaisyChainValue(chain_value);
}

std::vector<int > logic_Program::getModuleParamsIds(int m_id,int mode_value) {

	if ( 0 == mvmu_ModuleMap.count(m_id) ) {
		//return ; //����
		assert(false);
	}

	logic_BasicModule *tModule = mvmu_ModuleMap[m_id];
	return tModule->getParamsIds(mode_value);
}

int logic_Program::getModuleModeValue(int m_id) {

	if ( 0 == mvmu_ModuleMap.count(m_id) ) {
		return -1; //����
	}

	logic_BasicModule *tModule = mvmu_ModuleMap[m_id];
	return tModule->getModeValue();
}

void logic_Program::setModuleModeValue(int m_id,int mode_id) {

	if ( 0 == mvmu_ModuleMap.count(m_id) ) {
		return ; //����
	}

	logic_BasicModule *tModule = mvmu_ModuleMap[m_id];
	tModule->setModeValue(mode_id);
}

//�õ�����treenode
std::vector<logic_TreeNode *> logic_Program::getAllTreeNode(int rootID) {

	std::vector<logic_TreeNode *> L;

	if ( 0 == mvmu_ModuleMap.count(rootID) ) {
		return L; //����
	}

	logic_Tree *tree = mvmu_TreeMap[rootID];
	this->recurs_GetNode(tree->getRoot(),L);

	return L;

}

void logic_Program::recurs_GetNode(logic_TreeNode *some,std::vector<logic_TreeNode *> & L) {

	L.push_back(some);

	//�� getAllTreeNodeId() ���ã��ݹ�get id
	for (unsigned i = 0; i < some->mvvu_Children.size(); i++) {
		recurs_GetNode(some->mvvu_Children[i],L);
	}
}

/// \brief for if

//insert into for
bool logic_Program::insertModuleIntoFor(int m_id,int pre_id,int m_type,int for_id) {

	/////�˴��ѱ�Ȼ�� append �ˣ��� pre_id ��Ȼ��0

	if( mvmu_ModuleMap.count(for_id) == 0 )
		return false;

	///// Step1�������Ѿ�д�õ� appendModule() ������pre_id ��Ȼ��0
	this->appendModule(m_id,0,m_type);

	///// Step2���� for ģ���м���
	logic_BasicModule * tmpModule = mvmu_ModuleMap[for_id];

	if( 2003 != tmpModule->getModuleType() ) //����forģ�飬����
		return false;

	/// type һ����2003
	logic_ForModule *tmpForModule = (logic_ForModule *)tmpModule; //ǿ��ת����for module
	
	if( tmpForModule->addTreeId(m_id) < 0 )
		return false;

	mvmi_TreeId_For_IfIdMap[m_id] = for_id;

	return true;
}

//insert into if
bool logic_Program::insertModuleIntoIf(int m_id,int pre_id,int m_type,int if_id,int branch_id) {

	/////�˴��ѱ�Ȼ�� append �ˣ��� pre_id ��Ȼ��0

	if( mvmu_ModuleMap.count(if_id) == 0 )
		return false;

	///// Step1�������Ѿ�д�õ� appendModule() ����
	this->appendModule(m_id,pre_id,m_type);

	///// Step2���� for ģ���м���
	logic_BasicModule * tmpModule = mvmu_ModuleMap[if_id];

	if( 2004 != tmpModule->getModuleType() ) //����forģ�飬����
		return false;

	/// type һ����2004
	logic_IfModule *tmpIfModule = (logic_IfModule *)tmpModule; //ǿ��ת����for module
	
	if( tmpIfModule->addTreeId(branch_id,m_id) < 0 )
		return false;

	mvmi_TreeId_For_IfIdMap[m_id] = if_id;

	return true;
}

// get for ��ǰactive��
int logic_Program::getForActiveTree(int for_id) {

	if( mvmu_ModuleMap.count(for_id) == 0 )
		return -3;

	logic_BasicModule * tmpModule = mvmu_ModuleMap[for_id];

	if( 2003 != tmpModule->getModuleType() ) //����forģ�飬����
		return false;

	/// type һ����2003
	logic_ForModule *tmpForModule = (logic_ForModule *)tmpModule; //ǿ��ת����for module

	int tree = tmpForModule->getCurActiveTree(); //����С��0

	return tree;
}

//if ��ǰactive��
int logic_Program::getIfActiveTree(int if_id,int branch_id) {

	if( mvmu_ModuleMap.count(if_id) == 0 )
		return -3;

	logic_BasicModule * tmpModule = mvmu_ModuleMap[if_id];

	if( 2004 != tmpModule->getModuleType() ) //����forģ�飬����
		return false;

	/// type һ����2004
	logic_IfModule *tmpIfModule = (logic_IfModule *)tmpModule; //ǿ��ת����for module

	int tree = tmpIfModule->getCurActiveTree(branch_id); //����С��0

	return tree;
}

// set for
void logic_Program::setForActiveTree(int for_id,int tree_id) {

	assert( mvmu_ModuleMap.count(for_id) > 0 ); //�ٶ� count ����0

	logic_BasicModule * tmpModule = mvmu_ModuleMap[for_id];

	assert( 2003 == tmpModule->getModuleType() ); //����forģ�飬����

	/// type һ����2003
	logic_ForModule *tmpForModule = (logic_ForModule *)tmpModule; //ǿ��ת����for module
	tmpForModule->setCurActiveTree(tree_id); //����С��0

	return;
}

//if
void logic_Program::setIfActiveTree(int if_id,int branch_id,int tree_id) {

	assert( mvmu_ModuleMap.count(if_id) > 0 ); //�ٶ� count ����0

	logic_BasicModule * tmpModule = mvmu_ModuleMap[if_id];

	assert( 2004 == tmpModule->getModuleType() ); //����forģ�飬����

	/// type һ����2004
	logic_IfModule *tmpIfModule = (logic_IfModule *)tmpModule; //ǿ��ת����for module
	tmpIfModule->setCurActiveTree(branch_id,tree_id); //����С��0

	return;
}

//get ָ�� branch��int content
int logic_Program::getIfBranchContentInt(int if_id,int branch_id) {

	if( mvmu_ModuleMap.count(if_id) == 0 )
		return -3;

	logic_BasicModule * tmpModule = mvmu_ModuleMap[if_id];

	if( 2004 != tmpModule->getModuleType() ) //����forģ�飬����
		return false;

	/// type һ����2004
	logic_IfModule *tmpIfModule = (logic_IfModule *)tmpModule; //ǿ��ת����for module

	int content = tmpIfModule->getBranchContentInt(branch_id); //����С��0

	return content;
}

//string
std::string logic_Program::getIfBranchContentStr(int if_id,int branch_id) {

	if( mvmu_ModuleMap.count(if_id) == 0 )
		return NULL;

	logic_BasicModule * tmpModule = mvmu_ModuleMap[if_id];

	if( 2004 != tmpModule->getModuleType() ) //����forģ�飬����
		return NULL;

	/// type һ����2004
	logic_IfModule *tmpIfModule = (logic_IfModule *)tmpModule; //ǿ��ת����for module

	std::string content = tmpIfModule->getBranchContentStr(branch_id);

	return content;
}